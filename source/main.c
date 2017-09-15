#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include "mmemory.h"

bool check_equal_collection(char *begin_l, char *end_l, char *begin_r, char *end_r)
{
    if (end_l - begin_l != end_r - begin_r) {
        return false;
    }
    bool is_equal = true;
    char *current_l, *current_r;
    for (current_l = begin_l, current_r = begin_r;
         current_l < end_l && current_r < end_r && is_equal; current_l++, current_r++) {
        is_equal &= *current_l == *current_r;
    }
    return is_equal;
}

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

    int err=_malloc(&area,10);
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

    err =_write(area+50, buffer, 20);

    assert(equal(-1,err));

    VA allocated_buffer = (char *) malloc(sizeof(char) * 6);

    _read(area+3, allocated_buffer, 6);

    assert(strcmp(&buffer_end,&allocated_buffer));


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

