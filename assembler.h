/* created by :Adir Ohayon
 * 
 * assembler.h contains most of program constants
 * and also global variables that used in all program
 */
#ifndef ASSEMBLER_H_INCLUDED
#define ASSEMBLER_H_INCLUDED
#define MAX_SIZE_OF_LINE 80
#define MAX_PARAMS_IN_LINE 10
#define END_OF_STRING -1
#define EXTERNAL_ADDRESS 0
#define EXTERNAL_FLAG -2
#define MAX_REGISTER_SIZE 2
#define DATA_FLAG 1
#define CODE_FLAG 0
#define MATRIX 1
#define REGISTER 2
#define NUMBER 3
#define LABEL 4
#define TRUE 1
#define FALSE 0
#define ERROR_CODE -1
#define MOVE_SIX_BITS_LEFT 6
#define MOVE_FOUR_BITS_LEFT 4
#define MOVE_TWO_BITS_LEFT 2
#include "table.h"
#include "interpreter.h"
#include "memory.h"
#include "printer.h"
#include "analyzer.h"
#include "error.h"
/* define global variables for program */
extern int errorMark;/*this variable that storw if error occured */
extern int lineNum; /* this variable store line number */
extern int DC; /* this variable count data lines*/
extern int IC; /* this variable count command lines */
extern tableNode *symbolTable; /* this variable points to linked list respresents symbols table */
extern memNode *fullMemory; /* this variable points to list represent commanda memory*/
extern memNode *DataMemory; /* this variable represent data memory */
extern FILE *extFilePointer; /* this mark externals file pointer */
#endif /* ASSEMBLER_H_INCLUDED*/
