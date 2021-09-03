#pragma once
#include "ZLibStream.h"

#  define BYFOUR
#  define TBLS 8

#define CRCDO1 crc = CRC32::Table[0][((int)crc ^ (*buf++)) & 0xff] ^ (crc >> 8)
#define CRCDO8 CRCDO1; CRCDO1; CRCDO1; CRCDO1; CRCDO1; CRCDO1; CRCDO1; CRCDO1


#define GF2_DIM 32      /* dimension of GF(2) vectors (length of CRC) */
/* ========================================================================= */
#define DOLIT4 c ^= *buf4++; \
        c = CRC32::Table[3][c & 0xff] ^ CRC32::Table[2][(c >> 8) & 0xff] ^ \
            CRC32::Table[1][(c >> 16) & 0xff] ^ CRC32::Table[0][c >> 24]
#define DOLIT32 DOLIT4; DOLIT4; DOLIT4; DOLIT4; DOLIT4; DOLIT4; DOLIT4; DOLIT4


/* ========================================================================= */
#define DOBIG4 c ^= *buf4++; \
        c = CRC32::Table[4][c & 0xff] ^ CRC32::Table[5][(c >> 8) & 0xff] ^ \
            CRC32::Table[6][(c >> 16) & 0xff] ^ CRC32::Table[7][c >> 24]
#define DOBIG32 DOBIG4; DOBIG4; DOBIG4; DOBIG4; DOBIG4; DOBIG4; DOBIG4; DOBIG4

struct CRC32
{
    static const z_crc_t  Table[TBLS][256];

    static unsigned long Calculate(unsigned long crc, const unsigned char* buf, unsigned int len);
    static unsigned long Combine(unsigned long crc1, unsigned long crc2, __int64 len2);

    static unsigned long Little(unsigned long crc, const unsigned char* buf, unsigned int  len);
    static unsigned long Big(unsigned long  crc, const unsigned char* buf, unsigned int len);

    static unsigned long MatrixTime(unsigned long* mat, unsigned long vec);
    static void MatrixSquare(unsigned long* square, unsigned long* mat);
};