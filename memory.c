/* Created by:adir ohayon
 * 
 * memory contains functions and linked list data structure to represent 
 * assembler memory
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory.h"
/* addNewMemNode this method add memory node by address order
input: head of the list, value, and address
return head of changed list */
memNode* addNewMemNode(memNode *head, int value,int addr){
	memNode *new;
	memNode *ptr;
	memNode *prev;
	/* if list is empty create first node and points head to it */
	if(head == NULL){
		head = malloc( sizeof(memNode));
		head->memoryValue = value;
        head->address = addr;
		return head;
	}
	/* if list is no empty find correct location by size and insert it */
	else {
        ptr = head;
		prev = head;
        new = malloc( sizeof(memNode));
        new->memoryValue = value;
		new->address = addr;
		/* if new node is smaller than head store before */
		if(ptr->address > addr){
            new->next = head;
            return new;
		}
		/* while end of list not reached */
		while(ptr->next != NULL){
		/* if node is smaller than next and bigger than prev storwle between */ 
            if(ptr->address > addr){
                prev->next = new;
                new ->next = ptr;
                return head;
            }
            prev = ptr;
			ptr = ptr->next;
		}
		/*if smaller than last insert before */
		if(ptr->address > addr){
            prev->next = new;
            new ->next = ptr;
            return head;
		}
		/* if node is biggest store as last */
		ptr->next = new;
		return head;
	}
}
/* printMemoryList this method print list elements address and value
input:head of list to be printed */
void printMemoryList(memNode *head){
	memNode *ptr = head;
	while(ptr != NULL){
		printf(" [%d] = %d ",ptr->address,ptr->memoryValue);
		ptr = ptr->next;
	}
}
/*deleteMemoryList this method frees all list memory
input:head of list to be removed */
void deleteMemoryList(memNode *head)
{
	memNode *ptr = head;
	memNode *next;
   while (ptr != NULL)
   {
       next = ptr->next;
       free(ptr);
       ptr = next;
}
   head = NULL;
}
/*findInMemoryList this method receive head node and value find it in list
and reture ptr to this node if not found return NULL */
memNode* findInMemoryList(memNode* head,int value)
{
    memNode *ptr = head;
	while(ptr != NULL){
		if(head->memoryValue == value)return ptr;
		ptr = ptr->next;
	}
	return NULL;
}
/*updatMemoryByIc receive head to list and ic value
 increase all memory nodes by ic value */
void updatMemoryByIc(memNode *head,int IC){
    memNode *ptr = head;
	while(ptr != NULL){
		ptr->address+=IC;
		ptr = ptr->next;
	}
}

