#include "mmemory.h"
#include "memory_area.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>



memory_area *area_array;
VA m_start;

int array_size;

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
bool check_NULL_value(VA ptr, void* pBuffer)
{
    return pBuffer==NULL || ptr==NULL;
}

void combine_free_area_in_array_area(int i)
{
    for(int c = i; c <= array_size ; c++)
        area_array[c] = area_array[c + 1];
    array_size--;
}

int __init (int n, int szPage)
{
	if(area_array!=NULL || m_start!=NULL)
	{
		free(area_array);
		free(m_start);
	}


    if (n <= 0 || szPage <= 0)
        return INCORRECT_PARAMETERS_ERROR;

    int init_size = szPage*n;

    m_start=(VA)malloc(init_size);

    area_array=(memory_area*) malloc(init_size*sizeof(memory_area));

    if (area_array == NULL)
            return UNKNOWN_ERROR;

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


    if (szBlock == 0)
        return INCORRECT_PARAMETERS_ERROR;

    if(area_array == NULL)
        return UNKNOWN_ERROR;

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


int _free (VA ptr)
{
    if(area_array == NULL)
        return UNKNOWN_ERROR;

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

int read_write_error(VA ptr, void* pBuffer,size_t szBuffer)
{
    if(area_array == NULL)
        return UNKNOWN_ERROR;
    if(check_NULL_value(ptr,pBuffer) || szBuffer<=0)
        return INCORRECT_PARAMETERS_ERROR;

    bool is_va_find=false;
    for(int i=0; i<array_size; i++)
    {
        if(ptr>=area_array[i].va && ptr<area_array[i].va+area_array[i].size)
        {
            if(area_array[i].va+area_array[i].size-ptr<szBuffer)
                return OUT_OF_RANGE_ERROR;
            is_va_find=true;
        }


    }
    if(!is_va_find)
        return INCORRECT_PARAMETERS_ERROR;
    return SUCCESSFUL_CODE;
}

int _write (VA ptr, void* pBuffer, size_t szBuffer)
{
    switch(read_write_error(ptr,pBuffer,szBuffer)){
    case -1:
        return INCORRECT_PARAMETERS_ERROR;
    case -2:
        return OUT_OF_RANGE_ERROR;
    case 1:
        return UNKNOWN_ERROR;
    case 0:
        memcpy(ptr,pBuffer,szBuffer);
        return SUCCESSFUL_CODE;
    }

}

int _read (VA ptr, void* pBuffer, size_t szBuffer)
{
    switch(read_write_error(ptr,pBuffer,szBuffer)){
    case -1:
        return INCORRECT_PARAMETERS_ERROR;
    case -2:
        return OUT_OF_RANGE_ERROR;
    case 1:
        return UNKNOWN_ERROR;
    case 0:
        memcpy(pBuffer,ptr,szBuffer);
        return SUCCESSFUL_CODE;
    }

}









int get_array_size()
{
    return array_size;
}

void free_array()
{
    free(area_array);
    area_array=NULL;
}

int count_free_area()
{
    int count=0;
    for(int i=0; i<=array_size; i++)
        if(area_array[i].is_free)
        {
            //printf("%i\n",area_array[i].size);
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






