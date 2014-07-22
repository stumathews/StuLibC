/**
 * @file encryption.h
 * @brief Encryption library prototypes.
 * @author Stuart Mathews
 * @date 19 July 2013
 *
 * This header contains the function and type declarations for dealing with encryption functionality in the library.
 * This includes encrypting and decrypting simple text to more advanced encryption.
 * @see http://devel.stuartmathews.com/stulibc
 */

#ifndef STULIBC_ENCRYPTION_H
#define STULIBC_ENCRYPTION_H
#include <stdint.h>
#define DELTA 0x9e3779b9
#define MX (((z>>5^y<<2) + (y>>3^z<<4)) ^ ((sum^y) + (key[(p&3)^e] ^ z)))

/** @brief Corrected Block TEA (often referred to as XXTEA) is a block cipher.
   * The cipher's designers were Roger Needham and David Wheeler of the Cambridge Computer Laboratory.
   * This is the precursor to the previous XTEA algorithm implementation by the same authors.
   * @param v uint32_t* is the n word data vector
   * @param n int is negative for decoding
   * @param key[4] uint32_t const is the 4 word key
   * @return void
   * @remarks if n is zero result is 1 and no coding or decoding takes place, otherwise the result is zero.assumes 32 bit 'long' and same endian coding and decoding
   */
void btea(uint32_t *v, int n, uint32_t const key[4]);

#endif // STULIBC_ENCRYPTION_H
