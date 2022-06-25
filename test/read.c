#include <stdio.h>

#include "../src/safe.h"

int main(int argc, char** argv) {

    FILE* in = fopen(argv[1], "r");
    puts(read(in, -1));
    fclose(in);
    return 0;
}
