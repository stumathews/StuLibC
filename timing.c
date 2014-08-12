#include "timing.h"

#define buf_size 80
char* TIM_GetDateTimeStr()
{
    time_t rawtime;
    struct tm* timeinfo;

    static char buffer[buf_size]; // This needs to be a static

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    if(strftime(buffer,buf_size,"%x/%Y %X", timeinfo))
        return buffer;
    else return "unable to obtain date";
}
