#include "terminal_text_color.h"

#if ! (defined(WIN32) || defined(_WIN32))
#include <stdio.h>

static int terminal_text_color_code_to_actual_color_code(terminal_color_code_type color_code)
{
	const int code_offset = 29;
	int code = 0;
	switch (color_code) {
	/* fall through intended */
	case terminal_color_code_black:
	case terminal_color_code_red:
	case terminal_color_code_green:
	case terminal_color_code_yellow:
	case terminal_color_code_blue:
	case terminal_color_code_magenta:
	case terminal_color_code_cyan:
	case terminal_color_code_white:
		code = code_offset + (int) color_code;
		break;
	default:
		break;
	}
	return code;
}

static void POSIX_terminal_text_color_set(terminal_color_code_type text_color_code)
{
	const int color_code = terminal_text_color_code_to_actual_color_code(text_color_code);
	if (color_code != 0) {
		printf("\033[0;%dm", color_code);
	} else {
		printf("\033[0m");
	}
}

#else

#include "Boolean_type.h"
#include <Windows.h>

#define TEXT_COLOR_FLAGS (FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)

typedef enum Windows_text_color_type {
	Windows_text_color_black             = 0,
	Windows_text_color_dark_blue         = FOREGROUND_BLUE,
	Windows_text_color_dark_green        = FOREGROUND_GREEN,
	Windows_text_color_dark_cyan         = FOREGROUND_GREEN | FOREGROUND_BLUE,
	Windows_text_color_dark_red          = FOREGROUND_RED,
	Windows_text_color_dark_magenta      = FOREGROUND_RED | FOREGROUND_BLUE,
	Windows_text_color_dark_yellow       = FOREGROUND_RED | FOREGROUND_GREEN,
	Windows_text_color_dark_gray         = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	Windows_text_color_gray              = FOREGROUND_INTENSITY,
	Windows_text_color_blue              = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
	Windows_text_color_green             = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
	Windows_text_color_cyan              = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
	Windows_text_color_red               = FOREGROUND_INTENSITY | FOREGROUND_RED,
	Windows_text_color_magenta           = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
	Windows_text_color_yellow            = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
	Windows_text_color_white             = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
} Windows_text_color_type;

static Windows_text_color_type
terminal_text_color_code_to_Windows_console_text_color_code(terminal_color_code_type color_code)
{
	Windows_text_color_type code = Windows_text_color_white;
	switch (color_code) {
	case terminal_color_code_black:
		code = Windows_text_color_black;
		break;
	case terminal_color_code_red:
		code = Windows_text_color_red;
		break;
	case terminal_color_code_green:
		code = Windows_text_color_green;
		break;
	case terminal_color_code_yellow:
		code = Windows_text_color_yellow;
		break;
	case terminal_color_code_blue:
		code = Windows_text_color_blue;
		break;
	case terminal_color_code_magenta:
		code = Windows_text_color_magenta;
		break;
	case terminal_color_code_cyan:
		code = Windows_text_color_cyan;
		break;
	case terminal_color_code_white:
		break;
	default:
		break;
	}
	return code;
}

static void Windows_terminal_text_color_set(terminal_color_code_type text_color_code)
{
	static Boolean_type is_first_time = Boolean_true;
	static HANDLE hConsole = INVALID_HANDLE_VALUE;
	static WORD default_attributes = 0U;

	if (is_first_time) {
		CONSOLE_SCREEN_BUFFER_INFO consoleInfo = {0};
		is_first_time = Boolean_false;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
		default_attributes = consoleInfo.wAttributes;
	}

	if (text_color_code != terminal_color_code_default) {
		const Windows_text_color_type color_code = terminal_text_color_code_to_Windows_console_text_color_code(text_color_code);
		SetConsoleTextAttribute(hConsole, ((DWORD) default_attributes & ~TEXT_COLOR_FLAGS) | (WORD) color_code);
	} else {
		SetConsoleTextAttribute(hConsole, default_attributes);
	}
}
#endif

void terminal_text_color_set(terminal_color_code_type text_color_code)
{
#if !(defined(WIN32) || defined(_WIN32))
	POSIX_terminal_text_color_set(text_color_code);
#else
	Windows_terminal_text_color_set(text_color_code);
#endif
}
