/* Created by:adir ohayon
 * 
 * table contains data strcture and functions to manage symbols table
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"
#include "assembler.h"
/* addNewTableNode this method receive head of table,data,address,and if its data or command
and add node to list*/
tableNode* addNewTableNode(tableNode *head, char dat[],int addr,int comandOrDat){
	tableNode *new;
	tableNode *ptr;
    if(findInTableList(head,dat) != NULL) /* if element already in list produce error */
    {
        printf("line:%d, Error element %s already in list\n",lineNum,dat);
        return head;
    }
    /* if list is empty create head and return*/
	if(head == NULL){
		head = malloc( sizeof(tableNode));
		strcpy(head->name,dat);
		head->address = addr;
        head->commandOrData = comandOrDat;
        head->next = NULL;
		return head;
	}
	else {
		ptr = head;
		/* reach end of list*/
		while(ptr->next != NULL){
			ptr = ptr->next;
		}
		/* create new node and insert */
		new = malloc(sizeof(tableNode));
		strcpy(new->name,dat);
		ptr->next = new;
		new->address = addr;
        new->commandOrData = comandOrDat;
		return head;
	}
}
/* printTableList this method receive head of list and print it
for debugging */
void printTableList(tableNode *head){
	tableNode *ptr = head;
	while(ptr != NULL){
		printf(" %s:%d ,externalFlag:%d",ptr->name,ptr->address,ptr->externalFlag);
		ptr = ptr->next;
	}
}
/* deleteTableList this method receive head of list and
remove list frees memory */
void deleteTableList(tableNode *head)
{
	tableNode *ptr = head;
	tableNode *next;
   while (ptr != NULL)
   {
       next = ptr->next;
       free(ptr);
       ptr = next;
}
   head = NULL;
}
/*findInTableList receive head of table and data
and search element in table if found return pointr to it
else return NULL*/
tableNode* findInTableList(tableNode* head,char data[])
{
    tableNode *ptr = head;
	while(ptr != NULL){
		if(strcmp(ptr->name,data) == 0)return ptr;
		ptr = ptr->next;
	}
	return NULL;
}
/*markAsEntry this method receive head and data and mark element as 
entry element */
void markAsEntry(tableNode* head,char data[]){
    tableNode *ptr = findInTableList(head,data);
    if(ptr == NULL){
        printf("line:%d, Error: cannot find label: %s\n",lineNum,data);
        errorMark = TRUE;
    }
    else ptr->entryFlag = 1;
}
/* markAsExternal this method receive head and data
and mark node as external */
void markAsExternal(tableNode* head,char data[]){
    tableNode *ptr = findInTableList(head,data);
    if(ptr == NULL){
        printf("line:%d, Error: cannot find label: %s\n",lineNum,data);
        errorMark = TRUE;
    }
    else ptr->externalFlag = 1;
}
/* updateDataByIc this method receive head and ic
and update nodes by IC value */
void updateDataByIc(tableNode *head,int IC){
    tableNode *ptr = head;
	while(ptr != NULL){
		if(ptr->commandOrData == DATA_FLAG)ptr->address+=IC;
		ptr = ptr->next;
	}
}
/*getTableNodeAddress this method receive head and data
and return address of node */
int getTableNodeAddress(tableNode *head,char data[]){
    tableNode *ptr;
    ptr = findInTableList(head,data);
    if(ptr == NULL){
        printf("line:%d , Error: cannot find label: %s\n",lineNum,data);
        errorMark = TRUE;
        return ERROR_CODE;
    }
    return ptr->address;
}
/*checkIfNodeIsExternal this method receive head and data
and checks if this node is external node*/
int checkIfNodeIsExternal(tableNode *head,char data[]){
    tableNode *ptr;
    ptr = findInTableList(head,data);
    if(ptr == NULL){
        printf("line:%d , Error: cannot find label: %s\n",lineNum,data);
        errorMark = TRUE;
    }
    else {
        return ptr->externalFlag;
    }
    return -1;
}
