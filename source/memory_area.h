#ifndef MEMORY_AREA_INCLUDED
#define MEMORY_AREA_INCLUDED

#include "mmemory.h"
#include <stdbool.h>

#define SUCCESSFUL_CODE  0;
#define INCORRECT_PARAMETERS_ERROR -1;
#define NOT_ENOUGH_MEMORY_ERROR -2;
#define OUT_OF_RANGE_ERROR -2;
#define UNKNOWN_ERROR 1;

typedef struct {
VA va;
size_t size;
bool is_free;
} memory_area;


#endif // MEMORY_AREA_INCLUDED
