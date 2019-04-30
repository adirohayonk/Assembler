/* created by :Adir Ohayon
 * 
 * analyzer contains functions that assist you to split strings
 * and create new one
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "analyzer.h"
#include "assembler.h"
/*findCharInString this method find character
in string and return character index
input: string and one character */
int findCharInString(char *string,char ch){
    int i = 0;
    /* if end of string not reached */
    while(string[i] != '\0'){
        if(string[i] == ch)return i; /* check for character and return index */
        i++;
    }
    return ERROR_CODE; /* if character not found return -1 */
}
/*checkParameterType this method get parameter
find out its type and return type
input: one parameter*/
int checkParameterType(char *parameter){
  /* search for matrix sign return matrix flag*/
    if(findCharInString(parameter,'[') != ERROR_CODE){
        return MATRIX;
    }
  /* checks for register sign if exist return register flag */
    else if(findCharInString(parameter,'r') != ERROR_CODE){
        return REGISTER;
    }
  /*checks for number sign if exist return number flag */
    else if(findCharInString(parameter,'#') != ERROR_CODE){
        return NUMBER;
    }
    /* if none above was found return label flag */
    else {
        return LABEL;
    }
}
/* subStr method receive a string ,a start
index and number of letters and returns
new string from start index in size of letters number provided */
char * subStr(char *string,int start,int end){
	int ind = 0;
	int newInd =0;
	char *substr = malloc(MAX_SIZE_OF_LINE*(sizeof(char)));/* create space for new string */
    /* while end of string not reached */
	while(string[ind] != '\0'){
	/* if pass starting index starts to store letters */
		if(ind > start){
			substr[newInd] =string[ind];
			newInd++;
		}
		/* if reach start + letters number mark end of string break loop */
		if(ind == (start+end) && end != END_OF_STRING)
		{
			substr[newInd] = '\0';
			break;
		}
		ind++;
	}
	/* returns created string */
	return substr;
}
/* getNameWithExtension method recieves a filename and extension
concatenate them together and returns new string with file name and extension */
char * getNameWithExtension(char *filename,char *extension){
    char *fileWithoutExtension;
    char *fileWithExtension = malloc(strlen(filename)+strlen(extension)); /* set space for new filename with extension */
    fileWithoutExtension = strtok(filename,".");/* split file name for correct filename */
    strcpy(fileWithExtension,fileWithoutExtension);/* copy filename */
	strcat(fileWithExtension,extension);/* concatenate extension */
    return fileWithExtension;/* returns new file name*/
}
