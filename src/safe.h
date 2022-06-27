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


#ifndef SAFELIB_H
#define SAFELIB_H

/*
struct to store vector and its size
*/
struct Crate {

    char** vector;
    size_t count;
};

/*
struct to store vector and its size
*/
typedef struct Crate Crate;

//========================================================

/*
char* var = replace(_String, _Substring, _Substitute)
_______________________________________________________
replace() replaces all instances of _Substring from 
_String with _Substitute
*/
char* replace(char* _String, char* _Substring, char* _Substitute);

/*
char* var = replace(_Vector, _VectorSize, _Separator)
_______________________________________________________
join() joins all elements of the _Vector separated
by string _Separator
*/
char* join(char** _Vector, size_t _Vecsize, char* _Separator);

/*
Crate var = split(_String, _Delimiter);
_____________________________________
split() splits the _String with _Delimiter
and stores the elements in a vector
*/
Crate split(char* _String, char* _Delimiter);

/*
 char* var = readline(_Stream); 
 // stream can be stdin or a file pointer that has already been opened
 _____________________________________________________________________
 readline() reads char values from given stream until it detects LF
*/
char* readline(FILE* _Stream);

/*
 char* var = readline(_Stream); 
 // stream can be stdin or a file pointer that has already been opened
 _____________________________________________________________________
 readline() reads char values from given stream until it detects LF
*/
char* input(char* _Prompt);

/*
 char* var = read(_Stream, _Bytes); 
 ___________________________________________________________
 read() reads _Bytes no. of bytes from given stream, if 
 _Bytes is greater than the size of file, it reads until EOF
 To read whole file pass -1 in _Bytes argument.
*/
char* read(FILE* _Stream, long bytes);

/*
 Crate var = readlines(_Stream, _Count); 
 ___________________________________________________________________
 readlines() reads _Count no. of lines from the file and stores it
 in the array of strings and returns it, if _Count is greater than
 the no. of lines present in the file, it reads until EOF 
*/
Crate readlines(FILE* _Stream, size_t _Lines);

#endif