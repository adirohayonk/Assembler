
#ifndef LISTS_H_INCLUDED
#define LISTS_H_INCLUDED
#define MAX_LABEL_SIZE 30
/* this struct hold table node flag to mark external and entry
address and if table data is data or command */
typedef struct tableNode{
    char name[MAX_LABEL_SIZE];
	int address;
	int entryFlag;
	int externalFlag;
	int commandOrData;
	struct tableNode *next;
}tableNode;
/* this method receive head and relevant data and store in list and reurn head*/
tableNode* addNewTableNode(tableNode *head, char dat[],int addr,int comandOrDat);
/* this method recive head node and print list for debuging */
void printTableList(tableNode *head);
/* this method receive head and delete list free memory */
void deleteTableList(tableNode *head);
/* this method receive head and data and find element in list */
tableNode* findInTableList(tableNode* head,char data[]);
/* this method receive head and data and mark node as entry */
void markAsEntry(tableNode* head,char data[]);
/* this method receive head and data and mark node ad external */
void markAsExternal(tableNode* head,char data[]);
/* this method receive head and ic and update node by this ic */
void updateDataByIc(tableNode *head,int IC);
/* this method receive head and data find node address and return it */
int getTableNodeAddress(tableNode *head,char data[]);
/* this method receive head and data and check if node is external*/
int checkIfNodeIsExternal(tableNode *head,char data[]);
#endif /* LISTS_H_INCLUDED*/
