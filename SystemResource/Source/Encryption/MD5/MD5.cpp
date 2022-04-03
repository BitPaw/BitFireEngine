#include "MD5.h"




/* ROTATE_LEFT rotates x left n bits.
*/
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

/* FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
Rotation is separate from addition to prevent recomputation.
 */
#define FF(a, b, c, d, x, s, ac) { \
 (a) += F ((b), (c), (d)) + (x) + (UINT4)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
   (a) += (b); \
  }
#define GG(a, b, c, d, x, s, ac) { \
 (a) += G ((b), (c), (d)) + (x) + (UINT4)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }
#define HH(a, b, c, d, x, s, ac) { \
 (a) += H ((b), (c), (d)) + (x) + (UINT4)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }
#define II(a, b, c, d, x, s, ac) { \
 (a) += I ((b), (c), (d)) + (x) + (UINT4)(ac); \
 (a) = ROTATE_LEFT ((a), (s)); \
 (a) += (b); \
  }



unsigned int BF::MD5::CalculatePerRoundShift(const unsigned int value)
{
  

    // s specifies the per-round shift amounts
    // s[0..15] : = { 7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22 }
    // s[16..31] : = { 5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20 }
    // s[32..47] : = { 4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23 }
    // s[48..63] : = { 6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21 }

    return 0;
}

size_t BF::MD5::Encrypt(const char* input, const size_t inputSize, char* output, const size_t outputSize)
{
    const size_t amountOfBlocks = (inputSize / MD5Length) + 1;
    const size_t needSize = amountOfBlocks * MD5Length;

    // Check size
    {
        bool isOutputBigEnough = needSize <= outputSize;

        if (!isOutputBigEnough)
        {
            return -1;
        }
    }

    size_t inputIndex = 0;
    size_t outputIndex = 0;


#if 0
    const unsigned char s[4][4] =
    {
        7, 12, 17, 22,
        5,  9, 14, 20,
        4, 11, 16, 23,
        6, 10, 15, 21
    };

#else
    const unsigned char s[] =
    {
        7, 12, 17, 22,
        7, 12, 17, 22,
        7, 12, 17, 22,
        7, 12, 17, 22,
        5,  9, 14, 20,
        5,  9, 14, 20,
        5,  9, 14, 20,
        5,  9, 14, 20,
        4, 11, 16, 23,
        4, 11, 16, 23,
        4, 11, 16, 23,
        4, 11, 16, 23,
        6, 10, 15, 21,
        6, 10, 15, 21,
        6, 10, 15, 21,
        6, 10, 15, 21
    };
#endif // 0


    // K[i] := floor(232 × abs (sin(i + 1)))
    const unsigned int K[64] // Acess with index % 4
    {
       0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, // [0.. 3] 
       0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, // [4.. 7]        
       0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, // [8..11]       
       0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, // [12..15]
       0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, // [16..19]       
       0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8, // [20..23]        
       0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, // [24..27]       
       0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a, // [28..31]        
       0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, // [32..35]       
       0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, // [36..39]        
       0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, // [40..43] 
       0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665, // [44..47]        
       0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, // [48..51] 
       0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1, // [52..55]       
       0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, // [56..59]
       0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391  // [60..63] 
    };

    output[0] = 0b10000000; // Add first bit
    for (size_t i = 1; i < MD5Length; i++) output[i] = 0; // Set whole string 0


    const size_t rowSize = 4u;
    unsigned int element[rowSize] =
    {
        0x67452301, // A
        0xefcdab89, // B
        0x98badcfe, // C
        0x10325476  // D
    };

    for (size_t i = 0; i < amountOfBlocks; i++) // 64-Bytes / 512-Bit
    {
        unsigned int M[16] = {}; //  break chunk into sixteen 32 - bit words M[j], 0 ? j ? 15
        
        // Initialize hash value for this chunk:
        unsigned int A = element[0];
        unsigned int B = element[1];
        unsigned int C = element[2];
        unsigned int D = element[3];

        // Main loop:
        for (size_t i = 0; i < 63; i++)
        {
            unsigned int F = -1;
            unsigned int g = -1;

            const unsigned char index = i / 16u;

            switch (index)
            {
                case 0: //  0 <= i <= 15
//#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
                    F = (B & C) | ((~B) & D); // (B and C) or ((not B) and D)
                    g = i;
                    break;

                case 1: // 16 <= i <= 31
//#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
                    F = (D & B) | ((~ D) & C); // (D and B) or ((not D) and C)
                    g = (5 * i + 1) % 16;
                    break;

                case 2: // 32 <= i <= 47
//#define H(x, y, z) ((x) ^ (y) ^ (z))
                    F = B ^ C ^ D; // B xor C xor D
                    g = (3 * i + 5) % 16;
                    break;

                    //#define I(x, y, z) ((y) ^ ((x) | (~z)))
                case 3: // 48 <= i <= 63
                    F = C ^ (B | (~D)); // C xor (B or (not D))
                    g = (7 * i) % 16;
                    break;
            }



            // Be wary of the below definitions of a,b,c,d
            F = F + A + K[i] + M[g];  // M[g] must be a 32-bits block
            A = D;
            D = C;
            C = B;

            {
                const unsigned int x = i % 4;
                const unsigned int y = i / 16;

                B = B + ROTATE_LEFT(F, s[i]);
            }          
        }
             
        // Add this chunk's hash to result so far:
        element[0] += A;
        element[1] += B;
        element[2] += C;
        element[3] += D;
    }
     
    for (size_t i = 0; i < rowSize; i++)
    {
        char* insertionPoint = output + outputIndex;
        unsigned int* insertValue = (unsigned int*)insertionPoint;

     
        unsigned int value = element[i];


       

#if 0
        (*insertValue) = value;
#else

        (*insertValue) = 
            (value & 0xFF000000) >> 24 |
            (value & 0x00FF0000) >> 8 |
            (value & 0x0000FF00) << 8  |
            (value & 0x000000FF) << 24;
#endif // 0



        outputIndex += sizeof(unsigned int);
    }

    return outputIndex;
}

size_t BF::MD5::Decrypt(const char* input, const size_t inputSize, char* output, const size_t outputSize)
{
    return false;
}
