# C_programming

## Overview

This repository contains a collection of portable C application programming interfaces (APIs) and sample programs.

## Features

- **Header files implementing new C features for C89 and C99**  
  A Boolean type for C89, static_assert and alignof for C89 and C99, string references, etc.
- **Dynamic arrays**  
  A dynamic array API which supports per-instance custom allocator, common dynamic array operations and debugging.  
  Macros are used for dynamic array operations.
- **Fat pointers**  
  A fat pointer API which supports runtime bounds checking and error reporting.
- **Safer integer arithmetic**  
  Safer integer arithmetic C API for runtime integer operation error debugging and reporting.  
  Safer integer types for emulation of built-in integers and for debugging and reporting integer operation and conversion errors (requires C++)
- **Simple tokenizer**  
  A tokenizer library for splitting text into simple tokens.
- **Terminal text color**  
  A library for configuring the color of text on the terminal.
- **Unit testing**  
  A lightweight and simple unit testing library for C or C++ code.  
  Suitable for testing pure functions and black box interfaces.
- **Reference type emulation**  
  An experiment to demonstrate the interoperability between C pointers and C++ references.  
  References are emulated in C code using preprocessor macros.  
  Avoid using this in production code.
- **Sample programs**  
  Small programs demonstrating the use of the APIs.

## Getting Started

1. Clone the repository.
2. Make sure a recent version of CMake is installed.
3. In the local repository folder, create a new folder, e.g. build.
4. Use CMake to generate the build files for your target platform in the new folder you created.
5. Run the generated build to compile all libraries and programs.
