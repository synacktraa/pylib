# Safelib

> This is a C library which provides safe data reading and handling functions.

---
## Usage

### Replace

```c
#include <stdio.h>

#include "./src/safe.h"

int main(void) {

    char* str = "C language is a general-purpose programming language";
    puts(replace(str, "language", "LANG"));
    return 0;
}
// Output: C LANG is a general-purpose programming LANG

```

### Split

```c
#include <stdio.h>

#include "./src/safe.h"

void display(size_t cnt, char** list) {

    printf("{");
    for(size_t i = 0; i < cnt; i++) {
        printf(" \"%s\",", list[i]);
    }
    printf("\b }\n");
}

int main(void) {

    char* str = "C language is a general-purpose programming language";
    cache_t* instance = split(str, "language");
    display(instance->count, instance->vector);
    return 0;
}

// Output: { "C ", " is a general-purpose programming ", "" }
```

### Join

```c
#include <stdio.h>

#include "./src/safe.h"

int main(void) {

    char* list[3] = {"C ", " is a general-purpose programming ", ""};
    puts(join(list, 3, "language"));
    return 0;
}

// Output: C language is a general-purpose programming language
```

### Readline

```c
#include <stdio.h>

#include "./src/safe.h"

int main(void) {

    FILE* in = fopen("Makefile", "r");
    puts(readline(in));
    fclose(in);
    return 0;
}

```

### Readlines

```c
#include <stdio.h>

#include "./src/safe.h"

void display(size_t cnt, char** list) {

    for(size_t i = 0; i < cnt; i++) {
        printf("%s", list[i]);
    }
}

int main(void) {

    FILE* in = fopen("Makefile", "r");
    cache_t* instance = readlines(in, 1024);
    display(instance->count, instance->vector);
    fclose(in);
    return 0;
}
```

### Read

```c
#include <stdio.h>

#include "./src/safe.h"

int main(void) {

    FILE* in = fopen("Makefile", "r");
    FILE* ptr = fopen("License", "r");
    // if 2nd arg is -1, read function reads the whole file
    puts(read(in, -1)); 
    puts(read(ptr, 20)); // reads 20 bytes 
    fclose(in);
    fclose(ptr);
    return 0;
}

```

### Input

```c
#include <stdio.h>

#include "./src/safe.h"

int main(void) {

    char* message = input("Prompt: ");
    puts(message);
    return 0;
}
```

### Title

```c
#include <stdio.h>
#include "./src/safe.h"

int main(void) {
    
       char str1[] = "C is a general-purpose language, 123";
       printf("%s\n",title(str1));
       return 0;
    }

 ```

---
## **TODO**

- make this library into shared library

---
## **License**

### <a target="_blank" href="https://choosealicense.com/licenses/mit/">MIT</a>

Copyright for portions of project [safelib](https://github.com/SynAcktraa/safelib) are held by [Github Account [SynAcktraa](https://github.com/SynAcktraa) Owner, 2022] as part of project [safelib](https://github.com/SynAcktraa/safelib)

All other copyright for project [safelib](https://github.com/SynAcktraa/safelib) are held by [Github Account [SynAcktraa](https://github.com/SynAcktraa) Owner, 2022].

Check the [LICENSE](LICENSE) for more details.
