#ifndef SIZEOF_ARRAY_H
#define SIZEOF_ARRAY_H

#define SIZEOF_ARRAY(ARRAY) ( sizeof(ARRAY) / sizeof((ARRAY)[0]) )
#define sizeof_array(array) SIZEOF_ARRAY(array)

#endif
