#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "mmemory.h"
#include "memory_area.h"
#include "defragmentation_tests.h"



int equal(size_t l, size_t r)
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

void free_incorrect_peremeters_error_test()
{
	__init(4,10);
	VA area=(VA)malloc(12);
    int err=_free(area);
    assert(equal(-1, err));

}

void free_previous_area_not_free_next_area_not_free()
{
	__init(4,10);
	VA area;
	VA area1;
	VA area2;
	_malloc(&area,10);
	_malloc(&area1,10);
	_malloc(&area2,10);
    int err=_free(area1);
    assert(equal(0, err));
    assert(equal(3, get_array_size()));
}

void free_previous_area_free_next_area_not_free()
{
	__init(4,10);
	VA area;
	VA area1;
	VA area2;

	_malloc(&area,10);
	_malloc(&area1,10);
	_malloc(&area2,10);

    int err=_free(area);
    assert(equal(0, err));
    err=_free(area1);
    assert(equal(0, err));


    assert(equal(2, get_array_size()));
}

void free_previous_area_not_free_next_area_free()
{
	__init(4,10);
	VA area;
	VA area1;
	VA area2;

	_malloc(&area,10);
	_malloc(&area1,10);
	_malloc(&area2,10);

    int err=_free(area2);
    assert(equal(0, err));


    assert(equal(2, get_array_size()));
}

void free_previous_area_free_next_area_free()
{
	__init(4,10);
	VA area;
	VA area1;
	VA area2;

	_malloc(&area,10);
	_malloc(&area1,10);
	_malloc(&area2,10);

    int err=_free(area2);
    assert(equal(0, err));

    err=_free(area1);
    assert(equal(0, err));

    assert(equal(1, get_array_size()));
}

void write_incorrect_parameters_error_test()
{
	__init(4,10);
	VA area;

	_malloc(&area,10);
    char *buffer = NULL;
    size_t buffer_size = 7;

    int err =_write(area, buffer, buffer_size);
    assert(equal(-1, err));

}

void write_not_found_area_test()
{
	__init(4,10);
    VA area;

    _malloc(&area,15);

    char *buffer = "buffer";

    int err =_write(area+50, buffer, 10);
    assert(equal(-1,err));
}

void write_out_of_range_error_test()
{
	__init(4,10);
    VA area;

    _malloc(&area,15);

    char *buffer = "buffer";

    int err =_write(area, buffer, 20);
    assert(equal(-2,err));
}

void write_correct_test()
{
    __init(4,10);
    VA area;
    VA area1;

    _malloc(&area,15);
    _malloc(&area1,15);

    char *buffer = "xxxbufferxxx";
    char *buffer_end = "buffer";

    size_t buffer_size = 13;
    int err =_write(area, buffer, buffer_size);
	assert(equal(0,err));

    buffer_size=7;
    err =_write(area1+3, buffer_end, buffer_size);
    assert(equal(0,err));

}

void read_incorrect_parameters_error_test()
{
	__init(4,10);
	VA area;

	_malloc(&area,10);
    char *buffer = NULL;
    size_t buffer_size = 7;

    int err =_read(area, buffer, buffer_size);
    assert(equal(-1, err));
}

void read_not_found_area_test()
{
	__init(4,10);
    VA area;

    _malloc(&area,15);

    char *buffer= "buffer";

    int err =_read(area+50, buffer, 10);
    assert(equal(-1,err));
}

void read_out_of_range_error_test()
{
	__init(4,10);
    VA area;

    _malloc(&area,15);

    char *buffer = "buffer";

    int err =_read(area, buffer, 20);
    assert(equal(-2,err));
}

void read_correct_test()
{
    __init(4,10);
    VA area;
    VA area1;
    VA temp_buffer;

    _malloc(&area,15);
    _malloc(&area1,15);

    char *buffer = "xxxbufferxxx";
    char *buffer_end = "buffer";

    size_t buffer_size = 13;
    _write(area, buffer, buffer_size);

    buffer_size=7;
    _write(area1, buffer_end, buffer_size);
    temp_buffer = (char *) malloc(sizeof(char) * buffer_size);
    int err=_read(area1, temp_buffer, buffer_size);
    assert(equal(0,err));

    err=_read(area+3, temp_buffer, 6);
    assert(equal(0,err));
    assert(memcmp(&buffer_end,&temp_buffer,6));

}

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
    malloc_exist_free_area();
    malloc_not_exist_free_area();
}

void free_tests()
{
    free_incorrect_peremeters_error_test();
    free_previous_area_not_free_next_area_not_free();
    free_previous_area_free_next_area_not_free();
    free_previous_area_not_free_next_area_free();
    free_previous_area_free_next_area_free();
}

void write_tests()
{
    write_incorrect_parameters_error_test();
    write_not_found_area_test();
    write_out_of_range_error_test();
    write_correct_test();
}

void read_tests()
{
    read_incorrect_parameters_error_test();
    read_not_found_area_test();
    read_out_of_range_error_test();
    read_correct_test();
}


int main() {

    init_tests();
    malloc_tests();
    free_tests();
    write_tests();
    read_tests();

    defragmentation_test(10);
    defragmentation_test_random(50);

    printf("tests complete \n");

    return 0;
}

