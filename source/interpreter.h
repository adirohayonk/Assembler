/* created by : Adir Ohayon
 * 
 * interpreter header file
 */
#ifndef INTERPRETER_H_INCLUDED
#define INTERPRETER_H_INCLUDED
/* receive .string parameters decode and store in memory */
void decodeString(char *params);
/* receive .data parameters decode and store in memory */
void decodeData(char *params);
/* receive .mat parameters decode and store in memory */
void decodeMatrix(char *params);
/* receive .ectern parameters decode and store in memory */
void decodeExtern(char *params);
/* receive .entry parameters decode and store in memory */
void decodeEntry(char *params);
/* receive command,parameters,ans pass num find command group and pass to group function */
void decodeCommand(char *command,char *params,int passOneOrTwo);
/* receive second group command and decode it to memory */
void decodeSecondGroupCommands(char *command,int commandCode,char *params,int passOneOrTwo);
/* receive first group command and decode it to memory */
void decodeFirstGroupCommands(char *command,int commandCode,char *params,int passOneOrTwo);
/* receive third group command and decode it to memory */
void decodeThirdGroupCommands(char *command,int commandCode,int passOneOrTwo);
#endif /* INTERPRETER_H_INCLUDED*/
