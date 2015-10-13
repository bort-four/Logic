/* Logic.h contains common tools for the entire project
*/

#ifndef LOGIC_HEADER
#define LOGIC_HEADER

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>


/* === common datatypes & constants === */

/* _boolean */

typedef char Boolean;
#define true  1
#define false 0


/* Vector
 * Dynamic array */

typedef struct {
	void* addr;
	size_t maxLen, len, itemSize;
} Vector;

#define ptr(type, vect) ((type*)(vect).addr)

#define initVect(vect, type)                                                   \
{                                                                              \
	(vect).len = (vect).maxLen = 0; (vect).addr = NULL;                        \
	(vect).itemSize = sizeof(type);                                            \
}

#define forVect(it, vect) for ((it) = 0; (it) < (vect).len; ++(it))

#define forVectIf(it, vect, cond)                                              \
	for ((it) = 0; (it) < (vect).len && (cond); ++(it))

#define addBack(vect, type, value)                                             \
{                                                                              \
	expandVector(&(vect), (vect).len + 1, true);                               \
	ptr(type, vect)[(vect).len] = value;                                       \
	(vect).len++;                                                              \
}

#define delFrom(vect, type, pos)                                               \
{                                                                              \
	ptr(type, vect)[(pos)] = ptr(type, vect)[(vect).len - 1];                  \
    (vect).len--;                                                              \
}

#define freeVect(vect)                                                         \
{                                                                              \
	freePtr((vect).addr);                                                      \
	(vect).len = (vect).maxLen = 0;                                            \
}


/* === common macros === */

#define _ABS(x)	((x < 0) ? -(x) : (x))
#define _MAX(x, y)	(((x) > (y)) ? (x) : (y))
#define _MIN(x, y)	(((x) < (y)) ? (x) : (y))

#define BAD_INDEX -1

#define freePtr(ptr) {if ((ptr) != NULL) {free(ptr); ptr = NULL;}}

#define _SWAP(var1, var2, type)                                                \
{                                                                              \
	type _swap_var = (var1);                                                   \
	(var1) = (var2); (var2) = _swap_var;                                       \
}


/* === for debug output === */

//~ typedef enum {FM_NORM, FM_BLUE, FM_YELL, FM_ERR} PrintFormat;

//~ #define setFormat(fm)                                                          
//~ {                                                                              
	//~ switch (fm)                                                                
	//~ {                                                                          
		//~ case FM_NORM: printf("\033[0m");  break;                               
		//~ case FM_BLUE: printf("\033[36m"); break;                               
		//~ case FM_YELL: printf("\033[33m"); break;                               
		//~ case FM_ERR:  printf("\033[31m"); break;                               
	//~ }                                                                          
//~ }
//~ 
//~ #define print(format, msg)                                                     
//~ {                                                                              
	//~ setFormat(format);                                                         
	//~ printf(msg);                                                               
	//~ setFormat(FM_NORM);                                                        
//~ }

/* === for parse & error recovery === */

typedef enum { SRC_FILE, SRC_STREAM, SRC_STRING } SourceType;

typedef struct
{
	SourceType type;
	FILE* file;
	char* fileName;
	char* strPtr;
	Vector charVect;	/* Vector of char */
} Source;


typedef enum { PARSER_ERROR, INTERPRETATION_ERROR, INNER_ERROR } ErrorType;

typedef struct {
	Source* sourcePtr;
	size_t lineNum, columnNum;
} ErrorLocation;

typedef struct
{
	ErrorType type;
	ErrorLocation location;
	char* message;
	
} Error;




/* === functions === */

void expandVector(Vector* vectPtr, size_t needLen, Boolean extra);
char* getDynamicStr(char str[]);


/* for parse & error recovery */

Source createFileSource(char fileName[]);
Source createStreamSource(FILE* stream);
Source createStringSource(char string[]);
int getChar(Source* sourcePtr);
void comeBack(Source* sourcePtr);
Boolean isEmpty(Source* sourcePtr);
void freeSource(Source* sourcePtr);

Error createParserError(char msg[], Source* sourcePtr,
						size_t lineNum, size_t columnNum);
Error createInterpretationError(char msg[]);
Error createInnerError(char msg[]);

void addTextToError(Error* errorPtr, char msg[]);
void printError(Error* errorPtr, FILE* stream);
void freeError(Error* errorPtr);

#endif  /* LOGIC_HEADER */


/* garbage */

//~ Name makeName(char str[]);

//~ #define NAME_LEN 32
//~ #define BUFF_LEN 64
//~ static const size_t BAD_INDEX = SIZE_MAX;
//~ typedef struct {char n[NAME_LEN];} Name;
//~ typedef struct {char str[BUFF_LEN];} Buffer;

//~ #define nameCmp(name1, name2) (strcmp(name1.n, name2.n) == 0)
//~ #define nameStrCmp(name, str) (strcmp((name).n, str) == 0)




//~ #define forRange(num, begin, end) for ((num) = (begin); (num) < (end); ++(num))


/*
#define my_assert(prm) \
    {if ((prm).errCode) {freeMem(&(prm)); exit((prm).errCode);}}

#define del_from(vect, type, num) \
    {ptr(type, vect)[num] = ptr(type, vect)[--(vect).len];}
*/






