#pragma once
#include "GZipHeader.h"
#include "BlockState.h"
#include "Tree.h"
#include "DeflateMode.h"

#define FLUSH_BLOCK_ONLY(s, last) { \
   s->_tr_flush_block((s->block_start >= 0L ? \
                   (char *)&s->window[(unsigned)s->block_start] : \
                   (char *)0), \
                (unsigned long)((long)s->strstart - s->block_start), \
                (last)); \
   s->block_start = s->strstart; \
   s->strm->flush_pending(); \
   Tracev((stderr,"[FLUSH]")); \
}

/* Same but force premature exit if necessary. */
#define FLUSH_BLOCK(s, last) { \
   FLUSH_BLOCK_ONLY(s, last); \
   if (s->strm->avail_out == 0) return (last) ? block_state::finish_started : block_state::need_more; \
}

/* Maximum stored block length in deflate format (not including header). */
#define MAX_STORED 65535

/* Minimum of a and b. */
#define MIN(a, b) ((a) > (b) ? (b) : (a))

#define HCRC_UPDATE(beg) \
    do { \
        if (DeflateState->gzhead->hcrc && DeflateState->pending > (beg)) \
            adler = CRC32::Calculate(adler, DeflateState->pending_buf + (beg), DeflateState->pending - (beg)); \
    } while (0)

#  define check_match(s, start, match, length)




#ifndef TOO_FAR
#  define TOO_FAR 4096
#endif




/* Note: the deflate() code requires max_lazy >= MIN_MATCH and max_chain >= 4
 * For deflate_fast() (levels <= 3) good is ignored and lazy has a different
 * meaning.
 */

 /* rank Z_BLOCK between Z_NO_FLUSH and Z_PARTIAL_FLUSH */
#define RANK(f) (((f) * 2) - ((f) > 4 ? 9 : 0))


#define UPDATE_HASH(s,h,c) (h = (((h)<<s->hash_shift) ^ (c)) & s->hash_mask)



#ifdef FASTEST
#else
#define INSERT_STRING(s, str, match_head) \
   (UPDATE_HASH(s, s->ins_h, s->window[(str) + (MIN_MATCH-1)]), \
    match_head = s->prev[(str) & s->w_mask] = s->head[s->ins_h], \
    s->head[s->ins_h] = (unsigned short)(str))
#endif


#define CLEAR_HASH(s) \
    s->head[s->hash_size-1] = 0; \
    zmemzero((unsigned char *)s->head, (unsigned)(s->hash_size-1)*sizeof(*s->head));


#ifndef ZLIB_DEBUG
#  define send_code(s, c, tree) send_bits(s, tree[c].fc.code, tree[c].dl.len)
#endif

#define put_short(s, w) { \
    put_byte(s, (unsigned char)((w) & 0xff)); \
    put_byte(s, (unsigned char)((unsigned short)(w) >> 8)); \
}

#define send_bits(s, value, length) \
{ int len = length;\
  if (s->bi_valid > (int)Buf_size - len) {\
    int val = (int)value;\
    s->bi_buf |= (unsigned short)val << s->bi_valid;\
    put_short(s, s->bi_buf);\
    s->bi_buf = (unsigned short)val >> (Buf_size - s->bi_valid);\
    s->bi_valid += len - Buf_size;\
  } else {\
    s->bi_buf |= (unsigned short)(value) << s->bi_valid;\
    s->bi_valid += len;\
  }\
}





#define Z_NO_FLUSH      0
#define Z_PARTIAL_FLUSH 1
#define Z_SYNC_FLUSH    2
#define Z_FULL_FLUSH    3
#define Z_FINISH        4
#define Z_BLOCK         5
#define Z_TREES         6    /* Allowed flush values; see deflate() and inflate() below for details */

#include "StateData.h"

struct DeflateStateData : public StateData
{
    public:   
    int   status;        /* as the name implies */
    unsigned char* pending_buf;  /* output still pending */
    unsigned long   pending_buf_size; /* size of pending_buf */
    unsigned char* pending_out;  /* next pending byte to output to the stream */
    unsigned long   pending;       /* nb of bytes in the pending buffer */
    GZipHeader* gzhead;  /* gzip header information to write */
    unsigned long   gzindex;       /* where in extra, name, or comment */
    unsigned char  method;        /* can only be DEFLATED */
    int   last_flush;    /* value of flush param for previous deflate call */

                /* used by deflate.c: */

    unsigned int  w_size;        /* LZ77 window size (32K by default) */
    unsigned int  w_bits;        /* log2(w_size)  (8..16) */
    unsigned int  w_mask;        /* w_size - 1 */

 

    unsigned long window_size;
    /* Actual size of window: 2*wSize, except when the user input buffer
     * is directly used as sliding window.
     */

    unsigned short* prev;
    /* Link to older string with same hash index. To limit the size of this
     * array to 64K, this link is maintained only for the last 32K strings.
     * An index in this array is thus a window index modulo 32K.
     */

    unsigned short* head; /* Heads of the hash chains or 0. */

    unsigned int  ins_h;          /* hash index of string to be inserted */
    unsigned int  hash_size;      /* number of elements in hash table */
    unsigned int  hash_bits;      /* log2(hash_size) */
    unsigned int  hash_mask;      /* hash_size-1 */

    unsigned int  hash_shift;
    /* Number of bits by which ins_h must be shifted at each input
     * step. It must be such that after MIN_MATCH steps, the oldest
     * byte no longer takes part in the hash key, that is:
     *   hash_shift * MIN_MATCH >= hash_bits
     */

    long block_start;
    /* Window position at the beginning of the current output block. Gets
     * negative when the window is moved backwards.
     */

    unsigned int match_length;           /* length of best match */
    unsigned int prev_match;             /* previous match */
    int match_available;         /* set if previous match exists */
    unsigned int strstart;               /* start of string to insert */
    unsigned int match_start;            /* start of matching string */
    unsigned int lookahead;              /* number of valid bytes ahead in window */

    unsigned int prev_length;
    /* Length of the best match at previous step. Matches not greater than this
     * are discarded. This is used in the lazy match evaluation.
     */

    unsigned int max_chain_length;
    /* To speed up deflation, hash chains are never searched beyond this
     * length.  A higher limit improves compression ratio but degrades the
     * speed.
     */

    unsigned int max_lazy_match;
    /* Attempt to find a better match only when the current match is strictly
     * smaller than this value. This mechanism is used only for compression
     * levels >= 4.
     */
#   define max_insert_length  max_lazy_match
     /* Insert new strings in the hash table only if the match length is not
      * greater than this length. This saves time but degrades compression.
      * max_insert_length is used only for compression levels <= 3.
      */

    int level;    /* compression level (1..9) */
    int strategy; /* favor or force Huffman coding*/

    unsigned int good_match;
    /* Use a faster search when the previous match is longer than this */

    int nice_match; /* Stop searching when current match exceeds this */

                /* used by trees.c: */
    /* Didn't use ct_data typedef below to suppress compiler warning */
    struct ct_data_s dyn_ltree[HEAP_SIZE];   /* literal and length tree */
    struct ct_data_s dyn_dtree[2 * D_CODES + 1]; /* distance tree */
    struct ct_data_s bl_tree[2 * BL_CODES + 1];  /* Huffman tree for bit lengths */

    struct tree_desc_s l_desc;               /* desc. for literal tree */
    struct tree_desc_s d_desc;               /* desc. for distance tree */
    struct tree_desc_s bl_desc;              /* desc. for bit length tree */

    unsigned short bl_count[MAX_BITS + 1];
    /* number of codes at each bit length for an optimal tree */

    int heap[2 * L_CODES + 1];      /* heap used to build the Huffman trees */
    int heap_len;               /* number of elements in the heap */
    int heap_max;               /* element of largest frequency */
    /* The sons of heap[n] are heap[2*n] and heap[2*n+1]. heap[0] is not used.
     * The same heap array is used to build all trees.
     */

    unsigned char depth[2 * L_CODES + 1];
    /* Depth of each subtree used as tie breaker for trees of equal frequency
     */

    unsigned char* l_buf;          /* buffer for literals or lengths */

    unsigned int  lit_bufsize;
    /* Size of match buffer for literals/lengths.  There are 4 reasons for
     * limiting lit_bufsize to 64K:
     *   - frequencies can be kept in 16 bit counters
     *   - if compression is not successful for the first block, all input
     *     data is still in the window so we can still emit a stored block even
     *     when input comes from standard input.  (This can also be done for
     *     all blocks if lit_bufsize is not greater than 32K.)
     *   - if compression is not successful for a file smaller than 64K, we can
     *     even emit a stored file instead of a stored block (saving 5 bytes).
     *     This is applicable only for zip (not gzip or zlib).
     *   - creating new Huffman trees less frequently may not provide fast
     *     adaptation to changes in the input data statistics. (Take for
     *     example a binary file with poorly compressible code followed by
     *     a highly compressible string table.) Smaller buffer sizes give
     *     fast adaptation but have of course the overhead of transmitting
     *     trees more frequently.
     *   - I can't count above 4
     */

    unsigned int last_lit;      /* running index in l_buf */

    unsigned short* d_buf;
    /* Buffer for distances. To simplify the code, d_buf and l_buf have
     * the same number of elements. To use different lengths, an extra flag
     * array would be necessary.
     */

    unsigned long opt_len;        /* bit length of current block with optimal trees */
    unsigned long static_len;     /* bit length of current block with static trees */
    unsigned int matches;       /* number of string matches in current block */
    unsigned int insert;        /* bytes at end of window left to insert */

#ifdef ZLIB_DEBUG
    unsigned long compressed_len; /* total bit length of compressed file mod 2^32 */
    unsigned long bits_sent;      /* bit length of compressed data sent mod 2^32 */
#endif

    unsigned short bi_buf;
    /* Output buffer. bits are inserted starting at the bottom (least
     * significant bits).
     */
    int bi_valid;
    /* Number of valid bits in bi_buf.  All bits above the last valid bit
     * are always zero.
     */

    unsigned long high_water;
    /* High water mark offset in window for initialized bytes -- bytes above
     * this are set to zero in order to avoid memory check warnings when
     * longest match routines access bytes past the input.  This is then
     * updated to the new high water mark.
     */




    unsigned int longest_match( unsigned int cur_match);
    void slide_hash();
    void fill_window();
    block_state deflate_stored( int flush);
    block_state deflate_fast( int flush);
    block_state deflate_slow( int flush);
     block_state deflate_rle( int flush);
     block_state deflate_huff( int flush);
     void lm_init();
     void putShortMSB( unsigned int b);

    void  _tr_init();
    int  _tr_tally( unsigned dist, unsigned lc);
    void  _tr_flush_block( char* buf, unsigned long stored_len, int last);
    void  _tr_flush_bits();
    void  _tr_align();
    void  _tr_stored_block( char* buf, unsigned long stored_len, int last);

    void init_block();
    void pqdownheap( ct_data* tree, int k);
    void gen_bitlen( tree_desc* desc);
    void build_tree( tree_desc* desc);
    void scan_tree( ct_data* tree, int max_code);
    void send_tree( ct_data* tree, int max_code);
    int  build_bl_tree();
    void send_all_trees( int lcodes, int dcodes, int blcodes);
    void compress_block( const ct_data* ltree, const ct_data* dtree);
    int  detect_data_type();
    void bi_windup();
    void bi_flush();


    static int   uncompress(unsigned char* dest, unsigned long* destLen, const unsigned char* source, unsigned long sourceLen);
    static int   uncompress2(unsigned char* dest, unsigned long* destLen, const unsigned char* source, unsigned long* sourceLen);
    static int   compress(unsigned char* dest, unsigned long* destLen, const unsigned char* source, unsigned long sourceLen);
    static int   compress2(unsigned char* dest, unsigned long* destLen, const unsigned char* source, unsigned long sourceLen, int level);
    static unsigned long   compressBound(unsigned long sourceLen);
};

//typedef block_state(*compress_func) ( int flush);

typedef struct config_s
{
    unsigned short good_length; /* reduce lazy search above this match length */
    unsigned short max_lazy;    /* do not perform lazy search above this match length */
    unsigned short nice_length; /* quit search above this match length */
    unsigned short max_chain;
    DeflateMode Mode;
} config;




#ifdef FASTEST
const config configuration_table[2] = {
    /*      good lazy nice chain */
    /* 0 */ {0,    0,  0,    0, deflate_stored},  /* store only */
    /* 1 */ {4,    4,  8,    4, deflate_fast} }; /* max speed, no lazy matches */
#else
static const config configuration_table[10] = {
    /*      good lazy nice chain */
    /* 0 */ {0,    0,  0,    0, DeflateMode::Stored},  /* store only */
    /* 1 */ {4,    4,  8,    4, DeflateMode::Fast}, /* max speed, no lazy matches */
    /* 2 */ {4,    5, 16,    8, DeflateMode::Fast},
    /* 3 */ {4,    6, 32,   32, DeflateMode::Fast},

    /* 4 */ {4,    4, 16,   16, DeflateMode::Slow},  /* lazy matches */
    /* 5 */ {8,   16, 32,   32, DeflateMode::Slow},
    /* 6 */ {8,   16, 128, 128, DeflateMode::Slow},
    /* 7 */ {8,   32, 128, 256, DeflateMode::Slow},
    /* 8 */ {32, 128, 258, 1024, DeflateMode::Slow},
    /* 9 */ {32, 258, 258, 4096, DeflateMode::Slow} }; /* max compression */
#endif