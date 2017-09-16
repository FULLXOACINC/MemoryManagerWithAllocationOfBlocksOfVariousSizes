#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include "mmemory.h"

bool equal(size_t l, size_t r)
{
    return l == r;
}


void init_incorrect_peremeters_error_test()
{
    int err=__init(-4,-100);
    assert(equal(-1, err));

    err=__init(-4,100);
    assert(equal(-1, err));

    err=__init(4,0);
    assert(equal(-1, err));

}

void init_second_time_test()
{
    int err=__init(1,40);
    assert(equal(0, err));
    err=__init(1,40);
    assert(equal(0, err));
}

void init_correct_test()
{
    int err=__init(1,40);
    assert(equal(0, err));
}

void malloc_incorrect_peremeters_error_test()
{
	__init(4,10);
	VA area;

    int err=_malloc(&area,0);
	assert(equal(-1, err));
}

void malloc_not_enough_memory_error_test()
{
	__init(4,10);
	VA area;
	VA area1;
	_malloc(&area,10);
	_malloc(&area1,20);
	int err=_malloc(&area,20);
    assert(equal(-2, err));

}

void malloc_unknown_error_test()
{
	__init(4,10);
	VA area;
	free_array();
	int err=_malloc(&area,20);
    assert(equal(1, err));
}

void malloc_exist_free_area()
{
	__init(4,10);
	VA area;
	int err=_malloc(&area,20);
    assert(equal(0, err));
    assert(equal(1, get_array_size()));
}

void malloc_not_exist_free_area()
{
	__init(4,10);
	VA area;
	int err=_malloc(&area,40);
    assert(equal(0, err));
    assert(equal(0, get_array_size()));
}

void free_unknown_error_test()
{

}

void free_incorrect_peremeters_error_test()
{

}

void free_previous_area_not_free_next_area_not_free()
{

}

void free_incorrect_peremeters_error_test()
{

}
// void free_tests()
// {
//     VA area;
//     VA area1;
//     VA area2;
//     VA area3;

//     _malloc(&area ,10);
//     _malloc(&area1,10);
//     _malloc(&area2,10);


//     _free(area1);
//     _free(area2);


//     int err=_malloc(&area3,30);
//     assert(equal(0, err));

//     _free(area);
//     _free(area3);

// }
// void read_write_tests()
// {
//     VA area;
//     VA area1;
//     VA temp_buffer;

//     _malloc(&area,15);
//     _malloc(&area1,15);

//     char *buffer = "xxxbufferxxx";
//     char *buffer_end = "buffer";

//     size_t buffer_size = 13;
//     int err =_write(area, buffer, buffer_size);

//     err =_write(area1, buffer, 20);
//     assert(equal(-2,err));

//     err =_write(area+50, buffer, 20);
//     assert(equal(-1,err));

//     buffer_size=6;
//     temp_buffer = (char *) malloc(sizeof(char) * buffer_size);

//     err=_read(area+3, temp_buffer, buffer_size);

//     assert(equal(0,err));
//     assert(strcmp(&buffer_end,&temp_buffer));

//     _free(area);
//     _free(area1);

// }

void init_tests()
{
    init_incorrect_peremeters_error_test();
    init_second_time_test();
    init_correct_test();
}

void malloc_tests()
{
    malloc_incorrect_peremeters_error_test();
    malloc_not_enough_memory_error_test();
    malloc_unknown_error_test();
    malloc_exist_free_area();
    malloc_not_exist_free_area();
}

void free_tests()
{
    free_unknown_error_test();
    free_incorrect_peremeters_error_test();
    free_previous_area_not_free_next_area_not_free();
    free_previous_area_free_next_area_not_free();
    free_previous_area_not_free_next_area_free();
    free_previous_area_free_next_area_free();
}

void read_write_tests()
{
    // read_write_unknown_error_test();
    // read_write_incorrect_peremeters_error_test();
    // read_write_not_found_area_test();
    // read_write_out_of_range_error_test();
    // read_write_correct_test();
}

int main() {

    init_tests();
    malloc_tests();
    free_tests();
    read_write_tests();

    printf("tests complete \n");

    return 0;
}

