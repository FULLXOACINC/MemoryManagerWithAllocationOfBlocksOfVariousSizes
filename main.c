#include <stdio.h>
#include "mmemory.h"

int main() {
    __init(4,100);
    VA area;
    VA area1;
    VA area2;
    VA area3;
    VA area4;
    VA area5;

    _malloc(&area,10);
    _malloc(&area1,10);
    _malloc(&area2,10);
    _malloc(&area3,10);
    _malloc(&area4,10);
    _malloc(&area5,10);

    _free(area);
    _free(area1);
    _free(area2);
    _free(area3);
    _free(area4);
    _free(area5);
    return 5;
}
