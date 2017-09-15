#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include "mmemory.h"

bool equal(size_t l, size_t r)
{
    return l == r;
}

void init_tests()
{
    int err=__init(-4,-100);
    assert(equal(-1, err));

    err=__init(-4,100);
    assert(equal(-1, err));

    err=__init(4,0);
    assert(equal(-1, err));

    err=__init(4,10);
    assert(equal(0, err));

}
void malloc_tests()
{
    VA area;
    VA area1;
    VA area2;

    int err=_malloc(&area,1);
    assert(equal(0, err));

    err=_malloc(&area1,20);
    assert(equal(0, err));

    err=_malloc(&area2,20);
    assert(equal(-2, err));

    _free(area);
    _free(area1);
    _free(area2);

}
void free_tests()
{
    VA area;
    VA area1;
    VA area2;
    VA area3;

    _malloc(&area ,10);
    _malloc(&area1,10);
    _malloc(&area2,10);


    _free(area1);
    _free(area2);


    int err=_malloc(&area3,30);
    assert(equal(0, err));

    _free(area);
    _free(area3);

}
void read_write_tests()
{
    VA area;
    VA area1;

    _malloc(&area,15);
    _malloc(&area1,15);

    char *buffer = "xxxbufferxxx";
    char *buffer_end = "buffer";

    size_t buffer_size = 13;
    int err =_write(area, buffer, buffer_size);

    err =_write(area1, buffer, 20);
    assert(equal(-2,err));

    err =_write(area+50, buffer, 20);
    assert(equal(-1,err));

    buffer_size=6;
    VA temp_buffer = (char *) malloc(sizeof(char) * buffer_size);

    err=_read(area+3, temp_buffer, buffer_size);

    assert(equal(0,err));
    assert(strcmp(&buffer_end,&temp_buffer));

    _free(area);
    _free(area1);

}


int main() {

    init_tests();
    malloc_tests();
    free_tests();
    read_write_tests();

    printf("tests complete\n");

    return 0;
}

