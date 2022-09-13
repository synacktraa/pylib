#include <stdio.h>
#include <string.h>

#include "../src/safe.h"

int main(void)
{
	char str1[] = "c is a GENERAL LANGUAGE, 123";
	printf("%s\n",capitalize(str1));
	return 0;
}

// Output: { "C is a general-purpose language"}
