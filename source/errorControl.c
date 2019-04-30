/* created by :Adir Ohayon
 * 
 * errorControl contains functions to check correctness of input
 * and to return errors when input is incorrect
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "errorControl.h"
#include "assembler.h"
/* isCharAndNum this method receive a character and checks if
that character is number or letter if yes return true
else return false*/
int isCharAndNum(char ch){
	if(ch >= BUTTOM_ASCII_CODE_FOR_NUMBERS && ch <= TOP_ASCII_CODE_FOR_NUMBERS)return TRUE;
	else if(ch >= BUTTOM_ASCII_CODE_FOR_CAPITAL_LETTERS && ch <= TOP_ASCII_CODE_FOR_CAPITAL_LETTERS)return TRUE;
	else if(ch >= BUTTOM_ASCII_CODE_FOR_LOWER_CASE_LETTERS && ch <= TOP_ASCII_CODE_FOR_LOWER_CASE_LETTERS)return TRUE;
	else return FALSE;
}
/* isSavedWords this method receive a word and checks
if this word ia one of saved words of assembly language
if yes returns true else returns false */
int isSavedWords(char *word){
	if(strcmp(word,"mov") == 0)return TRUE;
    if(strcmp(word,"cmp") == 0)return TRUE;
	if(strcmp(word,"add") == 0)return TRUE;
	if(strcmp(word,"sub") == 0)return TRUE;
    if(strcmp(word,"not") == 0)return TRUE;
	if(strcmp(word,"clr") == 0)return TRUE;
	if(strcmp(word,"lea") == 0)return TRUE;
    if(strcmp(word,"inc") == 0)return TRUE;
	if(strcmp(word,"dec") == 0)return TRUE;
	if(strcmp(word,"jmp") == 0)return TRUE;
    if(strcmp(word,"bne") == 0)return TRUE;
	if(strcmp(word,"red") == 0)return TRUE;
	if(strcmp(word,"prn") == 0)return TRUE;
    if(strcmp(word,"jsr") == 0)return TRUE;
	if(strcmp(word,"rts") == 0)return TRUE;
	if(strcmp(word,"stop") == 0)return TRUE;
	return FALSE;
}
/* isCorrectRegister this method receive a word and checks
if this word is one of correct registers numbers
if yes returns true else returns false */
int isCorrectRegister(char *word){
	if(strcmp(word,"r0") == 0)return TRUE;
	if(strcmp(word,"r1") == 0)return TRUE;
	if(strcmp(word,"r2") == 0)return TRUE;
	if(strcmp(word,"r3") == 0)return TRUE;
    if(strcmp(word,"r4") == 0)return TRUE;
	if(strcmp(word,"r5") == 0)return TRUE;
	if(strcmp(word,"r6") == 0)return TRUE;
    if(strcmp(word,"r7") == 0)return TRUE;
    return FALSE;
}
/*isCorrectNumber this method receive a word
and checks if that word is number in correct format
and from correct type if yes returns true else returns false */
int isCorrectNumber(char *word){
   /* first charcter in number must be # */
    if(word[0] == '#'){
       word++;
       /* convert to number and checks for correct convertion */
       if(atoi(word) != 0){
            return TRUE;
       }
    }
    return FALSE;
}
/* isCorrectMatrix this method receive a word
and checks if this word is matrix in correct format
if yes return true else return false */
int isCorrectMatrix(char *word){
    char matrixName[MAX_SIZE_OF_LINE];
    char parameters[MAX_SIZE_OF_LINE];
    char firstRegister[MAX_SIZE_OF_LINE];
    char *secondRegister = malloc(MAX_SIZE_OF_LINE*sizeof(char));
    sscanf(word,"%[^/[]%s",matrixName,parameters); /* split matrix name */
	sscanf(parameters,"[%[^]]%s",firstRegister,secondRegister); /* split first register between [] */
	secondRegister++; /* second register contain ][] skip the ] */
	sscanf(secondRegister,"[%[^]]",secondRegister); /* split second register between [] */
	/* check if both registers are correct registers */
    if(!isCorrectRegister(firstRegister) || (!isCorrectRegister(secondRegister))){
        return FALSE;
    }
    /* checks if label is correct label */
    if(!isCorrectLabel(matrixName,FALSE)){
        return FALSE;
    }
    return TRUE;
}
/* isCorrectLabel function checks if label is correct
errorFlag mark True when label is not parameter check
when checks label from data zone*/
int isCorrectLabel(char *label,int errorsFlag){
    int i = 0;
    int lenOfLabel = strlen(label);
    /* checks if label is above maximum size */
    if(lenOfLabel > MAX_LABEL_SIZE){
        if(errorsFlag == TRUE)printf("line:%d, Error: label is too long, in label:%s \n",lineNum,label);
        return FALSE;
    }
    /* check if label include only characters and numbers */
    while(label[i] != '\0'){
        if(!isCharAndNum(label[i])){
            if(errorsFlag == TRUE)printf("line:%d, Error: wrong label name, in label:%s \n",lineNum,label);
            return FALSE;
        }
        i++;
    }
    /* if label don't start with a letter generate error */
    if(!isalpha(label[0])){
        if(errorsFlag == TRUE)printf("line:%d, Error: label should start with a letter, in label:%s \n",lineNum,label);
        return FALSE;
    }
    /* if label is saved word or register name generate error */
    if(isSavedWords(label) || isCorrectRegister(label)){
        if(errorsFlag == TRUE)printf("line:%d, Error: label contain saved word, in label:%s \n",lineNum,label);
        return FALSE;
    }
    return TRUE;
}
/* isCorrectParameter this method receive a parameter and checks if its correct
use all methods above if incorrect return false else returns true */
int isCorrectParameter(char *parameter){
    if((!isCorrectNumber(parameter)) && (!isCorrectRegister(parameter))
    && (!isCorrectMatrix(parameter)) && (!isCorrectLabel(parameter,FALSE)))return FALSE;
    return TRUE;
}
/* checkNoParametersCommandns this method recieve command from group third without operatora
and content after command and checks if content is empty
if not return false and generate error */
int checkNoParametersCommands(char *command,char *parameters){
    int lengthOfParms = strlen(parameters); /* store lentgh of data after command */
    /* checks if content after command is empty if not generate error */
    if(parameters != NULL && parameters[0] != '\0' && lengthOfParms != 0){
            printf("line:%d, Error: should not have parameters, in command:%s \n",lineNum,command);
            return FALSE;
    }
    return TRUE;
}
/* checkOneParametersCommands this method receive a command from group two with one parameter
and checks if parameter is correct and if only one parameter provided if not
returns false and generate error */
int checkOneParametersCommands(char *command,char *parameter){
    int lengthOfParms = strlen(parameter);
    /* if parameter is empty than is missimg generate error */
    if(parameter == NULL || parameter[0] == '\0' || lengthOfParms == 0){
            printf("line:%d, Error: parameter is missing, in command:%s\n",lineNum,command);
            return FALSE;
    }
    /* only prn command allow all parameters type in parameter */
    if(strcmp(command,"prn") == 0){
        if(!isCorrectParameter(parameter)){
                printf("line:%d, Error: wrong parameter type:%s ,in command:%s \n",lineNum,parameter,command);
                return FALSE;
        }
    }
    /* all other commands can have any parameter beside number */
    else {
        if((!isCorrectMatrix(parameter)) && (!isCorrectLabel(parameter,FALSE))
           && (!isCorrectRegister(parameter))) {
               printf("line:%d, Error: wrong parameter type:%s ,in command:%s \n",lineNum,parameter,command);
               return FALSE;
        }
    }
    return TRUE;
}
/* checkTwoParametersCommands this method receive a command from group one with two parameters
and checks if parameters is correct if not returns false and generate error */
int checkTwoParametersCommands(char *command,char *parameter1,char *parameter2){
    /* if first parameter is missing generate error*/
    if(parameter1 == NULL || parameter1[0] == '\0'){
            printf("line:%d, Error: first parameter is missing, in command:%s\n",lineNum,command);
            return FALSE;
    }
    /* if second parameter is missing generate error */
    if(parameter2 == NULL || parameter2[0] == '\0'){
            printf("line:%d, Error: second parameter is missing, in command:%s\n",lineNum,command);
            return FALSE;
    }
    /* first parameter of lea must be matrix or label */
    if(strcmp(command,"lea") == 0){
        if((!isCorrectMatrix(parameter1)) && (!isCorrectLabel(parameter1,FALSE))){
                printf("line:%d, Error: wrong parameter type:%s ,in command:%s \n",lineNum,parameter1,command);
                return FALSE;
        }
    }
    /*all other first group commands can have any parameter type in parameter1 */
    else {
        /* check if parameter is not any of allowed parameters */
        if(!isCorrectParameter(parameter1)){
                printf("line:%d, Error: wrong parameter type:%s ,in command:%s \n",lineNum,parameter1,command);
                return FALSE;
        }
    }
    /* only cmp command allowed all parameters in second parameter  */
    if(strcmp(command,"cmp") == 0){
        if(!isCorrectParameter(parameter2)){
                printf("line:%d, Error: wrong parameter type:%s ,in command:%s \n",lineNum,parameter2,command);
                return FALSE;
        }
    }
    /* all other first group commands can have any parameter type besides number in parameter2 */
    else {
        if((!isCorrectMatrix(parameter2)) && (!isCorrectLabel(parameter2,FALSE))
           && (!isCorrectRegister(parameter2))){
                printf("line:%d, Error: wrong parameter type:%s ,in command:%s \n",lineNum,parameter2,command);
                return FALSE;
        }
    }
    return TRUE;
}
int elementCount = 0;/* used for count elements and compare to commas global for matrix */
int commasCount = 0;/* used for count commas and compare to elements and for matrix*/
/*checkDataCommand this method receive parameters of
from data type list of numbers and error flag to not print errors
if checks during matrix check */
int checkDataCommand(char *parameters,int errorsFlag){
    char tempString[MAX_SIZE_OF_LINE];
    char *element;
    int i = 0;
    commasCount = 0;
    elementCount = 0;
    while(parameters[i] != '\0'){
        if(parameters[i] == ',')commasCount++;
        i++;
    }
    i = 0;
    /* if no data provided generate error */
    if(parameters == NULL || parameters[0] == '\0'){
            if(errorsFlag == TRUE)
                printf("line:%d, Error: no arguments provided for .data \n",lineNum);
            return FALSE;
    }
    strcpy(tempString,parameters); /* store data to prevent damage */
    element = strtok(tempString,","); /*split elements by commas */
    elementCount++;
    while(element != NULL )
    {
    /* checks if float number provided if so generare error */
        if(strchr(element,'.') != NULL){
            if(errorsFlag == TRUE)
                printf("line:%d, Error: only integer numbers allowed, element:%s \n",lineNum,element);
            elementCount = 2; /* mark float number  error for matrix check */
            return FALSE;
        }
        while(element[i] != '\0'){
            /* if character of data is not -,+ or number generate error*/
            if((!isdigit(element[i])) && element[i] != '-' && element[i] != '+'){
                if(errorsFlag == TRUE)
                    printf("line:%d, Error: wrong element type, element:%s \n",lineNum,element);
                return FALSE;
            }
        i++;
        }
        element = strtok(NULL,","); /* split next element */
        if(element != NULL)elementCount++;
        i = 0;
    }
    if((elementCount-1) != commasCount){
        if(errorsFlag == TRUE)
            printf("line:%d, Error: too Much Commas \n",lineNum);
        return FALSE;
    }
    return TRUE;
}
/* getStringLength this method receives a string
and return its length */
int getStringLength(char *str){
    int length = 0;
    while(str[length] != '\0')length++;
    return length;
}
/* checkStringCommand this method receive .string parameters
and check for its correctness */
int checkStringCommand(char *parameters){
    /* generate error if string is empty */
    if(parameters == NULL || parameters[0] == '\0'){
            printf("line:%d, Error: empty string provided \n",lineNum);
            return FALSE;
    }
    /* checks if end and start with auotes if not print error */
    if(parameters[getStringLength(parameters)-1] != '\"'){
            printf("line:%d, Error: missing quotes at end of string, string:%s \n",lineNum,parameters);
            return FALSE;
    }
    if(parameters[0] != '\"'){
            printf("line:%d, Error: missing quotes at start of string, string:%s \n",lineNum,parameters);
            return FALSE;
    }
    return TRUE;
}
/* checkMatCommand this method receive .mat parameters and check if
provided correctly */
int checkMatCommand(char *parameters){
    char row[MAX_SIZE_OF_LINE];
    char data[MAX_SIZE_OF_LINE];
    char *col = malloc(MAX_SIZE_OF_LINE*sizeof(char));
    /*split row between [] and store next element ][] in col and after space data in data */
	sscanf(parameters,"[%[^]]%s %s",row,col,data);
	col++;/* skip ] in ][] */
	sscanf(col,"[%[^]]",col); /* split col between [] and store in col*/
	if(!isdigit(row[0]) || row[1] != '\0'){
        printf("line:%d, Error: wrong row number, row:%s \n",lineNum,row);
        return FALSE;
	}
    if(!isdigit(col[0]) || col[1] != '\0'){
        printf("line:%d, Error: wrong column number, column:%s \n",lineNum,row);
        return FALSE;
	}
	/* check data provided */
	if(!checkDataCommand(data,FALSE)){
        if((elementCount-1) != 0){
            printf("line:%d, Error: wrong data for matrix, data:%s \n",lineNum,data);
            return FALSE;
        }
	}
	/* checks if too many or too little elements provided */
	if((elementCount) != (atoi(col)+atoi(row)) && (elementCount-1) != 0){
        printf("line:%d, Error: wrong number of elements for matrix \n",lineNum);
        return FALSE;
	}
    return TRUE;
}
