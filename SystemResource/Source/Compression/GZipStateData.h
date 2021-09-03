#pragma once

#include "GZipFile.h"

/* internal gzip file state data structure */
struct GZipStateData
{
    public:
    GZipFile File;      
    int mode;               /* see gzip modes above */
    int fd;                 /* file descriptor */
    char* path;             /* path or fd for error messages */
    unsigned int size;          /* buffer size, zero if not allocated yet */
    unsigned int want;          /* requested buffer size, default is GZBUFSIZE */
    unsigned char* in;      /* input buffer (double-sized when writing) */
    unsigned char* out;     /* output buffer (double-sized when reading) */
    int direct;             /* 0 if processing gzip, 1 if transparent */
        /* just for reading */
    int how;                /* 0: get header, 1: copy, 2: decompress */
    __int64 start;        /* where the gzip data started, for rewinding */
    int eof;                /* true if end of input file reached */
    int past;               /* true if read requested past end */
        /* just for writing */
    int level;              /* compression level */
    int strategy;           /* compression strategy */
        /* seek request */
    __int64 skip;         /* amount to skip (already rewound if backwards) */
    int seek;               /* true if seek request pending */
        /* error information */
    int err;                /* error code */
    char* msg;              /* error message */
        /* zlib inflate or deflate stream */
    ZLibStream strm;          /* stream structure in-place (not a pointer) */



    void  gz_error( int, const char*);
    int gz_load( unsigned char*, unsigned int, unsigned int *);
    int gz_avail();
    int gz_look();
    int gz_decomp();
    int gz_fetch();
    int gz_skip( __int64);
    unsigned int gz_read( void*, unsigned int);
    void gz_reset();
    int gz_init();
    int gz_comp( int);
    int gz_zero( __int64);
    unsigned int gz_write( void const*, unsigned int);

};
