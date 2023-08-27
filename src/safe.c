


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
 dealloc() | a static function which free all the 
 allocated memory stored in vault
*/
static void dealloc(void) {

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
static inline void create(size_t space, cache_t *instance) {

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

    char* res = NULL, *ptr = _String;
    size_t _Sub_len = strlen(_Substitute), 
           _Substr_len = strlen(_Substring),
           _Length = strlen(_String);

    if(!strcmp(_Substring, "")){
        res = (char*)allocate(
            1, 
            _Length+ (_Length*_Sub_len) + 1
        );

        strcat(res, _Substitute);
        for(size_t idx = 0; idx < _Length; idx++) {
            strncat(res, _String+idx, 1);
            strcat(res, _Substitute);
        }
    }

    else{
        res = strdup(_String);
        while ((ptr=strstr(ptr,_Substring))!=NULL) {
            
            size_t skip = strlen(res) - strlen(ptr), eval = strlen(ptr+_Substr_len);
            res = (char*)reallocate(res, skip+_Sub_len+eval+1);
            strcpy(res+skip, _Substitute);
            strncat(res, ptr+_Substr_len, eval);
            ptr++; 
        }
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
    size_t idx, _Seplen = strlen(_Separator);
    for(idx = 0; idx < _VectorSize; idx++) {

        size_t _Length = strlen(string), _ElementSize = strlen(_Vector[idx]);
        string = (char*)reallocate(string, _Length + _ElementSize + _Seplen+1);

        strncat(string, _Vector[idx], _ElementSize);
        if(idx+1 != _VectorSize)
            strncat(string, _Separator, _Seplen);
    }
    push(string);
    return string;
}

/*
 * char* var = capitalize(_String)
 * ________________________________________________________________
 * capitalizes the first Character in  a string if it's an alphabet
 * then leaves turns all the other alphabets in the string to lower
 * case
 */
char* capitalize(char* _String)
{
	int i;
	for (i=0; _String[i] != '\0'; i++)
	{
		if (i==0)
		{
			if (_String[i] >= 'a' && _String[i] <= 'z')
			{
				_String[i] -= 32;
			}
			else
			{
				continue;
			}
		}
		else
		{
			if (_String[i] >= 'A' && _String[i] <= 'Z')
			{
				_String[i] += 32;
			}
			else
			{
				continue;
			}
		}
	}
	return _String;
}

/*
 * char* var = title(_String)
 * ________________________________________________________________
 * capitalizes the first letter of each word in the _String
 */
char* title(char* _String)
{
	int i,temp;

	temp = 0;

	for(i = 0; _String[i] != '\0'; i++)
	{
		if (_String[i] == ' ')
		{
			if (_String[i+1] >= 'a' && _String[i+1] <= 'z' )
			{
				_String[i+1] -= 32; 
			}
			else
			{
				continue;
			}
			temp = i+1;
		}
		else
		{
			if (i != temp)
			{
				if (_String[i] >= 'A' && _String[i] <= 'Z')
				{
					_String[i] += 32;
				}
				else
				{
					continue;
				}
			}
			else
			{
				continue;
			}
		}
	}

	return (_String);
}

/*
cache_t var = split(_String, _Delimiter);
_____________________________________
split() splits the _String with _Delimiter
and stores the elements in a vector
*/
cache_t* split(char* _String, char* _Delimiter){

    if(!strcmp(_Delimiter, "")) {
        puts("ValueError: empty separator");
        exit(1);
    }

    cache_t *instance = (cache_t*)allocate(1, sizeof(cache_t));
    push(instance);
    instance->vector = NULL;
    instance->count = 0;

    char* duplicate = strdup(_String);
    char* ptr = _String, *prev;
    size_t  _Delim_len = strlen(_Delimiter);

    /*
        appends the string till the first occurence of delimiter
    */
    size_t size = 0;
    if((ptr = strstr(ptr, _Delimiter)) != NULL){
        size = strlen(ptr);
        prev = ptr++;
    }    
    size_t quantify = strlen(duplicate) - size;
    create(quantify, instance);
    strncpy(
        instance->vector[instance->count++],
        duplicate, 
        quantify
    );
    free(duplicate);

    if(ptr == NULL)
        goto end;

    while ((ptr=strstr(ptr, _Delimiter))!=NULL) {

        quantify = (strlen(prev)-strlen(ptr))-_Delim_len;
        create(quantify, instance);
        strncpy(
            instance->vector[instance->count++],
            prev+_Delim_len, 
            quantify
        );
        prev = ptr++;
    }

    /*
        appends rest of the string
    */
    quantify = strlen(prev+_Delim_len);
    create(quantify, instance);
    strncpy(
        instance->vector[instance->count++], 
        prev+_Delim_len, 
        quantify
    );

    end:
        push(instance->vector);
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
    buffer = (char*)reallocate(
        buffer, 
        strlen(buffer)+1
    );

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
char* read(FILE* _Stream, long _Bytes) {

    fseek(_Stream, 0, SEEK_END);
    // get file size
    long t_Bytes = ftell(_Stream);
    rewind(_Stream);

    if(t_Bytes < _Bytes || _Bytes == -1)
        _Bytes = t_Bytes;

    void *data = allocate(1, _Bytes+1);
    fread(data, 1, (size_t)_Bytes, _Stream);

    push(data);
    return (char*)data;
}


/*
 cache_t var = readlines(_Stream, _Count); 
 ___________________________________________________________________
 readlines() reads _Count no. of lines from the file and stores it
 in the array of strings and returns it, if _Count is greater than
 the no. of lines present in the file, it reads until EOF 
  To read whole file pass -1 in _Count argument.
*/
cache_t* readlines(FILE* _Stream, int _Count) {

    cache_t *instance = (cache_t*)allocate(1, sizeof(cache_t));
    push(instance);
    instance->vector = NULL;

    int lcnt = 0;
    if(_Count == -1) {
        while(!feof(_Stream)){
            instance->vector = (char**)reallocate(
                instance->vector, 
                sizeof(char*)*(lcnt+1)
            );
            instance->vector[lcnt++] = readline(_Stream);
        }
    } else {
        while(lcnt < _Count && !feof(_Stream)) {
            instance->vector = (char**)reallocate(
                instance->vector, 
                sizeof(char*)*(lcnt+1)
            );
            instance->vector[lcnt++] = readline(_Stream);
        }
    }

    instance->count = (size_t)lcnt;

    push(instance->vector);
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
    // run dealloc() function before exiting the program
    atexit(dealloc);
}
