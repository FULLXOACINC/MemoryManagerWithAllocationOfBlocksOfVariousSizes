#include "memory_area.h"
#include <stdlib.h>
#include <stdio.h>

struct memory_area * create_memory_area(size_t max_size) {
    struct memory_area *area = (struct memory_area *) malloc(sizeof(struct memory_area));

    area->size=max_size;
    area->begin_address=0;
    area->is_free=true;
    area->next_area=NULL;
    area->prev_area=NULL;

    return area;
}

void free_memory_area(struct memory_area *memory_area){
    if(memory_area->next_area!=NULL)
        free_memory_area(memory_area->next_area);
    printf("GOOD!\n");
    free(memory_area);
}

int memory_area_push(struct memory_area *self,struct memory_area *new_area){
    bool is_found=false;
    struct memory_area *correct= NULL;

    if(self->next_area==NULL && new_area->size<=self->size){
        is_found=true;
        correct=self;

    }
    else
        while(self->next_area!=NULL){
            if(self->size >= new_area->size && self->is_free ){
                correct=self;
                is_found=true;
            }
            self=self->next_area;
        }
    if(!is_found)
        return NOT_ENOUGH_MEMORY_ERROR;
    struct memory_area *next_area= correct->next_area;
    struct memory_area *prev_area= correct->prev_area;

    struct memory_area *free_area= create_memory_area(correct->size-new_area->size);

    if(prev_area!=NULL){
        prev_area->next_area=new_area;
    }

    if(next_area!=NULL){
        if(free_area->size>0)
            next_area->prev_area=free_area;
        else
            next_area->prev_area=new_area;
    }

    new_area->next_area=free_area;
    free_area->prev_area=new_area;

    free(correct);

///////////////////////
    struct memory_area *count=new_area;

    while(true){
        printf("%i \n",count->size);
        if(count->next_area!=NULL)
            count=count->next_area;
        else
            break;
    }
////////////////////////


    return SUCCESSFUL_CODE;
}
