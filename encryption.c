#include "encryption.h"



long ENC_btea( long * v, long n , long * k )
{
    unsigned long z=v[n-1], y=v[0], sum=0,e,
    DELTA=0x9e3779b9 ;
    long m, p, q ;
    if ( n>1)
    {
        /* Coding Part */
        q = 6+52/n ;
        while ( q-- > 0 ) {
        sum += DELTA ;
        e = sum >> 2&3 ;
        for ( p = 0 ; p < n-1 ; p++ )
        y = v[p+1], z = v[p] += MX
        y = v[0] ;
        z = v[n-1] += MX
        }
        return 0 ;
    }
    else if ( n <-1 )
    {
        n = -n ;
        q = 6+52/n ;
        sum = q*DELTA ;
        while (sum != 0)
        {
            e = sum>>2 & 3 ;
            for (p = n-1 ; p > 0 ; p-- )
                z = v[p-1], y = v[p] -= MX
            z = v[n-1] ;
            y = v[0] -= MX
            sum -= DELTA ;
        }
        return 0 ;
    }
return 1 ;
} /* Signal n=0,1,-1 */
