/* created by :Adir Ohayon
 * 
 * main file run first and second time on file
 * and call relevant function to decode commands
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <limits.h>
#include "assembler.h"
#include "printer.h"
#include "analyzer.h"
#include "errorControl.h"
/* define global variables */
int DC=0,IC=100;
tableNode *symbolTable = NULL;
memNode *fullMemory = NULL;
memNode *DataMemory = NULL;
int lineNum = 0;
int errorMark = 0;
FILE *extFilePointer;
/* end of global variables definition */
int main(int argc,char *argv[])
{
    /*char partOfLine[MAX_SIZE_OF_LINE];*/
    /*char originalLine[MAX_SIZE_OF_LINE];*/
    FILE *file;
    FILE *objectFilePointer;
    FILE *entFilePointer;
    int isLabel = 0;
    int totalInstructions = IC; /*set to IC first to see Difference after first pass */
    int totalData = 0;
    char *line=malloc(MAX_SIZE_OF_LINE*sizeof(char));
    char originalLine[MAX_SIZE_OF_LINE];
    char parameters[MAX_SIZE_OF_LINE];
    char *label;
    char command[MAX_SIZE_OF_LINE];
    char *extFileName;
	/* error control if user provide too much parameters
	 * too few or wrong filename
	 */
	if(argc < 2)
	{
		printf("please enter filenames as parameters\n");
		return 1;
	}
    /* handle extension argument error */
	if(strchr(argv[1],'.') != NULL){
        printf("Please provide filename without extension\n");
        return 1;
	}
	file =fopen(getNameWithExtension(argv[1],".as"),"r");
	if(file == 0)
	{
		printf("could not open file\n");
		return 1;
	}
    /* store file name to remove in case of error */
    extFileName = getNameWithExtension(argv[1],".ext");
    extFilePointer = fopen(getNameWithExtension(argv[1],".ext"),"w");
	/* end of error control */
	/*first pass */
    while(fgets(originalLine,sizeof(originalLine),file))
    {
        lineNum++;
        if(originalLine[0] == ';')continue;
        if(originalLine[0] == '\n')continue;
        strcpy(line,originalLine);
        label = strtok(line,":");
        if(strcmp(label,originalLine) != 0){
            isLabel = 1;
            line = subStr(originalLine,strlen(label),END_OF_STRING);/* keep the rest of the line */
            if(!isCorrectLabel(label,TRUE)){
                errorMark = TRUE; /* if label is incorrect mark error */
                continue; /* skip to next line */
            }
        }
        else isLabel = 0; /* else mark label don't appear */
        sscanf(line," %s %[^\n]-",command,parameters);
        if(strcmp(command,".entry") == 0){
            if(isLabel == 1){
                printf("line:%d,ERROR LABEL BEFORE ENTRY IS FORBBIDEN\n",lineNum);
                isLabel = 0; /* cause program to ignore label */
                errorMark = TRUE;
            }
        }
        else if(strcmp(command,".extern") == 0){
            if(isLabel == 1){
                printf("line:%d,ERROR LABEL BEFORE EXTERN IS FORBBIDEN\n",lineNum);
                isLabel = 0; /* cause program to ignore label */
                errorMark = TRUE;
            }
            decodeExtern(parameters);
        }
        else if(strcmp(command,".string") == 0){
            decodeString(parameters);
        }
        else if(strcmp(command,".data") == 0){
            decodeData(parameters);
        }
        else if(strcmp(command,".mat") == 0){
            decodeMatrix(parameters);
        }
        else {
            decodeCommand(command,parameters,1);
        }
        /*if there is label put it in symbol table with DC OR IC*/
        if(isLabel == 1){
            if(command[0] == '.'){
                symbolTable = addNewTableNode(symbolTable,label,DC,DATA_FLAG);
            }
            else
                symbolTable = addNewTableNode(symbolTable,label,IC,CODE_FLAG);
        }
        /* clean strings */
        strcpy(command,"");
        strcpy(parameters,"");
        strcpy(label,"");
        strcpy(line,"");
        isLabel = 0;
    }
    /* if errors found in first pass stop */
    if(errorMark == 1){
        fclose(extFilePointer);
        remove(extFileName);
        return -1;
    }
    lineNum = 0;
    /* store total number of data and instructions */
    totalInstructions = IC-totalInstructions;
    totalData = DC;
    updateDataByIc(symbolTable,IC);
    updatMemoryByIc(DataMemory,IC);
    /*end of first pass */
    rewind(file);
    IC = 100;
    DC = 0;
    /*start of second pass */
    while(fgets(originalLine,sizeof(originalLine),file)){
        lineNum++;
        if(originalLine[0] == ';')continue;
        if(originalLine[0] == '\n')continue;
        strcpy(line,originalLine);
        label = strtok(line,":");
        if(strcmp(label,originalLine) != 0){
            line = subStr(originalLine,strlen(label),END_OF_STRING);/* keep the rest of the line */
        }
        sscanf(line," %s %[^\n]",command,parameters);
        if(strcmp(command,".entry") == 0){
            markAsEntry(symbolTable,parameters);
            continue; /* jump to next line */
        }
        else if(command[0] == '.'){
                continue; /* skip if line is .data .extern .mat .string*/
        }
        decodeCommand(command,parameters,2);

        /* clean strings */
        strcpy(command,"");
        strcpy(parameters,"");
        strcpy(label,"");
    }
    /*end of second pass */
    /* if errors found in second pass stop */
    if(errorMark == 1){
        fclose(extFilePointer);
        remove(extFileName);
        return -1;
    }
    /* open and print object file and entry file */
    objectFilePointer = fopen(getNameWithExtension(argv[1],".ob"),"w");
    entFilePointer = fopen(getNameWithExtension(argv[1],".ent"),"w");
    fprintf(objectFilePointer,"%s   %s\n",convertNumWeirdBase(totalInstructions,DEFINITE),convertNumWeirdBase(totalData,DEFINITE));
    printBase4ObFile(objectFilePointer,fullMemory);
    printBase4ObFile(objectFilePointer,DataMemory);
    printBase4EntFile(entFilePointer,symbolTable);
    /*close files and freeing memory */
    free(line);
    free(extFileName);
    free(file);
    fclose(extFilePointer);
    fclose(entFilePointer);
    fclose(objectFilePointer);
    deleteMemoryList(fullMemory);
    deleteMemoryList(DataMemory);
    deleteTableList(symbolTable);
    return 0;
}
