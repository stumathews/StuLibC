#ifndef KBD_C_INCLUDED
#define KBD_C_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define BUFFER_INCREMENT 3

int kbd_GetLine(char* buf)
{
	int c;	
	buf = (char*) calloc( sizeof(char) * BUFFER_INCREMENT, BUFFER_INCREMENT );

	if( buf == NULL )
		return 0;
	int bufSize = BUFFER_INCREMENT;
	printf("bufsize:%d",bufSize);
	int chars_read = 0;
	
	while( (c = getchar()) != EOF && (c != '\n') && (chars_read < bufSize) )
		buf[chars_read++] = c;    
	buf[chars_read] = '\0';
	return chars_read;
}

#endif // SCREEN_C_INCLUDED
