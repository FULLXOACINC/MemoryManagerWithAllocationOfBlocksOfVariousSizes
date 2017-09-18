#include "mmemory.h"
#include "memory_area.h"
#include <stdlib.h>
#include <stdio.h>

VA *array;
int size;
void combine(int i)
{
    for(int c = i; c < size-1 ; c++)
        array[c] = array[c + 1];
    size--;
}

void  defragmentation_test()
{
    int err;
    size=40;
    __init(10,400);
    array=(VA*) malloc(size*sizeof(VA));

    for(int i=0;i<40;i++){
        err=_malloc(&array[i],10);
    }

    for(int i=0;i<40;i+=2){
        _free(array[i]);
        printf("%i %i %i\n",i/2,10,count_free_area());

    }

}

void  defragmentation_test_random()
{
    FILE *fp;

    fp = fopen("res.txt", "w+");

    int err;
    size=500;
    int current;
    __init(10,size);
    array=(VA*) malloc(size*sizeof(VA));

    for(int i=0;i<size;i++){
        err=_malloc(&array[i],10);
    }

    for(int i=0;i<500;i++){
        current=rand()%(size);
        _free(array[current]);
        //printf(" %i %i\n",max_free_area(),count_free_area());
        fprintf(fp, "%i %i\n",max_free_area(),count_free_area());
        combine(current);


    }
    fclose(fp);

}
