#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "mmemory.h"
#include "memory_area.h"

void read_incorrect_parameters_error_test()
{
	__init(4,10);
	VA area;

	_malloc(&area,10);
    char *buffer = NULL;
    size_t buffer_size = 7;

    int err =_read(area, buffer, buffer_size);
    assert(err==-1);
}

void read_not_found_area_test()
{
	__init(4,10);
    VA area;

    _malloc(&area,15);

    char *buffer= "buffer";

    int err =_read(area+50, buffer, 10);
    assert(err==-1);
}

void read_out_of_range_error_test()
{
	__init(4,10);
    VA area;

    _malloc(&area,15);

    char *buffer = "buffer";

    int err =_read(area, buffer, 20);
    assert(err==-2);
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
    assert(err==0);

    err=_read(area+3, temp_buffer, 6);
    assert(err==0);
    assert(memcmp(&buffer_end,&temp_buffer,6));

}
void read_tests()
{
    read_incorrect_parameters_error_test();
    read_not_found_area_test();
    read_out_of_range_error_test();
    read_correct_test();
}
