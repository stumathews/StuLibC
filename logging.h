#ifndef STULIBC_LOGGING_H
#define STULIBC_LOGGING_H
#include <stdio.h>

int LOG_If(int condition_result, char* message, char* resultContext);
void LOG_It(char* message);
static void LOG(char* message, FILE* stream,char* context);

#endif // STULIBC_LOGGING_H
