#include <stdio.h>

#include "../src/safe.h"

void display(size_t cnt, char** list) {

    for(size_t i = 0; i < cnt; i++) {
        printf("%s", list[i]);
    }
}

int main(int argc, char** argv) {

    FILE* in = fopen(argv[1], "r");
    ret instance = readlines(in, 1024);
    display(instance.count, instance.vector);
    fclose(in);
    return 0;
}