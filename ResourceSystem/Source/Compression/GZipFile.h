#pragma once // GZipFile

//#  define gzgetc(g) ((g)->have ? ((g)->have--, (g)->pos++, *((g)->next)++) : (gzgetc)(g))


#include <stdio.h>
#include "ZLibStream.h"
#include "GZipFile.h"
#include "GZipStateData.h"

#ifdef STDC
#  include <string.h>
#  include <stdlib.h>
#  include <limits.h>
#endif

#ifndef _POSIX_SOURCE
#  define _POSIX_SOURCE
#endif
#include <fcntl.h>

#ifdef _WIN32
#  include <stddef.h>
#endif

#if defined(__TURBOC__) || defined(_MSC_VER) || defined(_WIN32)
#  include <io.h>
#endif

#if defined(_WIN32) || defined(__CYGWIN__)
#  define WIDECHAR
#endif

/* get errno and strerror definition */
#if defined UNDER_CE
#  include <windows.h>
#  define strerror(errno) gz_strwinerror((DWORD)GetLastError())
#else
#  ifndef NO_STRERROR
#    include <errno.h>
#  endif
#endif



/* default memLevel */
#if MAX_MEM_LEVEL >= 8
#  define DEF_MEM_LEVEL 8
#else
#  define DEF_MEM_LEVEL  MAX_MEM_LEVEL
#endif

/* default i/o buffer size -- double this for output when reading (this and
   twice this must be able to fit in an unsigned type) */
#define GZBUFSIZE 8192

   /* gzip modes, also provide a little integrity check on the passed structure */
#define GZ_NONE 0
#define GZ_READ 7247
#define GZ_WRITE 31153
#define GZ_APPEND 1     /* mode set to GZ_WRITE after the file is opened */

/* values for GZipStateData how */
#define LOOK 0      /* look for a gzip header */
#define COPY 1      /* copy input directly */
#define GZIP 2      /* decompress a gzip stream */



/* GT_OFF(File), where File is an unsigned value, is true if File > maximum __int64
   value -- needed when comparing unsigned to __int64, which is signed
   (possible __int64 types off_t, off64_t, and long are all signed) */
#ifdef INT_MAX
#  define GT_OFF(File) (sizeof(int) == sizeof(__int64) && (File) > INT_MAX)
#else
unsigned  gz_intmax OF((void));
#  define GT_OFF(File) (sizeof(int) == sizeof(__int64) && (File) > gz_intmax())
#endif




struct GZipFile
{
    public:
    unsigned int have;
    unsigned char* next;
    __int64 pos;

    int   gzgetc_();  /* backward compatibility */
    GZipFile* gzopen(const char*, const char*);
    long   gzseek(long, int);
    long   gztell();
    long   gzoffset();
    GZipFile* gzdopen(int fd, const char* mode);
    int   gzbuffer( unsigned int size);
    int   gzsetparams( int level, int strategy);
    int   gzread( void* buf, unsigned int len);
    unsigned int   gzfread(void* buf, unsigned int size, unsigned int nitems);
    int   gzwrite( void const* buf, unsigned int len);
    unsigned int   gzfwrite(void const* buf, unsigned int size, unsigned int nitems);
    int   gzprintf(const char* format, int a1, int a2, int a3, int a4, int  a5, int a6, int  a7, int  a8, int a9, int  a10, int  a11, int a12, int  a13, int a14, int  a15, int a16, int a17, int  a18, int a19, int a20);
    int   gzputs( const char* s);
    char* gzgets( char* buf, int len);
    int   gzputc( int c);
    int   gzgetc();
    int   gzungetc(int c);
    int   gzflush( int flush);
    int      gzrewind();
    int   gzeof();
    int   gzdirect();
    int      gzclose();
    int   gzclose_r();
    int   gzclose_w();
    const char* gzerror( int* errnum);
    void   gzclearerr();
    GZipFile* gz_open(const char*, int, const char*);

    GZipFile* gzopen64(const char*, const char*);
    __int64   gzseek64( __int64, int);
    __int64   gztell64();
    __int64   gzoffset64();

    int gzvprintf(const char* format, va_list va);
};