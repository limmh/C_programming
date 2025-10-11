#ifndef REFERENCE_TYPE_EMULATION_H
#define REFERENCE_TYPE_EMULATION_H

/*
Emulates reference types in C

Unlike C++, C does not support reference types natively.
Both C and C++ support pointer types.

Example of a pointer (valid for both C and C++):
int a = 0, b = 0;
int *ptr_int = &a; // ptr_int now references variable a
++(*ptr_int);      // ptr_int is dereferenced, variable a is incremented by 1 => a == 1
ptr_int = &b;      // ptr_int now references variable b
--(*ptr_int);      // ptr_int is dereferenced, variable b is decremented by 1 => b == -1

Example of a reference (only for C++):
int a = 0, b = 0;
int &ref_int = a; // ref_int now references variable a
++ref_int;        // ref_int is implicitly dereferenced, variable a is incremented by 1 => a == 1
ref_int = b;      // ref_int is implicitly dereferenced, the value of variable b is assigned to variable a => a == 0
--ref_int;        // ref_int is implicitly dereferenced, variable a is decremented by 1 => a == -1, but b remains unchanged

Differences between pointers and references in C++
1. A pointer can be NULL or uninitialized or is assigned with a valid variable address or contains an address of variable whose lifetime has ended,
   but a reference must refer to a valid object or variable and cannot be NULL.
2. Pointers must be explicitly dereferenced to read or update the variables to which they reference.
   References are implicitly dereferenced without requiring pointer semantics.
3. Pointers can reassigned with the address of another variable if they are not declared as const, e.g. int * const ptr_int = &a.
   References can no longer reference other objects or variables once they are defined for the first time.
4. Pointers can remain uninitialized when they are declared, but references must be initialized to reference valid objects or variables.

Emulating references with limited pointer semantics in C
- A pointer can be declared as int * const ptr = &var; , where var is of type int and its address is assigned to ptr.
- Since ptr is a constant pointer to a variable of type T, once the address of an object is assigned to it, ptr cannot be changed.
- As a result, ptr always points to (or refers to) var.
- To access var through ptr, ptr has to be dereferenced explicitly using the dereferencing operator *, i.e. *ptr.
- For example, to increase var by 1, we can write this; (*ptr)++ or ++(*ptr).
- In C++, a reference to var is created by defining a variable of reference type as follows.
  int &ref = var; // ref is an alias of var, no pointer semantics
  ++ref;        // no explicit dereference, var will become 1.

Compare the two examples below.

Pointer semantics (C or C++)
int var = 0;
int * const ref = &var; // the address of var is assigned to ref
++(*ref);               // ref is dereferenced and var is incremented by 1

Reference semantics (only for C++)
int var = 0;   
int &ref = var; // ref is an alias of var
++ref;          // ref is implicitly dereferenced, var is incremented by 1

We can define the following macros to hide pointer sematics in C.
REF(reference)  : Declares a reference to an object or variable (used on the left hand side of a declaration)
REF_OF(object)   : Defines a reference of/to object (used in initialization of a reference, on the right hand side)
DEREF(reference): Dereferences the reference (used in expressions)

After that, we can write the following code.
int var = 0;
int REF(ref) = REF_OF(var); // ref emulates a reference in C and hides pointer semantics
++DEREF(ref);               // ref is dereferenced, so that var is incremented by 1

Here is a more complete example.

#include <stdio.h>

int main(void)
{
	int n = 0;
	int REF(ref_n) = REF_OF(n);
	printf("Before increment by 1: %d\n", DEREF(ref_n)); // explicit dereferencing is needed
	++DEREF(ref_n);
	printf("After increment by 1: %d\n", n);
	DEREF(ref_n) += DEREF(ref_n);
	printf("After increment by its previous value: %d\n", n);
	return 0; 
}

Notes:
- Reference-like variables are actually pointers in C code, but are references in C++ code.
- When using the macros in C code,
  - Explicit dereferencing of reference-like variables are still required using the DEREF macro.
  - DO NOT assign NULL to reference-like variables.
  - DO NOT leave reference-like variables uninitialized.
    Always assign REF_OF(<variable>) to every reference-like variable.
  - DO NOT perform pointer arithmetic on reference-like variables.
  - DO NOT take the addresses of reference-like variables.
    To take the address of the variable referenced by a reference-like variable.
    Write &DEREF(ref) to get the address of the variable that ref references.
- C code which use reference-like variables can be checked by compiling the code as C++ code, so that
  compiler checks on reference-like variables can be performed more accurately.
*/

#ifdef REF
#error "The REF macro has already been defined in another file. Please change the name of the REF macro in this file."
#endif

#ifdef REF_OF
#error "The REF_OF macro has already been defined in another file. Please change the name of the REF_OF macro in this file."
#endif

#ifdef DEREF
#error "The DEREF macro has already been defined in another file. Please change the name of the DEREF macro in this file."
#endif

#ifdef __cplusplus
#define REF(reference) (&(reference))
#define REF_OF(object) (object)
#define DEREF(reference) (reference)
#else
#define REF(reference) (* const (reference))
#define REF_OF(object) (&(object))
#define DEREF(reference) (*(reference))
#endif

#ifndef ref
#define ref(reference) REF(reference)
#else
#pragma message("The ref macro has already been defined in another file. It will not be redefined.")
#endif

#ifndef ref_of
#define ref_of(object) REF_OF(object)
#else
#pragma message("The ref_of macro has already been defined in another file. It will not be redefined.")
#endif

#ifndef deref
#define deref(reference) DEREF(reference)
#else
#pragma message("The deref macro has already been defined in another file. It will not be redefined.")
#endif

#endif
