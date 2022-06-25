#include <stdio.h>

#include "../src/safe.h"

int main(void) {

    char* list[3] = {"C ", " is a general-purpose programming ", ""};
    puts(join(list, 3, "language"));
    return 0;
}

// Output: C language is a general-purpose programming language