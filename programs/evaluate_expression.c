#include "dynamic_array.h"
#include "simple_tokenizer.h"
#include "safer_fixed_width_integers.h"

#include <assert.h>
#include <iso646.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum expression_token_type_enum
{
	expression_token_unknown = 0,
	expression_token_identifier,
	expression_token_integer,
	expression_token_decimal_number,
	expression_token_operator_addition,
	expression_token_operator_subtraction,
	expression_token_operator_multiplication,
	expression_token_operator_division,
	expression_token_operator_assignment,
	expression_token_operator_dot,
	expression_token_left_parenthesis,
	expression_token_right_parenthesis,
	expression_token_can_be_ignored,
	expression_token_unsupported
} expression_token_type_enum;

typedef struct expression_token_type
{
	const_stringref_type value;
	expression_token_type_enum type;
} expression_token_type;

static const char *get_expression_token_type_name(expression_token_type_enum type)
{
	switch (type) {
	case expression_token_unknown:
		return "unknown token type";
	case expression_token_identifier:
		return "identifier";
	case expression_token_integer:
		return "integer";
	case expression_token_decimal_number:
		return "decimal number";
	case expression_token_operator_addition:
		return "addition operator";
	case expression_token_operator_subtraction:
		return "subtraction operator";
	case expression_token_operator_multiplication:
		return "multiplication operator";
	case expression_token_operator_division:
		return "division operator";
	case expression_token_operator_assignment:
		return "assignment operator";
	case expression_token_operator_dot:
		return "dot operator";
	case expression_token_left_parenthesis:
		return "left parenthesis";
	case expression_token_right_parenthesis:
		return "right parenthesis";
	case expression_token_can_be_ignored:
		return "token that can be ignored";
	default:
		return "unsupported token";
	}
}

static void print_token_value(FILE *fp, expression_token_type token)
{
	assert(fp != NULL);
	for (size_t i = 0U; i < token.value.length; ++i) {
		fputc(token.value.string[i], fp);
	}
}

static void print_list_of_tokens(FILE *fp, const expression_token_type *ptokens, size_t token_count)
{
	assert(fp != NULL);
	assert(ptokens != NULL);
	for (size_t i = 0U; i < token_count; ++i) {
		const expression_token_type token = ptokens[i];
		fprintf(fp, "Token %llu: ", (unsigned long long) (i + 1U));
		print_token_value(fp, token);
		const char *token_type_name = get_expression_token_type_name(token.type);
		fprintf(fp, " (%s)\n", token_type_name);
	}
}

static expression_token_type_enum
simple_tokenizer_token_type_to_expression_token_type(simple_tokenizer_token_type simple_tokenizer_token)
{
	expression_token_type_enum new_token_type = expression_token_unknown;
	switch (simple_tokenizer_token.type) {
	case simple_tokenizer_token_letters:
	case simple_tokenizer_token_utf8_character:
		new_token_type = expression_token_identifier;
		break;
	case simple_tokenizer_token_digits:
		new_token_type = expression_token_integer;
		break;
	case simple_tokenizer_token_punctuation:
		if (1U == simple_tokenizer_token.value.length) {
			const char operator = simple_tokenizer_token.value.string[0];
			if      (operator == '+')
				new_token_type = expression_token_operator_addition;
			else if (operator == '-')
				new_token_type = expression_token_operator_subtraction;
			else if (operator == '*')
				new_token_type = expression_token_operator_multiplication;
			else if (operator == '/')
				new_token_type = expression_token_operator_division;
			else if (operator == '=')
				new_token_type = expression_token_operator_assignment;
			else if (operator == '.')
				new_token_type = expression_token_operator_dot;
			else if (operator == '(')
				new_token_type = expression_token_left_parenthesis;
			else if (operator == ')')
				new_token_type = expression_token_right_parenthesis;
			else if (operator == '_')
				new_token_type = expression_token_identifier;
			else
				new_token_type = expression_token_unsupported;
		} else {
			new_token_type = expression_token_unsupported;
		}
		break;
	case simple_tokenizer_token_spaces:
	case simple_tokenizer_token_newline:
		new_token_type = expression_token_can_be_ignored;
		break;
	default:
		new_token_type = expression_token_unsupported;
		break;
	}
	return new_token_type;
}

static dynamic_array_type(expression_token_type)
simple_tokenizer_tokens_to_expression_tokens(const simple_tokenizer_token_type *p_input_tokens, size_t input_token_count)
{
	dynamic_array_type(expression_token_type) tokens = dynamic_array_create(expression_token_type, 0U);
	expression_token_type token = {.value = {.string = NULL, .length = 0U}, .type = expression_token_unknown};

	for (size_t index = 0U; index < input_token_count; ++index) {
		bool add_token = false;
		const simple_tokenizer_token_type simple_token = p_input_tokens[index];
		expression_token_type_enum new_token_type = simple_tokenizer_token_type_to_expression_token_type(simple_token);

		switch (token.type) {
		case expression_token_unknown:
			token.type = new_token_type;
			token.value = simple_token.value;
			break;
		case expression_token_identifier:
			if (new_token_type == token.type or new_token_type == expression_token_integer) {
				assert((token.value.string + token.value.length) == simple_token.value.string);
				token.value.length += simple_token.value.length;
			} else {
				add_token = true;
			}
			break;
		case expression_token_integer:
			if (new_token_type == expression_token_operator_dot) {
				assert((token.value.string + token.value.length) == simple_token.value.string);
				token.value.length += simple_token.value.length;
				token.type = expression_token_decimal_number;
			} else {
				add_token = true;
			}
			break;
		case expression_token_decimal_number:
			if (new_token_type == expression_token_integer) {
				assert(token.value.length > 0U);
				const char last_char = token.value.string[token.value.length - 1U];
				if (last_char == '.') {
					assert((token.value.string + token.value.length) == simple_token.value.string);
					token.value.length += simple_token.value.length;
				} else {
					add_token = true;
				}
			} else {
				add_token = true;
			}
			break;
		case expression_token_operator_addition:
		case expression_token_operator_subtraction: // fall through intended
			if (new_token_type == expression_token_integer) {
				assert((token.value.string + token.value.length) == simple_token.value.string);
				token.value.length += simple_token.value.length;
				token.type = expression_token_integer;
			} else if (new_token_type == expression_token_operator_dot) {
				if ((index + 1U) < input_token_count) {
					const simple_tokenizer_token_type next_input_token = p_input_tokens[index + 1];
					const expression_token_type_enum next_token_type = simple_tokenizer_token_type_to_expression_token_type(next_input_token);
					if (next_token_type == expression_token_integer) {
						assert((token.value.string + token.value.length) == simple_token.value.string);
						assert((simple_token.value.string + simple_token.value.length) == next_input_token.value.string);
						token.value.length += simple_token.value.length;
						token.value.length += next_input_token.value.length;
						token.type = expression_token_decimal_number;
						++index; // intended
					} else {
						add_token = true;
					}
				}
			} else {
				add_token = true;
			}
			break;
		case expression_token_operator_dot:
			if (new_token_type == expression_token_integer) {
				assert((token.value.string + token.value.length) == simple_token.value.string);
				token.value.length += simple_token.value.length;
				token.type = expression_token_decimal_number;
			} else {
				add_token = true;
			}
			break;
		default:
			add_token = true;
			break;
		}

		if (add_token) {
			if (token.type != expression_token_can_be_ignored) {
				dynamic_array_append_element(expression_token_type, tokens, token);
			}
			token.type = new_token_type;
			token.value = simple_token.value;
		}
	}

	if (input_token_count > 0U and token.type != expression_token_can_be_ignored) {
		dynamic_array_append_element(expression_token_type, tokens, token);
	}

	return tokens;
}

static dynamic_array_type(char)
generate_expression_string(const expression_token_type *ptokens, size_t token_count, const char *separator, size_t separator_length)
{
	assert(ptokens != NULL);
	dynamic_array_type(char) expression = dynamic_array_create(char, 0U);
	for (size_t i = 0U; i < token_count; ++i) {
		const expression_token_type token = ptokens[i];
		dynamic_array_append_elements(char, expression, token.value.string, token.value.length);
		if ((i + 1U) < token_count) {
			if (separator != NULL and separator_length > 0U) {
				dynamic_array_append_elements(char, expression, separator, separator_length);
			}
		}
	}
	dynamic_array_push_back(char, expression, '\0');
	return expression;
}

static bool report_expression_errors(FILE *fp, const expression_token_type *ptokens, size_t token_count)
{
	assert(fp != NULL);
	assert(ptokens != NULL);
	bool result = true;
	size_t number_of_unmatched_left_parentheses = 0U;
	size_t number_of_unmatched_right_parentheses = 0U;

	for (size_t i = 0U; i < token_count; ++i) {
		const expression_token_type token = ptokens[i];
		if (token.type == expression_token_operator_addition or
			token.type == expression_token_operator_subtraction or
			token.type == expression_token_operator_multiplication or
			token.type == expression_token_operator_division) {
			if (i == 0U) {
				result = false;
				fprintf(fp, "No operand (number) at the beginning.\n");
			} else if ((i + 1U) < token_count) {
				const expression_token_type next_token = ptokens[i + 1];
				if (next_token.type != expression_token_integer and
					next_token.type != expression_token_decimal_number and
					next_token.type != expression_token_left_parenthesis) {
					result = false;
					fprintf(fp, "No operand (number) between ");
					print_token_value(fp, token);
					fprintf(fp, " and ");
					print_token_value(fp, next_token);
					fprintf(fp, ".\n");
				}
			} else {
				result = false;
				fprintf(fp, "No operand (number) at the end.\n");
			}
		} else if (token.type == expression_token_integer or
				token.type == expression_token_decimal_number) {
			if ((i + 1U) < token_count) {
				const expression_token_type next_token = ptokens[i + 1];
				if ((next_token.type == expression_token_decimal_number or
					next_token.type == expression_token_integer) or
					next_token.type == expression_token_left_parenthesis) {
					result = false;
					fprintf(fp, "No operator (+, -, * or /) between ");
					print_token_value(fp, token);
					fprintf(fp, " and ");
					print_token_value(fp, next_token);
					fprintf(fp, ".\n");
				}
			}
		} else if (token.type == expression_token_left_parenthesis) {
			++number_of_unmatched_left_parentheses;
			if ((i + 1U) < token_count) {
				const expression_token_type next_token = ptokens[i + 1];
				if (next_token.type != expression_token_left_parenthesis and
					next_token.type != expression_token_integer and
					next_token.type != expression_token_decimal_number) {
					result = false;
					fprintf(fp, "No operand (number) between ");
					print_token_value(fp, token);
					fprintf(fp, " and ");
					print_token_value(fp, next_token);
					fprintf(fp, ".\n");
				}
			}
		} else if (token.type == expression_token_right_parenthesis) {
			if (number_of_unmatched_left_parentheses > 0U) {
				--number_of_unmatched_left_parentheses;
			} else {
				++number_of_unmatched_right_parentheses;
			}
			if ((i + 1U) < token_count) {
				const expression_token_type next_token = ptokens[i + 1];
				if (next_token.type != expression_token_right_parenthesis and
					next_token.type != expression_token_operator_addition and
					next_token.type != expression_token_operator_subtraction and
					next_token.type != expression_token_operator_multiplication and
					next_token.type != expression_token_operator_division) {
					result = false;
					fprintf(fp, "No operator (+, -, * or /) between ");
					print_token_value(fp, token);
					fprintf(fp, " and ");
					print_token_value(fp, next_token);
					fprintf(fp, ".\n");
				}
			}
		} else if (token.type == expression_token_identifier) {
			result = false;
			fprintf(fp, "Identifier \"");
			print_token_value(fp, token);
			fprintf(fp, "\" is undefined.\n");
		} else if (token.type == expression_token_operator_dot) {
			result = false;
			fprintf(fp, "The dot operator is not a valid operator on its own.\n");
		} else {
			result = false;
			fprintf(fp, "\"");
			print_token_value(fp, token);
			fprintf(fp, "\" is not supported.\n");
		}
	}

	if (number_of_unmatched_left_parentheses > 0U) {
		result = false;
		fprintf(fp, "%llu unmatched left %s found.\n", (unsigned long long) number_of_unmatched_left_parentheses,
			((number_of_unmatched_left_parentheses > 1U) ? "parentheses": "parenthesis") );
	}
	if (number_of_unmatched_right_parentheses > 0U) {
		result = false;
		fprintf(fp, "%llu unmatched right %s found.\n", (unsigned long long) number_of_unmatched_right_parentheses,
			((number_of_unmatched_right_parentheses > 1U) ? "parentheses": "parenthesis") );
	}
	return result;
}

static dynamic_array_type(expression_token_type)
generate_partially_corrected_expression_tokens(const expression_token_type *ptokens, size_t token_count)
{
	assert(ptokens != NULL);
	const char *read_only_zero = "0";
	const_stringref_type zero_stringref = {.string = read_only_zero, .length = 1U};
	const expression_token_type integer_zero_token = {.value = zero_stringref, .type = expression_token_integer};
	const char *read_only_plus = "+";
	const_stringref_type plus_stringref = {.string = read_only_plus, .length = 1U};
	const expression_token_type operator_plus_token = {.value = plus_stringref, .type = expression_token_operator_addition};
	dynamic_array_type(expression_token_type) tokens = dynamic_array_create(expression_token_type, 0U);

	for (size_t i = 0U; i < token_count; ++i) {
		bool add_plus_token = false;
		const expression_token_type token = ptokens[i];
		if (token.type == expression_token_operator_addition or
			token.type == expression_token_operator_subtraction) {
			if (i == 0U) {
				dynamic_array_push_back(expression_token_type, tokens, integer_zero_token);
			} else {
				const expression_token_type previous_token = ptokens[i - 1];
				if (previous_token.type == expression_token_left_parenthesis) {
					dynamic_array_push_back(expression_token_type, tokens, integer_zero_token);
				}
			}
		} else if (token.type == expression_token_integer or
				token.type == expression_token_decimal_number or
				token.type == expression_token_right_parenthesis) {
			if ((i + 1U) < token_count) {
				const expression_token_type next_token = ptokens[i + 1];
				if ( (next_token.type == expression_token_integer or
					next_token.type == expression_token_decimal_number) and
					next_token.value.length > 1U and
					(next_token.value.string[0] == '+' or next_token.value.string[0] == '-') ) {
						add_plus_token = true;
					}
			}
		}

		dynamic_array_push_back(expression_token_type, tokens, token);
		if (add_plus_token)
			dynamic_array_push_back(expression_token_type, tokens, operator_plus_token);
	}

	return tokens;
}

static int operator_precedence_level(char operator)
{
	int level = 0;
	switch (operator) {
	case '+':
	case '-': // fall through intended
		level = 1;
		break;
	case '*':
	case '/': // fall through intended
		level = 2;
		break;
	default:
		break;
	}
	return level;
}

static dynamic_array_type(expression_token_type)
infix_expression_tokens_to_postfix_expression_tokens(const expression_token_type *ptokens, size_t token_count)
{
	assert(ptokens != NULL);
	dynamic_array_type(expression_token_type) output_tokens = dynamic_array_create(expression_token_type, 0U);
	dynamic_array_type(expression_token_type) operator_tokens = dynamic_array_create(expression_token_type, 0U);

	for (size_t i = 0U; i < token_count; ++i) {
		const expression_token_type token = ptokens[i];
		switch (token.type) {
		case expression_token_integer:
		case expression_token_decimal_number:
			dynamic_array_push_back(expression_token_type, output_tokens, token);
			break;
		case expression_token_operator_addition:
		case expression_token_operator_subtraction:
		case expression_token_operator_multiplication:
		case expression_token_operator_division: // fall through intended
			{
				const char current_operator = token.value.string[0];
				const int current_op_precedence = operator_precedence_level(current_operator);
				while (dynamic_array_length(operator_tokens) > 0U) {
					const size_t last_index = dynamic_array_length(operator_tokens) - 1U;
					const char previous_operator =
						dynamic_array_element(expression_token_type, operator_tokens, last_index).value.string[0];
					const int previous_op_precedence = operator_precedence_level(previous_operator);
					if (previous_op_precedence >= current_op_precedence) {
						expression_token_type op_token = {0};
						dynamic_array_pop_back(expression_token_type, operator_tokens, op_token);
						dynamic_array_push_back(expression_token_type, output_tokens, op_token);
					} else {
						break;
					}
				}
				dynamic_array_push_back(expression_token_type, operator_tokens, token);
			}
			break;
		case expression_token_left_parenthesis:
			dynamic_array_push_back(expression_token_type, operator_tokens, token);
			break;
		case expression_token_right_parenthesis:
			while (dynamic_array_length(operator_tokens) > 0U) {
				expression_token_type op_token = {0};
				dynamic_array_pop_back(expression_token_type, operator_tokens, op_token);
				if (op_token.type != expression_token_left_parenthesis) {
					dynamic_array_push_back(expression_token_type, output_tokens, op_token);
				} else {
					break;
				}
			}
			break;
		default:
			break;
		}
	}

	while (dynamic_array_length(operator_tokens) > 0U) {
		expression_token_type op_token = {0};
		dynamic_array_pop_back(expression_token_type, operator_tokens, op_token);
		if (op_token.type == expression_token_operator_addition or
			op_token.type == expression_token_operator_subtraction or
			op_token.type == expression_token_operator_multiplication or
			op_token.type == expression_token_operator_division) {
			dynamic_array_push_back(expression_token_type, output_tokens, op_token);
		}
	}

	dynamic_array_delete(operator_tokens);
	return output_tokens;
}

typedef enum number_type_enum
{
	number_type_integer = 0,
	number_type_decimal_number
} number_type_enum;

typedef struct number_type
{
	union internal {
		int64_t integer;
		double decimal;
	} value;
	number_type_enum type;
} number_type;

typedef enum evaluation_result_error_type
{
	evaluation_result_error_none = 0,
	evaluation_result_error_integer_division_by_zero,
	evaluation_result_error_postfix_expression_incorrect
} evaluation_result_error_type;

typedef struct evaluation_result_type
{
	number_type number;
	evaluation_result_error_type error;
} evaluation_result_type;

static evaluation_result_type
evaluate_postfix_expression_tokens(const expression_token_type *ptokens, size_t token_count)
{
	assert(ptokens != NULL);
	evaluation_result_type result = {
		.number = {.value = {.integer = 0}, .type = number_type_integer},
		.error = evaluation_result_error_none
	};
	dynamic_array_type(number_type) numbers = dynamic_array_create(number_type, 0U);
	dynamic_array_type(char) number_string = dynamic_array_create(char, 0U);

	for (size_t i = 0U; i < token_count; ++i) {
		const expression_token_type token = ptokens[i];
		switch (token.type) {
		case expression_token_integer:
			{
				number_type number = {0};
				dynamic_array_resize(char, number_string, token.value.length);
				memcpy(&dynamic_array_element(char, number_string, 0U), token.value.string, token.value.length * sizeof(char));
				dynamic_array_push_back(char, number_string, '\0');
				number.value.integer = (int64_t) strtoll(&dynamic_array_element(char, number_string, 0U), NULL, 10);
				number.type = number_type_integer;
				dynamic_array_push_back(number_type, numbers, number);
			}
			break;
		case expression_token_decimal_number:
			{
				number_type number = {0};
				dynamic_array_resize(char, number_string, token.value.length);
				memcpy(&dynamic_array_element(char, number_string, 0U), token.value.string, token.value.length * sizeof(char));
				dynamic_array_push_back(char, number_string, '\0');
				number.value.decimal = strtod(&dynamic_array_element(char, number_string, 0U), NULL);
				number.type = number_type_decimal_number;
				dynamic_array_push_back(number_type, numbers, number);
			}
			break;
		case expression_token_operator_addition:
			if (dynamic_array_length(numbers) >= 2U) {
				number_type operand_2 = {0};
				dynamic_array_pop_back(number_type, numbers, operand_2);
				number_type operand_1 = {0};
				dynamic_array_pop_back(number_type, numbers, operand_1);
				number_type result_operand = {0};
				if (operand_1.type == number_type_decimal_number and
					operand_2.type == number_type_decimal_number) {
					result_operand.value.decimal = operand_1.value.decimal + operand_2.value.decimal;
					result_operand.type = number_type_decimal_number;
				} else if (operand_1.type == number_type_decimal_number and
					operand_2.type == number_type_integer) {
					result_operand.value.decimal = operand_1.value.decimal + (double)operand_2.value.integer;
					result_operand.type = number_type_decimal_number;
				} else if (operand_1.type == number_type_integer and
					operand_2.type == number_type_decimal_number) {
					result_operand.value.decimal = (double)operand_1.value.integer + operand_2.value.decimal;
					result_operand.type = number_type_decimal_number;
				} else {
					const i64_result_type i64_result = safer_i64_add(operand_1.value.integer, operand_2.value.integer);
					if (i64_result.error == integer_operation_error_none) {
						result_operand.value.integer = i64_result.value;
						result_operand.type = number_type_integer;
					} else {
						result_operand.value.decimal = (double)operand_1.value.integer + (double)operand_2.value.integer;
						result_operand.type = number_type_decimal_number;
					}
				}
				dynamic_array_push_back(number_type, numbers, result_operand);
			} else {
				result.error = evaluation_result_error_postfix_expression_incorrect;
			}
			break;
		case expression_token_operator_subtraction:
			if (dynamic_array_length(numbers) >= 2U) {
				number_type operand_2 = {0};
				dynamic_array_pop_back(number_type, numbers, operand_2);
				number_type operand_1 = {0};
				dynamic_array_pop_back(number_type, numbers, operand_1);
				number_type result_operand = {0};
				if (operand_1.type == number_type_decimal_number and
					operand_2.type == number_type_decimal_number) {
					result_operand.value.decimal = operand_1.value.decimal - operand_2.value.decimal;
					result_operand.type = number_type_decimal_number;
				} else if (operand_1.type == number_type_decimal_number and
					operand_2.type == number_type_integer) {
					result_operand.value.decimal = operand_1.value.decimal - (double)operand_2.value.integer;
					result_operand.type = number_type_decimal_number;
				} else if (operand_1.type == number_type_integer and
					operand_2.type == number_type_decimal_number) {
					result_operand.value.decimal = (double)operand_1.value.integer - operand_2.value.decimal;
					result_operand.type = number_type_decimal_number;
				} else {
					const i64_result_type i64_result = safer_i64_minus(operand_1.value.integer, operand_2.value.integer);
					if (i64_result.error == integer_operation_error_none) {
						result_operand.value.integer = i64_result.value;
						result_operand.type = number_type_integer;
					} else {
						result_operand.value.decimal = (double)operand_1.value.integer - (double)operand_2.value.integer;
						result_operand.type = number_type_decimal_number;
					}
				}
				dynamic_array_push_back(number_type, numbers, result_operand);
			} else {
				result.error = evaluation_result_error_postfix_expression_incorrect;
			}
			break;
		case expression_token_operator_multiplication:
			if (dynamic_array_length(numbers) >= 2U) {
				number_type operand_2 = {0};
				dynamic_array_pop_back(number_type, numbers, operand_2);
				number_type operand_1 = {0};
				dynamic_array_pop_back(number_type, numbers, operand_1);
				number_type result_operand = {0};
				if (operand_1.type == number_type_decimal_number and
					operand_2.type == number_type_decimal_number) {
					result_operand.value.decimal = operand_1.value.decimal * operand_2.value.decimal;
					result_operand.type = number_type_decimal_number;
				} else if (operand_1.type == number_type_decimal_number and
					operand_2.type == number_type_integer) {
					result_operand.value.decimal = operand_1.value.decimal * (double)operand_2.value.integer;
					result_operand.type = number_type_decimal_number;
				} else if (operand_1.type == number_type_integer and
					operand_2.type == number_type_decimal_number) {
					result_operand.value.decimal = (double)operand_1.value.integer * operand_2.value.decimal;
					result_operand.type = number_type_decimal_number;
				} else {
					const i64_result_type i64_result = safer_i64_multiply(operand_1.value.integer, operand_2.value.integer);
					if (i64_result.error == integer_operation_error_none) {
						result_operand.value.integer = i64_result.value;
						result_operand.type = number_type_integer;
					} else {
						result_operand.value.decimal = (double)operand_1.value.integer * (double)operand_2.value.integer;
						result_operand.type = number_type_decimal_number;
					}
				}
				dynamic_array_push_back(number_type, numbers, result_operand);
			} else {
				result.error = evaluation_result_error_postfix_expression_incorrect;
			}
			break;
		case expression_token_operator_division:
			if (dynamic_array_length(numbers) >= 2U) {
				number_type operand_2 = {0};
				dynamic_array_pop_back(number_type, numbers, operand_2);
				number_type operand_1 = {0};
				dynamic_array_pop_back(number_type, numbers, operand_1);
				number_type result_operand = {0};
				if (operand_1.type == number_type_decimal_number and
					operand_2.type == number_type_decimal_number) {
					result_operand.value.decimal = operand_1.value.decimal / operand_2.value.decimal;
					result_operand.type = number_type_decimal_number;
				} else if (operand_1.type == number_type_decimal_number and
					operand_2.type == number_type_integer) {
					result_operand.value.decimal = operand_1.value.decimal / (double)operand_2.value.integer;
					result_operand.type = number_type_decimal_number;
				} else if (operand_1.type == number_type_integer and
					operand_2.type == number_type_decimal_number) {
					result_operand.value.decimal = (double)operand_1.value.integer / operand_2.value.decimal;
					result_operand.type = number_type_decimal_number;
				} else {
					const i64_result_type i64_result = safer_i64_divide(operand_1.value.integer, operand_2.value.integer);
					if (i64_result.error == integer_operation_error_none) {
						result_operand.value.integer = i64_result.value;
						result_operand.type = number_type_integer;
					} else if (i64_result.error == integer_operation_error_division_of_signed_integer_by_zero) {
						result.error = evaluation_result_error_integer_division_by_zero;
					} else {
						result_operand.value.decimal = (double)operand_1.value.integer / (double)operand_2.value.integer;
						result_operand.type = number_type_decimal_number;
					}
				}
				dynamic_array_push_back(number_type, numbers, result_operand);
			} else {
				result.error = evaluation_result_error_postfix_expression_incorrect;
			}
			break;
		default:
			result.error = evaluation_result_error_postfix_expression_incorrect;
			break;
		}

		if (result.error != evaluation_result_error_none) {
			break;
		}
	}

	if (evaluation_result_error_none == result.error and dynamic_array_length(numbers) == 1U) {
		result.number  = dynamic_array_element(number_type, numbers, 0U);
	}

	dynamic_array_delete(number_string);
	dynamic_array_delete(numbers);
	return result;
}

const char *get_evaluation_result_error_text(evaluation_result_error_type error)
{
	switch (error) {
	case evaluation_result_error_none:
		return "";
	case evaluation_result_error_integer_division_by_zero:
		return "Integer division by zero";
	case evaluation_result_error_postfix_expression_incorrect:
		return "Incorrect expression";
	default:
		return "Unknown error";
	}
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		printf("Usage: %s <expression>\n", argv[0]);
		return 0;
	}

	dynamic_array_type(char)  expression = dynamic_array_create(char, 0U);
	const char *substring = argv[1];
	dynamic_array_append_elements(char, expression, substring, strlen(substring));
	for (int i = 2U; i < argc; ++i) {
		dynamic_array_append_element(char, expression, ' ');
		substring = argv[i];
		dynamic_array_append_elements(char, expression, substring, strlen(substring));
	}
	dynamic_array_push_back(char, expression, '\0');

	dynamic_array_type(simple_tokenizer_token_type)  simple_tokens =
		dynamic_array_create(simple_tokenizer_token_type, 0U);

	const size_t number_of_simple_tokens =
		simple_tokenizer_tokenize(
			&dynamic_array_element(char, expression, 0U),
			dynamic_array_length(expression) - 1U,
			NULL, 0U
		);

	dynamic_array_resize(
		simple_tokenizer_token_type,
		simple_tokens,
		number_of_simple_tokens
	);

	(void)
	simple_tokenizer_tokenize(
		&dynamic_array_element(char, expression, 0U),
		dynamic_array_length(expression),
		&dynamic_array_element(simple_tokenizer_token_type, simple_tokens, 0U),
		dynamic_array_length(simple_tokens)
	);

	dynamic_array_type(expression_token_type)  tokens =
		simple_tokenizer_tokens_to_expression_tokens(
			&dynamic_array_element(simple_tokenizer_token_type, simple_tokens, 0U),
			dynamic_array_length(simple_tokens)
		);

	FILE *fp = stdout;
	fprintf(fp, "Expression: %s\n", &dynamic_array_element(char, expression, 0U));
	print_list_of_tokens(
		fp,
		&dynamic_array_element(expression_token_type, tokens, 0U),
		dynamic_array_length(tokens)
	);

	dynamic_array_type(expression_token_type)  new_tokens =
		generate_partially_corrected_expression_tokens(
			&dynamic_array_element(expression_token_type, tokens, 0U),
			dynamic_array_length(tokens)
		);

	dynamic_array_type(char)  partially_corrected_expression =
		generate_expression_string(
			&dynamic_array_element(expression_token_type, new_tokens, 0U),
			dynamic_array_length(new_tokens),
			" ", 1U
		);

	fprintf(fp, "Partially corrected expression: %s\n",
		&dynamic_array_element(char, partially_corrected_expression, 0U));
	print_list_of_tokens(
		fp,
		&dynamic_array_element(expression_token_type, new_tokens, 0U),
		dynamic_array_length(new_tokens)
	);

	const bool expression_is_valid =
		report_expression_errors(
			fp,
			&dynamic_array_element(expression_token_type, new_tokens, 0U),
			dynamic_array_length(new_tokens)
		);

	if (expression_is_valid) {
		fprintf(fp, "No error found in the expression.\n");

		dynamic_array_type(expression_token_type) postfix_tokens =
			infix_expression_tokens_to_postfix_expression_tokens(
				&dynamic_array_element(expression_token_type, new_tokens, 0U),
				dynamic_array_length(new_tokens)
			);

		dynamic_array_type(char) postfix_expression =
			generate_expression_string(
				&dynamic_array_element(expression_token_type, postfix_tokens, 0U),
				dynamic_array_length(postfix_tokens),
				",", 1U
			);

		fprintf(fp, "Postfix expression: %s\n", &dynamic_array_element(char, postfix_expression, 0U));

		evaluation_result_type evaluation_result =
			evaluate_postfix_expression_tokens(
				&dynamic_array_element(expression_token_type, postfix_tokens, 0U),
				dynamic_array_length(postfix_tokens)
			);

		if (evaluation_result.error == evaluation_result_error_none) {
			number_type number = evaluation_result.number;
			if (number.type == number_type_decimal_number) {
				fprintf(fp,"Result: %g\n", number.value.decimal);
			} else {
				fprintf(fp, "Result: %lld\n", (long long)number.value.integer);
			}
		} else {
			fprintf(fp, "Error: %s\n", get_evaluation_result_error_text(evaluation_result.error));
		}

		dynamic_array_delete(postfix_expression);
		dynamic_array_delete(postfix_tokens);
	}

	dynamic_array_delete(partially_corrected_expression);
	dynamic_array_delete(new_tokens);
	dynamic_array_delete(tokens);
	dynamic_array_delete(simple_tokens);
	dynamic_array_delete(expression);
	return 0;
}
