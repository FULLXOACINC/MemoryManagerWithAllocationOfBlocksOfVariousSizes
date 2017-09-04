#ifndef MEMORY_AREA_H_INCLUDED
#define MEMORY_AREA_H_INCLUDED

#include "mmemory.h"
#include <stdbool.h>

#define SUCCESSFUL_CODE  0;
#define INCORRECT_PARAMETERS_ERROR -1;
#define NOT_ENOUGH_MEMORY_ERROR -2;
#define OUT_OF_RANGE_ERROR -2;
#define UNKNOWN_ERROR 1;
struct memory_area{
    struct memory_area *next_area;
    struct memory_area *prev_area;
    size_t size;
    size_t begin_address;
    bool is_free;
    };

struct memory_area * create_queue(size_t max_size);

void free_memory_area(struct memory_area *area);

int memory_area_push(struct memory_area *self,struct memory_area *new_area);

#endif // MEMORY_AREA_H_INCLUDED
