# terminal_text_color

A simple C library for setting terminal text color.

## Overview

Provides a portable API to set the text color in supported terminals (e.g. Windows command prompt, xterm, Linux console, etc.).

## Features

- Easy-to-use function for changing text color.
- Supports standard colors: black, red, green, yellow, blue, magenta, cyan, white, and default color.

## Usage Example

```c
#include "terminal_text_color.h"

terminal_text_color_set(terminal_color_code_blue);
printf("This is blue text!\n");
terminal_text_color_set(terminal_color_code_default);
```

## Main Types

- `terminal_color_code_type`: Enum of supported terminal color codes.

## Key Function

- `terminal_text_color_set(code)`: Sets the text color for terminal output.

## Compatibility

- Works in C and C++ projects.
- Assumes POSIX terminals support ANSI escape codes.

## License

MIT License
