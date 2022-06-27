#include <stdio.h>

#include "../src/safe.h"

int main(int argc, char** argv) {

    (void)argc;
    FILE* in = fopen(argv[1], "r");
    puts(read(in, -1));
    fclose(in);
    return 0;
}
