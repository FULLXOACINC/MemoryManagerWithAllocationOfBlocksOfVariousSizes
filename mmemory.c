#include <stdio.h>
#include "mmemory.h"
#include "memory_area.h"
#include <stdbool.h>
#include <stdlib.h>


VA m_start;
VA m_finish;
memory_area *area_array;
int area_array_size;
int index=0;


int _malloc (VA* ptr, size_t szBlock){
    if(index==0){
        memory_area area;
        area.va=&m_start[0];
        *ptr=area.va;
        area.size=szBlock;
        area.is_free=false;
        area_array[index]=area;
        index++;
    }
    else{
        for(int i=0;i<index;i++)
            if(area_array[i].size>szBlock && area_array[i].is_free)
                printf("d");
    }

    return SUCCESSFUL_CODE;
}


int __init (int n, int szPage){
    if (n <= 0 || szPage <= 0) {
        return INCORRECT_PARAMETERS_ERROR;
    }

    int init_size = szPage*n;

    m_start=(VA)malloc(init_size);

    m_finish=m_start+init_size;

    area_array_size=init_size>>5;

    area_array=(memory_area*) malloc(area_array_size*sizeof(memory_area));

    index=0;

    return SUCCESSFUL_CODE;
}


