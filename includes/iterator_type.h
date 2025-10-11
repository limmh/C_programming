#ifndef ITERATOR_TYPE_H
#define ITERATOR_TYPE_H

#include <assert.h>
#include <stddef.h>

/*
Usage example:

int main(void)
{
	enum { array_size = 5 };
	int array[array_size] = {1, 2, 3, 4, 5};
    iterator_type(int) it = iterator_init();
    iterator_type(int) begin = iterator_begin(array);
    iterator_type(int) end = iterator_end(begin, array_size);
    printf("Printing the numbers\n");
    foreach_iterator(it, begin, end) {
        printf("%d\n", iterator_deref(it));
    }
    iterator_reset(it);
    begin = iterator_reverse_begin(iterator_increment(begin, array_size - 1));
    end = iterator_reverse_end(begin, array_size);
    printf("Printing the numbers in reverse order\n");
    foreach_iterator_in_reverse(it, begin, end) {
        printf("%d\n", iterator_deref(it));
    }
	return 0;
}

*/

#define iterator_type(type_name) type_name *

#define iterator_init() NULL

#define iterator_deref(iterator) (*(iterator))

#define iterator_increment(iterator, offset) ((iterator) + (offset))

#define iterator_decrement(iterator, offset) ((iterator) - (offset))

#define iterator_begin(first_iterator) (first_iterator)

#define iterator_end(iterator, offset) iterator_increment(iterator, offset)

#define iterator_reverse_begin(last_iterator) (last_iterator)

#define iterator_reverse_end(iterator, offset) iterator_decrement(iterator, offset)

#define iterator_reset(iterator) ((iterator) = iterator_init())

#define foreach_iterator(iterator, first_iterator, one_past_last_iterator) \
	assert(first_iterator <= one_past_last_iterator); \
	for ((iterator) = (first_iterator); (iterator) != (one_past_last_iterator); (iterator) = iterator_increment(iterator, 1))

#define foreach_iterator_in_reverse(iterator, last_iterator, one_before_first_iterator) \
	assert(last_iterator >= one_before_first_iterator); \
	for ((iterator) = (last_iterator); (iterator) != (one_before_first_iterator); (iterator) = iterator_decrement(iterator, 1))

#endif
