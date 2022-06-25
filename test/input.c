#include <stdio.h>

#include "../src/safe.h"

int main(void) {

    char* message = input("Prompt: ");
    puts(message);
    return 0;
}