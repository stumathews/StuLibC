#include "timing.h"
#include <time.h>

#define buf_size 80


clock_t TIME_StartCPURecord()
{
  return clock();
}

clock_t TIME_StopCPURecord(clock_t startTime)
{
  return TIME_GetCPUTimeTakenInSeconds( startTime, TIME_StartCPURecord());
}

clock_t TIME_GetCPUTimeTakenInSeconds(clock_t startTime, clock_t endTime)
{
  return (endTime - startTime) / CLOCKS_PER_SEC;
}

clock_t TIME_GetCPUTimeTakenInUnits(clock_t startTime, clock_t endTime)
{
  return endTime - startTime;
}

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
