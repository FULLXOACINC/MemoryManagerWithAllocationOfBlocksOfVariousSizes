#include "memory_area.h"
#include <stdlib.h>

int get_array_size()
{
    return array_size;
}

int count_free_area()
{
    int count=0;
    for(int i=0; i<=array_size; i++)
        if(area_array[i].is_free)
        {
            count+=area_array[i].size;
        }

    return count;
}

int max_free_area()
{
    int max=0;

    for(int i=0; i<=array_size; i++)
        if(area_array[i].size>max && area_array[i].is_free)
        {

            max=area_array[i].size;
        }

    return max;
}

