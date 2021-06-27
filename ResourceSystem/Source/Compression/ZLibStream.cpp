#include <stdio.h>
#include <assert.h>
#include "ZLibStream.h"
#include "InflateStateData.h"
#include "DeflateStateData.h"
#include "Adler32.h"
#include "CRC32.h"
#include <vcruntime_string.h>

unsigned syncsearch(unsigned int* have, const unsigned char* buf, unsigned int len)
{
    unsigned got;
    unsigned next;

    got = *have;
    next = 0;
    while (next < len && got < 4)
    {
        if ((int)(buf[next]) == (got < 2 ? 0 : 0xff))
            got++;
        else if (buf[next])
            got = 0;
        else
            got = 4 - got;
        next++;
    }
    *have = got;
    return next;
}


void ZLibStream::inflate_fast( unsigned int start)
{
    // inlfate Mode
    unsigned char* in;      /* static next_in */
    unsigned char* last;    /* have enough input while in < last */
    unsigned char* out;     /* static next_out */
    unsigned char* beg;     /* inflate()'s initial next_out */
    unsigned char* end;     /* while out < end, enough space available */
#ifdef INFLATE_STRICT
    unsigned dmax;              /* maximum distance from zlib header */
#endif
    unsigned wsize;             /* window size or zero if not using window */
    unsigned whave;             /* valid bytes in the window */
    unsigned wnext;             /* window write index */
    unsigned char* window;  /* allocated sliding window, if wsize != 0 */
    unsigned long hold;         /* static hold */
    unsigned bits;              /* static bits */
    HuffCode const* lcode;      /* static lencode */
    HuffCode const* dcode;      /* static distcode */
    unsigned lmask;             /* mask for first level of length codes */
    unsigned dmask;             /* mask for first level of distance codes */
    HuffCode here;                  /* retrieved table entry */
    unsigned op;                /* HuffCode bits, operation, extra bits, or */
                                /*  window position, window bytes to copy */
    unsigned len;               /* match length, unused bytes */
    unsigned dist;              /* match distance */
    unsigned char* from;    /* where to copy match from */

    /* copy state to static variables */
    
    in = next_in;
    last = in + (avail_in - 5);
    out = next_out;
    beg = out - (start - avail_out);
    end = out + (avail_out - 257);
#ifdef INFLATE_STRICT
    dmax = InflateState->dmax;
#endif
    wsize = InflateState->wsize;
    whave = InflateState->whave;
    wnext = InflateState->wnext;
    window = InflateState->window;
    hold = InflateState->hold;
    bits = InflateState->bits;
    lcode = InflateState->lencode;
    dcode = InflateState->distcode;
    lmask = (1U << InflateState->lenbits) - 1;
    dmask = (1U << InflateState->distbits) - 1;

    /* decode literals and length/distances until end-of-block or not enough
       input data or output space */
    do
    {
        if (bits < 15)
        {
            hold += (unsigned long)(*in++) << bits;
            bits += 8;
            hold += (unsigned long)(*in++) << bits;
            bits += 8;
        }
        here = lcode[hold & lmask];
dolen:
        op = (unsigned)(here.bits);
        hold >>= op;
        bits -= op;
        op = (unsigned)(here.op);
        if (op == 0)
        {                          /* literal */
            Tracevv((stderr, here.val >= 0x20 && here.val < 0x7f ?
                "inflate:         literal '%c'\n" :
                "inflate:         literal 0x%02x\n", here.val));
            *out++ = (unsigned char)(here.val);
        }
        else if (op & 16)
        {                     /* length base */
            len = (unsigned)(here.val);
            op &= 15;                           /* number of extra bits */
            if (op)
            {
                if (bits < op)
                {
                    hold += (unsigned long)(*in++) << bits;
                    bits += 8;
                }
                len += (unsigned)hold & ((1U << op) - 1);
                hold >>= op;
                bits -= op;
            }
            Tracevv((stderr, "inflate:         length %u\n", len));
            if (bits < 15)
            {
                hold += (unsigned long)(*in++) << bits;
                bits += 8;
                hold += (unsigned long)(*in++) << bits;
                bits += 8;
            }
            here = dcode[hold & dmask];
dodist:
            op = (unsigned)(here.bits);
            hold >>= op;
            bits -= op;
            op = (unsigned)(here.op);
            if (op & 16)
            {                      /* distance base */
                dist = (unsigned)(here.val);
                op &= 15;                       /* number of extra bits */
                if (bits < op)
                {
                    hold += (unsigned long)(*in++) << bits;
                    bits += 8;
                    if (bits < op)
                    {
                        hold += (unsigned long)(*in++) << bits;
                        bits += 8;
                    }
                }
                dist += (unsigned)hold & ((1U << op) - 1);
#ifdef INFLATE_STRICT
                if (dist > dmax)
                {
                    msg = (char*)"invalid distance too far back";
                    InflateState->mode = BAD;
                    break;
                }
#endif
                hold >>= op;
                bits -= op;
                Tracevv((stderr, "inflate:         distance %u\n", dist));
                op = (unsigned)(out - beg);     /* max distance in output */
                if (dist > op)
                {                /* see if copy from window */
                    op = dist - op;             /* distance back in window */
                    if (op > whave)
                    {
                        if (InflateState->sane)
                        {
                            msg =
                                (char*)"invalid distance too far back";
                            InflateState->mode = BAD;
                            break;
                        }
#ifdef INFLATE_ALLOW_INVALID_DISTANCE_TOOFAR_ARRR
                        if (len <= op - whave)
                        {
                            do
                            {
                                *out++ = 0;
                            }
                            while (--len);
                            continue;
                        }
                        len -= op - whave;
                        do
                        {
                            *out++ = 0;
                        }
                        while (--op > whave);
                        if (op == 0)
                        {
                            from = out - dist;
                            do
                            {
                                *out++ = *from++;
                            }
                            while (--len);
                            continue;
                        }
#endif
                    }
                    from = window;
                    if (wnext == 0)
                    {           /* very common case */
                        from += wsize - op;
                        if (op < len)
                        {         /* some from window */
                            len -= op;
                            do
                            {
                                *out++ = *from++;
                            }
                            while (--op);
                            from = out - dist;  /* rest from output */
                        }
                    }
                    else if (wnext < op)
                    {      /* wrap around window */
                        from += wsize + wnext - op;
                        op -= wnext;
                        if (op < len)
                        {         /* some from end of window */
                            len -= op;
                            do
                            {
                                *out++ = *from++;
                            }
                            while (--op);
                            from = window;
                            if (wnext < len)
                            {  /* some from start of window */
                                op = wnext;
                                len -= op;
                                do
                                {
                                    *out++ = *from++;
                                }
                                while (--op);
                                from = out - dist;      /* rest from output */
                            }
                        }
                    }
                    else
                    {                      /* contiguous in window */
                        from += wnext - op;
                        if (op < len)
                        {         /* some from window */
                            len -= op;
                            do
                            {
                                *out++ = *from++;
                            }
                            while (--op);
                            from = out - dist;  /* rest from output */
                        }
                    }
                    while (len > 2)
                    {
                        *out++ = *from++;
                        *out++ = *from++;
                        *out++ = *from++;
                        len -= 3;
                    }
                    if (len)
                    {
                        *out++ = *from++;
                        if (len > 1)
                            *out++ = *from++;
                    }
                }
                else
                {
                    from = out - dist;          /* copy direct from output */
                    do
                    {                        /* minimum length is three */
                        *out++ = *from++;
                        *out++ = *from++;
                        *out++ = *from++;
                        len -= 3;
                    }
                    while (len > 2);
                    if (len)
                    {
                        *out++ = *from++;
                        if (len > 1)
                            *out++ = *from++;
                    }
                }
            }
            else if ((op & 64) == 0)
            {          /* 2nd level distance code */
                here = dcode[here.val + (hold & ((1U << op) - 1))];
                goto dodist;
            }
            else
            {
                msg = (char*)"invalid distance code";
                InflateState->mode = BAD;
                break;
            }
        }
        else if ((op & 64) == 0)
        {              /* 2nd level length code */
            here = lcode[here.val + (hold & ((1U << op) - 1))];
            goto dolen;
        }
        else if (op & 32)
        {                     /* end-of-block */
            Tracevv((stderr, "inflate:         end of block\n"));
            InflateState->mode = TYPE;
            break;
        }
        else
        {
            msg = (char*)"invalid literal/length code";
            InflateState->mode = BAD;
            break;
        }
    }
    while (in < last && out < end);

    /* return unused bytes (on entry, bits < 8, so in won't go too far back) */
    len = bits >> 3;
    in -= len;
    bits -= len << 3;
    hold &= (1U << bits) - 1;

    /* update state and return */
    next_in = in;
    next_out = out;
    avail_in = (unsigned)(in < last ? 5 + (last - in) : 5 - (in - last));
    avail_out = (unsigned)(out < end ?  257 + (end - out) : 257 - (out - end));

    InflateState->hold = hold;
    InflateState->bits = bits;
    return;
}

int ZLibStream::deflateInit_( int level, const char* version, int stream_size)
{
    return deflateInit2_(level, Z_DEFLATED, MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY, version, stream_size);
    /* To do: ignore next_in if we use it as window */
}

int ZLibStream::deflateInit2_( int level, int method, int windowBits, int memLevel, int strategy,  const char* version, int stream_size)
{
    DeflateStateData* s;
    int wrap = 1;
    static const char my_version[] = ZLIB_VERSION;

    unsigned short* overlay;
    /* We overlay pending_buf and d_buf+l_buf. This works since the average
     * output size for (length,distance) codes is <= 24 bits.
     */

    if (version == 0 || version[0] != my_version[0] ||
        stream_size != sizeof(ZLibStream))
    {
        return Z_VERSION_ERROR;
    }

    msg = 0;
    if (zalloc == (alloc_func)0)
    {
#ifdef Z_SOLO
        return Z_STREAM_ERROR;
#else
        zalloc = zcalloc;
        opaque = (void*)0;
#endif
    }
    if (zfree == (free_func)0)
#ifdef Z_SOLO
        return Z_STREAM_ERROR;
#else
        zfree = zcfree;
#endif

#ifdef FASTEST
    if (level != 0) level = 1;
#else
    if (level == Z_DEFAULT_COMPRESSION) level = 6;
#endif

    if (windowBits < 0)
    { /* suppress zlib wrapper */
        wrap = 0;
        windowBits = -windowBits;
    }
#ifdef GZIP
    else if (windowBits > 15)
    {
        wrap = 2;       /* write gzip wrapper instead */
        windowBits -= 16;
    }
#endif
    if (memLevel < 1 || memLevel > MAX_MEM_LEVEL || method != Z_DEFLATED ||
        windowBits < 8 || windowBits > 15 || level < 0 || level > 9 ||
        strategy < 0 || strategy > Z_FIXED || (windowBits == 8 && wrap != 1))
    {
        return Z_STREAM_ERROR;
    }
    if (windowBits == 8) windowBits = 9;  /* until 256-byte window bug fixed */
    s = (DeflateStateData*)ZALLOC(this, 1, sizeof(DeflateStateData));
    if (s == 0) return Z_MEM_ERROR;
    s->strm = this;
    s->status = INIT_STATE;     /* to pass state test in deflateReset() */

    s->wrap = wrap;
    s->gzhead = 0;
    s->w_bits = (unsigned int)windowBits;
    s->w_size = 1 << s->w_bits;
    s->w_mask = s->w_size - 1;

    s->hash_bits = (unsigned int)memLevel + 7;
    s->hash_size = 1 << s->hash_bits;
    s->hash_mask = s->hash_size - 1;
    s->hash_shift = ((s->hash_bits + MIN_MATCH - 1) / MIN_MATCH);

    s->window = (unsigned char*)ZALLOC(this, s->w_size, 2 * sizeof(unsigned char));
    s->prev = (unsigned short*)ZALLOC(this, s->w_size, sizeof(unsigned short));
    s->head = (unsigned short*)ZALLOC(this, s->hash_size, sizeof(unsigned short));

    s->high_water = 0;      /* nothing written to s->window yet */

    s->lit_bufsize = 1 << (memLevel + 6); /* 16K elements by default */

    overlay = (unsigned short*)ZALLOC(this, s->lit_bufsize, sizeof(unsigned short) + 2);
    s->pending_buf = (unsigned char*)overlay;
    s->pending_buf_size = (unsigned long)s->lit_bufsize * (sizeof(unsigned short) + 2L);

    if (s->window == 0 || s->prev == 0 || s->head == 0 ||
        s->pending_buf == 0)
    {
        s->status = FINISH_STATE;
        msg = ERR_MSG(Z_MEM_ERROR);
        deflateEnd();
        return Z_MEM_ERROR;
    }
    s->d_buf = overlay + s->lit_bufsize / sizeof(unsigned short);
    s->l_buf = s->pending_buf + (1 + sizeof(unsigned short)) * s->lit_bufsize;

    s->level = level;
    s->strategy = strategy;
    s->method = (unsigned char)method;

    return deflateReset();
}

int ZLibStream::deflateStateCheck()
{
    if (zalloc == (alloc_func)0 || zfree == (free_func)0)
        return 1;
    if (DeflateState == 0 || DeflateState->strm !=  this|| (DeflateState->status != INIT_STATE &&
#ifdef GZIP
        DeflateState->status != GZIP_STATE &&
#endif
        DeflateState->status != EXTRA_STATE &&
        DeflateState->status != NAME_STATE &&
        DeflateState->status != COMMENT_STATE &&
        DeflateState->status != HCRC_STATE &&
        DeflateState->status != BUSY_STATE &&
        DeflateState->status != FINISH_STATE))
        return 1;
    return 0;
}

int ZLibStream::deflateSetDictionary( const unsigned char* dictionary, unsigned int dictLength)
{
    unsigned int str, n;
    int wrap;
    unsigned avail;
    unsigned char* next;

    if (deflateStateCheck() || dictionary == 0)
        return Z_STREAM_ERROR;

    wrap = DeflateState->wrap;
    if (wrap == 2 || (wrap == 1 && DeflateState->status != INIT_STATE) || DeflateState->lookahead)
        return Z_STREAM_ERROR;

    /* when using zlib wrappers, compute Adler-32 for provided dictionary */
    if (wrap == 1)
        adler = Adler32::Calculate(adler, dictionary, dictLength);
    DeflateState->wrap = 0;                    /* avoid computing Adler-32 in read_buf */

    /* if dictionary would fill window, just replace the history */
    if (dictLength >= DeflateState->w_size)
    {
        if (wrap == 0)
        {            /* already empty otherwise */
            CLEAR_HASH(DeflateState);
            DeflateState->strstart = 0;
            DeflateState->block_start = 0L;
            DeflateState->insert = 0;
        }
        dictionary += dictLength - DeflateState->w_size;  /* use the tail */
        dictLength = DeflateState->w_size;
    }

    /* insert dictionary into window and hash */
    avail = avail_in;
    next = next_in;
    avail_in = dictLength;
    next_in = (unsigned char*)dictionary;
    DeflateState->fill_window();
    while (DeflateState->lookahead >= MIN_MATCH)
    {
        str = DeflateState->strstart;
        n = DeflateState->lookahead - (MIN_MATCH - 1);
        do
        {
            UPDATE_HASH(DeflateState, DeflateState->ins_h, DeflateState->window[str + MIN_MATCH - 1]);
#ifndef FASTEST
            DeflateState->prev[str & DeflateState->w_mask] = DeflateState->head[DeflateState->ins_h];
#endif
            DeflateState->head[DeflateState->ins_h] = (unsigned short)str;
            str++;
        }
        while (--n);
        DeflateState->strstart = str;
        DeflateState->lookahead = MIN_MATCH - 1;
        DeflateState->fill_window();
    }
    DeflateState->strstart += DeflateState->lookahead;
    DeflateState->block_start = (long)DeflateState->strstart;
    DeflateState->insert = DeflateState->lookahead;
    DeflateState->lookahead = 0;
    DeflateState->match_length = DeflateState->prev_length = MIN_MATCH - 1;
    DeflateState->match_available = 0;
    next_in = next;
    avail_in = avail;
    DeflateState->wrap = wrap;
    return Z_OK;
}

int ZLibStream::deflateGetDictionary( unsigned char* dictionary, unsigned int* dictLength)
{
    unsigned int len;

    if (deflateStateCheck())
        return Z_STREAM_ERROR;
 
    len = DeflateState->strstart + DeflateState->lookahead;
    if (len > DeflateState->w_size)
        len = DeflateState->w_size;
    if (dictionary != 0 && len)
        memcpy(dictionary, DeflateState->window + DeflateState->strstart + DeflateState->lookahead - len, len);
    if (dictLength != 0)
        *dictLength = len;
    return Z_OK;
}

int  ZLibStream::deflateResetKeep()
{
    if (deflateStateCheck())
    {
        return Z_STREAM_ERROR;
    }

    total_in = total_out = 0;
    msg = 0; /* use zfree if we ever allocate msg dynamically */
    data_type = Z_UNKNOWN;

    DeflateState->pending = 0;
    DeflateState->pending_out = DeflateState->pending_buf;

    if (DeflateState->wrap < 0)
    {
        DeflateState->wrap = -DeflateState->wrap; /* was made negative by deflate(..., Z_FINISH); */
    }
    DeflateState->status =
#ifdef GZIP
        DeflateState->wrap == 2 ? GZIP_STATE :
#endif
        DeflateState->wrap ? INIT_STATE : BUSY_STATE;
    adler =
#ifdef GZIP
        DeflateState->wrap == 2 ? CRC32::Calculate(0L, 0, 0) :
#endif
        Adler32::Calculate(0L, 0, 0);
    DeflateState->last_flush = Z_NO_FLUSH;

    DeflateState->_tr_init();

    return Z_OK;
}

int   ZLibStream::deflateReset()
{
    int ret;

    ret = deflateResetKeep();
    if (ret == Z_OK)
        DeflateState->lm_init();
    return ret;
}

int  ZLibStream::deflateSetHeader( GZipHeader* head)
{
    if (deflateStateCheck() || DeflateState->wrap != 2)
        return Z_STREAM_ERROR;
    DeflateState->gzhead = head;
    return Z_OK;
}

int ZLibStream::deflatePending( unsigned int* pending, int* bits)
{
    if (deflateStateCheck()) return Z_STREAM_ERROR;
    if (pending != 0)
        *pending = DeflateState->pending;
    if (bits != 0)
        *bits = DeflateState->bi_valid;
    return Z_OK;
}

int  ZLibStream::deflatePrime( int bits, int value)
{
    int put;

    if (deflateStateCheck()) return Z_STREAM_ERROR;
    if ((unsigned char*)(DeflateState->d_buf) < DeflateState->pending_out + ((Buf_size + 7) >> 3))
        return Z_BUF_ERROR;
    do
    {
        put = Buf_size - DeflateState->bi_valid;
        if (put > bits)
            put = bits;
        DeflateState->bi_buf |= (unsigned short)((value & ((1 << put) - 1)) << DeflateState->bi_valid);
        DeflateState->bi_valid += put;
        DeflateState->_tr_flush_bits();
        value >>= put;
        bits -= put;
    }
    while (bits);
    return Z_OK;
}

int  ZLibStream::deflateParams( int level, int strategy)
{
    DeflateMode mode;

    if (deflateStateCheck()) return Z_STREAM_ERROR;

#ifdef FASTEST
    if (level != 0) level = 1;
#else
    if (level == Z_DEFAULT_COMPRESSION) level = 6;
#endif
    if (level < 0 || level > 9 || strategy < 0 || strategy > Z_FIXED)
    {
        return Z_STREAM_ERROR;
    }
    mode = configuration_table[DeflateState->level].Mode;

    if ((strategy != DeflateState->strategy || mode != configuration_table[level].Mode) && DeflateState->high_water)
    {
        /* Flush the last buffer: */
        int err = deflate(Z_BLOCK);
        if (err == Z_STREAM_ERROR)
            return err;
        if (avail_out == 0)
            return Z_BUF_ERROR;
    }
    if (DeflateState->level != level)
    {
        if (DeflateState->level == 0 && DeflateState->matches != 0)
        {
            if (DeflateState->matches == 1)
                DeflateState->slide_hash();
            else
                CLEAR_HASH(DeflateState);
            DeflateState->matches = 0;
        }
        DeflateState->level = level;
        DeflateState->max_lazy_match = configuration_table[level].max_lazy;
        DeflateState->good_match = configuration_table[level].good_length;
        DeflateState->nice_match = configuration_table[level].nice_length;
        DeflateState->max_chain_length = configuration_table[level].max_chain;
    }
    DeflateState->strategy = strategy;

    return Z_OK;
}

int   ZLibStream::deflateTune(int good_length, int max_lazy, int nice_length, int max_chain)
{
    if (deflateStateCheck()) return Z_STREAM_ERROR;
    DeflateState->good_match = (unsigned int)good_length;
    DeflateState->max_lazy_match = (unsigned int)max_lazy;
    DeflateState->nice_match = nice_length;
    DeflateState->max_chain_length = (unsigned int)max_chain;
    return Z_OK;
}

unsigned long ZLibStream::deflateBound( unsigned long sourceLen)
{

    unsigned long complen, wraplen;

    /* conservative upper bound for compressed data */
    complen = sourceLen +
        ((sourceLen + 7) >> 3) + ((sourceLen + 63) >> 6) + 5;

    /* if can't get parameters, return conservative bound plus zlib wrapper */
    if (deflateStateCheck())
        return complen + 6;

    /* compute wrapper length */
    ;
    switch (DeflateState->wrap)
    {
        case 0:                                 /* raw deflate */
            wraplen = 0;
            break;
        case 1:                                 /* zlib wrapper */
            wraplen = 6 + (DeflateState->strstart ? 4 : 0);
            break;
#ifdef GZIP
        case 2:                                 /* gzip wrapper */
            wraplen = 18;
            if (DeflateState->gzhead != 0)
            {          /* user-supplied gzip header */
                unsigned char* str;
                if (DeflateState->gzhead->extra != 0)
                    wraplen += 2 + DeflateState->gzhead->extra_len;
                str = DeflateState->gzhead->name;
                if (str != 0)
                    do
                    {
                        wraplen++;
                    }
                while (*str++);
                    str = DeflateState->gzhead->comment;
                    if (str != 0)
                        do
                        {
                            wraplen++;
                        }
                    while (*str++);
                        if (DeflateState->gzhead->hcrc)
                            wraplen += 2;
            }
            break;
#endif
        default:                                /* for compiler happiness */
            wraplen = 6;
    }

    /* if not default parameters, return conservative bound */
    if (DeflateState->w_bits != 15 || DeflateState->hash_bits != 8 + 7)
        return complen + wraplen;

    /* default settings: return tight bound for that case */
    return sourceLen + (sourceLen >> 12) + (sourceLen >> 14) +
        (sourceLen >> 25) + 13 - 6 + wraplen;
}

void ZLibStream::flush_pending()
{
    unsigned len;

    DeflateState->_tr_flush_bits();
    len = DeflateState->pending;
    if (len > avail_out) len = avail_out;
    if (len == 0) return;

    memcpy(next_out, DeflateState->pending_out, len);
    next_out += len;
    DeflateState->pending_out += len;
    total_out += len;
    avail_out -= len;
    DeflateState->pending -= len;
    if (DeflateState->pending == 0)
    {
        DeflateState->pending_out = DeflateState->pending_buf;
    }
}

int  ZLibStream::deflate( int flush)
{
    int old_flush; /* value of flush param for previous deflate call */

    if (deflateStateCheck() || flush > Z_BLOCK || flush < 0)
    {
        return Z_STREAM_ERROR;
    }

    if (next_out == 0 ||
        (avail_in != 0 && next_in == 0) ||
        (DeflateState->status == FINISH_STATE && flush != Z_FINISH))
    {
        ERR_RETURN(this, Z_STREAM_ERROR);
    }
    if (avail_out == 0) ERR_RETURN(this, Z_BUF_ERROR);

    old_flush = DeflateState->last_flush;
    DeflateState->last_flush = flush;

    /* Flush as much pending output as possible */
    if (DeflateState->pending != 0)
    {
        flush_pending();
        if (avail_out == 0)
        {
            /* Since avail_out is 0, deflate will be called again with
             * more output space, but possibly with both pending and
             * avail_in equal to zero. There won't be anything to do,
             * but this is not an error situation so make sure we
             * return OK instead of BUF_ERROR at next call of deflate:
             */
            DeflateState->last_flush = -1;
            return Z_OK;
        }

        /* Make sure there is something to do and avoid duplicate consecutive
         * flushes. For repeated and useless calls with Z_FINISH, we keep
         * returning Z_STREAM_END instead of Z_BUF_ERROR.
         */
    }
    else if (avail_in == 0 && RANK(flush) <= RANK(old_flush) &&
        flush != Z_FINISH)
    {
        ERR_RETURN(this, Z_BUF_ERROR);
    }

    /* User must not provide more input after the first FINISH: */
    if (DeflateState->status == FINISH_STATE && avail_in != 0)
    {
        ERR_RETURN(this, Z_BUF_ERROR);
    }

    /* Write the header */
    if (DeflateState->status == INIT_STATE)
    {
        /* zlib header */
        unsigned int header = (Z_DEFLATED + ((DeflateState->w_bits - 8) << 4)) << 8;
        unsigned int level_flags;

        if (DeflateState->strategy >= Z_HUFFMAN_ONLY || DeflateState->level < 2)
            level_flags = 0;
        else if (DeflateState->level < 6)
            level_flags = 1;
        else if (DeflateState->level == 6)
            level_flags = 2;
        else
            level_flags = 3;
        header |= (level_flags << 6);
        if (DeflateState->strstart != 0) header |= PRESET_DICT;
        header += 31 - (header % 31);

        DeflateState->putShortMSB(header);

        /* Save the Adler32::Calculate of the preset dictionary: */
        if (DeflateState->strstart != 0)
        {
            DeflateState->putShortMSB((unsigned int)(adler >> 16));
            DeflateState->putShortMSB((unsigned int)(adler & 0xffff));
        }
        adler = Adler32::Calculate(0L, 0, 0);
        DeflateState->status = BUSY_STATE;

        /* Compression must start with an empty pending buffer */
        flush_pending();
        if (DeflateState->pending != 0)
        {
            DeflateState->last_flush = -1;
            return Z_OK;
        }
    }
#ifdef GZIP
    if (DeflateState->status == GZIP_STATE)
    {
        /* gzip header */
        adler = CRC32::Calculate(0L, 0, 0);
        put_byte(DeflateState, 31);
        put_byte(DeflateState, 139);
        put_byte(DeflateState, 8);
        if (DeflateState->gzhead == 0)
        {
            put_byte(DeflateState, 0);
            put_byte(DeflateState, 0);
            put_byte(DeflateState, 0);
            put_byte(DeflateState, 0);
            put_byte(DeflateState, 0);
            put_byte(DeflateState, DeflateState->level == 9 ? 2 :
                (DeflateState->strategy >= Z_HUFFMAN_ONLY || DeflateState->level < 2 ?
                    4 : 0));
            put_byte(DeflateState, OS_CODE);
            DeflateState->status = BUSY_STATE;

            /* Compression must start with an empty pending buffer */
            flush_pending();
            if (DeflateState->pending != 0)
            {
                DeflateState->last_flush = -1;
                return Z_OK;
            }
        }
        else
        {
            put_byte(DeflateState, (DeflateState->gzhead->Text ? 1 : 0) +
                (DeflateState->gzhead->hcrc ? 2 : 0) +
                (DeflateState->gzhead->extra == 0 ? 0 : 4) +
                (DeflateState->gzhead->name == 0 ? 0 : 8) +
                (DeflateState->gzhead->comment == 0 ? 0 : 16)
            );
            put_byte(DeflateState, (unsigned char)(DeflateState->gzhead->time & 0xff));
            put_byte(DeflateState, (unsigned char)((DeflateState->gzhead->time >> 8) & 0xff));
            put_byte(DeflateState, (unsigned char)((DeflateState->gzhead->time >> 16) & 0xff));
            put_byte(DeflateState, (unsigned char)((DeflateState->gzhead->time >> 24) & 0xff));
            put_byte(DeflateState, DeflateState->level == 9 ? 2 :
                (DeflateState->strategy >= Z_HUFFMAN_ONLY || DeflateState->level < 2 ?
                    4 : 0));
            put_byte(DeflateState, DeflateState->gzhead->os & 0xff);
            if (DeflateState->gzhead->extra != 0)
            {
                put_byte(DeflateState, DeflateState->gzhead->extra_len & 0xff);
                put_byte(DeflateState, (DeflateState->gzhead->extra_len >> 8) & 0xff);
            }
            if (DeflateState->gzhead->hcrc)
                adler = CRC32::Calculate(adler, DeflateState->pending_buf,
                    DeflateState->pending);
            DeflateState->gzindex = 0;
            DeflateState->status = EXTRA_STATE;
        }
    }
    if (DeflateState->status == EXTRA_STATE)
    {
        if (DeflateState->gzhead->extra != 0)
        {
            unsigned long beg = DeflateState->pending;   /* start of bytes to update crc */
            unsigned int left = (DeflateState->gzhead->extra_len & 0xffff) - DeflateState->gzindex;
            while (DeflateState->pending + left > DeflateState->pending_buf_size)
            {
                unsigned int copy = DeflateState->pending_buf_size - DeflateState->pending;
                memcpy(DeflateState->pending_buf + DeflateState->pending, DeflateState->gzhead->extra + DeflateState->gzindex, copy);
                DeflateState->pending = DeflateState->pending_buf_size;
                HCRC_UPDATE(beg);
                DeflateState->gzindex += copy;
                flush_pending();
                if (DeflateState->pending != 0)
                {
                    DeflateState->last_flush = -1;
                    return Z_OK;
                }
                beg = 0;
                left -= copy;
            }
            memcpy(DeflateState->pending_buf + DeflateState->pending,
                DeflateState->gzhead->extra + DeflateState->gzindex, left);
            DeflateState->pending += left;
            HCRC_UPDATE(beg);
            DeflateState->gzindex = 0;
        }
        DeflateState->status = NAME_STATE;
    }
    if (DeflateState->status == NAME_STATE)
    {
        if (DeflateState->gzhead->name != 0)
        {
            unsigned long beg = DeflateState->pending;   /* start of bytes to update crc */
            int val;
            do
            {
                if (DeflateState->pending == DeflateState->pending_buf_size)
                {
                    HCRC_UPDATE(beg);
                    flush_pending();
                    if (DeflateState->pending != 0)
                    {
                        DeflateState->last_flush = -1;
                        return Z_OK;
                    }
                    beg = 0;
                }
                val = DeflateState->gzhead->name[DeflateState->gzindex++];
                put_byte(DeflateState, val);
            }
            while (val != 0);
            HCRC_UPDATE(beg);
            DeflateState->gzindex = 0;
        }
        DeflateState->status = COMMENT_STATE;
    }
    if (DeflateState->status == COMMENT_STATE)
    {
        if (DeflateState->gzhead->comment != 0)
        {
            unsigned long beg = DeflateState->pending;   /* start of bytes to update crc */
            int val;
            do
            {
                if (DeflateState->pending == DeflateState->pending_buf_size)
                {
                    HCRC_UPDATE(beg);
                    flush_pending();
                    if (DeflateState->pending != 0)
                    {
                        DeflateState->last_flush = -1;
                        return Z_OK;
                    }
                    beg = 0;
                }
                val = DeflateState->gzhead->comment[DeflateState->gzindex++];
                put_byte(DeflateState, val);
            }
            while (val != 0);
            HCRC_UPDATE(beg);
        }
        DeflateState->status = HCRC_STATE;
    }
    if (DeflateState->status == HCRC_STATE)
    {
        if (DeflateState->gzhead->hcrc)
        {
            if (DeflateState->pending + 2 > DeflateState->pending_buf_size)
            {
                flush_pending();
                if (DeflateState->pending != 0)
                {
                    DeflateState->last_flush = -1;
                    return Z_OK;
                }
            }
            put_byte(DeflateState, (unsigned char)(adler & 0xff));
            put_byte(DeflateState, (unsigned char)((adler >> 8) & 0xff));
            adler = CRC32::Calculate(0L, 0, 0);
        }
        DeflateState->status = BUSY_STATE;

        /* Compression must start with an empty pending buffer */
        flush_pending();
        if (DeflateState->pending != 0)
        {
            DeflateState->last_flush = -1;
            return Z_OK;
        }
    }
#endif

    /* Start a new block or continue the current one.
     */
    if (avail_in != 0 || DeflateState->lookahead != 0 ||
        (flush != Z_NO_FLUSH && DeflateState->status != FINISH_STATE))
    {
        block_state bstate;


        if (DeflateState->level == 0)
        {
            bstate = DeflateState->deflate_stored(flush);
        }
        else
        {
            if (DeflateState->strategy == Z_HUFFMAN_ONLY)
            {
                bstate = DeflateState->deflate_huff(flush);
            }
            else
            {
                if (DeflateState->strategy == Z_RLE)
                {
                    bstate = DeflateState->deflate_rle(flush);
                }
                else
                {
                    DeflateMode mode = configuration_table[DeflateState->level].Mode;

                    switch (mode)
                    {
                        case DeflateMode::Stored:
                            bstate = DeflateState->deflate_stored(flush);
                            break;

                        case DeflateMode::Fast:
                            bstate = DeflateState->deflate_fast(flush);
                            break;

                        default:
                        case DeflateMode::Slow:
                            bstate = DeflateState->deflate_slow(flush);
                            break;
                    }
                }
            }
        }        

        if (bstate == block_state::finish_started || bstate == block_state::finish_done)
        {
            DeflateState->status = FINISH_STATE;
        }
        if (bstate == block_state::need_more || bstate == block_state::finish_started)
        {
            if (avail_out == 0)
            {
                DeflateState->last_flush = -1; /* avoid BUF_ERROR next call, see above */
            }
            return Z_OK;
            /* If flush != Z_NO_FLUSH && avail_out == 0, the next call
             * of deflate should use the same flush parameter to make sure
             * that the flush is complete. So we don't have to output an
             * empty block here, this will be done at next call. This also
             * ensures that for a very small output buffer, we emit at most
             * one empty block.
             */
        }
        if (bstate == block_state::block_done)
        {
            if (flush == Z_PARTIAL_FLUSH)
            {
                DeflateState->_tr_align();
            }
            else if (flush != Z_BLOCK)
            { /* FULL_FLUSH or SYNC_FLUSH */
                DeflateState->_tr_stored_block((char*)0, 0L, 0);
                
                if (flush == Z_FULL_FLUSH)
                {
                    CLEAR_HASH(DeflateState);             /* forget history */
                    if (DeflateState->lookahead == 0)
                    {
                        DeflateState->strstart = 0;
                        DeflateState->block_start = 0L;
                        DeflateState->insert = 0;
                    }
                }
            }
            flush_pending();
            if (avail_out == 0)
            {
                DeflateState->last_flush = -1; /* avoid BUF_ERROR at next call, see above */
                return Z_OK;
            }
        }
    }

    if (flush != Z_FINISH) return Z_OK;
    if (DeflateState->wrap <= 0) return Z_STREAM_END;

    /* Write the trailer */
#ifdef GZIP
    if (DeflateState->wrap == 2)
    {
        put_byte(DeflateState, (unsigned char)(adler & 0xff));
        put_byte(DeflateState, (unsigned char)((adler >> 8) & 0xff));
        put_byte(DeflateState, (unsigned char)((adler >> 16) & 0xff));
        put_byte(DeflateState, (unsigned char)((adler >> 24) & 0xff));
        put_byte(DeflateState, (unsigned char)(total_in & 0xff));
        put_byte(DeflateState, (unsigned char)((total_in >> 8) & 0xff));
        put_byte(DeflateState, (unsigned char)((total_in >> 16) & 0xff));
        put_byte(DeflateState, (unsigned char)((total_in >> 24) & 0xff));
    }
    else
#endif
    {
        DeflateState->putShortMSB((unsigned int)(adler >> 16));
        DeflateState->putShortMSB((unsigned int)(adler & 0xffff));
    }
    flush_pending();
    
    if (DeflateState->wrap > 0) DeflateState->wrap = -DeflateState->wrap; /* write the trailer only once! */
    return DeflateState->pending != 0 ? Z_OK : Z_STREAM_END;
}

int   ZLibStream::deflateEnd()
{
    int status;

    if (deflateStateCheck()) return Z_STREAM_ERROR;

    status = DeflateState->status;

    /* Deallocate in reverse order of allocations: */
    TRY_FREE(this, DeflateState->pending_buf);
    TRY_FREE(this, DeflateState->head);
    TRY_FREE(this, DeflateState->prev);
    TRY_FREE(this, DeflateState->window);

    ZFREE(this, DeflateState);
    DeflateState = 0;

    return status == BUSY_STATE ? Z_DATA_ERROR : Z_OK;
}

int   ZLibStream::deflateCopy(ZLibStream* dest, ZLibStream* source)
{
#ifdef MAXSEG_64K
    return Z_STREAM_ERROR;
#else
    DeflateStateData* ds;
    DeflateStateData* ss;
    unsigned short* overlay;


    if (source->deflateStateCheck() || dest == 0)
    {
        return Z_STREAM_ERROR;
    }

    ss = source->DeflateState;

    memcpy((void*)dest, (void*)source, sizeof(ZLibStream));

    ds = (DeflateStateData*)ZALLOC(dest, 1, sizeof(DeflateStateData));
    if (ds == 0) return Z_MEM_ERROR;
    dest->DeflateState = (DeflateStateData*)ds;
    memcpy((void*)ds, (void*)ss, sizeof(DeflateStateData));
    ds->strm = dest;

    ds->window = (unsigned char*)ZALLOC(dest, ds->w_size, 2 * sizeof(unsigned char));
    ds->prev = (unsigned short*)ZALLOC(dest, ds->w_size, sizeof(unsigned short));
    ds->head = (unsigned short*)ZALLOC(dest, ds->hash_size, sizeof(unsigned short));
    overlay = (unsigned short*)ZALLOC(dest, ds->lit_bufsize, sizeof(unsigned short) + 2);
    ds->pending_buf = (unsigned char*)overlay;

    if (ds->window == 0 || ds->prev == 0 || ds->head == 0 ||
        ds->pending_buf == 0)
    {
        dest->deflateEnd();
        return Z_MEM_ERROR;
    }
    /* following memcpy do not work for 16-bit MSDOS */
    memcpy(ds->window, ss->window, ds->w_size * 2 * sizeof(unsigned char));
    memcpy((void*)ds->prev, (void*)ss->prev, ds->w_size * sizeof(unsigned short));
    memcpy((void*)ds->head, (void*)ss->head, ds->hash_size * sizeof(unsigned short));
    memcpy(ds->pending_buf, ss->pending_buf, (unsigned int)ds->pending_buf_size);

    ds->pending_out = ds->pending_buf + (ss->pending_out - ss->pending_buf);
    ds->d_buf = overlay + ds->lit_bufsize / sizeof(unsigned short);
    ds->l_buf = ds->pending_buf + (1 + sizeof(unsigned short)) * ds->lit_bufsize;

    ds->l_desc.dyn_tree = ds->dyn_ltree;
    ds->d_desc.dyn_tree = ds->dyn_dtree;
    ds->bl_desc.dyn_tree = ds->bl_tree;

    return Z_OK;
#endif /* MAXSEG_64K */
}

unsigned int ZLibStream::read_buf( unsigned char* buf, unsigned size)
{
    unsigned len = avail_in;
    StateData* dateData;

    if (InflateState == 0)
    {
        dateData = InflateState;
    }
    else
    {
        dateData = DeflateState;
    }

    if (len > size) len = size;
    if (len == 0) return 0;

    avail_in -= len;

    memcpy(buf, next_in, len);
    if (dateData->wrap == 1)
    {
        adler = Adler32::Calculate(adler, buf, len);
    }
#ifdef GZIP
    else if (dateData->wrap == 2)
    {
        adler = CRC32::Calculate(adler, buf, len);
    }
#endif
    next_in += len;
    total_in += len;

    return len;
}

bool ZLibStream::inflateStateCheck()
{
    if (  zalloc == (alloc_func)0 || zfree == (free_func)0)
        return 1;

    if (InflateState == 0 || InflateState->mode < HEAD || InflateState->mode > SYNC)
        return 1;
    return 0;
}

int  ZLibStream::inflateResetKeep()
{
    if (inflateStateCheck()) return Z_STREAM_ERROR;

    total_in = total_out = InflateState->total = 0;
    msg = 0;
    if (InflateState->wrap)        /* to support ill-conceived Java test suite */
        adler = InflateState->wrap & 1;
    InflateState->mode = HEAD;
    InflateState->last = 0;
    InflateState->havedict = 0;
    InflateState->dmax = 32768U;
    InflateState->head = 0;
    InflateState->hold = 0;
    InflateState->bits = 0;
    InflateState->lencode = InflateState->distcode = InflateState->next = InflateState->codes;
    InflateState->sane = 1;
    InflateState->back = -1;
    Tracev((stderr, "inflate: reset\n"));
    return Z_OK;
}

int  ZLibStream::inflateReset()
{
    if (inflateStateCheck()) return Z_STREAM_ERROR;

    InflateState->wsize = 0;
    InflateState->whave = 0;
    InflateState->wnext = 0;
    return inflateResetKeep();
}

int  ZLibStream::inflateReset2( int windowBits)
{
    int wrap;

    /* get the state */
    if (inflateStateCheck()) return Z_STREAM_ERROR;

    /* extract wrap request from windowBits parameter */
    if (windowBits < 0)
    {
        wrap = 0;
        windowBits = -windowBits;
    }
    else
    {
        wrap = (windowBits >> 4) + 5;
#ifdef GUNZIP
        if (windowBits < 48)
            windowBits &= 15;
#endif
    }

    /* set number of window bits, free window if different */
    if (windowBits && (windowBits < 8 || windowBits > 15))
        return Z_STREAM_ERROR;
    if (InflateState->window != 0 && InflateState->wbits != (unsigned)windowBits)
    {
        ZFREE(this, InflateState->window);
        InflateState->window = 0;
    }

    /* update state and reset the rest of it */
    InflateState->wrap = wrap;
    InflateState->wbits = (unsigned)windowBits;
    return inflateReset();
}

int   ZLibStream::inflateInit2_( int windowBits, const char* version, int stream_size)
{
    int ret;

    if (version == 0 || version[0] != ZLIB_VERSION[0] ||
        stream_size != (int)(sizeof(ZLibStream)))
        return Z_VERSION_ERROR;
  
    msg = 0;                 /* in case we return an error */
    if (zalloc == (alloc_func)0)
    {
#ifdef Z_SOLO
        return Z_STREAM_ERROR;
#else
        zalloc = zcalloc;
        opaque = (void*)0;
#endif
    }
    if (zfree == (free_func)0)
#ifdef Z_SOLO
        return Z_STREAM_ERROR;
#else
        zfree = zcfree;
#endif
    InflateState = new InflateStateData();

    if (InflateState == nullptr) return Z_MEM_ERROR;

    Tracev((stderr, "inflate: allocated\n"));
    
    InflateState->strm = this;
    InflateState->window = 0;
    InflateState->mode = HEAD;     /* to pass state test in inflateReset2() */

    ret = inflateReset2(windowBits);

    if (ret != Z_OK)
    {
        delete InflateState;
        InflateState = nullptr;
    }
    return ret;
}

int  ZLibStream::inflateInit_( const char* version, int stream_size)
{
    return inflateInit2_(DEF_WBITS, version, stream_size);
}

int ZLibStream::inflatePrime( int bits, int value)
{
    // inlfate Mode

    if (inflateStateCheck()) return Z_STREAM_ERROR;
    
    if (bits < 0)
    {
        InflateState->hold = 0;
        InflateState->bits = 0;
        return Z_OK;
    }
    if (bits > 16 || InflateState->bits + (unsigned int)bits > 32) return Z_STREAM_ERROR;
    value &= (1L << bits) - 1;
    InflateState->hold += (unsigned)value << InflateState->bits;
    InflateState->bits += (unsigned int)bits;
    return Z_OK;
}

int ZLibStream::updatewindow( const unsigned char* end, unsigned int copy)
{
    // inlfate Mode
    unsigned dist;

    

    /* if it hasn't been done already, allocate space for the window */
    if (InflateState->window == 0)
    {
        InflateState->window = (unsigned char*)
            ZALLOC(this, 1U << InflateState->wbits,        sizeof(unsigned char));
        if (InflateState->window == 0) return 1;
    }

    /* if window not in use yet, initialize */
    if (InflateState->wsize == 0)
    {
        InflateState->wsize = 1U << InflateState->wbits;
        InflateState->wnext = 0;
        InflateState->whave = 0;
    }

    /* copy InflateState->wsize or less output bytes into the circular window */
    if (copy >= InflateState->wsize)
    {
        memcpy(InflateState->window, end - InflateState->wsize, InflateState->wsize);
        InflateState->wnext = 0;
        InflateState->whave = InflateState->wsize;
    }
    else
    {
        dist = InflateState->wsize - InflateState->wnext;
        if (dist > copy) dist = copy;
        memcpy(InflateState->window + InflateState->wnext, end - copy, dist);
        copy -= dist;
        if (copy)
        {
            memcpy(InflateState->window, end - copy, copy);
            InflateState->wnext = copy;
            InflateState->whave = InflateState->wsize;
        }
        else
        {
            InflateState->wnext += dist;
            if (InflateState->wnext == InflateState->wsize) InflateState->wnext = 0;
            if (InflateState->whave < InflateState->wsize) InflateState->whave += dist;
        }
    }
    return 0;
}

int  ZLibStream::inflate( int flush)
{
    // inlfate Mode
    unsigned char* next = nullptr;    /* next input */
    unsigned char* put = nullptr;     /* next output */
    unsigned int have = 0, left = 0;        /* available input and output */
    unsigned long hold = 0;         /* bit buffer */
    unsigned int bits = 0;              /* bits in bit buffer */
    unsigned int in = 0, out = 0;           /* save starting available input and output */
    unsigned int copy = 0;              /* number of stored or match bytes to copy */
    unsigned char* from = nullptr;    /* where to copy match bytes from */
    HuffCode here;                  /* current decoding table entry */
    HuffCode last;                  /* parent table entry */
    unsigned int len = 0;               /* length to copy for repeats, bits to drop */
    int ret = 0;                    /* return code */
#ifdef GUNZIP
    unsigned char hbuf[4] = { 0,0,0,0 };      /* buffer for gzip header crc calculation */
#endif
    const unsigned short order[19] = { 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15 }; /* permutation of code lengths */

    if (inflateStateCheck() || next_out == 0 || (next_in == 0 && avail_in != 0))
        return Z_STREAM_ERROR;

    
    if (InflateState->mode == TYPE) InflateState->mode = TYPEDO;      /* skip check */
    


    put = next_out;
    left = avail_out;
    next = next_in;
    have = avail_in;
    hold = InflateState->hold;
    bits = InflateState->bits;
    in = have;
    out = left;
    ret = Z_OK;

    while (true)
        switch (InflateState->mode)
        {
            case HEAD:
                if (InflateState->wrap == 0)
                {
                    InflateState->mode = TYPEDO;
                    break;
                }
                NEEDBITS(16);
#ifdef GUNZIP
                if ((InflateState->wrap & 2) && hold == 0x8b1f)
                {  /* gzip header */
                    if (InflateState->wbits == 0)
                        InflateState->wbits = 15;
                    InflateState->check = CRC32::Calculate(0L, 0, 0);
                    CRC2(InflateState->check, hold);
                    INITBITS();
                    InflateState->mode = FLAGS;
                    break;
                }
                InflateState->flags = 0;           /* expect zlib header */
                if (InflateState->head != 0)
                    InflateState->head->done = -1;
                if (!(InflateState->wrap & 1) ||   /* check if zlib header allowed */
#else
                if (
#endif
                    ((BITS(8) << 8) + (hold >> 8)) % 31)
                {
                    msg = (char*)"incorrect header check";
                    InflateState->mode = BAD;
                    break;
                }
                if (BITS(4) != Z_DEFLATED)
                {
                    msg = (char*)"unknown compression method";
                    InflateState->mode = BAD;
                    break;
                }
                DROPBITS(4);
                len = BITS(4) + 8;
                if (InflateState->wbits == 0)
                    InflateState->wbits = len;
                if (len > 15 || len > InflateState->wbits)
                {
                    msg = (char*)"invalid window size";
                    InflateState->mode = BAD;
                    break;
                }
                InflateState->dmax = 1U << len;
                Tracev((stderr, "inflate:   zlib header ok\n"));
                adler = InflateState->check = Adler32::Calculate(0L, 0, 0);
                InflateState->mode = hold & 0x200 ? DICTID : TYPE;
                INITBITS();
                break;
#ifdef GUNZIP
            case FLAGS:
                NEEDBITS(16);
                InflateState->flags = (int)(hold);
                if ((InflateState->flags & 0xff) != Z_DEFLATED)
                {
                    msg = (char*)"unknown compression method";
                    InflateState->mode = BAD;
                    break;
                }
                if (InflateState->flags & 0xe000)
                {
                    msg = (char*)"unknown header flags set";
                    InflateState->mode = BAD;
                    break;
                }
                if (InflateState->head != 0)
                    InflateState->head->Text = (int)((hold >> 8) & 1);
                if ((InflateState->flags & 0x0200) && (InflateState->wrap & 4))
                    CRC2(InflateState->check, hold);
                INITBITS();
                InflateState->mode = TIME;
            case TIME:
                NEEDBITS(32);
                if (InflateState->head != 0)
                    InflateState->head->time = hold;
                if ((InflateState->flags & 0x0200) && (InflateState->wrap & 4))
                    CRC4(InflateState->check, hold);
                INITBITS();
                InflateState->mode = OS;
            case OS:
                NEEDBITS(16);
                if (InflateState->head != 0)
                {
                    InflateState->head->xflags = (int)(hold & 0xff);
                    InflateState->head->os = (int)(hold >> 8);
                }
                if ((InflateState->flags & 0x0200) && (InflateState->wrap & 4))
                    CRC2(InflateState->check, hold);
                INITBITS();
                InflateState->mode = EXLEN;
            case EXLEN:
                if (InflateState->flags & 0x0400)
                {
                    NEEDBITS(16);
                    InflateState->length = (unsigned)(hold);
                    if (InflateState->head != 0)
                        InflateState->head->extra_len = (unsigned)hold;
                    if ((InflateState->flags & 0x0200) && (InflateState->wrap & 4))
                        CRC2(InflateState->check, hold);
                    INITBITS();
                }
                else if (InflateState->head != 0)
                    InflateState->head->extra = 0;
                InflateState->mode = EXTRA;
            case EXTRA:
                if (InflateState->flags & 0x0400)
                {
                    copy = InflateState->length;
                    if (copy > have) copy = have;
                    if (copy)
                    {
                        if (InflateState->head != 0 &&
                            InflateState->head->extra != 0)
                        {
                            len = InflateState->head->extra_len - InflateState->length;
                            memcpy(InflateState->head->extra + len, next,
                                len + copy > InflateState->head->extra_max ?
                                InflateState->head->extra_max - len : copy);
                        }
                        if ((InflateState->flags & 0x0200) && (InflateState->wrap & 4))
                            InflateState->check = CRC32::Calculate(InflateState->check, next, copy);
                        have -= copy;
                        next += copy;
                        InflateState->length -= copy;
                    }
                    if (InflateState->length) goto inf_leave;
                }
                InflateState->length = 0;
                InflateState->mode = NAME;
            case NAME:
                if (InflateState->flags & 0x0800)
                {
                    if (have == 0) goto inf_leave;
                    copy = 0;
                    do
                    {
                        len = (unsigned)(next[copy++]);
                        if (InflateState->head != 0 &&
                            InflateState->head->name != 0 &&
                            InflateState->length < InflateState->head->name_max)
                            InflateState->head->name[InflateState->length++] = (unsigned char)len;
                    }
                    while (len && copy < have);
                    if ((InflateState->flags & 0x0200) && (InflateState->wrap & 4))
                        InflateState->check = CRC32::Calculate(InflateState->check, next, copy);
                    have -= copy;
                    next += copy;
                    if (len) goto inf_leave;
                }
                else if (InflateState->head != 0)
                    InflateState->head->name = 0;
                InflateState->length = 0;
                InflateState->mode = COMMENT;
            case COMMENT:
                if (InflateState->flags & 0x1000)
                {
                    if (have == 0) goto inf_leave;
                    copy = 0;
                    do
                    {
                        len = (unsigned)(next[copy++]);
                        if (InflateState->head != 0 &&
                            InflateState->head->comment != 0 &&
                            InflateState->length < InflateState->head->comm_max)
                            InflateState->head->comment[InflateState->length++] = (unsigned char)len;
                    }
                    while (len && copy < have);
                    if ((InflateState->flags & 0x0200) && (InflateState->wrap & 4))
                        InflateState->check = CRC32::Calculate(InflateState->check, next, copy);
                    have -= copy;
                    next += copy;
                    if (len) goto inf_leave;
                }
                else if (InflateState->head != 0)
                    InflateState->head->comment = 0;
                InflateState->mode = HCRC;
            case HCRC:
                if (InflateState->flags & 0x0200)
                {
                    NEEDBITS(16);
                    if ((InflateState->wrap & 4) && hold != (InflateState->check & 0xffff))
                    {
                        msg = (char*)"header crc mismatch";
                        InflateState->mode = BAD;
                        break;
                    }
                    INITBITS();
                }
                if (InflateState->head != 0)
                {
                    InflateState->head->hcrc = (int)((InflateState->flags >> 9) & 1);
                    InflateState->head->done = 1;
                }
                adler = InflateState->check = CRC32::Calculate(0L, 0, 0);
                InflateState->mode = TYPE;
                break;
#endif
            case DICTID:
            {
                NEEDBITS(32);

                adler = InflateState->check = ZSWAP32(hold);
                INITBITS();
                InflateState->mode = DICT;
            }
            case DICT:
                if (InflateState->havedict == 0)
                {
                    RESTORE();
                    return Z_NEED_DICT;
                }
                adler = InflateState->check = Adler32::Calculate(0L, 0, 0);
                InflateState->mode = TYPE;
            case TYPE:
                if (flush == Z_BLOCK || flush == Z_TREES) goto inf_leave;
            case TYPEDO:
                if (InflateState->last)
                {
                    BYTEBITS();
                    InflateState->mode = CHECK;
                    break;
                }
                NEEDBITS(3);
                InflateState->last = BITS(1);
                DROPBITS(1);
                switch (BITS(2))
                {
                    case 0:                             /* stored block */
                        Tracev((stderr, "inflate:     stored block%s\n",
                            InflateState->last ? " (last)" : ""));
                        InflateState->mode = STORED;
                        break;
                    case 1:                             /* fixed block */
                        InflateState->fixedtables();
                        Tracev((stderr, "inflate:     fixed codes block%s\n",
                            InflateState->last ? " (last)" : ""));
                        InflateState->mode = LEN_;             /* decode codes */
                        if (flush == Z_TREES)
                        {
                            DROPBITS(2);
                            goto inf_leave;
                        }
                        break;
                    case 2:                             /* dynamic block */
                        Tracev((stderr, "inflate:     dynamic codes block%s\n",
                            InflateState->last ? " (last)" : ""));
                        InflateState->mode = TABLE;
                        break;
                    case 3:
                        msg = (char*)"invalid block type";
                        InflateState->mode = BAD;
                }
                DROPBITS(2);
                break;
            case STORED:
                BYTEBITS();                         /* go to byte boundary */
                NEEDBITS(32);
                if ((hold & 0xffff) != ((hold >> 16) ^ 0xffff))
                {
                    msg = (char*)"invalid stored block lengths";
                    InflateState->mode = BAD;
                    break;
                }
                InflateState->length = (unsigned)hold & 0xffff;
                Tracev((stderr, "inflate:       stored length %u\n",
                    InflateState->length));
                INITBITS();
                InflateState->mode = COPY_;
                if (flush == Z_TREES) goto inf_leave;
            case COPY_:
                InflateState->mode = COPY;
            case COPY:
                copy = InflateState->length;
                if (copy)
                {
                    if (copy > have) copy = have;
                    if (copy > left) copy = left;
                    if (copy == 0) goto inf_leave;
                    memcpy(put, next, copy);
                    have -= copy;
                    next += copy;
                    left -= copy;
                    put += copy;
                    InflateState->length -= copy;
                    break;
                }
                Tracev((stderr, "inflate:       stored end\n"));
                InflateState->mode = TYPE;
                break;
            case TABLE:
                NEEDBITS(14);
                InflateState->nlen = BITS(5) + 257;
                DROPBITS(5);
                InflateState->ndist = BITS(5) + 1;
                DROPBITS(5);
                InflateState->ncode = BITS(4) + 4;
                DROPBITS(4);
#ifndef PKZIP_BUG_WORKAROUND
                if (InflateState->nlen > 286 || InflateState->ndist > 30)
                {
                    msg = (char*)"too many length or distance symbols";
                    InflateState->mode = BAD;
                    break;
                }
#endif
                Tracev((stderr, "inflate:       table sizes ok\n"));
                InflateState->have = 0;
                InflateState->mode = LENLENS;
            case LENLENS:
                while (InflateState->have < InflateState->ncode)
                {
                    NEEDBITS(3);
                    InflateState->lens[order[InflateState->have++]] = (unsigned short)BITS(3);
                    DROPBITS(3);
                }
                while (InflateState->have < 19)
                    InflateState->lens[order[InflateState->have++]] = 0;
                InflateState->next = InflateState->codes;
                InflateState->lencode = (const HuffCode*)(InflateState->next);
                InflateState->lenbits = 7;
                ret = inflate_table(HuffCodeType::CODES, InflateState->lens, 19, &(InflateState->next),
                    &(InflateState->lenbits), InflateState->work);
                if (ret)
                {
                    msg = (char*)"invalid code lengths set";
                    InflateState->mode = BAD;
                    break;
                }
                Tracev((stderr, "inflate:       code lengths ok\n"));
                InflateState->have = 0;
                InflateState->mode = CODELENS;
            case CODELENS:
                while (InflateState->have < InflateState->nlen + InflateState->ndist)
                {
                    for (;;)
                    {
                        here = InflateState->lencode[BITS(InflateState->lenbits)];
                        if ((unsigned)(here.bits) <= bits) break;                              


                        PULLBYTE();
                    }
                    if (here.val < 16)
                    {
                        DROPBITS(here.bits);
                        InflateState->lens[InflateState->have++] = here.val;
                    }
                    else
                    {
                        if (here.val == 16)
                        {
                            NEEDBITS(here.bits + 2);
                            DROPBITS(here.bits);
                            if (InflateState->have == 0)
                            {
                                msg = (char*)"invalid bit length repeat";
                                InflateState->mode = BAD;
                                break;
                            }
                            len = InflateState->lens[InflateState->have - 1];
                            copy = 3 + BITS(2);
                            DROPBITS(2);
                        }
                        else if (here.val == 17)
                        {
                            NEEDBITS(here.bits + 3);
                            DROPBITS(here.bits);
                            len = 0;
                            copy = 3 + BITS(3);
                            DROPBITS(3);
                        }
                        else
                        {
                            NEEDBITS(here.bits + 7);
                            DROPBITS(here.bits);
                            len = 0;
                            copy = 11 + BITS(7);
                            DROPBITS(7);
                        }
                        if (InflateState->have + copy > InflateState->nlen + InflateState->ndist)
                        {
                            msg = (char*)"invalid bit length repeat";
                            InflateState->mode = BAD;
                            break;
                        }
                        while (copy--)
                            InflateState->lens[InflateState->have++] = (unsigned short)len;
                    }
                }

                /* handle error breaks in while */
                if (InflateState->mode == BAD) break;

                /* check for end-of-block code (better have one) */
                if (InflateState->lens[256] == 0)
                {
                    msg = (char*)"invalid code -- missing end-of-block";
                    InflateState->mode = BAD;
                    break;
                }

                /* build code tables -- note: do not change the lenbits or distbits
                   values here (9 and 6) without reading the comments in inftrees.h
                   concerning the ENOUGH constants, which depend on those values */
                InflateState->next = InflateState->codes;
                InflateState->lencode = (const HuffCode*)(InflateState->next);
                InflateState->lenbits = 9;
                ret = inflate_table(HuffCodeType::LENS, InflateState->lens, InflateState->nlen, &(InflateState->next),
                    &(InflateState->lenbits), InflateState->work);
                if (ret)
                {
                    msg = (char*)"invalid literal/lengths set";
                    InflateState->mode = BAD;
                    break;
                }
                InflateState->distcode = (const HuffCode*)(InflateState->next);
                InflateState->distbits = 6;
                ret = inflate_table(HuffCodeType::DISTS, InflateState->lens + InflateState->nlen, InflateState->ndist,
                    &(InflateState->next), &(InflateState->distbits), InflateState->work);
                if (ret)
                {
                    msg = (char*)"invalid distances set";
                    InflateState->mode = BAD;
                    break;
                }
                Tracev((stderr, "inflate:       codes ok\n"));
                InflateState->mode = LEN_;
                if (flush == Z_TREES) goto inf_leave;
            case LEN_:
                InflateState->mode = LEN;
            case LEN:
                if (have >= 6 && left >= 258)
                {
                    RESTORE();
                    inflate_fast(out);
                    LOAD();
                    if (InflateState->mode == TYPE)
                        InflateState->back = -1;
                    break;
                }
                InflateState->back = 0;
                for (;;)
                {
                    here = InflateState->lencode[BITS(InflateState->lenbits)];
                    if ((unsigned)(here.bits) <= bits) break;
                    PULLBYTE();
                }
                if (here.op && (here.op & 0xf0) == 0)
                {
                    last = here;
                    for (;;)
                    {
                        here = InflateState->lencode[last.val +
                            (BITS(last.bits + last.op) >> last.bits)];
                        if ((unsigned)(last.bits + here.bits) <= bits) break;
                        PULLBYTE();
                    }
                    DROPBITS(last.bits);
                    InflateState->back += last.bits;
                }
                DROPBITS(here.bits);
                InflateState->back += here.bits;
                InflateState->length = (unsigned)here.val;
                if ((int)(here.op) == 0)
                {
                    Tracevv((stderr, here.val >= 0x20 && here.val < 0x7f ?
                        "inflate:         literal '%c'\n" :
                        "inflate:         literal 0x%02x\n", here.val));
                    InflateState->mode = LIT;
                    break;
                }
                if (here.op & 32)
                {
                    Tracevv((stderr, "inflate:         end of block\n"));
                    InflateState->back = -1;
                    InflateState->mode = TYPE;
                    break;
                }
                if (here.op & 64)
                {
                    msg = (char*)"invalid literal/length code";
                    InflateState->mode = BAD;
                    break;
                }
                InflateState->extra = (unsigned)(here.op) & 15;
                InflateState->mode = LENEXT;
            case LENEXT:
                if (InflateState->extra)
                {
                    NEEDBITS(InflateState->extra);
                    InflateState->length += BITS(InflateState->extra);
                    DROPBITS(InflateState->extra);
                    InflateState->back += InflateState->extra;
                }
                Tracevv((stderr, "inflate:         length %u\n", InflateState->length));
                InflateState->was = InflateState->length;
                InflateState->mode = DIST;
            case DIST:
                for (;;)
                {
                    here = InflateState->distcode[BITS(InflateState->distbits)];
                    if ((unsigned)(here.bits) <= bits) break;
                    PULLBYTE();
                }
                if ((here.op & 0xf0) == 0)
                {
                    last = here;
                    for (;;)
                    {
                        here = InflateState->distcode[last.val +                            (BITS(last.bits + last.op) >> last.bits)];
                        if ((unsigned)(last.bits + here.bits) <= bits) break;
                        PULLBYTE();
                    }
                    DROPBITS(last.bits);
                    InflateState->back += last.bits;
                }
                DROPBITS(here.bits);
                InflateState->back += here.bits;
                if (here.op & 64)
                {
                    msg = (char*)"invalid distance code";
                    InflateState->mode = BAD;
                    break;
                }
                InflateState->offset = (unsigned)here.val;
                InflateState->extra = (unsigned)(here.op) & 15;
                InflateState->mode = DISTEXT;
            case DISTEXT:
                if (InflateState->extra)
                {
                    NEEDBITS(InflateState->extra);
                    InflateState->offset += BITS(InflateState->extra);
                    DROPBITS(InflateState->extra);
                    InflateState->back += InflateState->extra;
                }
#ifdef INFLATE_STRICT
                if (InflateState->offset > InflateState->dmax)
                {
                    msg = (char*)"invalid distance too far back";
                    InflateState->mode = BAD;
                    break;
                }
#endif
                Tracevv((stderr, "inflate:         distance %u\n", InflateState->offset));
                InflateState->mode = MATCH;
            case MATCH:
                if (left == 0) goto inf_leave;
                copy = out - left;
                if (InflateState->offset > copy)
                {         /* copy from window */
                    copy = InflateState->offset - copy;
                    if (copy > InflateState->whave)
                    {
                        if (InflateState->sane)
                        {
                            msg = (char*)"invalid distance too far back";
                            InflateState->mode = BAD;
                            break;
                        }
#ifdef INFLATE_ALLOW_INVALID_DISTANCE_TOOFAR_ARRR
                        Trace((stderr, "inflate.c too far\n"));
                        copy -= InflateState->whave;
                        if (copy > InflateState->length) copy = InflateState->length;
                        if (copy > left) copy = left;
                        left -= copy;
                        InflateState->length -= copy;
                        do
                        {
                            *put++ = 0;
                        }
                        while (--copy);
                        if (InflateState->length == 0) InflateState->mode = LEN;
                        break;
#endif
                    }
                    if (copy > InflateState->wnext)
                    {
                        copy -= InflateState->wnext;
                        from = InflateState->window + (InflateState->wsize - copy);
                    }
                    else
                        from = InflateState->window + (InflateState->wnext - copy);
                    if (copy > InflateState->length) copy = InflateState->length;
                }
                else
                {                              /* copy from output */
                    from = put - InflateState->offset;
                    copy = InflateState->length;
                }
                if (copy > left) copy = left;
                left -= copy;
                InflateState->length -= copy;
                do
                {
                    *put++ = *from++;
                }
                while (--copy);
                if (InflateState->length == 0) InflateState->mode = LEN;
                break;
            case LIT:
                if (left == 0) goto inf_leave;
                *put++ = (unsigned char)(InflateState->length);
                left--;
                InflateState->mode = LEN;
                break;
            case CHECK:
                if (InflateState->wrap)
                {
                    NEEDBITS(32);
                    out -= left;
                    total_out += out;
                    InflateState->total += out;
                    if ((InflateState->wrap & 4) && out)
                        adler = InflateState->check =
                        UPDATE(InflateState->check, put - out, out);
                    out = left;
                    if ((InflateState->wrap & 4) && (
#ifdef GUNZIP
                        InflateState->flags ? hold :
#endif
                        ZSWAP32(hold)) != InflateState->check)
                    {
                        msg = (char*)"incorrect data check";
                        InflateState->mode = BAD;
                        break;
                    }
                    INITBITS();
                    Tracev((stderr, "inflate:   check matches trailer\n"));
                }
#ifdef GUNZIP
                InflateState->mode = LENGTH;
            case LENGTH:
                if (InflateState->wrap && InflateState->flags)
                {
                    NEEDBITS(32);
                    if (hold != (InflateState->total & 0xffffffffUL))
                    {
                        msg = (char*)"incorrect length check";
                        InflateState->mode = BAD;
                        break;
                    }
                    INITBITS();
                    Tracev((stderr, "inflate:   length matches trailer\n"));
                }
#endif
                InflateState->mode = DONE;
            case DONE:
                ret = Z_STREAM_END;
                goto inf_leave;
            case BAD:
                ret = Z_DATA_ERROR;
                goto inf_leave;
            case MEM:
                return Z_MEM_ERROR;
            case SYNC:
            default:
                return Z_STREAM_ERROR;
        }

    /*
       Return from inflate(), updating the total counts and the check value.
       If there was no progress during the inflate() call, return a buffer
       error.  Call updatewindow() to create and/or update the window state.
       Note: a memory error from inflate() is non-recoverable.
     */
inf_leave:
    RESTORE();
    if (InflateState->wsize || (out != avail_out && InflateState->mode < BAD &&
        (InflateState->mode < CHECK || flush != Z_FINISH)))
        if (updatewindow(next_out, out - avail_out))
        {
            InflateState->mode = MEM;
            return Z_MEM_ERROR;
        }
    in -= avail_in;
    out -= avail_out;
    total_in += in;
    total_out += out;
    InflateState->total += out;
    if ((InflateState->wrap & 4) && out)
        adler = InflateState->check =
        UPDATE(InflateState->check, next_out - out, out);
    data_type = (int)InflateState->bits + (InflateState->last ? 64 : 0) +
        (InflateState->mode == TYPE ? 128 : 0) +
        (InflateState->mode == LEN_ || InflateState->mode == COPY_ ? 256 : 0);
    if (((in == 0 && out == 0) || flush == Z_FINISH) && ret == Z_OK)
        ret = Z_BUF_ERROR;
    return ret;
}

int  ZLibStream::inflateEnd()
{
    // inlfate Mode
    if (inflateStateCheck())
        return Z_STREAM_ERROR;
    
    if (InflateState->window != 0) ZFREE(this, InflateState->window);
    ZFREE(this, InflateState);
    InflateState = 0;
    Tracev((stderr, "inflate: end\n"));
    return Z_OK;
}

int  ZLibStream::inflateGetDictionary( unsigned char* dictionary, unsigned int* dictLength)
{
    // inlfate Mode

    /* check state */
    if (inflateStateCheck()) return Z_STREAM_ERROR;
    

    /* copy dictionary */
    if (InflateState->whave && dictionary != 0)
    {
        memcpy(dictionary, InflateState->window + InflateState->wnext,
            InflateState->whave - InflateState->wnext);
        memcpy(dictionary + InflateState->whave - InflateState->wnext,
            InflateState->window, InflateState->wnext);
    }
    if (dictLength != 0)
        *dictLength = InflateState->whave;
    return Z_OK;
}

int  ZLibStream::inflateSetDictionary( const unsigned char* dictionary, unsigned int dictLength)
{
    // inlfate Mode
    unsigned long dictid;
    int ret;

    /* check state */
    if (inflateStateCheck()) return Z_STREAM_ERROR;
    
    if (InflateState->wrap != 0 && InflateState->mode != DICT)
        return Z_STREAM_ERROR;

    /* check for correct dictionary identifier */
    if (InflateState->mode == DICT)
    {
        dictid = Adler32::Calculate(0L, 0, 0);
        dictid = Adler32::Calculate(dictid, dictionary, dictLength);
        if (dictid != InflateState->check)
            return Z_DATA_ERROR;
    }

    /* copy dictionary to window using updatewindow(), which will amend the
       existing dictionary if appropriate */
    ret = updatewindow(dictionary + dictLength, dictLength);
    if (ret)
    {
        InflateState->mode = MEM;
        return Z_MEM_ERROR;
    }
    InflateState->havedict = 1;
    Tracev((stderr, "inflate:   dictionary set\n"));
    return Z_OK;
}

int  ZLibStream::inflateGetHeader( GZipHeader* head)
{
    // inlfate Mode

    /* check state */
    if (inflateStateCheck()) return Z_STREAM_ERROR;
    
    if ((InflateState->wrap & 2) == 0) return Z_STREAM_ERROR;

    /* save header structure */
    InflateState->head = head;
    head->done = 0;
    return Z_OK;
}

int  ZLibStream::inflateSync()
{
    unsigned len;               /* number of bytes to look at or looked at */
    unsigned long in, out;      /* temporary to save total_in and total_out */
    unsigned char buf[4];       /* to restore bit buffer to byte string */
    // inlfate Mode

    /* check parameters */
    if (inflateStateCheck()) return Z_STREAM_ERROR;
    
    if (avail_in == 0 && InflateState->bits < 8) return Z_BUF_ERROR;

    /* if first time, start search in bit buffer */
    if (InflateState->mode != SYNC)
    {
        InflateState->mode = SYNC;
        InflateState->hold <<= InflateState->bits & 7;
        InflateState->bits -= InflateState->bits & 7;
        len = 0;
        while (InflateState->bits >= 8)
        {
            buf[len++] = (unsigned char)(InflateState->hold);
            InflateState->hold >>= 8;
            InflateState->bits -= 8;
        }
        InflateState->have = 0;
        syncsearch(&(InflateState->have), buf, len);
    }

    /* search available input */
    len = syncsearch(&(InflateState->have), next_in, avail_in);
    avail_in -= len;
    next_in += len;
    total_in += len;

    /* return no joy or set up to restart inflate() on a new block */
    if (InflateState->have != 4) return Z_DATA_ERROR;
    in = total_in;  out = total_out;
    inflateReset();
    total_in = in;  total_out = out;
    InflateState->mode = TYPE;
    return Z_OK;
}

int   ZLibStream::inflateSyncPoint()
{
    if (inflateStateCheck()) return Z_STREAM_ERROR;

    return InflateState->mode == STORED && InflateState->bits == 0;
}

int  ZLibStream::inflateCopy(ZLibStream* dest, ZLibStream* source)
{
    InflateStateData* copy;
    unsigned char* window;
    unsigned wsize;

    /* check input */
    if (source->inflateStateCheck() || dest == 0)
        return Z_STREAM_ERROR;
    InflateState = source->InflateState;

    /* allocate space */
    copy = (InflateStateData*)
        ZALLOC(source, 1, sizeof(InflateStateData));
    if (copy == 0) return Z_MEM_ERROR;
    window = 0;
    if (InflateState->window != 0)
    {
        window = (unsigned char*)
            ZALLOC(source, 1U << InflateState->wbits, sizeof(unsigned char));
        if (window == 0)
        {
            ZFREE(source, copy);
            return Z_MEM_ERROR;
        }
    }

    /* copy state */
    memcpy((void*)dest, (void*)source, sizeof(ZLibStream));
    memcpy((void*)copy, (void*)InflateState, sizeof(InflateStateData));
    copy->strm = dest;
    if (InflateState->lencode >= InflateState->codes &&
        InflateState->lencode <= InflateState->codes + ENOUGH - 1)
    {
        copy->lencode = copy->codes + (InflateState->lencode - InflateState->codes);
        copy->distcode = copy->codes + (InflateState->distcode - InflateState->codes);
    }
    copy->next = copy->codes + (InflateState->next - InflateState->codes);
    if (window != 0)
    {
        wsize = 1U << InflateState->wbits;
        memcpy(window, InflateState->window, wsize);
    }
    copy->window = window;
    dest->InflateState = copy;
    return Z_OK;
}

int  ZLibStream::inflateUndermine( int subvert)
{
    if (inflateStateCheck()) return Z_STREAM_ERROR;

#ifdef INFLATE_ALLOW_INVALID_DISTANCE_TOOFAR_ARRR
    InflateState->sane = !subvert;
    return Z_OK;
#else
    (void)subvert;
    InflateState->sane = 1;
    return Z_DATA_ERROR;
#endif
}

int  ZLibStream::inflateValidate( int check)
{
    if (inflateStateCheck()) return Z_STREAM_ERROR;

    if (check)
        InflateState->wrap |= 4;
    else
        InflateState->wrap &= ~4;
    return Z_OK;
}

long  ZLibStream::inflateMark()
{
    if (inflateStateCheck())
        return -(1L << 16);
  
    return (long)(((unsigned long)((long)InflateState->back)) << 16) +
        (InflateState->mode == COPY ? InflateState->length :
            (InflateState->mode == MATCH ? InflateState->was - InflateState->length : 0));
}

unsigned long  ZLibStream::inflateCodesUsed()
{
    if (inflateStateCheck()) return (unsigned long)-1;

    return (unsigned long)(InflateState->next - InflateState->codes);
}

int ZLibStream::inflateBackEnd()
{
    if (InflateState == 0 || zfree == (free_func)0)
        return Z_STREAM_ERROR;
    ZFREE(this, InflateState);
    InflateState = 0;
    Tracev((stderr, "inflate: end\n"));
    return Z_OK;
}

int ZLibStream::inflateBack( in_func in, void* in_desc, out_func out, void* out_desc)
{
    unsigned char* next;    /* next input */
    unsigned char* put;     /* next output */
    unsigned have, left;        /* available input and output */
    unsigned long hold;         /* bit buffer */
    unsigned bits;              /* bits in bit buffer */
    unsigned copy;              /* number of stored or match bytes to copy */
    unsigned char* from;    /* where to copy match bytes from */
    HuffCode here;                  /* current decoding table entry */
    HuffCode last;                  /* parent table entry */
    unsigned len;               /* length to copy for repeats, bits to drop */
    int ret;                    /* return code */
    static const unsigned short order[19] = /* permutation of code lengths */
    { 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15 };


    /* Reset the state */
    msg = 0;
    InflateState->mode = TYPE;
    InflateState->last = 0;
    InflateState->whave = 0;
    next = next_in;
    have = next != 0 ? avail_in : 0;
    hold = 0;
    bits = 0;
    put = InflateState->window;
    left = InflateState->wsize;

    /* Inflate until end of block marked as last */
    for (;;)
        switch (InflateState->mode)
        {
            case TYPE:
                /* determine and dispatch block type */
                if (InflateState->last)
                {
                    BYTEBITS();
                    InflateState->mode = DONE;
                    break;
                }
                NEEDBITS(3);
                InflateState->last = BITS(1);
                DROPBITS(1);
                switch (BITS(2))
                {
                    case 0:                             /* stored block */
                        Tracev((stderr, "inflate:     stored block%s\n",
                            InflateState->last ? " (last)" : ""));
                        InflateState->mode = STORED;
                        break;
                    case 1:                             /* fixed block */
                        InflateState->fixedtables();
                        Tracev((stderr, "inflate:     fixed codes block%s\n",
                            InflateState->last ? " (last)" : ""));
                        InflateState->mode = LEN;              /* decode codes */
                        break;
                    case 2:                             /* dynamic block */
                        Tracev((stderr, "inflate:     dynamic codes block%s\n",
                            InflateState->last ? " (last)" : ""));
                        InflateState->mode = TABLE;
                        break;
                    case 3:
                        msg = (char*)"invalid block type";
                        InflateState->mode = BAD;
                }
                DROPBITS(2);
                break;

            case STORED:
                /* get and verify stored block length */
                BYTEBITS();                         /* go to byte boundary */
                NEEDBITS(32);

                if ((hold & 0xffff) != ((hold >> 16) ^ 0xffff))
                {
                    msg = (char*)"invalid stored block lengths";
                    InflateState->mode = BAD;
                    break;
                }
                InflateState->length = (unsigned)hold & 0xffff;

                Tracev((stderr, "inflate:       stored length %u\n", InflateState->length));

                INITBITS();

                /* copy stored block from input to output */
                while (InflateState->length != 0)
                {
                    copy = InflateState->length;


                    PULL();


                    ROOM();



                    if (copy > have) copy = have;
                    if (copy > left) copy = left;
                    memcpy(put, next, copy);
                    have -= copy;
                    next += copy;
                    left -= copy;
                    put += copy;
                    InflateState->length -= copy;
                }
                Tracev((stderr, "inflate:       stored end\n"));
                InflateState->mode = TYPE;
                break;

            case TABLE:
                /* get dynamic table entries descriptor */
                NEEDBITS(14);
                InflateState->nlen = BITS(5) + 257;
                DROPBITS(5);
                InflateState->ndist = BITS(5) + 1;
                DROPBITS(5);
                InflateState->ncode = BITS(4) + 4;
                DROPBITS(4);
#ifndef PKZIP_BUG_WORKAROUND
                if (InflateState->nlen > 286 || InflateState->ndist > 30)
                {
                    msg = (char*)"too many length or distance symbols";
                    InflateState->mode = BAD;
                    break;
                }
#endif
                Tracev((stderr, "inflate:       table sizes ok\n"));

                /* get code length code lengths (not a typo) */
                InflateState->have = 0;
                while (InflateState->have < InflateState->ncode)
                {
                    NEEDBITS(3);
                    InflateState->lens[order[InflateState->have++]] = (unsigned short)BITS(3);
                    DROPBITS(3);
                }
                while (InflateState->have < 19)
                    InflateState->lens[order[InflateState->have++]] = 0;
                InflateState->next = InflateState->codes;
                InflateState->lencode = (HuffCode const*)(InflateState->next);
                InflateState->lenbits = 7;
                ret = inflate_table(HuffCodeType::CODES, InflateState->lens, 19, &(InflateState->next),
                    &(InflateState->lenbits), InflateState->work);
                if (ret)
                {
                    msg = (char*)"invalid code lengths set";
                    InflateState->mode = BAD;
                    break;
                }
                Tracev((stderr, "inflate:       code lengths ok\n"));

                /* get length and distance code code lengths */
                InflateState->have = 0;
                while (InflateState->have < InflateState->nlen + InflateState->ndist)
                {
                    for (;;)
                    {
                        here = InflateState->lencode[BITS(InflateState->lenbits)];
                        if ((unsigned)(here.bits) <= bits) break;
                        PULLBYTE();
                    }
                    if (here.val < 16)
                    {
                        DROPBITS(here.bits);
                        InflateState->lens[InflateState->have++] = here.val;
                    }
                    else
                    {
                        if (here.val == 16)
                        {
                            NEEDBITS(here.bits + 2);
                            DROPBITS(here.bits);
                            if (InflateState->have == 0)
                            {
                                msg = (char*)"invalid bit length repeat";
                                InflateState->mode = BAD;
                                break;
                            }
                            len = (unsigned)(InflateState->lens[InflateState->have - 1]);
                            copy = 3 + BITS(2);
                            DROPBITS(2);
                        }
                        else if (here.val == 17)
                        {
                            NEEDBITS(here.bits + 3);
                            DROPBITS(here.bits);
                            len = 0;
                            copy = 3 + BITS(3);
                            DROPBITS(3);
                        }
                        else
                        {
                            NEEDBITS(here.bits + 7);
                            DROPBITS(here.bits);
                            len = 0;
                            copy = 11 + BITS(7);
                            DROPBITS(7);
                        }
                        if (InflateState->have + copy > InflateState->nlen + InflateState->ndist)
                        {
                            msg = (char*)"invalid bit length repeat";
                            InflateState->mode = BAD;
                            break;
                        }
                        while (copy--)
                            InflateState->lens[InflateState->have++] = (unsigned short)len;
                    }
                }

                /* handle error breaks in while */
                if (InflateState->mode == BAD) break;

                /* check for end-of-block code (better have one) */
                if (InflateState->lens[256] == 0)
                {
                    msg = (char*)"invalid code -- missing end-of-block";
                    InflateState->mode = BAD;
                    break;
                }

                /* build code tables -- note: do not change the lenbits or distbits
                   values here (9 and 6) without reading the comments in inftrees.h
                   concerning the ENOUGH constants, which depend on those values */
                InflateState->next = InflateState->codes;
                InflateState->lencode = (HuffCode const*)(InflateState->next);
                InflateState->lenbits = 9;
                ret = inflate_table(HuffCodeType::LENS, InflateState->lens, InflateState->nlen, &(InflateState->next),
                    &(InflateState->lenbits), InflateState->work);
                if (ret)
                {
                    msg = (char*)"invalid literal/lengths set";
                    InflateState->mode = BAD;
                    break;
                }
                InflateState->distcode = (HuffCode const*)(InflateState->next);
                InflateState->distbits = 6;
                ret = inflate_table(HuffCodeType::DISTS, InflateState->lens + InflateState->nlen, InflateState->ndist,
                    &(InflateState->next), &(InflateState->distbits), InflateState->work);
                if (ret)
                {
                    msg = (char*)"invalid distances set";
                    InflateState->mode = BAD;
                    break;
                }
                Tracev((stderr, "inflate:       codes ok\n"));
                InflateState->mode = LEN;

            case LEN:
                /* use inflate_fast() if we have enough input and output */
                if (have >= 6 && left >= 258)
                {
                    RESTORE();
                    if (InflateState->whave < InflateState->wsize)
                        InflateState->whave = InflateState->wsize - left;
                    inflate_fast(InflateState->wsize);
                    LOAD();
                    break;
                }

                /* get a literal, length, or end-of-block code */
                for (;;)
                {
                    here = InflateState->lencode[BITS(InflateState->lenbits)];
                    if ((unsigned)(here.bits) <= bits) break;
                    PULLBYTE();
                }
                if (here.op && (here.op & 0xf0) == 0)
                {
                    last = here;
                    for (;;)
                    {
                        here = InflateState->lencode[last.val + (BITS(last.bits + last.op) >> last.bits)];

                        if ((unsigned)(last.bits + here.bits) <= bits) break;

                        PULLBYTE();
                    }
                    DROPBITS(last.bits);
                }
                DROPBITS(here.bits);
                InflateState->length = (unsigned)here.val;

                /* process literal */
                if (here.op == 0)
                {
                    Tracevv((stderr, here.val >= 0x20 && here.val < 0x7f ?
                        "inflate:         literal '%c'\n" :
                        "inflate:         literal 0x%02x\n", here.val));
                    ROOM();
                    *put++ = (unsigned char)(InflateState->length);
                    left--;
                    InflateState->mode = LEN;
                    break;
                }

                /* process end of block */
                if (here.op & 32)
                {
                    Tracevv((stderr, "inflate:         end of block\n"));
                    InflateState->mode = TYPE;
                    break;
                }

                /* invalid code */
                if (here.op & 64)
                {
                    msg = (char*)"invalid literal/length code";
                    InflateState->mode = BAD;
                    break;
                }

                /* length code -- get extra bits, if any */
                InflateState->extra = (unsigned)(here.op) & 15;
                if (InflateState->extra != 0)
                {
                    NEEDBITS(InflateState->extra);
                    InflateState->length += BITS(InflateState->extra);
                    DROPBITS(InflateState->extra);
                }
                Tracevv((stderr, "inflate:         length %u\n", InflateState->length));

                /* get distance code */
                for (;;)
                {
                    here = InflateState->distcode[BITS(InflateState->distbits)];
                    if ((unsigned)(here.bits) <= bits) break;
                    PULLBYTE();
                }
                if ((here.op & 0xf0) == 0)
                {
                    last = here;
                    for (;;)
                    {
                        here = InflateState->distcode[last.val +
                            (BITS(last.bits + last.op) >> last.bits)];
                        if ((unsigned)(last.bits + here.bits) <= bits) break;
                        PULLBYTE();
                    }
                    DROPBITS(last.bits);
                }
                DROPBITS(here.bits);
                if (here.op & 64)
                {
                    msg = (char*)"invalid distance code";
                    InflateState->mode = BAD;
                    break;
                }
                InflateState->offset = (unsigned)here.val;

                /* get distance extra bits, if any */
                InflateState->extra = (unsigned)(here.op) & 15;
                if (InflateState->extra != 0)
                {
                    NEEDBITS(InflateState->extra);
                    InflateState->offset += BITS(InflateState->extra);
                    DROPBITS(InflateState->extra);
                }
                if (InflateState->offset > InflateState->wsize - (InflateState->whave < InflateState->wsize ?
                    left : 0))
                {
                    msg = (char*)"invalid distance too far back";
                    InflateState->mode = BAD;
                    break;
                }
                Tracevv((stderr, "inflate:         distance %u\n", InflateState->offset));

                /* copy match from window to output */
                do
                {
                    ROOM();
                    copy = InflateState->wsize - InflateState->offset;
                    if (copy < left)
                    {
                        from = put + copy;
                        copy = left - copy;
                    }
                    else
                    {
                        from = put - InflateState->offset;
                        copy = left;
                    }
                    if (copy > InflateState->length) copy = InflateState->length;
                    InflateState->length -= copy;
                    left -= copy;
                    do
                    {
                        *put++ = *from++;
                    }
                    while (--copy);
                }
                while (InflateState->length != 0);
                break;

            case DONE:
                /* inflate stream terminated properly -- write leftover output */
                ret = Z_STREAM_END;
                if (left < InflateState->wsize)
                {
                    if (out(out_desc, InflateState->window, InflateState->wsize - left))
                        ret = Z_BUF_ERROR;
                }
                goto inf_leave;

            case BAD:
                ret = Z_DATA_ERROR;
                goto inf_leave;

            default:                /* can't happen, but makes compilers happy */
                ret = Z_STREAM_ERROR;
                goto inf_leave;
        }

    /* Return unused input */
inf_leave:
    next_in = next;
    avail_in = have;
    return ret;
}

int  ZLibStream::inflateBackInit_( int windowBits, unsigned char* window, const char* version, int stream_size)
{
    // inlfate Mode

    if (version == 0 || version[0] != ZLIB_VERSION[0] ||
        stream_size != (int)(sizeof(ZLibStream)))
        return Z_VERSION_ERROR;
    if (window == 0 ||
        windowBits < 8 || windowBits > 15)
        return Z_STREAM_ERROR;
    msg = 0;                 /* in case we return an error */
    if (zalloc == (alloc_func)0)
    {
#ifdef Z_SOLO
        return Z_STREAM_ERROR;
#else
        zalloc = zcalloc;
        opaque = (void*)0;
#endif
    }
    if (zfree == (free_func)0)
#ifdef Z_SOLO
        return Z_STREAM_ERROR;
#else
        zfree = zcfree;
#endif
    InflateState = (InflateStateData*)ZALLOC(this, 1, sizeof(InflateStateData));
    if (InflateState == 0) return Z_MEM_ERROR;
    Tracev((stderr, "inflate: allocated\n"));
    InflateState->dmax = 32768U;
    InflateState->wbits = (unsigned int)windowBits;
    InflateState->wsize = 1U << windowBits;
    InflateState->window = window;
    InflateState->wnext = 0;
    InflateState->whave = 0;
    return Z_OK;
}