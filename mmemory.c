#include <stdio.h>
#include "mmemory.h"
#include "memory_area.h"
#include <stdbool.h>





struct memory_area *memory_area=NULL;

int _malloc (VA* ptr, size_t szBlock){
    return 0;
}


int __init (int n, int szPage){

    if (memory_area !=NULL ) {
        free_memory_area(memory_area);
    }
    if (n <= 0 || szPage <= 0) {
        return INCORRECT_PARAMETERS_ERROR;
    }

    memory_area=create_memory_area(n*szPage);

    struct memory_area *test=create_memory_area(10);

    memory_area_push(memory_area,test);

    struct memory_area *count=memory_area;

    /*while(true){
        printf("%i \n",count->size);
        if(count->next_area!=NULL)
            count=count->next_area;
        else
            break;
    }*/
    printf("%i \n",memory_area->size);


    return memory_area->size;
}


