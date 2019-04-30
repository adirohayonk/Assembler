/* Created by:adir ohayon
 * 
*/	
#include <stdio.h>
#include <stdlib.h>
#define MAX_SYMBOL_SIZE 30
typedef struct node {
	char data[MAX_SYMBOL_SIZE];
	struct node *next;
	int decimalValue;
}node;

node *head = NULL;
void addNewNode(char dat[],int decVal){
	if(head == NULL){
		head =malloc( sizeof(node));
		head->data = dat;
		head->decimalValue = decVal;
	}
	else {
		node *ptr = head;
		while(ptr->next != NULL){
			ptr = ptr->next;
		}
		node *new = malloc( sizeof(node));
		ptr->next = new;
		new->data = dat;
		new->decimalValue = decVal;
		new->next = NULL;
	}
}
void printList(){
	node *ptr = head;
	while(ptr != NULL){
		printf("symbol is:%c , value is:%d",ptr->data,ptr->decimalValue);
		ptr = ptr->next;
	}
}
void deleteList()
{
	node *ptr = head;
	node *next;
   while (ptr != NULL) 
   {
       next = ptr->next;
       free(ptr);
       ptr = next;
}
   head = NULL;
}
int main()
{
	char c;
	while (scanf("%c",&c) != EOF) {
		addNewNode(c);
	}
	printf("##########your input is########\n");
	printList();
	printf("##########end of your input##########\n");
	deleteList();
	return 0;
}
