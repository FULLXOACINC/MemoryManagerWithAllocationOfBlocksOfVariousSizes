#include <assert.h>
#include "mmemory.h"
#include "memory_area.h"
#include "malloc_tests.h"



void malloc_incorrect_peremeters_error_test()
{
	__init(4,10);
	VA area;

    int err=_malloc(&area,0);
	assert(err==-1);
}

void malloc_not_enough_memory_error_test()
{
	__init(4,10);
	VA area;
	VA area1;
	_malloc(&area,10);
	_malloc(&area1,20);
	int err=_malloc(&area,20);
    assert(err==-2);

}

void malloc_exist_free_area()
{
	__init(4,10);
	VA area;
	int err=_malloc(&area,20);
    assert(err==0);
    assert(get_array_size()==1);
}

void malloc_not_exist_free_area()
{
	__init(4,10);
	VA area;
	int err=_malloc(&area,40);
    assert(err==0);
    assert(get_array_size()==0);
}

void malloc_tests()
{
    malloc_incorrect_peremeters_error_test();
    malloc_not_enough_memory_error_test();
    malloc_exist_free_area();
    malloc_not_exist_free_area();
}
