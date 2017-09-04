#include <stdio.h>
#include "mmemory.h"

int main() {
    __init(4,50);
    VA area;
    VA area1;

    _malloc(&area,10);
    _malloc(&area1,10);
    return 5;
}
