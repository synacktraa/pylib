#include <stdio.h>
#include <string.h>

#include "../src/safe.h"

int main(void)
{
	char str1[] = "C is a general-PANTHER language, 123";
	printf("%s\n",title(str1));
	return 0;
}

// Output: { "C Is A General-purpose language"}
