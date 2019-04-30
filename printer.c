/* created by :Adir Ohayon
 * 
 * printer contains functions to convert memory data to base 4 data
 * and create relvant output files
 */
#include <stdio.h>
#include <stdlib.h>
#include "printer.h"
#include "assembler.h"
#include "analyzer.h"
/* printBase4ObFile receives object file pointer and head of list
print all file after convert all decimal data to base 4 */
void printBase4ObFile(FILE *file,memNode *head){
    memNode *ptr = head;
    while(ptr != NULL){
        fprintf(file,"%s   %s\n",convertNumWeirdBase(ptr->address,ADDRESS),convertNumWeirdBase(ptr->memoryValue,COMMAND));
        ptr = ptr->next;
    }
}
/* printBase4EntFile receives entry file pointer and head of list
print all file after convert all decimal data to base 4 */
void printBase4EntFile(FILE *file,tableNode *head){
    tableNode *ptr=head;
    while(ptr != NULL){
        if(ptr->entryFlag == 1){
             fprintf(file,"%s   %s\n",ptr->name,convertNumWeirdBase(ptr->address,ADDRESS));
        }
        ptr = ptr->next;
    }
}
/* printBase4ExtFile receives external file data
print all to file after convert all decimal data to base 4 */
void printBase4ExtFile(char *label,int address){
        fprintf(extFilePointer,"%s   %s\n",label,convertNumWeirdBase(address,ADDRESS));
}
/* convertNumWeirdBase receive num and number of bits
and return string to weird base 4 number */
char * convertNumWeirdBase(int num,int numOfBits){
    int base4Number[5] = {0};
    int index = 4;
    int remainder;
    int sum = num;
    int countNumBits = 0;
    int weirdBaseIndex = 0;
    char *weirdBase4Num = malloc(sizeof(char)*5);
    while(sum != 0){
        remainder = sum % 4;
        sum = sum / 4;
        base4Number[index] = remainder;
        index--;
        countNumBits++;
    }
    if(numOfBits != DEFINITE)countNumBits = numOfBits;
    for(index = 5-countNumBits;index < 5;index++){
        switch(base4Number[index]){
            case 0:weirdBase4Num[weirdBaseIndex] = 'a';break;
            case 1:weirdBase4Num[weirdBaseIndex] = 'b';break;
            case 2:weirdBase4Num[weirdBaseIndex] = 'c';break;
            case 3:weirdBase4Num[weirdBaseIndex] = 'd';break;
        }
        weirdBaseIndex++;
    }
    weirdBase4Num[weirdBaseIndex] = '\0';
    return weirdBase4Num;
}
