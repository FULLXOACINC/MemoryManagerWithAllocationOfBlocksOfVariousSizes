#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "mmemory.h"
#include "memory_area.h"
#include "free_tests.h"


void free_incorrect_peremeters_error_test()
{
	__init(4,10);
	VA area=(VA)malloc(12);
    int err=_free(area);
    assert(err==-1);

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
    assert(err==0);
    assert(get_array_size()==3);
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
    assert(err==0);
    err=_free(area1);
    assert(err==0);


    assert(get_array_size()==2);
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
    assert(err==0);


    assert(get_array_size()==2);
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
    assert(err==0);

    err=_free(area1);
    assert(err==0);

    assert(get_array_size()==1);
}
void free_tests()
{
    free_incorrect_peremeters_error_test();
    free_previous_area_not_free_next_area_not_free();
    free_previous_area_free_next_area_not_free();
    free_previous_area_not_free_next_area_free();
    free_previous_area_free_next_area_free();
}
