/* created by :Adir Ohayon
 * 
 * errorControl header file
 */
#ifndef ERROR_H_INCLUDED
#define ERROR_H_INCLUDED
#define TOP_ASCII_CODE_FOR_NUMBERS 57
#define BUTTOM_ASCII_CODE_FOR_NUMBERS 48
#define TOP_ASCII_CODE_FOR_CAPITAL_LETTERS 90
#define BUTTOM_ASCII_CODE_FOR_CAPITAL_LETTERS 65
#define TOP_ASCII_CODE_FOR_LOWER_CASE_LETTERS 122
#define BUTTOM_ASCII_CODE_FOR_LOWER_CASE_LETTERS 97
/*receive char and check.if its char or num */
int isCharAndNum(char ch);
/* receive word and check if its saved word */
int isSavedWords(char *word);
/* receive word and check if its correct register */
int isCorrectRegister(char *word);
/* receive word and check if its correct number */
int isCorrectNumber(char *word);
/* receive word and check if its correct matrix */
int isCorrectMatrix(char *word);
/* receive label and check if correct label error flag 1 print errors 0 not*/
int isCorrectLabel(char *label,int errorsFlag);
/* receive parameter and check if its correct parameter from method above */
int isCorrectParameter(char *parameter);
/* receive group one command and check for correctness */
int checkNoParametersCommands(char *command,char *parameters);
/* receive group two command and check for correctness */
int checkOneParametersCommands(char *command,char *parameter);
/* receive group three command and check for correctness */
int checkTwoParametersCommands(char *command,char *parameter1,char *parameter2);
/* receive data parameters and check for correctness */
int checkDataCommand(char *parameters,int errorsFlag);
/* receive string and returns length */
int getStringLength(char *str);
/* receive string parameter and check correctness */
int checkStringCommand(char *parameters);
/* receive .mat parameter and check correctness */
int checkMatCommand(char *parameters);
#endif /* ERROR_H_INCLUDED */
