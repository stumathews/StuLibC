/* Known to compile and work with tcc in win32 & gcc on Linux (with warnings)
------------------------------------------------------------------------------
readable.c: My random number generator, ISAAC.
(c) Bob Jenkins, March 1996, Public Domain
You may use this code in any way you wish, and it is free.  No warrantee.
------------------------------------------------------------------------------
*/
#include <stdio.h>
#include <stddef.h>

/* if (flag!=0), then use the contents of randrsl[] to initialize mm[]. */
#define mix(a,b,c,d,e,f,g,h) \
{ \
   a^=b<<11; d+=a; b+=c; \
   b^=c>>2;  e+=b; c+=d; \
   c^=d<<8;  f+=c; d+=e; \
   d^=e>>16; g+=d; e+=f; \
   e^=f<<10; h+=e; f+=g; \
   f^=g>>4;  a+=f; g+=h; \
   g^=h<<8;  b+=g; h+=a; \
   h^=a>>9;  c+=h; a+=b; \
}

// maximum length of message
#define MAXMSG 256

/* a ub4 is an unsigned 4-byte quantity */
typedef  unsigned long int  ub4;

/* external results */
ub4 randrsl[256], randcnt;

/* internal state */
static    ub4 mm[256];
static    ub4 aa=0, bb=0, cc=0;

void isaac();
void randinit(int flag);
ub4 iRandom();
char iRandA();
// Seed ISAAC with a string
void iSeed(char *seed, int flag);
// XOR encrypt on random stream. Output: ASCII string
char* Vernam(char *msg);


