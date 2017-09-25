#include <assert.h>
#include "mmemory.h"
#include "init_tests.h"

void init_incorrect_peremeters_error_test()
{
    int err=__init(-4,-100);
    assert(err==-1);
}

void init_second_time_test()
{
    int err=__init(1,40);
    assert(err==0);
    err=__init(1,40);
    assert(err==0);
}

void init_correct_test()
{
    int err=__init(1,40);
    assert(err==0);
}

void init_tests()
{
    init_incorrect_peremeters_error_test();
    init_second_time_test();
    init_correct_test();
}
