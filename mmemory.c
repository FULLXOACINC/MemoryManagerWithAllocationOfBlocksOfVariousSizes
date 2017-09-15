#include <stdio.h>
#include "mmemory.h"
#include "memory_area.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


VA m_start;
memory_area *area_array;

int array_size;

int __init (int n, int szPage)
{
    if (n <= 0 || szPage <= 0)
    {
        return INCORRECT_PARAMETERS_ERROR;
    }

    int init_size = szPage*n;

    m_start=(VA)malloc(init_size);

    area_array=(memory_area*) malloc(init_size*sizeof(memory_area));

    memory_area area;

    area.va=m_start;
    area.size=init_size;
    area.is_free=true;
    array_size=0;
    area_array[array_size]=area;

    return SUCCESSFUL_CODE;
}

int _malloc (VA* ptr, size_t szBlock)
{
    bool area_is_find=false;
    for(int i=0; i<=array_size; i++)
    {
        if(area_array[i].size>=szBlock && area_array[i].is_free)
        {
            int free_size=area_array[i].size-szBlock;

            memory_area area;
            area.va=area_array[i].va;
            *ptr=area.va;

            area.size=szBlock;
            area.is_free=false;
            area_array[i]=area;

            if(free_size){
                add_free_area_to_array_area(i,free_size);

            }


            area_is_find=true;

            break;

        }
    }
    if(!area_is_find)
        return NOT_ENOUGH_MEMORY_ERROR;
    return SUCCESSFUL_CODE;
}

void add_free_area_to_array_area (int i,int free_area_size)
{

    memory_area free_area;
    free_area.va=area_array[i].va+area_array[i].size;
    free_area.size=free_area_size;
    free_area.is_free=true;

    for (int c = array_size; c >= i; c--)
        area_array[c+1] = area_array[c];

    area_array[i+1] = free_area;
    array_size++;

}

int _free (VA ptr)
{
    bool area_is_find=false;

    for(int i=0; i<=array_size; i++)
    {

        if(area_array[i].va==ptr && !area_array[i].is_free)
        {
            area_array[i].is_free=true;


            if(area_array[i-1].is_free && i>0)
                {
                    area_array[i-1].size+=area_array[i].size;
                    combine_free_area_in_array_area(i);
                    if(area_array[i].is_free)
                        {
                            area_array[i-1].size+=area_array[i].size;
                            combine_free_area_in_array_area(i);
                        }
                }
            else
                if(area_array[i+1].is_free)
                {
                    area_array[i].size+=area_array[i+1].size;
                    combine_free_area_in_array_area(i+1);
                }

            area_is_find=true;
            break;

        }
    }

    if(!area_is_find)
        return INCORRECT_PARAMETERS_ERROR;

    return SUCCESSFUL_CODE;

}

int _write (VA ptr, void* pBuffer, size_t szBuffer)
{
    memcpy(ptr,pBuffer,szBuffer);
    return 0;
}

int _read (VA ptr, void* pBuffer, size_t szBuffer)
{
    memcpy(pBuffer,ptr,szBuffer);
    return 0;
}

void combine_free_area_in_array_area(int i)
{
    for(int c = i; c <= array_size ; c++)
        area_array[c] = area_array[c + 1];
    array_size--;
}

void print_array()
{
    for (int c = 0; c <= array_size; c++)
       printf("%i \n", area_array[c].size);
}
