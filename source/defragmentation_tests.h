#ifndef DEFRAGMENTATION_TESTS_H_INCLUDED
#define DEFRAGMENTATION_TESTS_H_INCLUDED
#include "mmemory.h"
#include "memory_area.h"
VA *array;
int size;

void  defragmentation_test(int block_size);

void  defragmentation_test_random(int block_size);

#endif // DEFRAGMENTATION_TESTS_H_INCLUDED
