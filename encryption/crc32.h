#ifndef STULIBC_CRC32_H
#define STULIBC_CRC32_H

#include <inttypes.h>
#include <stdio.h>
#include <string.h>

uint32_t crc32(uint32_t crc, const char *buf, size_t len);

#endif
