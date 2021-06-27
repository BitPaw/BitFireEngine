#include "DeflateStateData.h"
#include <stdio.h>
#include "ZLibStream.h"

void DeflateStateData::slide_hash()
{
    unsigned n, m;
    unsigned short* p;
    unsigned int wsize = w_size;

    n = hash_size;
    p = &head[n];
    do
    {
        m = *--p;
        *p = (unsigned short)(m >= wsize ? m - wsize : 0);
    }
    while (--n);
    n = wsize;
#ifndef FASTEST
    p = &prev[n];
    do
    {
        m = *--p;
        *p = (unsigned short)(m >= wsize ? m - wsize : 0);
        /* If n is not on any hash chain, prev[n] is garbage but
         * its value will never be used.
         */
    }
    while (--n);
#endif
}

void DeflateStateData::lm_init()
{
    window_size = (unsigned long)2L * w_size;

    CLEAR_HASH(this);

    /* Set the default configuration parameters:
     */
    max_lazy_match = configuration_table[level].max_lazy;
    good_match = configuration_table[level].good_length;
    nice_match = configuration_table[level].nice_length;
    max_chain_length = configuration_table[level].max_chain;

    strstart = 0;
    block_start = 0L;
    lookahead = 0;
    insert = 0;
    match_length = prev_length = MIN_MATCH - 1;
    match_available = 0;
    ins_h = 0;
#ifndef FASTEST
#ifdef ASMV
    match_init(); /* initialize the asm code */
#endif
#endif
}

unsigned int DeflateStateData::longest_match( unsigned int cur_match)
{
    unsigned chain_length = max_chain_length;/* max hash chain length */
    register unsigned char* scan = window + strstart; /* current string */
    register unsigned char* match;                      /* matched string */
    register int len;                           /* length of current match */
    int best_len = (int)prev_length;         /* best match length so far */
    int nice_match = 0;             /* stop if match long enough */
    unsigned int limit = strstart > (unsigned int)MAX_DIST(this) ?
        strstart - (unsigned int)MAX_DIST(this) : 0;
    /* Stop when cur_match becomes <= limit. To simplify the code,
     * we prevent matches with the string of window index 0.
     */
    unsigned short* prev = 0;
    unsigned int wmask = w_mask;

#ifdef UNALIGNED_OK
    /* Compare two bytes at a time. Note: this is not always beneficial.
     * Try with and without -DUNALIGNED_OK to check.
     */
    register unsigned char* strend = window + strstart + MAX_MATCH - 1;
    register unsigned short scan_start = *(unsigned short*)scan;
    register unsigned short scan_end = *(unsigned short*)(scan + best_len - 1);
#else
    register unsigned char* strend = window + strstart + MAX_MATCH;
    register unsigned char scan_end1 = scan[best_len - 1];
    register unsigned char scan_end = scan[best_len];
#endif

    /* The code is optimized for HASH_BITS >= 8 and MAX_MATCH-2 multiple of 16.
     * It is easy to get rid of this optimization if necessary.
     */
    Assert(hash_bits >= 8 && MAX_MATCH == 258, "fc.code too clever");

    /* Do not waste too much time if we already have a good match: */
    if (prev_length >= good_match)
    {
        chain_length >>= 2;
    }
    /* Do not look for matches beyond the end of the input. This is necessary
     * to make deflate deterministic.
     */
    if ((unsigned int)nice_match > lookahead) nice_match = (int)lookahead;

    Assert((unsigned long)strstart <= window_size - MIN_LOOKAHEAD, "need lookahead");

    do
    {
        Assert(cur_match < strstart, "no future");
        match = window + cur_match;

        /* Skip to next match if the match length cannot increase
         * or if the match length is less than 2.  Note that the checks below
         * for insufficient lookahead only occur occasionally for performance
         * reasons.  Therefore uninitialized memory will be accessed, and
         * conditional jumps will be made that depend on those values.
         * However the length of the match is limited to the lookahead, so
         * the output of deflate is not affected by the uninitialized values.
         */
#if (defined(UNALIGNED_OK) && MAX_MATCH == 258)
         /* This code assumes sizeof(unsigned short) == 2. Do not use
          * UNALIGNED_OK if your compiler uses a different size.
          */
        if (*(unsigned short*)(match + best_len - 1) != scan_end ||
            *(unsigned short*)match != scan_start) continue;

        /* It is not necessary to compare scan[2] and match[2] since they are
         * always equal when the other bytes match, given that the hash keys
         * are equal and that HASH_BITS >= 8. Compare 2 bytes at a time at
         * strstart+3, +5, ... up to strstart+257. We check for insufficient
         * lookahead only every 4th comparison; the 128th check will be made
         * at strstart+257. If MAX_MATCH-2 is not a multiple of 8, it is
         * necessary to put more guard bytes at the end of the window, or
         * to check more often for insufficient lookahead.
         */
        Assert(scan[2] == match[2], "scan[2]?");
        scan++, match++;
        do
        {
        }
        while (*(unsigned short*)(scan += 2) == *(unsigned short*)(match += 2) &&
            *(unsigned short*)(scan += 2) == *(unsigned short*)(match += 2) &&
            *(unsigned short*)(scan += 2) == *(unsigned short*)(match += 2) &&
            *(unsigned short*)(scan += 2) == *(unsigned short*)(match += 2) &&
            scan < strend);
        /* The funny "do {}" generates better code on most compilers */

        /* Here, scan <= window+strstart+257 */
        Assert(scan <= window + (unsigned)(window_size - 1), "wild scan");
        if (*scan == *match) scan++;

        len = (MAX_MATCH - 1) - (int)(strend - scan);
        scan = strend - (MAX_MATCH - 1);

#else /* UNALIGNED_OK */

        if (match[best_len] != scan_end ||
            match[best_len - 1] != scan_end1 ||
            *match != *scan ||
            *++match != scan[1])      continue;

        /* The check at best_len-1 can be removed because it will be made
         * again later. (This heuristic is not always a win.)
         * It is not necessary to compare scan[2] and match[2] since they
         * are always equal when the other bytes match, given that
         * the hash keys are equal and that HASH_BITS >= 8.
         */
        scan += 2, match++;
        Assert(*scan == *match, "match[2]?");

        /* We check for insufficient lookahead only every 8th comparison;
         * the 256th check will be made at strstart+258.
         */
        do
        {
        }
        while (*++scan == *++match && *++scan == *++match &&
            *++scan == *++match && *++scan == *++match &&
            *++scan == *++match && *++scan == *++match &&
            *++scan == *++match && *++scan == *++match &&
            scan < strend);

        Assert(scan <= window + (unsigned)(window_size - 1), "wild scan");

        len = MAX_MATCH - (int)(strend - scan);
        scan = strend - MAX_MATCH;

#endif /* UNALIGNED_OK */

        if (len > best_len)
        {
            match_start = cur_match;
            best_len = len;
            if (len >= nice_match) break;
#ifdef UNALIGNED_OK
            scan_end = *(unsigned short*)(scan + best_len - 1);
#else
            scan_end1 = scan[best_len - 1];
            scan_end = scan[best_len];
#endif
        }
    }
    while ((cur_match = prev[cur_match & wmask]) > limit
        && --chain_length != 0);

    if ((unsigned int)best_len <= lookahead) return (unsigned int)best_len;
    return lookahead;
}

block_state DeflateStateData::deflate_stored( int flush)
{
    /* Smallest worthy block size when not flushing or finishing. By default
     * this is 32K. This can be as small as 507 bytes for memLevel == 1. For
     * large input and output buffers, the stored block size will be larger.
     */
    unsigned min_block = MIN(pending_buf_size - 5, w_size);

    /* Copy as many min_block or larger stored blocks directly to next_out as
     * possible. If flushing, copy the remaining available input to next_out as
     * stored blocks, if there is enough space.
     */
    unsigned len, left, have, last = 0;
    unsigned used = strm->avail_in;
    do
    {
        /* Set len to the maximum size block that we can copy directly with the
         * available input data and output space. Set left to how much of that
         * would be copied from what' left in the window.
         */
        len = MAX_STORED;       /* maximum deflate stored block length */
        have = (bi_valid + 42) >> 3;         /* number of header bytes */
        if (strm->avail_out < have)          /* need room for header */
            break;
        /* maximum stored block length that will fit in avail_out: */
        have = strm->avail_out - have;
        left = strstart - block_start;    /* bytes left in window */
        if (len > (unsigned long)left + strm->avail_in)
            len = left + strm->avail_in;     /* limit len to the input */
        if (len > have)
            len = have;                         /* limit len to the output */

        /* If the stored block would be less than min_block in length, or if
         * unable to copy all of the available input when flushing, then try
         * copying to the window and the pending buffer instead. Also don't
         * write an empty block when flushing -- deflate() does that.
         */
        if (len < min_block && ((len == 0 && flush != Z_FINISH) ||
            flush == Z_NO_FLUSH ||
            len != left + strm->avail_in))
            break;

        /* Make a dummy stored block in pending to get the header bytes,
         * including any pending bits. This also updates the debugging counts.
         */
        last = flush == Z_FINISH && len == left + strm->avail_in ? 1 : 0;
        _tr_stored_block( (char*)0, 0L, last);

        /* Replace the lengths in the dummy stored block with len. */
        pending_buf[pending - 4] = len;
        pending_buf[pending - 3] = len >> 8;
        pending_buf[pending - 2] = ~len;
        pending_buf[pending - 1] = ~len >> 8;

        /* Write the stored block header bytes. */
        strm->flush_pending();

#ifdef ZLIB_DEBUG
        /* Update debugging counts for the data about to be copied. */
        compressed_len += len << 3;
        bits_sent += len << 3;
#endif

        /* Copy uncompressed bytes from the window to next_out. */
        if (left)
        {
            if (left > len)
                left = len;
            memcpy(strm->next_out, window + block_start, left);
            strm->next_out += left;
            strm->avail_out -= left;
            strm->total_out += left;
            block_start += left;
            len -= left;
        }

        /* Copy uncompressed bytes directly from next_in to next_out, updating
         * the check value.
         */
        if (len)
        {
            strm->read_buf(strm->next_out, len);
            strm->next_out += len;
            strm->avail_out -= len;
            strm->total_out += len;
        }
    }
    while (last == 0);

    /* Update the sliding window with the last w_size bytes of the copied
     * data, or append all of the copied data to the existing window if less
     * than w_size bytes were copied. Also update the number of bytes to
     * insert in the hash tables, in the event that deflateParams() switches to
     * a non-zero compression level.
     */
    used -= strm->avail_in;      /* number of input bytes directly copied */
    if (used)
    {
        /* If any input was used, then no unused input remains in the window,
         * therefore block_start == strstart.
         */
        if (used >= w_size)
        {    /* supplant the previous history */
            matches = 2;         /* clear hash */
            memcpy(window, strm->next_in - w_size, w_size);
            strstart = w_size;
        }
        else
        {
            if (window_size - strstart <= used)
            {
                /* Slide the window down. */
                strstart -= w_size;
                memcpy(window, window + w_size, strstart);
                if (matches < 2)
                    matches++;   /* add a pending slide_hash() */
            }
            memcpy(window + strstart, strm->next_in - used, used);
            strstart += used;
        }
        block_start = strstart;
        insert += MIN(used, w_size - insert);
    }
    if (high_water < strstart)
        high_water = strstart;

    /* If the last block was written to next_out, then done. */
    if (last)
        return block_state::finish_done;

    /* If flushing and all input has been consumed, then done. */
    if (flush != Z_NO_FLUSH && flush != Z_FINISH &&
        strm->avail_in == 0 && (long)strstart == block_start)
        return block_state::block_done;

    /* Fill the window with any remaining input. */
    have = window_size - strstart - 1;
    if (strm->avail_in > have && block_start >= (long)w_size)
    {
        /* Slide the window down. */
        block_start -= w_size;
        strstart -= w_size;
        memcpy(window, window + w_size, strstart);
        if (matches < 2)
            matches++;           /* add a pending slide_hash() */
        have += w_size;          /* more space now */
    }
    if (have > strm->avail_in)
        have = strm->avail_in;
    if (have)
    {
        strm->read_buf(window + strstart, have);
        strstart += have;
    }
    if (high_water < strstart)
        high_water = strstart;

    /* There was not enough avail_out to write a complete worthy or flushed
     * stored block to next_out. Write a stored block to pending instead, if we
     * have enough input for a worthy block, or if flushing and there is enough
     * room for the remaining input as a stored block in the pending buffer.
     */
    have = (bi_valid + 42) >> 3;         /* number of header bytes */
        /* maximum stored block length that will fit in pending: */
    have = MIN(pending_buf_size - have, MAX_STORED);
    min_block = MIN(have, w_size);
    left = strstart - block_start;
    if (left >= min_block ||
        ((left || flush == Z_FINISH) && flush != Z_NO_FLUSH &&
            strm->avail_in == 0 && left <= have))
    {
        len = MIN(left, have);
        last = flush == Z_FINISH && strm->avail_in == 0 &&
            len == left ? 1 : 0;
        _tr_stored_block( (char*)window + block_start, len, last);
        block_start += len;

        strm->flush_pending();
    }

    /* We've done all we can with the available input and output. */
    return last ? block_state::finish_started : block_state::need_more;
}

block_state DeflateStateData::deflate_fast( int flush)
{
    unsigned int hash_head;       /* head of the hash chain */
    int bflush;           /* set if current block must be flushed */

    for (;;)
    {
        /* Make sure that we always have enough lookahead, except
         * at the end of the input file. We need MAX_MATCH bytes
         * for the next match, plus MIN_MATCH bytes to insert the
         * string following the next match.
         */
        if (lookahead < MIN_LOOKAHEAD)
        {
            fill_window();
            if (lookahead < MIN_LOOKAHEAD && flush == Z_NO_FLUSH)
            {
                return  block_state::need_more;
            }
            if (lookahead == 0) break; /* flush the current block */
        }

        /* Insert the string window[strstart .. strstart+2] in the
         * dictionary, and set hash_head to the head of the hash chain:
         */
        hash_head = 0;
        if (lookahead >= MIN_MATCH)
        {
            INSERT_STRING(this, strstart, hash_head);
        }

        /* Find the longest match, discarding those <= prev_length.
         * At this point we have always match_length < MIN_MATCH
         */
        if (hash_head != 0 && strstart - hash_head <= MAX_DIST(this))
        {
            /* To simplify the code, we prevent matches with the string
             * of window index 0 (in particular we have to avoid a match
             * of the string with itself at the start of the input file).
             */
            match_length = longest_match( hash_head);
            /* longest_match() sets match_start */
        }
        if (match_length >= MIN_MATCH)
        {
            check_match( strstart, match_start, match_length);

            _tr_tally_dist(this, strstart - match_start,
                match_length - MIN_MATCH, bflush);

            lookahead -= match_length;

            /* Insert new strings in the hash table only if the match length
             * is not too large. This saves time but degrades compression.
             */
#ifndef FASTEST
            if (match_length <= max_insert_length &&
                lookahead >= MIN_MATCH)
            {
                match_length--; /* string at strstart already in table */
                do
                {
                    strstart++;
                    INSERT_STRING(this, strstart, hash_head);
                    /* strstart never exceeds WSIZE-MAX_MATCH, so there are
                     * always MIN_MATCH bytes ahead.
                     */
                }
                while (--match_length != 0);
                strstart++;
            }
            else
#endif
            {
                strstart += match_length;
                match_length = 0;
                ins_h = window[strstart];
                UPDATE_HASH(this, ins_h, window[strstart + 1]);
#if MIN_MATCH != 3
                Call UPDATE_HASH() MIN_MATCH - 3 more times
#endif
                    /* If lookahead < MIN_MATCH, ins_h is garbage, but it does not
                     * matter since it will be recomputed at next deflate call.
                     */
            }
        }
        else
        {
            /* No match, output a literal byte */
            Tracevv((stderr, "%c", window[strstart]));
            _tr_tally_lit(this, window[strstart], bflush);
            lookahead--;
            strstart++;
        }
        if (bflush) FLUSH_BLOCK(this, 0);
    }
    insert = strstart < MIN_MATCH - 1 ? strstart : MIN_MATCH - 1;
    if (flush == Z_FINISH)
    {
        FLUSH_BLOCK(this, 1);
        return block_state::finish_done;
    }
    if (last_lit)
        FLUSH_BLOCK(this, 0);
    return block_state::block_done;
}

void DeflateStateData::fill_window()
{
    unsigned n;
    unsigned more;    /* Amount of free space at the end of the window. */
    unsigned int wsize = w_size;

    Assert(lookahead < MIN_LOOKAHEAD, "already enough lookahead");

    do
    {
        more = (unsigned)(window_size - (unsigned long)lookahead - (unsigned long)strstart);

        /* Deal with !@#$% 64K limit: */
        if (sizeof(int) <= 2)
        {
            if (more == 0 && strstart == 0 && lookahead == 0)
            {
                more = wsize;

            }
            else if (more == (unsigned)(-1))
            {
                /* Very unlikely, but possible on 16 bit machine if
                 * strstart == 0 && lookahead == 1 (input done a byte at time)
                 */
                more--;
            }
        }

        /* If the window is almost full and there is insufficient lookahead,
         * move the upper half to the lower one to make room in the upper half.
         */
        if (strstart >= wsize + MAX_DIST(this))
        {

            memcpy(window, window + wsize, (unsigned)wsize - more);
            match_start -= wsize;
            strstart -= wsize; /* we now have strstart >= MAX_DIST */
            block_start -= (long)wsize;
            slide_hash();
            more += wsize;
        }
        if (strm->avail_in == 0) break;

        /* If there was no sliding:
         *    strstart <= WSIZE+MAX_DIST-1 && lookahead <= MIN_LOOKAHEAD - 1 &&
         *    more == window_size - lookahead - strstart
         * => more >= window_size - (MIN_LOOKAHEAD-1 + WSIZE + MAX_DIST-1)
         * => more >= window_size - 2*WSIZE + 2
         * In the BIG_MEM or MMAP case (not yet supported),
         *   window_size == input_size + MIN_LOOKAHEAD  &&
         *   strstart + lookahead <= input_size => more >= MIN_LOOKAHEAD.
         * Otherwise, window_size == 2*WSIZE so more >= 2.
         * If there was sliding, more >= WSIZE. So in all cases, more >= 2.
         */
        Assert(more >= 2, "more < 2");

        n = strm->read_buf(window + strstart + lookahead, more);
        lookahead += n;

        /* Initialize the hash value now that we have some input: */
        if (lookahead + insert >= MIN_MATCH)
        {
            unsigned int str = strstart - insert;
            ins_h = window[str];
            UPDATE_HASH(this, ins_h, window[str + 1]);
#if MIN_MATCH != 3
            Call UPDATE_HASH() MIN_MATCH - 3 more times
#endif
                while (insert)
                {
                    UPDATE_HASH(this, ins_h, window[str + MIN_MATCH - 1]);
#ifndef FASTEST
                    prev[str & w_mask] = head[ins_h];
#endif
                    head[ins_h] = (unsigned short)str;
                    str++;
                    insert--;
                    if (lookahead + insert < MIN_MATCH)
                        break;
                }
        }
        /* If the whole input has less than MIN_MATCH bytes, ins_h is garbage,
         * but this is not important since only literal bytes will be emitted.
         */

    }
    while (lookahead < MIN_LOOKAHEAD && strm->avail_in != 0);

    /* If the WIN_INIT bytes after the end of the current data have never been
     * written, then zero those bytes in order to avoid memory check reports of
     * the use of uninitialized (or uninitialised as Julian writes) bytes by
     * the longest match routines.  Update the high water mark for the next
     * time through here.  WIN_INIT is set to MAX_MATCH since the longest match
     * routines allow scanning to strstart + MAX_MATCH, ignoring lookahead.
     */
    if (high_water < window_size)
    {
        unsigned long curr = strstart + (unsigned long)(lookahead);
        unsigned long init;

        if (high_water < curr)
        {
            /* Previous high water mark below current data -- zero WIN_INIT
             * bytes or up to end of window, whichever is less.
             */
            init = window_size - curr;
            if (init > WIN_INIT)
                init = WIN_INIT;

            zmemzero(window + curr, (unsigned)init);
            high_water = curr + init;
        }
        else if (high_water < (unsigned long)curr + WIN_INIT)
        {
            /* High water mark at or above current data, but below current data
             * plus WIN_INIT -- zero out to current data plus WIN_INIT, or up
             * to end of window, whichever is less.
             */
            init = (unsigned long)curr + WIN_INIT - high_water;
            if (init > window_size - high_water)
                init = window_size - high_water;
            zmemzero(window + high_water, (unsigned)init);
            high_water += init;
        }
    }

    Assert((unsigned long)strstart <= window_size - MIN_LOOKAHEAD,
        "not enough room for search");
}

block_state DeflateStateData::deflate_slow( int flush)
{
    unsigned int hash_head;          /* head of hash chain */
    int bflush;              /* set if current block must be flushed */

    /* Process the input block. */
    for (;;)
    {
        /* Make sure that we always have enough lookahead, except
         * at the end of the input file. We need MAX_MATCH bytes
         * for the next match, plus MIN_MATCH bytes to insert the
         * string following the next match.
         */
        if (lookahead < MIN_LOOKAHEAD)
        {
            fill_window();
            if (lookahead < MIN_LOOKAHEAD && flush == Z_NO_FLUSH)
            {
                return block_state::need_more;
            }
            if (lookahead == 0) break; /* flush the current block */
        }

        /* Insert the string window[strstart .. strstart+2] in the
         * dictionary, and set hash_head to the head of the hash chain:
         */
        hash_head = 0;
        if (lookahead >= MIN_MATCH)
        {
            INSERT_STRING(this, strstart, hash_head);
        }

        /* Find the longest match, discarding those <= prev_length.
         */
        prev_length = match_length, prev_match = match_start;
        match_length = MIN_MATCH - 1;

        if (hash_head != 0 && prev_length < max_lazy_match &&
            strstart - hash_head <= MAX_DIST(this))
        {
            /* To simplify the code, we prevent matches with the string
             * of window index 0 (in particular we have to avoid a match
             * of the string with itself at the start of the input file).
             */
            match_length = longest_match( hash_head);
            /* longest_match() sets match_start */

            if (match_length <= 5 && (strategy == Z_FILTERED
#if TOO_FAR <= 32767
                || (match_length == MIN_MATCH &&
                    strstart - match_start > TOO_FAR)
#endif
                ))
            {

                /* If prev_match is also MIN_MATCH, match_start is garbage
                 * but we will ignore the current match anyway.
                 */
                match_length = MIN_MATCH - 1;
            }
        }
        /* If there was a match at the previous step and the current
         * match is not better, output the previous match:
         */
        if (prev_length >= MIN_MATCH && match_length <= prev_length)
        {
            unsigned int max_insert = strstart + lookahead - MIN_MATCH;
            /* Do not insert strings in hash table beyond this. */

            check_match( strstart - 1, prev_match, prev_length);

            _tr_tally_dist(this, strstart - 1 - prev_match,
                prev_length - MIN_MATCH, bflush);

            /* Insert in hash table all strings up to the end of the match.
             * strstart-1 and strstart are already inserted. If there is not
             * enough lookahead, the last two strings are not inserted in
             * the hash table.
             */
            lookahead -= prev_length - 1;
            prev_length -= 2;
            do
            {
                if (++strstart <= max_insert)
                {
                    INSERT_STRING(this, strstart, hash_head);
                }
            }
            while (--prev_length != 0);
            match_available = 0;
            match_length = MIN_MATCH - 1;
            strstart++;

            if (bflush) FLUSH_BLOCK(this, 0);

        }
        else if (match_available)
        {
            /* If there was no match at the previous position, output a
             * single literal. If there was a match but the current match
             * is longer, truncate the previous match to a single literal.
             */
            Tracevv((stderr, "%c", window[strstart - 1]));
            _tr_tally_lit(this, window[strstart - 1], bflush);
            if (bflush)
            {
                FLUSH_BLOCK_ONLY(this, 0);
            }
            strstart++;
            lookahead--;
            if (strm->avail_out == 0) return  block_state::need_more;
        }
        else
        {
            /* There is no previous match to compare with, wait for
             * the next step to decide.
             */
            match_available = 1;
            strstart++;
            lookahead--;
        }
    }
    Assert(flush != Z_NO_FLUSH, "no flush?");
    if (match_available)
    {
        Tracevv((stderr, "%c", window[strstart - 1]));
        _tr_tally_lit(this, window[strstart - 1], bflush);
        match_available = 0;
    }
    insert = strstart < MIN_MATCH - 1 ? strstart : MIN_MATCH - 1;
    if (flush == Z_FINISH)
    {
        FLUSH_BLOCK(this, 1);
        return  block_state::finish_done;
    }
    if (last_lit)
        FLUSH_BLOCK(this, 0);
    return block_state::block_done;
}

block_state DeflateStateData::deflate_rle( int flush)
{
    int bflush;             /* set if current block must be flushed */
    unsigned int prev;              /* byte at distance one to match */
    unsigned char* scan, * strend;   /* scan goes up to strend for length of run */

    for (;;)
    {
        /* Make sure that we always have enough lookahead, except
         * at the end of the input file. We need MAX_MATCH bytes
         * for the longest run, plus one for the unrolled loop.
         */
        if (lookahead <= MAX_MATCH)
        {
            fill_window();
            if (lookahead <= MAX_MATCH && flush == Z_NO_FLUSH)
            {
                return block_state::need_more;
            }
            if (lookahead == 0) break; /* flush the current block */
        }

        /* See how many times the previous byte repeats */
        match_length = 0;
        if (lookahead >= MIN_MATCH && strstart > 0)
        {
            scan = window + strstart - 1;
            prev = *scan;
            if (prev == *++scan && prev == *++scan && prev == *++scan)
            {
                strend = window + strstart + MAX_MATCH;
                do
                {
                }
                while (prev == *++scan && prev == *++scan &&
                    prev == *++scan && prev == *++scan &&
                    prev == *++scan && prev == *++scan &&
                    prev == *++scan && prev == *++scan &&
                    scan < strend);
                match_length = MAX_MATCH - (unsigned int)(strend - scan);
                if (match_length > lookahead)
                    match_length = lookahead;
            }
            Assert(scan <= window + (unsigned int)(window_size - 1), "wild scan");
        }

        /* Emit match if have run of MIN_MATCH or longer, else emit literal */
        if (match_length >= MIN_MATCH)
        {
            check_match( strstart, strstart - 1, match_length);

            _tr_tally_dist(this, 1, match_length - MIN_MATCH, bflush);

            lookahead -= match_length;
            strstart += match_length;
            match_length = 0;
        }
        else
        {
            /* No match, output a literal byte */
            Tracevv((stderr, "%c", window[strstart]));
            _tr_tally_lit(this, window[strstart], bflush);
            lookahead--;
            strstart++;
        }
        if (bflush) FLUSH_BLOCK(this, 0);
    }
    insert = 0;
    if (flush == Z_FINISH)
    {
        FLUSH_BLOCK(this, 1);
        return block_state::finish_done;
    }
    if (last_lit)
        FLUSH_BLOCK(this, 0);
    return block_state::block_done;
}

block_state DeflateStateData::deflate_huff( int flush)
{
    int bflush;             /* set if current block must be flushed */

    for (;;)
    {
        /* Make sure that we have a literal to write. */
        if (lookahead == 0)
        {
            fill_window();
            if (lookahead == 0)
            {
                if (flush == Z_NO_FLUSH)
                    return block_state::need_more;
                break;      /* flush the current block */
            }
        }

        /* Output a literal byte */
        match_length = 0;
        Tracevv((stderr, "%c", window[strstart]));
        _tr_tally_lit(this, window[strstart], bflush);
        lookahead--;
        strstart++;
        if (bflush) FLUSH_BLOCK(this, 0);
    }
    insert = 0;
    if (flush == Z_FINISH)
    {
        FLUSH_BLOCK(this, 1);
        return block_state::finish_done;
    }
    if (last_lit)
        FLUSH_BLOCK(this, 0);
    return block_state::block_done;
}

void DeflateStateData::putShortMSB(unsigned int b)
{
    put_byte(this, (unsigned char)(b >> 8));
    put_byte(this, (unsigned char)(b & 0xff));
}

void DeflateStateData::_tr_init()
{
    tr_static_init();

    l_desc.dyn_tree = dyn_ltree;
    l_desc.stat_desc = &static_l_desc;

    d_desc.dyn_tree = dyn_dtree;
    d_desc.stat_desc = &static_d_desc;

    bl_desc.dyn_tree = bl_tree;
    bl_desc.stat_desc = &static_bl_desc;

    bi_buf = 0;
    bi_valid = 0;
#ifdef ZLIB_DEBUG
    compressed_len = 0L;
    bits_sent = 0L;
#endif

    /* Initialize the first block of the first file: */
    init_block();
}

void DeflateStateData::init_block()
{
    int n; /* iterates over tree elements */

    /* Initialize the trees. */
    for (n = 0; n < L_CODES; n++) dyn_ltree[n].fc.freq = 0;
    for (n = 0; n < D_CODES; n++) dyn_dtree[n].fc.freq = 0;
    for (n = 0; n < BL_CODES; n++) bl_tree[n].fc.freq = 0;

    dyn_ltree[END_BLOCK].fc.freq = 1;
    opt_len = static_len = 0L;
    last_lit = matches = 0;
}

void DeflateStateData::pqdownheap( ct_data* tree, int k)
{
    int v = heap[k];
    int j = k << 1;  /* left son of k */
    while (j <= heap_len)
    {
        /* Set j to the smallest of the two sons: */
        if (j < heap_len &&
            smaller(tree, heap[j + 1], heap[j], depth))
        {
            j++;
        }
        /* Exit if v is smaller than both sons */
        if (smaller(tree, v, heap[j], depth)) break;

        /* Exchange v with the smallest son */
        heap[k] = heap[j];  k = j;

        /* And continue down the tree, setting j to the left son of k */
        j <<= 1;
    }
    heap[k] = v;
}

void DeflateStateData::gen_bitlen( tree_desc* desc)
{
    ct_data* tree = desc->dyn_tree;
    int max_code = desc->max_code;
    const ct_data* stree = desc->stat_desc->static_tree;
    const int* extra = desc->stat_desc->extra_bits;
    int base = desc->stat_desc->extra_base;
    int max_length = desc->stat_desc->max_length;
    int h;              /* heap index */
    int n, m;           /* iterate over the tree elements */
    int bits;           /* bit length */
    int xbits;          /* extra bits */
    unsigned short f;              /* frequency */
    int overflow = 0;   /* number of elements with bit length too large */

    for (bits = 0; bits <= MAX_BITS; bits++) bl_count[bits] = 0;

    tree[heap[heap_max]].dl.len = 0; /* root of the heap */

    for (h = heap_max + 1; h < HEAP_SIZE; h++)
    {
        n = heap[h];
        bits = tree[tree[n].dl.dad].dl.len + 1;
        if (bits > max_length) bits = max_length, overflow++;
        tree[n].dl.len = (unsigned short)bits;
        /* We overwrite tree[n].dl.dad which is no longer needed */

        if (n > max_code) continue; /* not a leaf node */

        bl_count[bits]++;
        xbits = 0;
        if (n >= base) xbits = extra[n - base];
        f = tree[n].fc.freq;
        opt_len += (unsigned long)f * (unsigned)(bits + xbits);
        if (stree) static_len += (unsigned long)f * (unsigned)(stree[n].dl.len + xbits);
    }
    if (overflow == 0) return;

    Tracev((stderr, "\nbit length overflow\n"));
    /* This happens for example on obj2 and pic of the Calgary corpus */

    /* Find the first bit length which could increase: */
    do
    {
        bits = max_length - 1;
        while (bl_count[bits] == 0) bits--;
        bl_count[bits]--;      /* move one leaf down the tree */
        bl_count[bits + 1] += 2; /* move one overflow item as its brother */
        bl_count[max_length]--;
        /* The brother of the overflow item also moves one step up,
         * but this does not affect bl_count[max_length]
         */
        overflow -= 2;
    }
    while (overflow > 0);

    /* Now recompute all bit lengths, scanning in increasing frequency.
     * h is still equal to HEAP_SIZE. (It is simpler to reconstruct all
     * lengths instead of fixing only the wrong ones. This idea is taken
     * from 'ar' written by Haruhiko Okumura.)
     */
    for (bits = max_length; bits != 0; bits--)
    {
        n = bl_count[bits];
        while (n != 0)
        {
            m = heap[--h];
            if (m > max_code) continue;
            if ((unsigned)tree[m].dl.len != (unsigned)bits)
            {
                Tracev((stderr, "code %d bits %d->%d\n", m, tree[m].dl.len, bits));
                opt_len += ((unsigned long)bits - tree[m].dl.len) * tree[m].fc.freq;
                tree[m].dl.len = (unsigned short)bits;
            }
            n--;
        }
    }
}

void DeflateStateData::build_tree( tree_desc* desc)
{
    ct_data* tree = desc->dyn_tree;
    const ct_data* stree = desc->stat_desc->static_tree;
    int elems = desc->stat_desc->elems;
    int n, m;          /* iterate over heap elements */
    int max_code = -1; /* largest code with non zero frequency */
    int node;          /* new node being created */

    heap_len = 0, heap_max = HEAP_SIZE;

    for (n = 0; n < elems; n++)
    {
        if (tree[n].fc.freq != 0)
        {
            heap[++(heap_len)] = max_code = n;
            depth[n] = 0;
        }
        else
        {
            tree[n].dl.len = 0;
        }
    }

    while (heap_len < 2)
    {
        node = heap[++(heap_len)] = (max_code < 2 ? ++max_code : 0);
        tree[node].fc.freq = 1;
        depth[node] = 0;
        opt_len--; if (stree) static_len -= stree[node].dl.len;
        /* node is 0 or 1 so it does not have extra bits */
    }
    desc->max_code = max_code;

    for (n = heap_len / 2; n >= 1; n--) pqdownheap( tree, n);

    node = elems;              /* next internal node of the tree */
    do
    {
        pqremove(this, tree, n);  /* n = node of least frequency */
        m = heap[SMALLEST]; /* m = node of next least frequency */

        heap[--(heap_max)] = n; /* keep the nodes sorted by frequency */
        heap[--(heap_max)] = m;

        /* Create a new node father of n and m */
        tree[node].fc.freq = tree[n].fc.freq + tree[m].fc.freq;
        depth[node] = (unsigned char)((depth[n] >= depth[m] ?
            depth[n] : depth[m]) + 1);
        tree[n].dl.dad = tree[m].dl.dad = (unsigned short)node;
#ifdef DUMP_BL_TREE
        if (tree == bl_tree)
        {
            fprintf(stderr, "\nnode %d(%d), sons %d(%d) %d(%d)",
                node, tree[node].fc.freq, n, tree[n].fc.freq, m, tree[m].fc.freq);
        }
#endif
        /* and insert the new node in the heap */
        heap[SMALLEST] = node++;
        pqdownheap( tree, SMALLEST);

    }
    while (heap_len >= 2);

    heap[--(heap_max)] = heap[SMALLEST];

    /* At this point, the fields freq and dad are set. We can now
     * generate the bit lengths.
     */
    gen_bitlen( (tree_desc*)desc);

    /* The field len is now set, we can generate the bit codes */
    gen_codes((ct_data*)tree, max_code, bl_count);
}

void DeflateStateData::scan_tree( ct_data* tree, int max_code)
{
    int n;                     /* iterates over all tree elements */
    int prevlen = -1;          /* last emitted length */
    int curlen;                /* length of current code */
    int nextlen = tree[0].dl.len; /* length of next code */
    int count = 0;             /* repeat count of the current code */
    int max_count = 7;         /* max repeat count */
    int min_count = 4;         /* min repeat count */

    if (nextlen == 0) max_count = 138, min_count = 3;
    tree[max_code + 1].dl.len = (unsigned short)0xffff; /* guard */

    for (n = 0; n <= max_code; n++)
    {
        curlen = nextlen; nextlen = tree[n + 1].dl.len;
        if (++count < max_count && curlen == nextlen)
        {
            continue;
        }
        else if (count < min_count)
        {
            bl_tree[curlen].fc.freq += count;
        }
        else if (curlen != 0)
        {
            if (curlen != prevlen) bl_tree[curlen].fc.freq++;
            bl_tree[REP_3_6].fc.freq++;
        }
        else if (count <= 10)
        {
            bl_tree[REPZ_3_10].fc.freq++;
        }
        else
        {
            bl_tree[REPZ_11_138].fc.freq++;
        }
        count = 0; prevlen = curlen;
        if (nextlen == 0)
        {
            max_count = 138, min_count = 3;
        }
        else if (curlen == nextlen)
        {
            max_count = 6, min_count = 3;
        }
        else
        {
            max_count = 7, min_count = 4;
        }
    }
}

void DeflateStateData::send_tree( ct_data* tree, int max_code)
{
    int n;                     /* iterates over all tree elements */
    int prevlen = -1;          /* last emitted length */
    int curlen;                /* length of current code */
    int nextlen = tree[0].dl.len; /* length of next code */
    int count = 0;             /* repeat count of the current code */
    int max_count = 7;         /* max repeat count */
    int min_count = 4;         /* min repeat count */

    /* tree[max_code+1].dl.len = -1; */  /* guard already set */
    if (nextlen == 0) max_count = 138, min_count = 3;

    for (n = 0; n <= max_code; n++)
    {
        curlen = nextlen; nextlen = tree[n + 1].dl.len;
        if (++count < max_count && curlen == nextlen)
        {
            continue;
        }
        else if (count < min_count)
        {
            do { send_code(this, curlen, bl_tree); }
            while (--count != 0);

        }
        else if (curlen != 0)
        {
            if (curlen != prevlen)
            {
                send_code(this, curlen, bl_tree); count--;
            }
            Assert(count >= 3 && count <= 6, " 3_6?");
            send_code(this, REP_3_6, bl_tree); send_bits(this, count - 3, 2);

        }
        else if (count <= 10)
        {
            send_code(this, REPZ_3_10, bl_tree); send_bits(this, count - 3, 3);

        }
        else
        {
            send_code(this, REPZ_11_138, bl_tree); send_bits(this, count - 11, 7);
        }
        count = 0; prevlen = curlen;
        if (nextlen == 0)
        {
            max_count = 138, min_count = 3;
        }
        else if (curlen == nextlen)
        {
            max_count = 6, min_count = 3;
        }
        else
        {
            max_count = 7, min_count = 4;
        }
    }
}

int DeflateStateData::build_bl_tree()
{
    int max_blindex;  /* index of last bit length code of non zero freq */

    /* Determine the bit length frequencies for literal and distance trees */
    scan_tree( (ct_data*)dyn_ltree, l_desc.max_code);
    scan_tree( (ct_data*)dyn_dtree, d_desc.max_code);

    /* Build the bit length tree: */
    build_tree( (tree_desc*)(&(bl_desc)));

    for (max_blindex = BL_CODES - 1; max_blindex >= 3; max_blindex--)
    {
        if (bl_tree[bl_order[max_blindex]].dl.len != 0) break;
    }
    /* Update opt_len to include the bit length tree and counts */
    opt_len += 3 * ((unsigned long)max_blindex + 1) + 5 + 5 + 4;
    Tracev((stderr, "\ndyn trees: dyn %ld, stat %ld",
        opt_len, static_len));

    return max_blindex;
}

void DeflateStateData::send_all_trees( int lcodes, int dcodes, int blcodes)
{
    int rank;                    /* index in bl_order */

    Assert(lcodes >= 257 && dcodes >= 1 && blcodes >= 4, "not enough codes");
    Assert(lcodes <= L_CODES && dcodes <= D_CODES && blcodes <= BL_CODES,
        "too many codes");
    Tracev((stderr, "\nbl counts: "));
    send_bits(this, lcodes - 257, 5); /* not +255 as stated in appnote.txt */
    send_bits(this, dcodes - 1, 5);
    send_bits(this, blcodes - 4, 4); /* not -3 as stated in appnote.txt */
    for (rank = 0; rank < blcodes; rank++)
    {
        Tracev((stderr, "\nbl code %2d ", bl_order[rank]));
        send_bits(this, bl_tree[bl_order[rank]].dl.len, 3);
    }
    Tracev((stderr, "\nbl tree: sent %ld", bits_sent));

    send_tree( (ct_data*)dyn_ltree, lcodes - 1); /* literal tree */
    Tracev((stderr, "\nlit tree: sent %ld", bits_sent));

    send_tree( (ct_data*)dyn_dtree, dcodes - 1); /* distance tree */
    Tracev((stderr, "\ndist tree: sent %ld", bits_sent));
}

void  DeflateStateData::_tr_stored_block( char* buf, unsigned long stored_len, int last)
{
    send_bits(this, (STORED_BLOCK << 1) + last, 3);    /* send block type */
    bi_windup();        /* align on byte boundary */
    put_short(this, (unsigned short)stored_len);
    put_short(this, (unsigned short)~stored_len);
    memcpy(pending_buf + pending, (unsigned char*)buf, stored_len);
    pending += stored_len;
#ifdef ZLIB_DEBUG
    compressed_len = (compressed_len + 3 + 7) & (unsigned long)~7L;
    compressed_len += (stored_len + 4) << 3;
    bits_sent += 2 * 16;
    bits_sent += stored_len << 3;
#endif
}

void  DeflateStateData::_tr_flush_bits()
{
    bi_flush();
}

void  DeflateStateData::_tr_align()
{
    send_bits(this, STATIC_TREES << 1, 3);
    send_code(this, END_BLOCK, static_ltree);
#ifdef ZLIB_DEBUG
    compressed_len += 10L; /* 3 for block type, 7 for EOB */
#endif
    bi_flush();
}

void DeflateStateData::_tr_flush_block( char* buf, unsigned long stored_len, int last)
{
    unsigned long opt_lenb, static_lenb; /* opt_len and static_len in bytes */
    int max_blindex = 0;  /* index of last bit length code of non zero freq */

    /* Build the Huffman trees unless a stored block is forced */
    if (level > 0)
    {

        /* Check if the file is binary or text */
        if (strm->data_type == Z_UNKNOWN)
            strm->data_type = detect_data_type();

        /* Construct the literal and distance trees */
        build_tree( (tree_desc*)(&(l_desc)));
        Tracev((stderr, "\nlit data: dyn %ld, stat %ld", opt_len, static_len));

        build_tree( (tree_desc*)(&(d_desc)));
        Tracev((stderr, "\ndist data: dyn %ld, stat %ld", opt_len, static_len));

        max_blindex = build_bl_tree();

        /* Determine the best encoding. Compute the block lengths in bytes. */
        opt_lenb = (opt_len + 3 + 7) >> 3;
        static_lenb = (static_len + 3 + 7) >> 3;

        Tracev((stderr, "\nopt %lu(%lu) stat %lu(%lu) stored %lu lit %u ", opt_lenb, opt_len, static_lenb, static_len, stored_len, last_lit));

        if (static_lenb <= opt_lenb) opt_lenb = static_lenb;

    }
    else
    {
        Assert(buf != (char*)0, "lost buf");
        opt_lenb = static_lenb = stored_len + 5; /* force a stored block */
    }

#ifdef FORCE_STORED
    if (buf != (char*)0)
    { /* force stored block */
#else
    if (stored_len + 4 <= opt_lenb && buf != (char*)0)
    {
        /* 4: two words for the lengths */
#endif

        _tr_stored_block( buf, stored_len, last);

#ifdef FORCE_STATIC
    }
    else if (static_lenb >= 0)
    { /* force static trees */
#else
    }
    else if (strategy == Z_FIXED || static_lenb == opt_lenb)
    {
#endif
        send_bits(this, (STATIC_TREES << 1) + last, 3);
        compress_block( (const ct_data*)static_ltree,
            (const ct_data*)static_dtree);
#ifdef ZLIB_DEBUG
        compressed_len += 3 + static_len;
#endif
    }
    else
    {
        send_bits(this, (DYN_TREES << 1) + last, 3);
        send_all_trees( l_desc.max_code + 1, d_desc.max_code + 1,
            max_blindex + 1);
        compress_block( (const ct_data*)dyn_ltree,
            (const ct_data*)dyn_dtree);
#ifdef ZLIB_DEBUG
        compressed_len += 3 + opt_len;
#endif
    }
    Assert(compressed_len == bits_sent, "bad compressed size");
    /* The above check is made mod 2^32, for files larger than 512 MB
     * and unsigned long implemented on 32 bits.
     */
    init_block();

    if (last)
    {
        bi_windup();
#ifdef ZLIB_DEBUG
        compressed_len += 7;  /* align on byte boundary */
#endif
    }
    Tracev((stderr, "\ncomprlen %lu(%lu) ", compressed_len >> 3, compressed_len - 7 * last));
    }

int  DeflateStateData::_tr_tally(unsigned int dist, unsigned int lc)
{
    d_buf[last_lit] = (unsigned short)dist;
    l_buf[last_lit++] = (unsigned char)lc;
    if (dist == 0)
    {
        /* lc is the unmatched char */
        dyn_ltree[lc].fc.freq++;
    }
    else
    {
        matches++;
        /* Here, lc is the match length - MIN_MATCH */
        dist--;             /* dist = match distance - 1 */
        Assert((unsigned short)dist < (unsigned short)MAX_DIST() &&
            (unsigned short)lc <= (unsigned short)(MAX_MATCH - MIN_MATCH) &&
            (unsigned short)d_code(dist) < (unsigned short)D_CODES, "_tr_tally: bad match");

        dyn_ltree[_length_code[lc] + LITERALS + 1].fc.freq++;
        dyn_dtree[d_code(dist)].fc.freq++;
    }

    return (last_lit == lit_bufsize - 1);
}

void DeflateStateData::compress_block(const ct_data * ltree, const ct_data * dtree)
{
    unsigned dist;      /* distance of matched string */
    int lc;             /* match length or unmatched char (if dist == 0) */
    unsigned lx = 0;    /* running index in l_buf */
    unsigned code;      /* the code to send */
    int extra;          /* number of extra bits to send */

    if (last_lit != 0) do
    {
        dist = d_buf[lx];
        lc = l_buf[lx++];
        if (dist == 0)
        {
            send_code(this, lc, ltree); /* send a literal byte */
            Tracecv(isgraph(lc), (stderr, " '%c' ", lc));
        }
        else
        {
            /* Here, lc is the match length - MIN_MATCH */
            code = _length_code[lc];
            send_code(this, code + LITERALS + 1, ltree); /* send the length code */
            extra = extra_lbits[code];
            if (extra != 0)
            {
                lc -= base_length[code];
                send_bits(this, lc, extra);       /* send the extra length bits */
            }
            dist--; /* dist is now the match distance - 1 */
            code = d_code(dist);
            Assert(code < D_CODES, "bad d_code");

            send_code(this, code, dtree);       /* send the distance code */
            extra = extra_dbits[code];
            if (extra != 0)
            {
                dist -= (unsigned)base_dist[code];
                send_bits(this, dist, extra);   /* send the extra distance bits */
            }
        } /* literal or match pair ? */

        /* Check that the overlay between pending_buf and d_buf+l_buf is ok: */
        Assert((unsigned int)(pending) < lit_bufsize + 2 * lx,
            "pendingBuf overflow");

    }
    while (lx < last_lit);

    send_code(this, END_BLOCK, ltree);
}

int DeflateStateData::detect_data_type()
{
    unsigned long black_mask = 0xf3ffc07fUL;
    int n;

    /* Check for non-textual ("black-listed") bytes. */
    for (n = 0; n <= 31; n++, black_mask >>= 1)
        if ((black_mask & 1) && (dyn_ltree[n].fc.freq != 0))
            return Z_BINARY;

    /* Check for textual ("white-listed") bytes. */
    if (dyn_ltree[9].fc.freq != 0 || dyn_ltree[10].fc.freq != 0
        || dyn_ltree[13].fc.freq != 0)
        return Z_TEXT;
    for (n = 32; n < LITERALS; n++)
        if (dyn_ltree[n].fc.freq != 0)
            return Z_TEXT;

    return Z_BINARY;
}

void DeflateStateData::bi_flush()
{
    if (bi_valid == 16)
    {
        put_short(this, bi_buf);
        bi_buf = 0;
        bi_valid = 0;
    }
    else if (bi_valid >= 8)
    {
        put_byte(this, (unsigned char)bi_buf);
        bi_buf >>= 8;
        bi_valid -= 8;
    }
}

void DeflateStateData::bi_windup()
{
    if (bi_valid > 8)
    {
        put_short(this, bi_buf);
    }
    else if (bi_valid > 0)
    {
        put_byte(this, (unsigned char)bi_buf);
    }
    bi_buf = 0;
    bi_valid = 0;
#ifdef ZLIB_DEBUG
    bits_sent = (bits_sent + 7) & ~7;
#endif
}




int DeflateStateData::uncompress2(unsigned char* dest, unsigned long* destLen, const unsigned char* source, unsigned long* sourceLen)
{
    ZLibStream stream;
    int err;
    const unsigned int max = (unsigned int)-1;
    unsigned long len, left;
    unsigned char buf[1];    /* for detection of incomplete stream when *destLen == 0 */

    len = *sourceLen;
    if (*destLen)
    {
        left = *destLen;
        *destLen = 0;
    }
    else
    {
        left = 1;
        dest = buf;
    }

    stream.next_in = (unsigned char*)source;
    stream.avail_in = 0;
    stream.zalloc = (alloc_func)0;
    stream.zfree = (free_func)0;
    stream.opaque = (void*)0;

    err = inflateInit((&stream));
    if (err != Z_OK) return err;

    stream.next_out = dest;
    stream.avail_out = 0;

    do
    {
        if (stream.avail_out == 0)
        {
            stream.avail_out = left > (unsigned long)max ? max : (unsigned int)left;
            left -= stream.avail_out;
        }
        if (stream.avail_in == 0)
        {
            stream.avail_in = len > (unsigned long)max ? max : (unsigned int)len;
            len -= stream.avail_in;
        }
        err = stream.inflate(Z_NO_FLUSH);
    }
    while (err == Z_OK);

    *sourceLen -= len + stream.avail_in;
    if (dest != buf)
        *destLen = stream.total_out;
    else if (stream.total_out && err == Z_BUF_ERROR)
        left = 1;

    stream.inflateEnd();
    return err == Z_STREAM_END ? Z_OK :
        err == Z_NEED_DICT ? Z_DATA_ERROR :
        err == Z_BUF_ERROR && left + stream.avail_out ? Z_DATA_ERROR :
        err;
}

int DeflateStateData::uncompress(unsigned char* dest, unsigned long* destLen, const unsigned char* source, unsigned long sourceLen)
{
    return uncompress2(dest, destLen, source, &sourceLen);
}

int DeflateStateData::compress2(unsigned char* dest, unsigned long* destLen, const unsigned char* source, unsigned long sourceLen, int level)
{
    ZLibStream stream;
    int err;
    const unsigned int max = (unsigned int)-1;
    unsigned long left;

    left = *destLen;
    *destLen = 0;

    stream.zalloc = (alloc_func)0;
    stream.zfree = (free_func)0;
    stream.opaque = (void*)0;

    err = deflateInit((&stream),level);

    if (err != Z_OK) return err;

    stream.next_out = dest;
    stream.avail_out = 0;
    stream.next_in = (unsigned char*)source;
    stream.avail_in = 0;

    do
    {
        if (stream.avail_out == 0)
        {
            stream.avail_out = left > (unsigned long)max ? max : (unsigned int)left;
            left -= stream.avail_out;
        }
        if (stream.avail_in == 0)
        {
            stream.avail_in = sourceLen > (unsigned long)max ? max : (unsigned int)sourceLen;
            sourceLen -= stream.avail_in;
        }
        err = stream.deflate(sourceLen ? Z_NO_FLUSH : Z_FINISH);
    }
    while (err == Z_OK);

    *destLen = stream.total_out;

    stream.deflateEnd();

    return err == Z_STREAM_END ? Z_OK : err;
}

int DeflateStateData::compress(unsigned char* dest, unsigned long* destLen, const unsigned char* source, unsigned long sourceLen)
{
    return compress2(dest, destLen, source, sourceLen, Z_DEFAULT_COMPRESSION);
}

unsigned long DeflateStateData::compressBound(unsigned long sourceLen)
{
    return sourceLen + (sourceLen >> 12) + (sourceLen >> 14) + (sourceLen >> 25) + 13;
}