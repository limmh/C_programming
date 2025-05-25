#ifndef TERMINAL_TEXT_COLOR_H
#define TERMINAL_TEXT_COLOR_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum terminal_color_code_type
{
	terminal_color_code_default = 0,
	terminal_color_code_black,
	terminal_color_code_red,
	terminal_color_code_green,
	terminal_color_code_yellow,
	terminal_color_code_blue,
	terminal_color_code_magenta,
	terminal_color_code_cyan,
	terminal_color_code_white
} terminal_color_code_type;

void terminal_text_color_set(terminal_color_code_type text_color_code);

#ifdef __cplusplus
}
#endif

#endif
