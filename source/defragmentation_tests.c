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

void  defragmentation_test(int block_size)
{
    FILE *fp;

    fp = fopen("res_static.txt", "w+");

    size=block_size;
    __init(10,size);
    array=(VA*) malloc(size*sizeof(VA));

    for(int i=0;i<size;i++){
        _malloc(&array[i],10);
    }

    for(int i=0;i<size;i+=2){
        _free(array[i]);
        fprintf(fp, "%i %i\n",max_free_area(),count_free_area());
    }

}

void  defragmentation_test_random(int block_size)
{
    FILE *fp;

    fp = fopen("res.txt", "w+");

    size=block_size;
    int temp_size=size;
    int current;

    __init(10,temp_size);
    array=(VA*) malloc(size*sizeof(VA));

    for(int i=0;i<temp_size;i++)
    {
        _malloc(&array[i],10);
    }

    for(int i=0;i<temp_size;i++)
    {
        current=rand()%(size);
        _free(array[current]);
        fprintf(fp, "%i %i\n",max_free_area(),count_free_area());
        combine(current);
    }
    fclose(fp);

}
