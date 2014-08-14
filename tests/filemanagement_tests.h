#ifndef FILEMANAGEMENT_TESTS_H
#define FILEMANAGEMENT_TESTS_H

void test_FILE_GetFileSize()
{
	printf("%ld\n", FILE_GetFileSize("input.txt"));
	printf("%ld\n", FILE_GetFileSize("/input.txt"));
}
#endif
