#pragma once

#include "InflateMode.h"
#include "GZipHeader.h"
#include "HuffCode.h"
#include "StateData.h"

struct InflateStateData : public StateData
{
    
    InflateMode mode;          // current inflate mode
    GZipHeader* head;            // where to save gzip header information 

    int last;                   // true if processing last block 
    int havedict;               // true if dictionary provided
    int flags;                  // gzip header method and flags (0 if zlib)
    unsigned int dmax;              // zlib header max distance (INFLATE_STRICT)
    unsigned long check;        // protected copy of check value 
    unsigned long total;        // protected copy of output count 

        // sliding window 
    unsigned int wbits;             // log base 2 of requested window size 
    unsigned int wsize;             // window size or zero if not using window 
    unsigned int whave;             // valid bytes in the window 
    unsigned int wnext;             // window write index 
    
        /* bit accumulator */
    unsigned long hold;         /* input bit accumulator */
    unsigned int bits;              /* number of bits in "in" */
        /* for string and stored block copying */
    unsigned int length;            /* literal or length of data to copy */
    unsigned int offset;            /* distance back to copy string from */
        /* for table and code decoding */
    unsigned extra;             /* extra bits needed */
        /* fixed and dynamic code tables */
    HuffCode const* lencode;    /* starting table for length/literal codes */
    HuffCode const* distcode;   /* starting table for distance codes */
    unsigned int lenbits;           /* index bits for lencode */
    unsigned int distbits;          /* index bits for distcode */
        /* dynamic table building */
    unsigned int ncode;             /* number of code length code lengths */
    unsigned int nlen;              /* number of length code lengths */
    unsigned int ndist;             /* number of distance code lengths */
    unsigned int have;              /* number of code lengths in lens[] */
    HuffCode* next;             /* next available space in codes[] */
    unsigned short lens[320];   /* temporary storage for code lengths */
    unsigned short work[288];   /* work area for code table building */
    HuffCode codes[ENOUGH];         /* space for code tables */
    int sane;                   /* if false, allow invalid distance too far */
    int back;                   /* bits back of last unprocessed length/lit */
    unsigned int was;               /* initial length of match */


    InflateStateData();
    void fixedtables();
};