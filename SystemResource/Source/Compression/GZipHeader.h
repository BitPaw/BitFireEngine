#pragma once

struct GZipHeader
{
    public:
    int     Text;       /* true if compressed data believed to be text */
    unsigned long   time;       /* modification time */
    int     xflags;     /* extra flags (not used when writing a gzip file) */
    int     os;         /* operating system */
    unsigned char* extra;     /* pointer to extra field or 0 if none */
    unsigned int    extra_len;  /* extra field length (valid if extra != 0) */
    unsigned int    extra_max;  /* space at extra (only when reading header) */
    unsigned char* name;      /* pointer to zero-terminated file name or 0 */
    unsigned int    name_max;   /* space at name (only when reading header) */
    unsigned char* comment;   /* pointer to zero-terminated comment or 0 */
    unsigned int    comm_max;   /* space at comment (only when reading header) */
    int     hcrc;       /* true if there was or will be a header crc */
    int     done;       /* true when done reading gzip header (not used
                           when writing a gzip file) */
};