#include <assert.h>
#include "mmemory.h"
#include "memory_area.h"
#include "write_tests.h"


void write_incorrect_parameters_error_test()
{
	__init(4,10);
	VA area;

	_malloc(&area,10);
    char *buffer = NULL;
    size_t buffer_size = 7;

    int err =_write(area, buffer, buffer_size);
    assert(err==-1);

}

void write_not_found_area_test()
{
	__init(4,10);
    VA area;

    _malloc(&area,15);

    char *buffer = "buffer";

    int err =_write(area+50, buffer, 10);
    assert(err==-1);
}

void write_out_of_range_error_test()
{
	__init(4,10);
    VA area;

    _malloc(&area,15);

    char *buffer = "buffer";

    int err =_write(area, buffer, 20);
    assert(err==-2);
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
	assert(err==0);

    buffer_size=7;
    err =_write(area1+3, buffer_end, buffer_size);
    assert(err==0);

}
void write_tests()
{
    write_incorrect_parameters_error_test();
    write_not_found_area_test();
    write_out_of_range_error_test();
    write_correct_test();
}
