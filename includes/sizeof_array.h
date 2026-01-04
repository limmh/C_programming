#ifndef SIZEOF_ARRAY_H
#define SIZEOF_ARRAY_H

/*
SIZEOF_ARRAY(array) or sizeof_array(array):
Returns the number of elements in a fixed-size array.
WARNING: Only returns correct size values for true arrays, not pointers.
If you pass a pointer instead of an array in C, you will get incorrect results.
In C++, using sizeof_array(array) or SIZEOF_ARRAY(array) will result in a compile-time error if a pointer is passed to it.
 */

#ifndef __cplusplus

#define SIZEOF_ARRAY(ARRAY) ( sizeof(ARRAY) / sizeof((ARRAY)[0]) )
#define sizeof_array(array) SIZEOF_ARRAY(array)

#else

#include <cstddef>

template <typename T, std::size_t size>
inline std::size_t sizeof_array(const T (&)[size]) {
	return size;
}

#define SIZEOF_ARRAY(array) sizeof_array(array)

#endif

#endif
