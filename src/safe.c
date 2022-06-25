/*
====================================================
|    safelib - safe data manupulating functions    |
|               Version: 1.2.1                     |      
====================================================

|https://github.com/synacktraa/safelib|

| MIT License
|
| Copyright (c) 2022 SynAcktraa
|
| Permission is hereby granted, free of charge, to any person obtaining a copy
| of this software and associated documentation files (the "Software"), to deal
| in the Software without restriction, including without limitation the rights
| to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
| copies of the Software, and to permit persons to whom the Software is
| furnished to do so, subject to the following conditions:
| 
| The above copyright notice and this permission notice shall be included in all
| copies or substantial portions of the Software.
| 
| THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
| IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
| FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
| AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
| LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
| OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
| SOFTWARE.

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "safe.h"

// allocations will store number of allocations
static size_t allocations = 0;

// vault will store all allocated memory 
static char** vault = NULL;

/*
 push(memloc) | a static function which pushes allocated 
 memory to vault which will be deallocated before 
 program exits
*/
static inline void push(void* memloc) {

    // Resize array so as to append char*
    char**temp = (char**)realloc(vault, sizeof(char*) * (allocations+1));
    if (temp == NULL) {
        free(memloc);
        return;
    }
    vault = temp;

    // Append char* to array
    vault[allocations++] = memloc;
}

/*
 dalloc() | a static function which free all the 
 allocated memory stored in vault
*/
static void dalloc(void) {

    if(vault != NULL) {

        for(size_t idx = 0; idx < allocations; ++idx) {
            free(vault[idx]);
        }
        free(vault);
    }

}

static inline void* allocate(size_t _Count, size_t _Size) {
    void* tmp = calloc(_Count, _Size);
    if(tmp == NULL) 
        exit(EXIT_FAILURE);
    return tmp;
}

static inline void* reallocate(void* _Buffer, size_t _Size) {
    void* tmp = realloc(_Buffer, _Size);
    if(tmp == NULL) 
        exit(EXIT_FAILURE);
    return tmp;
}

// -----extends vector size and allocates specified memory after extending---------------
static inline void create(size_t space, ret *instance) {

    instance->vector = (char**)reallocate(
        instance->vector, sizeof(char*)*(instance->count+1)
    );
    instance->vector[instance->count] = (char*)allocate(1, space+1);
    push(instance->vector[instance->count]);
}
// -----------------------------------------------------------------------------------------


/*
char* var = replace(_String, _Substring, _Substitute)
_______________________________________________________
replace() replaces all instances of _Substring from 
_String with _Substitute
*/
char* replace(char* _String, char* _Substring, char* _Substitute) {

    char* res = strdup(_String);
    char *ptr = _String;
    size_t _Sub_len = strlen(_Substitute), _Substr_len = strlen(_Substring);

    while ((ptr=strstr(ptr,_Substring))!=NULL) {
        
        size_t skip = strlen(res) - strlen(ptr), eval = strlen(ptr+_Substr_len);
        res = (char*)reallocate(res, skip+_Sub_len+eval+1);
        strcpy(res+skip, _Substitute);
        strncat(res, ptr+_Substr_len, eval);
        ptr++; 
    }
    push(res);
    return res;
}

/*
char* var = replace(_Vector, _VectorSize, _Separator)
_______________________________________________________
join() joins all elements of the _Vector separated
by string _Separator
*/
char* join(char** _Vector, size_t _VectorSize, char* _Separator){

    char* string = (char*)allocate(1, 1);
    size_t idx, seplen = strlen(_Separator);
    for(idx = 0; idx < _VectorSize; idx++) {

        size_t len = strlen(string), add = strlen(_Vector[idx]);
        string = (char*)reallocate(string, len+add+seplen+1);

        strncat(string, _Vector[idx], add);
        if(idx+1 != _VectorSize)
            strncat(string, _Separator, seplen);
    }
    push(string);
    return string;
}

/*
ret var = split(_String, _Delimeter);
_____________________________________
split() splits the _String with _Delimeter
and stores the elements in a vector
*/
ret split(char* _String, char* _Delimeter){

    if(!strcmp(_Delimeter, "")) {
        puts("ValueError: empty separator");
        exit(1);
    }

    ret instance = {
        .vector = NULL,
        .count = 0
    };

    char* duplicate = strdup(_String);
    char* ptr = _String, *prev;
    size_t  _Delim_len = strlen(_Delimeter);

    /*
        appends the string till the first occurence of delimeter
    */
    size_t size = 0;
    if((ptr = strstr(ptr, _Delimeter)) != NULL)
        size = strlen(ptr);
    
    size_t skip = strlen(duplicate) - size;
    create(skip, &instance);
    strncpy(instance.vector[instance.count++], duplicate, skip);
    free(duplicate);

    if(ptr == NULL)
        goto end;
    prev = ptr++;

    while ((ptr=strstr(ptr, _Delimeter))!=NULL) {

        size_t calc = (strlen(prev)-strlen(ptr))-_Delim_len;
        create(calc, &instance);
        strncpy(instance.vector[instance.count++], prev+_Delim_len, calc);
        prev = ptr++;
    }

    /*
        appends rest of the string
    */
    size_t rest = strlen(prev+_Delim_len);
    create(rest, &instance);
    strncpy(instance.vector[instance.count], prev+_Delim_len, rest);
    instance.count++;

    end:
        push(instance.vector);
        return instance;
}


/*
 char* var = readline(_Stream); 
 // stream can be stdin or a file pointer that has already been opened
 _____________________________________________________________________
 readline() reads char values from given stream until it detects LF
*/
char* readline(FILE* _Stream) {

    size_t space = 80, cursor = 0;
    char* buffer = (char*)allocate(1, space);

    int ch = EOF;
    while((ch = getc(_Stream)) != '\n' && ch != EOF) { 
        
        buffer[cursor++] = (char)ch;

        /* if cursor crosses current buffer space
            it's doubled in space and new space gets reallocated */
        if(cursor >= space - 1) { 
            space <<=1;
            buffer = (char*)reallocate(buffer, space);
        }
    }

    if(ch != EOF && _Stream != stdin)
        buffer[cursor++] = '\n';

    buffer[cursor] = '\0'; // null termination

    // Minimize buffer
    buffer = (char*)reallocate(buffer, strlen(buffer)+1);

    push(buffer);
    return buffer;
}


/*
 char* var = readline(_Stream); 
 // stream can be stdin or a file pointer that has already been opened
 _____________________________________________________________________
 readline() reads char values from given stream until it detects LF
*/
char* input(char* _Prompt) {

    printf("%s", _Prompt);
    return (readline(stdin));
}


/*
 char* var = read(_Stream, _Bytes); 
 ___________________________________________________________
 read() reads _Bytes no. of bytes from given stream, if 
 _Bytes is greater than the size of file, it reads until EOF
 To read whole file pass -1 in _Bytes argument.
*/
char* read(FILE* _Stream, size_t _Bytes) {

    fseek(_Stream, 0, SEEK_END);
    // get file size
    size_t t_Bytes = (size_t)ftell(_Stream);
    rewind(_Stream);

    if(t_Bytes < _Bytes || (long)_Bytes == -1)
        _Bytes = t_Bytes;

    void *data = allocate(1, _Bytes+1);
    fread(data, 1, _Bytes, _Stream);

    push(data);
    return (char*)data;
}


/*
 ret var = readlines(_Stream, _Count); 
 ___________________________________________________________________
 readlines() reads _Count no. of lines from the file and stores it
 in the array of strings and returns it, if _Count is greater than
 the no. of lines present in the file, it reads until EOF 
*/
ret readlines(FILE* _Stream, size_t _Count) {

    ret instance = {
        .vector = (char**)allocate(_Count, sizeof(char*)),
    };

    size_t lcnt = 0;
    while(lcnt < _Count && !feof(_Stream)) {
        instance.vector[lcnt++] = readline(_Stream);
    }
    instance.count = lcnt;

    push(instance.vector);
    return instance;
}


/*
For MSVC, this places a pointer to the function in the user initializer section (.CRT$XCU), 
basically the same thing the compiler does for the constructor calls for static C++ objects. 
For GCC, uses a constructor attribute.
check: https://stackoverflow.com/questions/1113409/attribute-constructor-equivalent-in-vc
*/
#if defined (_MSC_VER) // MSVC
    #pragma section(".CRT$XCU",read)
    #define INITIALIZER_(FUNC,PREFIX) \
        static void FUNC(void); \
        __declspec(allocate(".CRT$XCU")) void (*FUNC##_)(void) = FUNC; \
        __pragma(comment(linker,"/include:" PREFIX #FUNC "_")) \
        static void FUNC(void)
    #ifdef _WIN64
        #define INITIALIZER(FUNC) INITIALIZER_(FUNC,"")
    #else
        #define INITIALIZER(FUNC) INITIALIZER_(FUNC,"_")
    #endif
#else // defined (__GNUC__) // GCC, Clang, MinGW
    #define INITIALIZER(FUNC) \
        static void FUNC(void) __attribute__((constructor)); \
        static void FUNC(void)
#endif


// function to be called at program/library load time, before main executes
INITIALIZER(init)
{
    // Disable buffering for standard output
    setvbuf(stdout, NULL, _IONBF, 0);
    // run dalloc() function before exiting the program
    atexit(dalloc);
}
