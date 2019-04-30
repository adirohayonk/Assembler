/* created by :Adir Ohayon
 * 
 * interpreter contains functions to decode type of code commands
 * and store their arguments and data in memory
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "interpreter.h"
#include "assembler.h"
#include "memory.h"
#include "table.h"
#include "analyzer.h"
#include "errorControl.h"
/*decodeString
this method receive a string and put it in memory char by char
input:one string */
void decodeString(char *params){
    int ind = 0;
    char tempString[MAX_SIZE_OF_LINE];
    if(!checkStringCommand(params)){
        errorMark = TRUE;
        return;
    }
    strcpy(tempString,params);  /* store data to prevent damage */
    /* loop until end of string */
    while(tempString[ind] != '\0'){
        if(tempString[ind] == '"')ind++; /* skip the quotes sign */
        else {
                DataMemory = addNewMemNode(DataMemory,tempString[ind],DC); /* store letter in memory */
                DC++; /* increase data counter */
                ind++; /* jump to next letter */
        }
    }
    /*if reach end of string store null character */
        DataMemory = addNewMemNode(DataMemory,'\0',DC);
        DC++;
}
/*decodeData this method receive a data arguments
and put it in memory one number by one
input:numbers seprated by comma*/
void decodeData(char *params){
   char tempString[MAX_SIZE_OF_LINE];
   char *parameter;
   if(!checkDataCommand(params,TRUE)){
        errorMark = TRUE;
        return;
   }
   strcpy(tempString,params); /* store data to prevent damage */
   parameter = strtok(tempString,","); /*split parameter by commas */
   while(parameter != NULL )
   {
      DataMemory = addNewMemNode(DataMemory,atoi(parameter),DC);/* put each parameter in memory */
      DC++;
      parameter = strtok(NULL,","); /* split next parameter */
   }
}
/*decodeMatrix this method receive a matrix
if its empty set space in memory
else fill memory with data
input:parameter of a matrix */
void decodeMatrix(char *params){
    char tempString[MAX_SIZE_OF_LINE];
    int numOfParams = 0; /*store number of parameters of matrix splitted */
    int row = 0,col = 0;
    int i,j;
    char *parameter;
    char data[MAX_SIZE_OF_LINE];
    if(!checkMatCommand(params)){
        errorMark = TRUE;
        return;
    }
    strcpy(tempString,params);
    numOfParams = sscanf(tempString,"[%d][%d] %s",&row,&col,data); /* split matrix data to variables */
    /* if not splited correctly generate error */
    if(numOfParams  < 2){
            printf("line:%d, wrong matrix format\n",lineNum);
            errorMark = TRUE;
    }
    else {
    /* if matrix is empty defined */
        if(numOfParams  == 2){
            for(i = 0;i<row;i++){
                for(j = 0;j < col;j++){
                    DataMemory = addNewMemNode(DataMemory,0,DC);/* set all slots to zero */
                    DC++;
                }
            }
        }
        else {
            parameter = strtok(data,",");/* split parameter*/
            while(parameter != NULL)
            {
                DataMemory = addNewMemNode(DataMemory,atoi(parameter),DC); /* set slot to parameter value */
                parameter = strtok(NULL,","); /* split another parameter */
                DC++;
            }
        }
    }
}
/*decodeExtern this method receives an extern label
and put it in symbol table
input: extern label */
void decodeExtern(char* params){
    char *parameter;
    parameter = strtok(params," "); /* split parameter */
    while(parameter != NULL)
    {
        if(!isCorrectLabel(parameter,TRUE)){
            errorMark = TRUE;
            return;
        }
        symbolTable = addNewTableNode(symbolTable,parameter,EXTERNAL_ADDRESS,EXTERNAL_FLAG); /* add parameter to memory */
        markAsExternal(symbolTable,parameter); /* mark parameter as external */
        parameter = strtok(NULL," "); /* split another parameter */
    }
}
/*decodeEntry this method mark parameter label as entry
input:entry parameter */
void decodeEntry(char *params){
    char *parameter;
    parameter = strtok(params," "); /* split parameter */
    while(parameter != NULL)
    {
        if(!isCorrectLabel(parameter,TRUE)){
            errorMark = TRUE;
            return;
        }
        markAsEntry(symbolTable,params); /* mark parameter as entry */
        parameter = strtok(NULL," "); /* split another parameter */
    }
}
/*decodeCommand this method get command code
and pass it to other function by group
input:command and parameters*/
void decodeCommand(char *command,char *params,int passOneOrTwo){
    int commandCode = -1;
    /*first group */
	if(strcmp(command,"mov") == 0)commandCode = 0;
	if(strcmp(command,"cmp") == 0)commandCode = 1;
	if(strcmp(command,"add") == 0)commandCode = 2;
	if(strcmp(command,"sub") == 0)commandCode = 3;
    if(strcmp(command,"lea") == 0)commandCode = 6;
    /* if command code was changed */
    if(commandCode != -1){
    /* call function with first group operators */
        decodeFirstGroupCommands(command,commandCode,params,passOneOrTwo);
        return;
    }
    /*second group */
	if(strcmp(command,"not") == 0)commandCode = 4;
	if(strcmp(command,"clr") == 0)commandCode = 5;
	if(strcmp(command,"inc") == 0)commandCode = 7;
	if(strcmp(command,"dec") == 0)commandCode = 8;
	if(strcmp(command,"jmp") == 0)commandCode = 9;
	if(strcmp(command,"bne") == 0)commandCode = 10;
	if(strcmp(command,"red") == 0)commandCode = 11;
	if(strcmp(command,"prn") == 0)commandCode = 12;
	if(strcmp(command,"jsr") == 0)commandCode = 13;
     if(commandCode != -1){
        /* call error check function */
            if(!checkOneParametersCommands(command,params)){
                errorMark = TRUE;
                return;
            }
     /* call function with second group operators */
        decodeSecondGroupCommands(command,commandCode,params,passOneOrTwo);
        return;
    }
	/*third group */
	if(strcmp(command,"rts") == 0)commandCode = 14;
	if(strcmp(command,"stop") == 0)commandCode = 15;
    if(commandCode == -1) {
            printf("line:%d, wrong command no such command\n",lineNum); /* print error */
            errorMark = TRUE;
	}
    if(commandCode != -1){
    /* call error check function */
            if(!checkNoParametersCommands(command,params)){
                errorMark = TRUE;
                return;
            }
    /* call function with third group operators */
        decodeThirdGroupCommands(command,commandCode,passOneOrTwo);
        return;
    }
}
/*decodeFirstGroupCommands this method set space for command
and calculate first word in memory
input:command,command code,parameters and group */
void decodeFirstGroupCommands(char *command,int commandCode,char *params,int passOneOrTwo){
    int memoryData = 0;
    char *firstParameter;
    char *secondParameter;
    char *matrixName;
    int labelAddress = 0;
    char *firstMatrixRegister;
    char *secondMatrixRegister;
    int markFirstParameterAsRegister = 0;
    int tempVariable = 0;
    int L = 0;
    memoryData = (commandCode<<MOVE_SIX_BITS_LEFT);
    firstParameter = strtok(params,",");
    secondParameter = strtok(NULL," ");
    /* call error check function */
    if(!checkTwoParametersCommands(command,firstParameter,secondParameter)){
        errorMark = TRUE;
        return;
    }
    switch(checkParameterType(firstParameter)){
        case MATRIX:{
            memoryData += (2<<MOVE_FOUR_BITS_LEFT); /* store addressing number in correct location */
            matrixName = strtok(firstParameter,"[");
            if(passOneOrTwo == 2){
                /* check if matrix exist and store address */
                if((labelAddress = getTableNodeAddress(symbolTable,matrixName)) == ERROR_CODE){
                    return;
                }
                tempVariable = (labelAddress << MOVE_TWO_BITS_LEFT);
                if(checkIfNodeIsExternal(symbolTable,matrixName)){
                    printBase4ExtFile(matrixName,IC+1);
                    tempVariable += 1; /* add ARE bits */
                }
                else tempVariable += 2;
                fullMemory = addNewMemNode(fullMemory,tempVariable,IC+1);
                L+=3;
                break;
            }
            firstMatrixRegister = strtok(NULL,"[]");
            secondMatrixRegister = strtok(NULL,"[]");
            firstMatrixRegister++; /*skip the r in register */
            secondMatrixRegister++;
            tempVariable = atoi(firstMatrixRegister) << MOVE_SIX_BITS_LEFT;
            tempVariable += atoi(secondMatrixRegister) << MOVE_TWO_BITS_LEFT;
            fullMemory = addNewMemNode(fullMemory,tempVariable,IC+2);
            L +=3;
            break;
        }
        case REGISTER:{
            if(passOneOrTwo == 2){
                L +=2;
                markFirstParameterAsRegister = 1;
                break;
            }
            memoryData += (3<<MOVE_FOUR_BITS_LEFT);
            L +=2;
            firstParameter++; /*skip the r in register */
            tempVariable = atoi(firstParameter) << MOVE_SIX_BITS_LEFT;
            /* if second parameters is register keep space for another register data */
            if(checkParameterType(secondParameter) == REGISTER){
                markFirstParameterAsRegister = 1;
            }
            /*else add data to memory */
            else fullMemory = addNewMemNode(fullMemory,tempVariable,IC+1);
            break;
        }
        case NUMBER:{
            if(passOneOrTwo == 2){
                L +=2;
                break;
            }
            L +=2;
            firstParameter++; /*skip the # sign */
            fullMemory = addNewMemNode(fullMemory,atoi(firstParameter),IC+1);
            break;
        }
        case LABEL:{
            if(passOneOrTwo == 2){
                labelAddress = getTableNodeAddress(symbolTable,firstParameter);
                tempVariable = labelAddress << MOVE_TWO_BITS_LEFT;
                if(checkIfNodeIsExternal(symbolTable,firstParameter)){
                    printBase4ExtFile(firstParameter,IC+1);
                    tempVariable += 1; /* add ARE bits */
                }
                else tempVariable += 2;
                fullMemory = addNewMemNode(fullMemory,tempVariable,IC+1);
                L+=2;
                break;
            }
            memoryData += (1<<MOVE_FOUR_BITS_LEFT);
            L +=2;
            break;
        }
    }
    /* check Second Parameter */
    switch(checkParameterType(secondParameter)){
        case MATRIX:{
            memoryData += (2<<MOVE_TWO_BITS_LEFT);
            matrixName = strtok(secondParameter,"[");
            if(passOneOrTwo == 2){
                /* check if matrix exist and store address */
                if((labelAddress = getTableNodeAddress(symbolTable,matrixName)) == ERROR_CODE){
                    return;
                }
                tempVariable = labelAddress << MOVE_TWO_BITS_LEFT;
                if(checkIfNodeIsExternal(symbolTable,matrixName)){
                    tempVariable += 1; /* add ARE bits */
                    printBase4ExtFile(matrixName,IC+L);
                }
                else tempVariable += 2;
                fullMemory = addNewMemNode(fullMemory,tempVariable,IC+L);
                L+=2;
                break;
            }
            firstMatrixRegister = strtok(NULL,"[]");
            secondMatrixRegister = strtok(NULL,"[]");
            firstMatrixRegister++; /*skip the r in register */
            secondMatrixRegister++;
            tempVariable = atoi(firstMatrixRegister) << MOVE_SIX_BITS_LEFT;
            tempVariable += atoi(secondMatrixRegister) << MOVE_TWO_BITS_LEFT;
            fullMemory = addNewMemNode(fullMemory,tempVariable,IC+L);
            L +=2;
            break;
        }
        case REGISTER:{
            if(passOneOrTwo == 2){
                if(markFirstParameterAsRegister == 0)L+=1;
                break;
            }
            memoryData += (3<<MOVE_TWO_BITS_LEFT);
            if(markFirstParameterAsRegister == 0){
                secondParameter++; /*skip the r in register */
                tempVariable = atoi(secondParameter) << MOVE_TWO_BITS_LEFT;
                fullMemory = addNewMemNode(fullMemory,tempVariable,IC+L);
                L +=1;
            }
            else {
                secondParameter++; /*skip the r in register */
                tempVariable += atoi(secondParameter) << MOVE_TWO_BITS_LEFT;
                fullMemory = addNewMemNode(fullMemory,tempVariable,IC+1);
            }
            break;
        }
        case NUMBER:{
            if(passOneOrTwo == 2){
                L +=1;
                break;
            }
            secondParameter++; /*skip the # sign */
            fullMemory = addNewMemNode(fullMemory,atoi(secondParameter),IC+L);
            L +=1;
            break;
        }
        case LABEL:{
            if(passOneOrTwo == 2){
                labelAddress = getTableNodeAddress(symbolTable,secondParameter);
                tempVariable = labelAddress << 2;
                if(checkIfNodeIsExternal(symbolTable,secondParameter)){
                    printBase4ExtFile(secondParameter,IC+L);
                    tempVariable += 1; /* add ARE bits */
                }
                else tempVariable += 2;
                fullMemory = addNewMemNode(fullMemory,tempVariable,IC+L);
                L+=1;
                break;
            }
            memoryData += (1<<MOVE_TWO_BITS_LEFT);
            L +=1;
            break;
        }
    }
    if(passOneOrTwo != 2)fullMemory = addNewMemNode(fullMemory,memoryData,IC);
    IC+=L;
}

void decodeSecondGroupCommands(char *command,int commandCode,char *params,int passOneOrTwo){
    int memoryData = 0;
    char *firstParameter;
    char *matrixName;
    int labelAddress = 0;
    char *firstMatrixRegister;
    char *secondMatrixRegister;
    int tempVariable = 0;
    int L = 0;
    memoryData = (commandCode<<MOVE_SIX_BITS_LEFT); /* store command code in correct location */
    firstParameter = strtok(params," ");/* split parameter by space */
    /* get type of parameter */
    switch(checkParameterType(firstParameter)){
        case MATRIX:{
            memoryData += (2<<MOVE_TWO_BITS_LEFT); /*store addressing type */
            matrixName = strtok(firstParameter,"[");
            /* check if matrix exist */
            if(findInTableList(symbolTable,matrixName) == NULL){
            printf("line:%d, Error: cannot find ,matrix:%s\n",lineNum,matrixName);
                errorMark = 1;
                return;
            }
            /* if pass 2 */
            if(passOneOrTwo == 2){
                labelAddress = getTableNodeAddress(symbolTable,matrixName); /* get address of label */
                tempVariable = labelAddress << MOVE_TWO_BITS_LEFT; /* store address in correct format */
                /* if label is external store in external file */
                if(checkIfNodeIsExternal(symbolTable,matrixName)){
                printBase4ExtFile(matrixName,IC+1);
                tempVariable += 1; /* add ARE bits external */
                }
                else tempVariable += 2; /* add ARE bits data */
                fullMemory = addNewMemNode(fullMemory,tempVariable,IC+1); /* store address in memory */
                L+=3; /* change length size */
                break;
            }
            firstMatrixRegister = strtok(NULL,"[]");
            secondMatrixRegister = strtok(NULL,"[]");
            firstMatrixRegister++; /*skip the r in register */
            secondMatrixRegister++;
            tempVariable = atoi(firstMatrixRegister) << MOVE_SIX_BITS_LEFT; /* move register bits to correct location */
            tempVariable += atoi(secondMatrixRegister) << MOVE_TWO_BITS_LEFT;
            fullMemory = addNewMemNode(fullMemory,tempVariable,IC+2); /* store data in memory */
            L +=3; /* change length size */
            break;
        }
        case REGISTER:{
            /* if pass number 2 only change length of word */
            if(passOneOrTwo == 2){
                L+=2;
                break;
            }
            memoryData += (3<<MOVE_TWO_BITS_LEFT); /* store addressing type */
            L +=2; /* change word length */
            firstParameter++; /*skip the r in register */
            tempVariable = atoi(firstParameter) << MOVE_TWO_BITS_LEFT; /* convert char to number */
            fullMemory = addNewMemNode(fullMemory,tempVariable,IC+1); /* store register number in correct location */
            break;
        }
        case NUMBER:{
            /* if pass number 2 only change length of word */
            if(passOneOrTwo == 2){
                L+=2;
                break;
            }
            L +=2;
            firstParameter++; /*skip the # sign */
            fullMemory = addNewMemNode(fullMemory,atoi(firstParameter),IC+1); /* store number in memory */
            break;
        }
        case LABEL:{
            if(passOneOrTwo == 2){
                labelAddress = getTableNodeAddress(symbolTable,firstParameter);
                tempVariable = labelAddress << MOVE_TWO_BITS_LEFT;
                if(checkIfNodeIsExternal(symbolTable,firstParameter)){
                    printBase4ExtFile(firstParameter,IC+1);
                    tempVariable += 1; /* add ARE bits */
                }
                else tempVariable += 2;
                fullMemory = addNewMemNode(fullMemory,tempVariable,IC+1);
                L+=2;
                break;
            }
            memoryData += (1<<MOVE_TWO_BITS_LEFT);
            L +=2;
            break;
        }
    }
    if(passOneOrTwo != 2)fullMemory = addNewMemNode(fullMemory,memoryData,IC);
    IC+=L;
}
void decodeThirdGroupCommands(char *command,int commandCode,int passOneOrTwo){
    int memoryData = (commandCode<<MOVE_SIX_BITS_LEFT);
    /* if command is from group 3 no arguments needed
    store only command code */
    if(passOneOrTwo != 2)fullMemory = addNewMemNode(fullMemory,memoryData,IC);
    IC++;
}
