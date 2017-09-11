#include <stdio.h>
#include "mmemory.h"
#include "memory_area.h"
#include <stdbool.h>
#include <stdlib.h>


VA m_start;
VA m_finish;
memory_area *area_array;
int area_array_size;
int index;

int __init (int n, int szPage)
{
    if (n <= 0 || szPage <= 0)
    {
        return INCORRECT_PARAMETERS_ERROR;
    }

    int init_size = szPage*n;

    m_start=(VA)malloc(init_size);

    m_finish=m_start+init_size;

    area_array_size=init_size;

    area_array=(memory_area*) malloc(area_array_size*sizeof(memory_area));

    memory_area area;

    area.va=m_start;
    area.size=init_size;
    area.is_free=true;
    area_array[index]=area;
    index=0;

    return SUCCESSFUL_CODE;
}

int _malloc (VA* ptr, size_t szBlock)
{
    for(int i=0; i<=index; i++)
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

            index++;

            if(free_size)
            {
                //printf("GOOd  %i\n",free_size);
                add_free_area_to_array_area(i,free_size);


            }
            break;

        }
    }
    return SUCCESSFUL_CODE;
}

void add_free_area_to_array_area (int i,int free_area_size)
{

    memory_area free_area;
    free_area.va=area_array[i].va+area_array[i].size;
    free_area.size=free_area_size;
    free_area.is_free=true;

    for (int c = index; c >= i; c--)
        area_array[c+1] = area_array[c];

    area_array[i+1] = free_area;


}

int _free (VA ptr)
{
    for (int c = 0; c <= index; c++)
        printf("%i \n", area_array[c].size);

    for(int i=0; i<=index; i++)
    {
        if(area_array[i].va==ptr && !area_array[i].is_free)
        {
            area_array[i].is_free=true;


            if(area_array[i-1].is_free && i>0){
                area_array[i-1].size+=area_array[i].size;
                combine_free_area_in_array_area(i);
                if(area_array[i].is_free){
                area_array[i-1].size+=area_array[i].size;
                combine_free_area_in_array_area(i);
            }
            }
            if(area_array[i+1].is_free){
                area_array[i].size+=area_array[i+1].size;
                combine_free_area_in_array_area(i+1);
            }


            break;

        }
    }
    printf(" \n");
    for (int c = 0; c <= index; c++)
        printf("%i \n", area_array[c].size);

    printf(" \n");
    printf(" \n");
    printf(" \n");

    return SUCCESSFUL_CODE;

}

void combine_free_area_in_array_area(int i)
{
    for(int c = i; c <= index - 1; c++)
        area_array[c] = area_array[c + 1];
    index--;
}
