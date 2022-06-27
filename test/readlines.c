#include <stdio.h>

#include "../src/safe.h"

void display(size_t cnt, char** list) {

    for(size_t i = 0; i < cnt; i++) {
        printf("%s", list[i]);
    }
}

int main(int argc, char** argv) {

    (void)argc;
    FILE* in = fopen(argv[1], "r");
    Crate instance = readlines(in, 10);
    display(instance.count, instance.vector);
    fclose(in);
    return 0;
}