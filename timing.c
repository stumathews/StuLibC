#include "timing.h"

char* TM_GetDate(enum DateType type)
{
    struct tm* theTime = localtime(NULL);

}
char* TM_GetTime(enum TimeType type)
{
    struct tm* theTime = localtime(NULL);
}

char* TM_GetDateTimeStr()
{
    time_t rawtime;
    struct tm* timeinfo;
    const size_t buf_size = 130;
    char buffer[buf_size];

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    if(strftime(buffer,buf_size,"%x/%Y %X", timeinfo))
        return buffer;
    else return "unable to obtain date";
}
