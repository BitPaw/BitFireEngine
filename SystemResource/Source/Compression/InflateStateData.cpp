#include "InflateStateData.h"
#include <crtdbg.h>
#include <corecrt_malloc.h>
#include "ZLibStream.h"

static const HuffCode lenfix[512] = {
     {96,7,0},{0,8,80},{0,8,16},{20,8,115},{18,7,31},{0,8,112},{0,8,48},
     {0,9,192},{16,7,10},{0,8,96},{0,8,32},{0,9,160},{0,8,0},{0,8,128},
     {0,8,64},{0,9,224},{16,7,6},{0,8,88},{0,8,24},{0,9,144},{19,7,59},
     {0,8,120},{0,8,56},{0,9,208},{17,7,17},{0,8,104},{0,8,40},{0,9,176},
     {0,8,8},{0,8,136},{0,8,72},{0,9,240},{16,7,4},{0,8,84},{0,8,20},
     {21,8,227},{19,7,43},{0,8,116},{0,8,52},{0,9,200},{17,7,13},{0,8,100},
     {0,8,36},{0,9,168},{0,8,4},{0,8,132},{0,8,68},{0,9,232},{16,7,8},
     {0,8,92},{0,8,28},{0,9,152},{20,7,83},{0,8,124},{0,8,60},{0,9,216},
     {18,7,23},{0,8,108},{0,8,44},{0,9,184},{0,8,12},{0,8,140},{0,8,76},
     {0,9,248},{16,7,3},{0,8,82},{0,8,18},{21,8,163},{19,7,35},{0,8,114},
     {0,8,50},{0,9,196},{17,7,11},{0,8,98},{0,8,34},{0,9,164},{0,8,2},
     {0,8,130},{0,8,66},{0,9,228},{16,7,7},{0,8,90},{0,8,26},{0,9,148},
     {20,7,67},{0,8,122},{0,8,58},{0,9,212},{18,7,19},{0,8,106},{0,8,42},
     {0,9,180},{0,8,10},{0,8,138},{0,8,74},{0,9,244},{16,7,5},{0,8,86},
     {0,8,22},{64,8,0},{19,7,51},{0,8,118},{0,8,54},{0,9,204},{17,7,15},
     {0,8,102},{0,8,38},{0,9,172},{0,8,6},{0,8,134},{0,8,70},{0,9,236},
     {16,7,9},{0,8,94},{0,8,30},{0,9,156},{20,7,99},{0,8,126},{0,8,62},
     {0,9,220},{18,7,27},{0,8,110},{0,8,46},{0,9,188},{0,8,14},{0,8,142},
     {0,8,78},{0,9,252},{96,7,0},{0,8,81},{0,8,17},{21,8,131},{18,7,31},
     {0,8,113},{0,8,49},{0,9,194},{16,7,10},{0,8,97},{0,8,33},{0,9,162},
     {0,8,1},{0,8,129},{0,8,65},{0,9,226},{16,7,6},{0,8,89},{0,8,25},
     {0,9,146},{19,7,59},{0,8,121},{0,8,57},{0,9,210},{17,7,17},{0,8,105},
     {0,8,41},{0,9,178},{0,8,9},{0,8,137},{0,8,73},{0,9,242},{16,7,4},
     {0,8,85},{0,8,21},{16,8,258},{19,7,43},{0,8,117},{0,8,53},{0,9,202},
     {17,7,13},{0,8,101},{0,8,37},{0,9,170},{0,8,5},{0,8,133},{0,8,69},
     {0,9,234},{16,7,8},{0,8,93},{0,8,29},{0,9,154},{20,7,83},{0,8,125},
     {0,8,61},{0,9,218},{18,7,23},{0,8,109},{0,8,45},{0,9,186},{0,8,13},
     {0,8,141},{0,8,77},{0,9,250},{16,7,3},{0,8,83},{0,8,19},{21,8,195},
     {19,7,35},{0,8,115},{0,8,51},{0,9,198},{17,7,11},{0,8,99},{0,8,35},
     {0,9,166},{0,8,3},{0,8,131},{0,8,67},{0,9,230},{16,7,7},{0,8,91},
     {0,8,27},{0,9,150},{20,7,67},{0,8,123},{0,8,59},{0,9,214},{18,7,19},
     {0,8,107},{0,8,43},{0,9,182},{0,8,11},{0,8,139},{0,8,75},{0,9,246},
     {16,7,5},{0,8,87},{0,8,23},{64,8,0},{19,7,51},{0,8,119},{0,8,55},
     {0,9,206},{17,7,15},{0,8,103},{0,8,39},{0,9,174},{0,8,7},{0,8,135},
     {0,8,71},{0,9,238},{16,7,9},{0,8,95},{0,8,31},{0,9,158},{20,7,99},
     {0,8,127},{0,8,63},{0,9,222},{18,7,27},{0,8,111},{0,8,47},{0,9,190},
     {0,8,15},{0,8,143},{0,8,79},{0,9,254},{96,7,0},{0,8,80},{0,8,16},
     {20,8,115},{18,7,31},{0,8,112},{0,8,48},{0,9,193},{16,7,10},{0,8,96},
     {0,8,32},{0,9,161},{0,8,0},{0,8,128},{0,8,64},{0,9,225},{16,7,6},
     {0,8,88},{0,8,24},{0,9,145},{19,7,59},{0,8,120},{0,8,56},{0,9,209},
     {17,7,17},{0,8,104},{0,8,40},{0,9,177},{0,8,8},{0,8,136},{0,8,72},
     {0,9,241},{16,7,4},{0,8,84},{0,8,20},{21,8,227},{19,7,43},{0,8,116},
     {0,8,52},{0,9,201},{17,7,13},{0,8,100},{0,8,36},{0,9,169},{0,8,4},
     {0,8,132},{0,8,68},{0,9,233},{16,7,8},{0,8,92},{0,8,28},{0,9,153},
     {20,7,83},{0,8,124},{0,8,60},{0,9,217},{18,7,23},{0,8,108},{0,8,44},
     {0,9,185},{0,8,12},{0,8,140},{0,8,76},{0,9,249},{16,7,3},{0,8,82},
     {0,8,18},{21,8,163},{19,7,35},{0,8,114},{0,8,50},{0,9,197},{17,7,11},
     {0,8,98},{0,8,34},{0,9,165},{0,8,2},{0,8,130},{0,8,66},{0,9,229},
     {16,7,7},{0,8,90},{0,8,26},{0,9,149},{20,7,67},{0,8,122},{0,8,58},
     {0,9,213},{18,7,19},{0,8,106},{0,8,42},{0,9,181},{0,8,10},{0,8,138},
     {0,8,74},{0,9,245},{16,7,5},{0,8,86},{0,8,22},{64,8,0},{19,7,51},
     {0,8,118},{0,8,54},{0,9,205},{17,7,15},{0,8,102},{0,8,38},{0,9,173},
     {0,8,6},{0,8,134},{0,8,70},{0,9,237},{16,7,9},{0,8,94},{0,8,30},
     {0,9,157},{20,7,99},{0,8,126},{0,8,62},{0,9,221},{18,7,27},{0,8,110},
     {0,8,46},{0,9,189},{0,8,14},{0,8,142},{0,8,78},{0,9,253},{96,7,0},
     {0,8,81},{0,8,17},{21,8,131},{18,7,31},{0,8,113},{0,8,49},{0,9,195},
     {16,7,10},{0,8,97},{0,8,33},{0,9,163},{0,8,1},{0,8,129},{0,8,65},
     {0,9,227},{16,7,6},{0,8,89},{0,8,25},{0,9,147},{19,7,59},{0,8,121},
     {0,8,57},{0,9,211},{17,7,17},{0,8,105},{0,8,41},{0,9,179},{0,8,9},
     {0,8,137},{0,8,73},{0,9,243},{16,7,4},{0,8,85},{0,8,21},{16,8,258},
     {19,7,43},{0,8,117},{0,8,53},{0,9,203},{17,7,13},{0,8,101},{0,8,37},
     {0,9,171},{0,8,5},{0,8,133},{0,8,69},{0,9,235},{16,7,8},{0,8,93},
     {0,8,29},{0,9,155},{20,7,83},{0,8,125},{0,8,61},{0,9,219},{18,7,23},
     {0,8,109},{0,8,45},{0,9,187},{0,8,13},{0,8,141},{0,8,77},{0,9,251},
     {16,7,3},{0,8,83},{0,8,19},{21,8,195},{19,7,35},{0,8,115},{0,8,51},
     {0,9,199},{17,7,11},{0,8,99},{0,8,35},{0,9,167},{0,8,3},{0,8,131},
     {0,8,67},{0,9,231},{16,7,7},{0,8,91},{0,8,27},{0,9,151},{20,7,67},
     {0,8,123},{0,8,59},{0,9,215},{18,7,19},{0,8,107},{0,8,43},{0,9,183},
     {0,8,11},{0,8,139},{0,8,75},{0,9,247},{16,7,5},{0,8,87},{0,8,23},
     {64,8,0},{19,7,51},{0,8,119},{0,8,55},{0,9,207},{17,7,15},{0,8,103},
     {0,8,39},{0,9,175},{0,8,7},{0,8,135},{0,8,71},{0,9,239},{16,7,9},
     {0,8,95},{0,8,31},{0,9,159},{20,7,99},{0,8,127},{0,8,63},{0,9,223},
     {18,7,27},{0,8,111},{0,8,47},{0,9,191},{0,8,15},{0,8,143},{0,8,79},
     {0,9,255}
};

static const HuffCode distfix[32] = {
    {16,5,1},{23,5,257},{19,5,17},{27,5,4097},{17,5,5},{25,5,1025},
    {21,5,65},{29,5,16385},{16,5,3},{24,5,513},{20,5,33},{28,5,8193},
    {18,5,9},{26,5,2049},{22,5,129},{64,5,0},{16,5,2},{23,5,385},
    {19,5,25},{27,5,6145},{17,5,7},{25,5,1537},{21,5,97},{29,5,24577},
    {16,5,4},{24,5,769},{20,5,49},{28,5,12289},{18,5,13},{26,5,3073},
    {22,5,193},{64,5,0}
};











char* const z_errmsg[10] = {
   (char*)"need dictionary",     /* Z_NEED_DICT       2  */
   (char*)"stream end",          /* Z_STREAM_END      1  */
   (char*)"",                    /* Z_OK              0  */
   (char*)"file error",          /* Z_ERRNO         (-1) */
   (char*)"stream error",        /* Z_STREAM_ERROR  (-2) */
   (char*)"data error",          /* Z_DATA_ERROR    (-3) */
   (char*)"insufficient memory", /* Z_MEM_ERROR     (-4) */
   (char*)"buffer error",        /* Z_BUF_ERROR     (-5) */
   (char*)"incompatible version",/* Z_VERSION_ERROR (-6) */
   (char*)""
};


const char* zlibVersion()
{
    return ZLIB_VERSION;
}

unsigned long   zlibCompileFlags()
{
    unsigned long flags;

    flags = 0;
    switch ((int)(sizeof(unsigned int)))
    {
        case 2:     break;
        case 4:     flags += 1;     break;
        case 8:     flags += 2;     break;
        default:    flags += 3;
    }
    switch ((int)(sizeof(unsigned long)))
    {
        case 2:     break;
        case 4:     flags += 1 << 2;        break;
        case 8:     flags += 2 << 2;        break;
        default:    flags += 3 << 2;
    }
    switch ((int)(sizeof(void*)))
    {
        case 2:     break;
        case 4:     flags += 1 << 4;        break;
        case 8:     flags += 2 << 4;        break;
        default:    flags += 3 << 4;
    }
    switch ((int)(sizeof(long)))
    {
        case 2:     break;
        case 4:     flags += 1 << 6;        break;
        case 8:     flags += 2 << 6;        break;
        default:    flags += 3 << 6;
    }
#ifdef ZLIB_DEBUG
    flags += 1 << 8;
#endif
#if defined(ASMV) || defined(ASMINF)
    flags += 1 << 9;
#endif
#ifdef ZLIB_WINAPI
    flags += 1 << 10;
#endif
#ifdef BUILDFIXED
    flags += 1 << 12;
#endif
#ifdef DYNAMIC_CRC_TABLE
    flags += 1 << 13;
#endif
#ifdef NO_GZCOMPRESS
    flags += 1L << 16;
#endif
#ifdef NO_GZIP
    flags += 1L << 17;
#endif
#ifdef PKZIP_BUG_WORKAROUND
    flags += 1L << 20;
#endif
#ifdef FASTEST
    flags += 1L << 21;
#endif
#if defined(STDC) || defined(Z_HAVE_STDARG_H)
#  ifdef NO_vsnprintf
    flags += 1L << 25;
#    ifdef HAS_vsprintf_void
    flags += 1L << 26;
#    endif
#  else
#    ifdef HAS_vsnprintf_void
    flags += 1L << 26;
#    endif
#  endif
#else
    flags += 1L << 24;
#  ifdef NO_snprintf
    flags += 1L << 25;
#    ifdef HAS_sprintf_void
    flags += 1L << 26;
#    endif
#  else
#    ifdef HAS_snprintf_void
    flags += 1L << 26;
#    endif
#  endif
#endif
    return flags;
}


/* exported to allow conversion of error code to string for compress() and
 * uncompress()
 */
const char* zError(int err)
{
    return ERR_MSG(err);
}

#define HAVE_MEMCPY

#ifndef HAVE_MEMCPY

void  memcpy(unsigned char* dest, const unsigned char* source, unsigned int len)
{
    if (len == 0) return;
    do
    {
        *dest++ = *source++; /* ??? to be unrolled */
    }
    while (--len != 0);
}

int  memcmp(s1, s2, len)
const unsigned char* s1;
const unsigned char* s2;
unsigned int  len;
{
    unsigned int j;

    for (j = 0; j < len; j++)
    {
        if (s1[j] != s2[j]) return 2 * (s1[j] > s2[j]) - 1;
    }
    return 0;
}

void  zmemzero(dest, len)
unsigned char* dest;
unsigned int  len;
{
    if (len == 0) return;
    do
    {
        *dest++ = 0;  /* ??? to be unrolled */
    }
    while (--len != 0);
}
#endif

#ifndef Z_SOLO


#ifndef MY_ZCALLOC /* Any system without a special alloc function */

#ifndef STDC
extern void* malloc(unsigned int size);
extern void* calloc(unsigned int items, unsigned int size);
extern void   free(void* ptr);
#endif

void* zcalloc(void* opaque, unsigned items, unsigned size)
{
    (void)opaque;
    return sizeof(unsigned int) > 2 ? (void*)malloc(items * size) : (void*)calloc(items, size);
}

void  zcfree(void* opaque, void* ptr)
{
    (void)opaque;
    free(ptr);
}

#endif /* MY_ZCALLOC */

#endif /* !Z_SOLO */

InflateStateData::InflateStateData()
{
    mode == InflateMode::BAD;
    head = nullptr;          

     last = -1;
     havedict = -1;
     flags = -1;
     dmax = -1;
     check = -1;
     total = -1;
     wbits = -1;
     wsize = -1;
     whave = -1;
     wnext = -1;

 
    hold = -1;
    bits = -1;

    length = -1;
    offset = -1;

    extra = -1;
   
     lencode = nullptr;    
     distcode = nullptr;
    lenbits = -1;
    distbits = -1;
    
    ncode = -1;
    nlen = -1;
    ndist = -1;
    have = -1;
    next = nullptr;
  // lens[320];  
   //work[288];  
     //codes[ENOUGH];       
     sane = -1;
     back = -1;
    was = -1;
}

void InflateStateData::fixedtables()
{
#ifdef BUILDFIXED
    static int virgin = 1;
    static code* lenfix, * distfix;
    static code fixed[544];

    /* build fixed huffman tables if first call (may not be thread safe) */
    if (virgin)
    {
        unsigned sym, bits;
        static code* next;

        /* literal/length table */
        sym = 0;
        while (sym < 144) lens[sym++] = 8;
        while (sym < 256) lens[sym++] = 9;
        while (sym < 280) lens[sym++] = 7;
        while (sym < 288) lens[sym++] = 8;
        next = fixed;
        lenfix = next;
        bits = 9;
        inflate_table(LENS, lens, 288, &(next), &(bits), work);

        /* distance table */
        sym = 0;
        while (sym < 32) lens[sym++] = 5;
        distfix = next;
        bits = 5;
        inflate_table(DISTS, lens, 32, &(next), &(bits), work);

        /* do this just once */
        virgin = 0;
    }
#else /* !BUILDFIXED */
#endif /* BUILDFIXED */
    lencode = lenfix;
    lenbits = 9;
    distcode = distfix;
    distbits = 5;
}