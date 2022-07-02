#include <stdio.h>

#include "../src/safe.h"


int main(void) {

    char* str = "C language is a general-purpose programming language";
    puts(replace(str, "", "h"));
    return 0;
}

// Output: C LANG is a general-purpose programming LANG