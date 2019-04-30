/* created by :Adir Ohayon
 * 
 * analyzer header file
 */
#ifndef ANALYZER_H_INCLUDED
#define ANALYZER_H_INCLUDED
/* method receive string and char and return char index*/
int findCharInString(char *string,char ch);
/* method receive string, index and number of letters and return substr */
char * subStr(char *string,int start,int end);
/*method receive parameter and returns its type */
int checkParameterType(char *parameter);
/* method recieve filename and creates new filename with extension provided*/
char * getNameWithExtension(char *filename,char *extension);
#endif /* ANALYZER_H_INCLUDED */
