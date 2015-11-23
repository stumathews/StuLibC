#ifndef INI_H
#define INI_H

#include <constants.h>
#include <list.h>

LIBRARY_API void INI_IniParse(const char* filename, List* settings);

#endif /* INI_H_ */
