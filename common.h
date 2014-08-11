
#ifndef STULIBC_COMMON_H
#define STULIBC_COMMON_H

#ifdef _WIN32
#define LIBRARY_API __declspec(dllexport)
#else
#define LIBRARY_API
#endif

#endif // STULIBC_STRING_H


