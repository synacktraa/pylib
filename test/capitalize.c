#include <stdio.h>
#include <string.h>

#include "../src/safe.h"

int main(void)
{
	char str1[] = "c IS A genERAL-PurPosE LanGuage";
	printf("%s\n",capitalize(str1));
	return 0;
}

// Output: { "C Is A General-purpose language"}
