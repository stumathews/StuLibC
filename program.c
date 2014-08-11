#include "screen.h"

int main(int argc, char**argv)
{
	char[80] buffer;
	scr_GetLine(buffer);
	puts(buffer);
	return 0;
}
