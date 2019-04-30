/* created by :Adir Ohayon
 * 
 * memory header file
 */
#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED
#define MAX_WORD_SIZE 30
/* struct represent memory node store value,address,and pointer 
to next node */
typedef struct memNode{
	int memoryValue;
	int address;
	struct memNode *next;
}memNode;
/* receive head and memory values and insert byincreasing value */
memNode* addNewMemNode(memNode *head, int value,int addr);
/* receive head and print liat for debugging */
void printMemoryList(memNode *head);
/* receive head and delete list frees memory */
void deleteMemoryList(memNode *head);
/* receive head and value and find node in list */
memNode* findInMemoryList(memNode* head,int value);
/* receive head and ic and update node by ic */
void updatMemoryByIc(memNode *head,int IC);
#endif /* MEMORY_H_INCLUDED*/
