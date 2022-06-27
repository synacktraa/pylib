#include <stdio.h>

#include "../src/safe.h"

int main(int argc, char** argv) {
    
    (void)argc;
    FILE* in = fopen(argv[1], "r");
    puts(readline(in));
    fclose(in);
    return 0;
}
