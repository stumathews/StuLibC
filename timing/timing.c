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

int TIM_DayOfWeek( int year, int month, int day)
{
	int adjustment, mm, yy;

		adjustment = (14 - month) / 12;
		mm = month + 12 * adjustment - 2;
		yy = year - adjustment;
		return (day + (13 * mm - 1) / 5 +
			yy + yy / 4 - yy / 100 + yy / 400) % 7;
}
