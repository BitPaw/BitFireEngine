#pragma once

#include "GZipHeader.h"
#include "DeflateStateData.h"
#include "InflateStateData.h"
#include <vcruntime_string.h>

#ifndef NO_GZIP
#  define GUNZIP
#endif


#define HAVE_MEMCPY

#define ZLIB_VERSION "1.2.11"
#define ZLIB_VERNUM 0x12b0
#define ZLIB_VER_MAJOR 1
#define ZLIB_VER_MINOR 2
#define ZLIB_VER_REVISION 11
#define ZLIB_VER_SUBREVISION 0   

#define Z_OK            0
#define Z_STREAM_END    1
#define Z_NEED_DICT     2
#define Z_ERRNO        (-1)
#define Z_STREAM_ERROR (-2)
#define Z_DATA_ERROR   (-3)
#define Z_MEM_ERROR    (-4)
#define Z_BUF_ERROR    (-5)
#define Z_VERSION_ERROR (-6)

#define Z_NO_COMPRESSION         0
#define Z_BEST_SPEED             1
#define Z_BEST_COMPRESSION       9
#define Z_DEFAULT_COMPRESSION  (-1) /* compression levels */

#define Z_FILTERED            1
#define Z_HUFFMAN_ONLY        2
#define Z_RLE                 3
#define Z_FIXED               4
#define Z_DEFAULT_STRATEGY    0/* compression strategy; see deflateInit2() below for details */

#define Z_BINARY   0
#define Z_TEXT     1
#define Z_ASCII    Z_TEXT   /* for compatibility with 1.2.2 and earlier */
#define Z_UNKNOWN  2/* Possible values of the data_type field for deflate() */

#define Z_DEFLATED   8/* The deflate compression method (the only one supported in this version) */

#define zlib_version zlibVersion()/* for compatibility with versions < 1.0.2 */


extern const char* zlibVersion (void);
extern unsigned long   zlibCompileFlags (void);

#ifdef Z_PREFIX_SET
#else
#  define deflateInit(__strm, level)                                          (__strm)->deflateInit_((level), ZLIB_VERSION, (int)sizeof(ZLibStream))
#  define inflateInit(__strm)                                                 (__strm)->inflateInit_(ZLIB_VERSION, (int)sizeof(ZLibStream))
#  define deflateInit2(__strm, level, method, windowBits, memLevel, strategy) (__strm)->deflateInit2_((level),(method),(windowBits),(memLevel),                        (strategy), ZLIB_VERSION, (int)sizeof(ZLibStream))
#  define inflateInit2(__strm, windowBits)                                    (__strm)->inflateInit2_((windowBits), ZLIB_VERSION,                         (int)sizeof(ZLibStream))
#  define inflateBackInit(__strm, windowBits, window)                         (__strm)->inflateBackInit_((windowBits), (window),                          ZLIB_VERSION, (int)sizeof(ZLibStream))
#endif










#if defined(STDC) && !defined(Z_SOLO)
#  if !(defined(_WIN32_WCE) && defined(_MSC_VER))
#    include <stddef.h>
#  endif
#  include <string.h>
#  include <stdlib.h>
#endif


extern  char* const z_errmsg[10]; /* indexed by 2-zlib_error */
/* (size given to avoid silly warnings with Visual C++) */

#define ERR_MSG(err) z_errmsg[Z_NEED_DICT-(err)]
#define ERR_RETURN(strm,err)   return (strm->msg = ERR_MSG(err), (err))


#ifndef DEF_WBITS
#  define DEF_WBITS MAX_WBITS
#endif
/* default windowBits for decompression. MAX_WBITS is for compression only */

#if MAX_MEM_LEVEL >= 8
#  define DEF_MEM_LEVEL 8
#else
#  define DEF_MEM_LEVEL  MAX_MEM_LEVEL
#endif
/* default memLevel */

#define STORED_BLOCK 0
#define STATIC_TREES 1
#define DYN_TREES    2
/* The three kinds of block type */



#define PRESET_DICT 0x20 /* preset dictionary flag in zlib header */

        /* target dependencies */



extern unsigned syncsearch(unsigned* have, const unsigned char* buf, unsigned len);













#if defined(WIN32) && !defined(__CYGWIN__)
#  define OS_CODE  10
#endif


#if (defined(_MSC_VER) && (_MSC_VER > 600)) && !defined __INTERIX
#  if defined(_WIN32_WCE)
#    define fdopen(fd,mode) NULL /* No fdopen() */
#    ifndef _PTRDIFF_T_DEFINED
typedef int ptrdiff_t;
#      define _PTRDIFF_T_DEFINED
#    endif
#  else
#    define fdopen(fd,type)  _fdopen(fd,type)
#  endif
#endif


/* provide prototypes for these when building zlib without LFS */
#if !defined(_WIN32) && \
    (!defined(_LARGEFILE64_SOURCE) || _LFS64_LARGEFILE-0 == 0)
extern unsigned long   adler32_combine64 OF((unsigned long, unsigned long, long));
extern unsigned long   crc32_combine64 OF((unsigned long, unsigned long, long));
#endif

/* common defaults */

#ifndef OS_CODE
#  define OS_CODE  3     /* assume Unix */
#endif

#ifndef F_OPEN
#  define F_OPEN(name, mode) fopen((name), (mode))
#endif

         /* functions */

#if defined(pyr) || defined(Z_SOLO)
#  define NO_MEMCPY
#endif
#if defined(SMALL_MEDIUM) && !defined(_MSC_VER) && !defined(__SC__)
 /* Use our own functions for small and medium model with MSC <= 5.0.
  * You may have to use the same strategy for Borland C (untested).
  * The __SC__ check is for Symantec.
  */
#  define NO_MEMCPY
#endif
#if defined(STDC) && !defined(HAVE_MEMCPY) && !defined(NO_MEMCPY)
#  define HAVE_MEMCPY
#endif
#ifdef HAVE_MEMCPY
#  ifdef SMALL_MEDIUM /* MSDOS small or medium model */
#    define memcpy _fmemcpy
#    define memcmp _fmemcmp
#    define zmemzero(dest, len) _fmemset(dest, 0, len)
#  else
#    define zmemzero(dest, len) memset(dest, 0, len)
#  endif
#else
void  memcpy (unsigned char* dest, const unsigned char* source, unsigned int len);
int  memcmp (const unsigned char* s1, const unsigned char* s2, unsigned int len);
void  zmemzero (unsigned char* dest, unsigned int len);
#endif

/* Diagnostic functions */
#ifdef ZLIB_DEBUG
#  include <stdio.h>
extern int  z_verbose;
extern void  z_error OF((char* m));
#  define Assert(cond,msg) {if(!(cond)) z_error(msg);}
#  define Trace(File) {if (z_verbose>=0) fprintf File ;}
#  define Tracev(File) {if (z_verbose>0) fprintf File ;}
#  define Tracevv(File) {if (z_verbose>1) fprintf File ;}
#  define Tracec(c,File) {if (z_verbose>0 && (c)) fprintf File ;}
#  define Tracecv(c,File) {if (z_verbose>1 && (c)) fprintf File ;}
#else
#  define Assert(cond,msg)
#  define Trace(File)
#  define Tracev(File)
#  define Tracevv(File)
#  define Tracec(c,File)
#  define Tracecv(c,File)
#endif

#ifndef Z_SOLO
void* zcalloc (void* opaque, unsigned items, unsigned size);
void  zcfree  (void* opaque, void* ptr);
#endif

#define ZALLOC(strm, items, size)          (*((strm)->zalloc))((strm)->opaque, (items), (size))
#define ZFREE(strm, addr)  (*((strm)->zfree))((strm)->opaque, (void*)(addr))
#define TRY_FREE(s, p) {if (p) ZFREE(s, p);}

/* Reverse the bytes in a 32-bit value */
#define ZSWAP32(q) ((((q) >> 24) & 0xff) + (((q) >> 8) & 0xff00) + (((q) & 0xff00) << 8) + (((q) & 0xff) << 24))






















#  define STDC


#ifdef Z_SOLO
typedef unsigned long unsigned int;
#else
#  define z_longlong long long
#  if defined(NO_SIZE_T)
typedef unsigned NO_SIZE_T unsigned int;
#  elif defined(STDC)
#    include <stddef.h>
#  else
typedef unsigned long unsigned int;
#  endif
#  undef z_longlong
#endif

/* Maximum value for memLevel in deflateInit2 */
#ifndef MAX_MEM_LEVEL
#  ifdef MAXSEG_64K
#    define MAX_MEM_LEVEL 8
#  else
#    define MAX_MEM_LEVEL 9
#  endif
#endif

/* Maximum value for windowBits in deflateInit2 and inflateInit2.
 * WARNING: reducing MAX_WBITS makes minigzip unable to extract .gz files
 * created by gzip. (Files created by minigzip can still be extracted by
 * gzip.)
 */
#ifndef MAX_WBITS
#  define MAX_WBITS   15 /* 32K LZ77 window */
#endif

 /* The memory requirements for deflate are (in bytes):
             (1 << (windowBits+2)) +  (1 << (memLevel+9))
  that is: 128K for windowBits=15  +  128K for memLevel = 8  (default values)
  plus a few kilobytes for small objects. For example, if you want to reduce
  the default memory requirements from 256K to 128K, compile with
      make CFLAGS="-O -DMAX_WBITS=14 -DMAX_MEM_LEVEL=7"
  Of course this will generally degrade compression (there's no free lunch).

    The memory requirements for inflate are (in bytes) 1 << windowBits
  that is, 32K for windowBits=15 (default value) plus about 7 kilobytes
  for small objects.
 */

 /* Type declarations */

#ifndef OF /* function prototypes */
#  ifdef STDC
#    define OF(args)  args
#  else
#    define OF(args)  ()
#  endif
#endif

#ifndef Z_ARG /* function prototypes for stdarg */
#  if defined(STDC) || defined(Z_HAVE_STDARG_H)
#    define Z_ARG(args)  args
#  else
#    define Z_ARG(args)  ()
#  endif
#endif


#if !defined(Z_U4) && !defined(Z_SOLO) && defined(STDC)
#  include <limits.h>
#  if (UINT_MAX == 0xffffffffUL)
#    define Z_U4 unsigned
#  elif (ULONG_MAX == 0xffffffffUL)
#    define Z_U4 unsigned long
#  elif (USHRT_MAX == 0xffffffffUL)
#    define Z_U4 unsigned short
#  endif
#endif

#ifdef Z_U4
typedef Z_U4 z_crc_t;
#else
typedef unsigned long z_crc_t;
#endif

#ifdef HAVE_UNISTD_H    /* may be set to #if 1 by ./configure */
#  define Z_HAVE_UNISTD_H
#endif

#ifdef HAVE_STDARG_H    /* may be set to #if 1 by ./configure */
#  define Z_HAVE_STDARG_H
#endif

#ifdef STDC
#  ifndef Z_SOLO
#    include <sys/types.h>      /* for off_t */
#  endif
#endif

#if defined(STDC) || defined(Z_HAVE_STDARG_H)
#  ifndef Z_SOLO
#    include <stdarg.h>         /* for va_list */
#  endif
#endif

#ifdef _WIN32
#  ifndef Z_SOLO
#    include <stddef.h>         /* for wchar_t */
#  endif
#endif


#if !defined(SEEK_SET) && !defined(Z_SOLO)
#  define SEEK_SET        0       /* Seek from beginning of file.  */
#  define SEEK_CUR        1       /* Seek from current position.  */
#  define SEEK_END        2       /* Set file pointer to EOF plus "offset" */
#endif





















/* undocumented functions */
extern const char* zError(int);
extern const z_crc_t* get_crc_table(void);




















#ifdef GUNZIP
#  define UPDATE(check, buf, len) \
    (InflateState->flags ? CRC32::Calculate(check, buf, len) : Adler32::Calculate(check, buf, len))
#else
#  define UPDATE(check, buf, len) adler32(check, buf, len)
#endif

/* check macros for header crc */
#ifdef GUNZIP
#  define CRC2(check, word) \
    do { \
        hbuf[0] = (unsigned char)(word); \
        hbuf[1] = (unsigned char)((word) >> 8); \
        check = CRC32::Calculate(check, hbuf, 2); \
    } while (0)

#  define CRC4(check, word) \
    do { \
        hbuf[0] = (unsigned char)(word); \
        hbuf[1] = (unsigned char)((word) >> 8); \
        hbuf[2] = (unsigned char)((word) >> 16); \
        hbuf[3] = (unsigned char)((word) >> 24); \
        check = CRC32::Calculate(check, hbuf, 4); \
    } while (0)
#endif

/* Load registers with state in inflate() for speed */
#define LOAD() \
    do { \
        put = next_out; \
        left = avail_out; \
        next = next_in; \
        have = avail_in; \
        hold = InflateState->hold; \
        bits = InflateState->bits; \
    } while (0)

/* Restore state from registers in inflate() */
#define RESTORE() \
    do { \
        next_out = put; \
        avail_out = left; \
        next_in = next; \
        avail_in = have; \
        InflateState->hold = hold; \
        InflateState->bits = bits; \
    } while (0)

/* Clear the input bit accumulator */
#define INITBITS() \
    do { \
        hold = 0; \
        bits = 0; \
    } while (0)

/* Get a byte of input into the bit accumulator, or return from inflate()
   if there is no input available. */
#define PULLBYTE() \
    do { \
        if (have == 0) goto inf_leave; \
        have--; \
        hold += (unsigned long)(*next++) << bits; \
        bits += 8; \
    } while (0)

      /* Return the low n bits of the bit accumulator (n < 16) */
#define BITS(n) ((unsigned)hold & ((1U << (n)) - 1))

/* Remove n bits from the bit accumulator */
#define DROPBITS(n) \
    do { \
        hold >>= (n); \
        bits -= (unsigned)(n); \
    } while (0)

/* Remove zero to seven bits as needed to go to a byte boundary */
#define BYTEBITS() \
    do { \
        hold >>= bits & 7; \
        bits -= bits & 7; \
    } while (0)

/* Assure that some input is available.  If input is requested, but denied,
   then return a Z_BUF_ERROR from inflateBack(). */
#define PULL() \
    do { \
        if (have == 0) { \
            have = in(in_desc, &next); \
            if (have == 0) { \
                next = 0; \
                ret = Z_BUF_ERROR; \
                goto inf_leave; \
            } \
        } \
    } while (0)

   /* Get a byte of input into the bit accumulator, or return from inflateBack()
      with an error if there is no input available. */
#define PULLBYTE() \
    do { \
        if (have == 0) goto inf_leave; \
        have--; \
        hold += (unsigned long)(*next++) << bits; \
        bits += 8; \
    } while (0)

      /* Assure that there are at least n bits in the bit accumulator.  If there is
         not enough available input to do that, then return from inflateBack() with
         an error. */
#define NEEDBITS(n)  while (bits < (unsigned)(n)){ PULLBYTE();}





         /* Assure that some output space is available, by writing out the window
                     if it's full.  If the write fails, return from inflateBack() with a
                     Z_BUF_ERROR. */
#define ROOM() \
    do { \
        if (left == 0) { \
            put = InflateState->window; \
            left = InflateState->wsize; \
            InflateState->whave = left; \
            if (out(out_desc, put, left)) { \
                ret = Z_BUF_ERROR; \
                goto inf_leave; \
            } \
        } \
    } while (0)







#ifndef NO_GZIP
#  define GZIP
#endif



#define INIT_STATE    42    /* zlib header -> BUSY_STATE */
#ifdef GZIP
#  define GZIP_STATE  57    /* gzip header -> BUSY_STATE | EXTRA_STATE */
#endif
#define EXTRA_STATE   69    /* gzip extra block -> NAME_STATE */
#define NAME_STATE    73    /* gzip file name -> COMMENT_STATE */
#define COMMENT_STATE 91    /* gzip comment -> HCRC_STATE */
#define HCRC_STATE   103    /* gzip header CRC -> BUSY_STATE */
#define BUSY_STATE   113    /* deflate -> FINISH_STATE */
#define FINISH_STATE 666    /* stream complete */
/* Stream status */

//const char deflate_copyright[] = " deflate 1.2.11 Copyright 1995-2017 Jean-loup Gailly and Mark Adler ";




#define put_byte(s, c) {s->pending_buf[s->pending++] = (unsigned char)(c);}

#define MIN_LOOKAHEAD (MAX_MATCH+MIN_MATCH+1)
#define MAX_DIST(s)  ((s)->w_size-MIN_LOOKAHEAD)
#define WIN_INIT MAX_MATCH




#define d_code(dist)   ((dist) < 256 ? _dist_code[dist] : _dist_code[256+((dist)>>7)])
/* Mapping from a distance to a distance code. dist is the distance - 1 and
 * must not have side effects. _dist_code[256] and _dist_code[257] are never
 * used.
 */

#ifndef ZLIB_DEBUG


#if defined(GEN_TREES_H) || !defined(STDC)
#else
extern const unsigned char  _length_code[];
extern const unsigned char  _dist_code[];
#endif

# define _tr_tally_lit(s, c, flush) \
  { unsigned char cc = (c); \
    s->d_buf[s->last_lit] = 0; \
    s->l_buf[s->last_lit++] = cc; \
    s->dyn_ltree[cc].fc.freq++; \
    flush = (s->last_lit == s->lit_bufsize-1); \
   }
# define _tr_tally_dist(s, distance, length, flush) \
  { unsigned char len = (unsigned char)(length); \
    unsigned short dist = (unsigned short)(distance); \
    s->d_buf[s->last_lit] = dist; \
    s->l_buf[s->last_lit++] = len; \
    dist--; \
    s->dyn_ltree[_length_code[len]+LITERALS+1].fc.freq++; \
    s->dyn_dtree[d_code(dist)].fc.freq++; \
    flush = (s->last_lit == s->lit_bufsize-1); \
  }
#else
#endif






typedef void* (*alloc_func) (void* opaque, unsigned int items, unsigned int size);
typedef void(*free_func)  (void* opaque, void* address);
typedef unsigned(*in_func) (void*, unsigned char**);
typedef int(*out_func) (void*, unsigned char*, unsigned);

struct ZLibStream
{
    public:
    unsigned char* next_in;     /* next input byte */
    unsigned int     avail_in;  /* number of bytes available at next_in */
    unsigned long    total_in;  /* total number of input bytes read so far */

    unsigned char* next_out; /* next output byte will go here */
    unsigned int     avail_out; /* remaining free space at next_out */
    unsigned long    total_out; /* total number of bytes output so far */

    char* msg;  /* last error message, NULL if no error */
    DeflateStateData* DeflateState; /* not visible by applications */
    InflateStateData* InflateState;

    alloc_func zalloc;  /* used to allocate the internal state */
    free_func  zfree;   /* used to free the internal state */
    void* opaque;  /* private data object passed to zalloc and zfree */

    int     data_type;  /* best guess about the data type: binary or text
                           for deflate, or the decoding state for inflate */
    unsigned long   adler;      /* Adler-32 or CRC-32 value of the uncompressed data */
    unsigned long   reserved;   /* reserved for future use */



    const unsigned int ChunkSize = 16384;

    void flush_pending();
    unsigned int read_buf( unsigned char* buf, unsigned size);


    int deflateStateCheck();
    int   deflate( int flush);
    int   deflateEnd();
    int   deflateSetDictionary( const unsigned char* dictionary, unsigned int  dictLength);
    int   deflateGetDictionary( unsigned char* dictionary, unsigned int* dictLength);
    int   deflateCopy(ZLibStream* dest, ZLibStream* source);
    int   deflateReset();
    int   deflateParams( int level, int strategy);
    int   deflateTune( int good_length, int max_lazy, int nice_length, int max_chain);
    unsigned long   deflateBound( unsigned long sourceLen);
    int   deflatePending( unsigned* pending, int* bits);
    int   deflatePrime( int bits, int value);
    int   deflateSetHeader( GZipHeader* head);


    int   inflate( int flush);
    int   inflateSetDictionary( const unsigned char* dictionary, unsigned int  dictLength);
    int   inflateGetDictionary( unsigned char* dictionary, unsigned int* dictLength);
    int   inflateEnd();
    int   inflateSync();
    int   inflateCopy(ZLibStream* dest, ZLibStream* source);
    int   inflateReset();
    int   inflateReset2( int windowBits);
    int   inflatePrime( int bits, int value);
    long   inflateMark();
    int   inflateGetHeader( GZipHeader* head);
    int   inflateBack( in_func in, void* in_desc, out_func out, void* out_desc);
    int   inflateBackEnd();

    void inflate_fast( unsigned int start);

    int   deflateInit_( int level, const char* version, int stream_size);
    int   inflateInit_( const char* version, int stream_size);
    int   deflateInit2_( int  level, int  method, int windowBits, int memLevel, int strategy, const char* version, int stream_size);
    int   inflateInit2_( int  windowBits, const char* version, int stream_size);
    int   inflateBackInit_( int windowBits, unsigned char* window, const char* version, int stream_size);

    int              inflateSyncPoint();
    int              inflateUndermine(int);
    int              inflateValidate(int);
    unsigned long    inflateCodesUsed();
    int              inflateResetKeep();
    int              deflateResetKeep();

    bool inflateStateCheck();
    int updatewindow( const unsigned char* end, unsigned copy);
};