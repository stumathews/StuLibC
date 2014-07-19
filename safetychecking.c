#include "safetychecking.h"
#define MAX_LOG_LINE_LENGTH 80

static char* safetyfile = "safety.txt";

void CHK_ResultExitIf(void* result, int condition)
{
    if(condition){
        FILE_AppendText("Check_ResultIf not implemented yet", safetyfile);
        exit(1);
    }
}
void CHK_ResultLogIf(void* result,int condition)
{
    if(condition)
            FILE_AppendText("Check_ResultIf not implemented yet", safetyfile);
}
void CHK_ResultLog(void* result, char* functionName,int lineNumber)
{
    char buffer[MAX_LOG_LINE_LENGTH];
    sprintf(buffer,"%s line: %d Check_ResultIf not implemented yet\n",functionName, lineNumber);
    FILE_AppendText( buffer, safetyfile);
}
