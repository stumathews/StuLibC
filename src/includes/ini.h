#ifndef INI_H
#define INI_H

#include <constants.h>
#include <list.h>
#include <iniscanner.h>

/**
 * Fetches all the settings from a well formed .ini file.
 * @param filename
 * @param settings
 * @return non-negative integer on success or negative integer otherwise
 */
LIBRARY_API int INI_IniParse(const char* filename, List* settings);

/**
 * Gets a specific setting within the list of settings
 * @param settings list of settings captured by parsing the .ini file
 * @param section the section you want to get a setting from
 * @param setting the name of the setting to get
 * @return char* value: the string value of the setting found or null if not found
 */
LIBRARY_API char* INI_GetSetting(List* settings, char* section, char* setting);

#endif /* INI_H_ */
