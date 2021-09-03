#include "Adler32.h"

#define DO1(buf,i)  {adler += (buf)[i]; sum2 += adler;}
#define DO2(buf,i)  DO1(buf,i); DO1(buf,i+1);
#define DO4(buf,i)  DO2(buf,i); DO2(buf,i+2);
#define DO8(buf,i)  DO4(buf,i); DO4(buf,i+4);
#define DO16(buf)   DO8(buf,0); DO8(buf,8);

unsigned long Adler32::Calculate(unsigned long adler, const unsigned char* buf, unsigned int len)
{
    const unsigned int base = _base;
    const unsigned int nMax = _nMax;
    unsigned long sum2;
    unsigned n;

    /* split Adler-32 into component sums */
    sum2 = (adler >> 16) & 0xffff;
    adler &= 0xffff;

    /* in case user likes doing a byte at a time, keep it fast */
    if (len == 1)
    {
        adler += buf[0];
        if (adler >= base)
            adler -= base;
        sum2 += adler;
        if (sum2 >= base)
            sum2 -= base;
        return adler | (sum2 << 16);
    }

    /* initial Adler-32 value (deferred check for len == 1 speed) */
    if (buf == 0)
        return 1L;

    /* in case short lengths are provided, keep it somewhat fast */
    if (len < 16)
    {
        while (len--)
        {
            adler += *buf++;
            sum2 += adler;
        }
        if (adler >= base)
            adler -= base;
                   /* only added so many BASE's */

        sum2 %= base;

        return adler | (sum2 << 16);
    }

    /* do length NMAX blocks -- requires just one modulo operation */
    while (len >= nMax)
    {
        len -= nMax;
        n = nMax / 16;          /* NMAX is divisible by 16 */
        do
        {
            DO16(buf);          /* 16 sums unrolled */
            buf += 16;
        }
        while (--n);

        adler %= base;
        sum2 %= base;
    }

    /* do remaining bytes (less than NMAX, still just one modulo) */
    if (len)
    {                  /* avoid modulos if none remaining */
        while (len >= 16)
        {
            len -= 16;
            DO16(buf);
            buf += 16;
        }
        while (len--)
        {
            adler += *buf++;
            sum2 += adler;
        }

        adler %= base;
        sum2 %= base;
    }

    /* return recombined sums */
    return adler | (sum2 << 16);
}

unsigned long Adler32::Combine(unsigned long adler1, unsigned long adler2, __int64 len2)
{
    const unsigned int base = _base;
    unsigned long sum1;
    unsigned long sum2;
    unsigned rem;

    /* for negative len, return invalid adler32 as a clue for debugging */
    if (len2 < 0)
        return 0xffffffffUL;

    /* the derivation of this formula is left as an exercise for the reader */
              /* assumes len2 >= 0 */

    len2 %= _base;

    rem = (unsigned)len2;
    sum1 = adler1 & 0xffff;
    sum2 = rem * sum1;

    sum2 %= _base;

    sum1 += (adler2 & 0xffff) + base - 1;
    sum2 += ((adler1 >> 16) & 0xffff) + ((adler2 >> 16) & 0xffff) + base - rem;
    if (sum1 >= base) sum1 -= base;
    if (sum1 >= base) sum1 -= base;
    if (sum2 >= ((unsigned long)base << 1)) sum2 -= ((unsigned long)base << 1);
    if (sum2 >= base) sum2 -= base;
    return sum1 | (sum2 << 16);
}