#include <stdio.h>

#include "../src/safe.h"

void display(size_t cnt, char** list) {

    printf("{");
    for(size_t i = 0; i < cnt; i++) {
        printf(" \"%s\",", list[i]);
    }
    printf("\b }\n");
}

int main(void) {

    char* str = "C language is a general-purpose programming language";
    ret instance = split(str, "language");
    display(instance.count, instance.vector);
    return 0;
}

// Output: { "C ", " is a general-purpose programming ", "" }