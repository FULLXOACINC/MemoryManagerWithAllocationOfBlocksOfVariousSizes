#include <stdio.h>

#include "defragmentation_tests.h"
#include "init_tests.h"
#include "malloc_tests.h"
#include "free_tests.h"
#include "write_tests.h"
#include "read_tests.h"



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

