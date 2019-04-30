/* created by :Adir Ohayon
 * 
 * printer header file
 */
#ifndef PRINTER_H_INCLUDED
#define PRINTER_H_INCLUDED
#define ADDRESS 4
#define COMMAND 5
#define DEFINITE -1
#include "memory.h"
#include "table.h"
/* receive object file pointer and print memory to file */
void printBase4ObFile(FILE *file,memNode *head);
/* receive ent file pointer and print symbol table relevant data to it */
void printBase4EntFile(FILE *file,tableNode *head);
/* receive ext file data and print to file */
void printBase4ExtFile(char label[],int address);
/* receive number ans numb of bits and return weird base 4 number */
char * convertNumWeirdBase(int num,int numOfBits);
#endif /* PRINTER_H_INCLUDED*/
