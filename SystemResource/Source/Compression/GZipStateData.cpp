#include "GZipStateData.h"
#include "DeflateStateData.h"


void GZipStateData::gz_reset()
{
    File.have = 0;              /* no output data available */
    if (mode == GZ_READ)
    {   /* for reading ... */
        eof = 0;             /* not at end of file */
        past = 0;            /* have not read past end yet */
        how = LOOK;          /* look for gzip header */
    }
    seek = 0;                /* no seek request pending */
    gz_error( Z_OK, NULL);    /* clear error */
    File.pos = 0;               /* no uncompressed data yet */
    strm.avail_in = 0;       /* no input data yet */
}

void GZipStateData::gz_error(int err, const char* msg)
{
    /* free previously allocated message and clear */
    if (msg != NULL)
    {
        if (err != Z_MEM_ERROR)
            free((void*)msg);
        msg = NULL;
    }

    /* if fatal, set File.have to 0 so that the gzgetc() macro fails */
    if (err != Z_OK && err != Z_BUF_ERROR)
        File.have = 0;

    /* set error code, and if no message, then done */
    err = err;
    if (msg == NULL)
        return;

    /* for an out of memory error, return literal string when requested */
    if (err == Z_MEM_ERROR)
        return;

    /* construct error message with path */
    if ((msg = (char*)malloc(strlen(path) + strlen(msg) + 3)) ==
        NULL)
    {
        err = Z_MEM_ERROR;
        return;
    }
#if !defined(NO_snprintf) && !defined(NO_vsnprintf)
    (void)snprintf((char*)msg, strlen(path) + strlen(msg) + 3,
        "%s%s%s", path, ": ", msg);
#else
    strcpy(msg, path);
    strcat(msg, ": ");
    strcat(msg, msg);
#endif
}

int GZipStateData::gz_load(unsigned char* buf, unsigned len, unsigned* have)
{
    int ret;
    unsigned get, max = ((unsigned)-1 >> 2) + 1;

    *have = 0;
    do
    {
        get = len - *have;
        if (get > max)
            get = max;
        ret = _read(fd, buf + *have, get);
        if (ret <= 0)
            break;
        *have += (unsigned)ret;
    }
    while (*have < len);
    if (ret < 0)
    {
        gz_error( Z_ERRNO, strerror(errno));
        return -1;
    }
    if (ret == 0)
        eof = 1;
    return 0;
}

int GZipStateData::gz_avail()
{
    unsigned got;

    if (err != Z_OK && err != Z_BUF_ERROR)
        return -1;
    if (eof == 0)
    {
        if (strm.avail_in)
        {       /* copy what's there to the start */
            unsigned char* p = in;
            unsigned const char* q = strm.next_in;
            unsigned n = strm.avail_in;
            do
            {
                *p++ = *q++;
            }
            while (--n);
        }
        if (gz_load( in + strm.avail_in,
            size - strm.avail_in, &got) == -1)
            return -1;
        strm.avail_in += got;
        strm.next_in = in;
    }
    return 0;
}

int GZipStateData::gz_look()
{
    /* allocate read buffers and inflate memory */
    if (size == 0)
    {
        /* allocate buffers */
        in = (unsigned char*)malloc(want);
        out = (unsigned char*)malloc(want << 1);
        if (in == NULL || out == NULL)
        {
            free(out);
            free(in);
            gz_error( Z_MEM_ERROR, "out of memory");
            return -1;
        }
        size = want;

        /* allocate inflate memory */
        strm.zalloc = 0;
        strm.zfree = 0;
        strm.opaque = 0;
        strm.avail_in = 0;
        strm.next_in = 0;
        

        if (inflateInit2((&strm), 15 + 16) != Z_OK)
        {    /* gunzip */
            free(out);
            free(in);
            size = 0;
            gz_error( Z_MEM_ERROR, "out of memory");
            return -1;
        }
    }

    /* get at least the magic bytes in the input buffer */
    if (strm.avail_in < 2)
    {
        if (gz_avail() == -1)
            return -1;
        if (strm.avail_in == 0)
            return 0;
    }

    /* look for gzip magic bytes -- if there, do gzip decoding (note: there is
       a logical dilemma here when considering the case of a partially written
       gzip file, to wit, if a single 31 byte is written, then we cannot tell
       whether this is a single-byte file, or just a partially written gzip
       file -- for here we assume that if a gzip file is being written, then
       the header will be written in a single operation, so that reading a
       single byte is sufficient indication that it is not a gzip file) */
    if (strm.avail_in > 1 &&
        strm.next_in[0] == 31 && strm.next_in[1] == 139)
    {
        strm.inflateReset();
        how = GZIP;
        direct = 0;
        return 0;
    }

    /* no gzip header -- if we were decoding gzip before, then this is trailing
       garbage.  Ignore the trailing garbage and finish. */
    if (direct == 0)
    {
        strm.avail_in = 0;
        eof = 1;
        File.have = 0;
        return 0;
    }

    /* doing raw i/o, copy any leftover input to output -- this assumes that
       the output buffer is larger than the input buffer, which also assures
       space for gzungetc() */
    File.next = out;
    if (strm.avail_in)
    {
        memcpy(File.next, strm.next_in, strm.avail_in);
        File.have = strm.avail_in;
        strm.avail_in = 0;
    }
    how = COPY;
    direct = 1;
    return 0;
}

int GZipStateData::gz_decomp()
{
    int ret = Z_OK;
    unsigned had;

    /* fill output buffer up to end of deflate stream */
    had = strm.avail_out;
    do
    {
        /* get more input for inflate() */
        if (strm.avail_in == 0 && gz_avail() == -1)
            return -1;
        if (strm.avail_in == 0)
        {
            gz_error( Z_BUF_ERROR, "unexpected end of file");
            break;
        }

        /* decompress and handle errors */
        ret = strm.inflate(Z_NO_FLUSH);
        if (ret == Z_STREAM_ERROR || ret == Z_NEED_DICT)
        {
            gz_error( Z_STREAM_ERROR,
                "internal error: inflate stream corrupt");
            return -1;
        }
        if (ret == Z_MEM_ERROR)
        {
            gz_error( Z_MEM_ERROR, "out of memory");
            return -1;
        }
        if (ret == Z_DATA_ERROR)
        {              /* deflate stream invalid */
            gz_error( Z_DATA_ERROR,
                strm.msg == NULL ? "compressed data error" : strm.msg);
            return -1;
        }
    }
    while (strm.avail_out && ret != Z_STREAM_END);

    /* update available output */
    File.have = had - strm.avail_out;
    File.next = strm.next_out - File.have;

    /* if the gzip stream completed successfully, look for another */
    if (ret == Z_STREAM_END)
        how = LOOK;

    /* good decompression */
    return 0;
}

int GZipStateData::gz_fetch()
{
    do
    {
        switch (how)
        {
            case LOOK:      /* -> LOOK, COPY (only if never GZIP), or GZIP */
                if (gz_look() == -1)
                    return -1;
                if (how == LOOK)
                    return 0;
                break;
            case COPY:      /* -> COPY */
                if (gz_load( out, size << 1, &(File.have))
                    == -1)
                    return -1;
                File.next = out;
                return 0;
            case GZIP:      /* -> GZIP or LOOK (if end of gzip stream) */
                strm.avail_out = size << 1;
                strm.next_out = out;
                if (gz_decomp() == -1)
                    return -1;
        }
    }
    while (File.have == 0 && (!eof || strm.avail_in));
    return 0;
}

int GZipStateData::gz_skip(__int64 len)
{
    unsigned n;

    /* skip over len bytes or reach end-of-file, whichever comes first */
    while (len)
        /* skip over whatever is in output buffer */
        if (File.have)
        {
            n = GT_OFF(File.have) || (__int64)File.have > len ?
                (unsigned)len : File.have;
            File.have -= n;
            File.next += n;
            File.pos += n;
            len -= n;
        }

    /* output buffer empty -- return if we're at the end of the input */
        else if (eof && strm.avail_in == 0)
            break;

    /* need more data to skip -- load up output buffer */
        else
        {
            /* get more output, looking for header if required */
            if (gz_fetch() == -1)
                return -1;
        }
    return 0;
}

unsigned int GZipStateData::gz_read(void* buf, unsigned int len)
{
    unsigned int got;
    unsigned n;

    /* if len is zero, avoid unnecessary operations */
    if (len == 0)
        return 0;

    /* process a skip request */
    if (seek)
    {
        seek = 0;
        if (gz_skip( skip) == -1)
            return 0;
    }

    /* get len bytes to buf, or less than len if at the end */
    got = 0;
    do
    {
        /* set n to the maximum amount of len that fits in an unsigned int */
        n = -1;
        if (n > len)
            n = len;

        /* first just try copying data from the output buffer */
        if (File.have)
        {
            if (File.have < n)
                n = File.have;
            memcpy(buf, File.next, n);
            File.next += n;
            File.have -= n;
        }

        /* output buffer empty -- return if we're at the end of the input */
        else if (eof && strm.avail_in == 0)
        {
            past = 1;        /* tried to read past end */
            break;
        }

        /* need output data -- for small len or new stream load up our output
           buffer */
        else if (how == LOOK || n < (size << 1))
        {
            /* get more output, looking for header if required */
            if (gz_fetch() == -1)
                return 0;
            continue;       /* no progress yet -- go back to copy above */
            /* the copy above assures that we will leave with space in the
               output buffer, allowing at least one gzungetc() to succeed */
        }

        /* large len -- read directly into user buffer */
        else if (how == COPY)
        {      /* read directly */
            if (gz_load( (unsigned char*)buf, n, &n) == -1)
                return 0;
        }

        /* large len -- decompress directly into user buffer */
        else
        {  /* how == GZIP */
            strm.avail_out = n;
            strm.next_out = (unsigned char*)buf;
            if (gz_decomp() == -1)
                return 0;
            n = File.have;
            File.have = 0;
        }

        /* update progress */
        len -= n;
        buf = (char*)buf + n;
        got += n;
        File.pos += n;
    }
    while (len);

    /* return number of bytes read into user buffer */
    return got;
}

int GZipStateData::gz_init()
{
    int ret;

    /* allocate input buffer (double size for gzprintf) */
    in = (unsigned char*)malloc(want << 1);
    if (in == NULL)
    {
        gz_error( Z_MEM_ERROR, "out of memory");
        return -1;
    }

    /* only need output buffer and deflate  if compressing */
    if (!direct)
    {
        /* allocate output buffer */
        out = (unsigned char*)malloc(want);
        if (out == NULL)
        {
            free(in);
            gz_error( Z_MEM_ERROR, "out of memory");
            return -1;
        }

        /* allocate deflate memory, set up for gzip compression */
        strm.zalloc = 0;
        strm.zfree = 0;
        strm.opaque = 0;
        ret = deflateInit2((&strm), level, Z_DEFLATED,
            MAX_WBITS + 16, DEF_MEM_LEVEL, strategy);
        if (ret != Z_OK)
        {
            free(out);
            free(in);
            gz_error( Z_MEM_ERROR, "out of memory");
            return -1;
        }
        strm.next_in = NULL;
    }

    /* mark  as initialized */
    size = want;

    /* initialize write buffer if compressing */
    if (!direct)
    {
        strm.avail_out = size;
        strm.next_out = out;
        File.next = strm.next_out;
    }
    return 0;
}

int GZipStateData::gz_comp(int flush)
{
    int ret, writ;
    unsigned have, put, max = ((unsigned)-1 >> 2) + 1;

    /* allocate memory if this is the first time through */
    if (size == 0 && gz_init() == -1)
        return -1;

    /* write directly if requested */
    if (direct)
    {
        while (strm.avail_in)
        {
            put = strm.avail_in > max ? max : strm.avail_in;
            writ = _write(fd, strm.next_in, put);
            if (writ < 0)
            {
                gz_error( Z_ERRNO, strerror(errno));
                return -1;
            }
            strm.avail_in -= (unsigned)writ;
            strm.next_in += writ;
        }
        return 0;
    }

    /* run deflate() on provided input until it produces no more output */
    ret = Z_OK;
    do
    {
        /* write out current buffer contents if full, or if flushing, but if
           doing Z_FINISH then don't write until we get to Z_STREAM_END */
        if (strm.avail_out == 0 || (flush != Z_NO_FLUSH &&
            (flush != Z_FINISH || ret == Z_STREAM_END)))
        {
            while (strm.next_out > File.next)
            {
                put = strm.next_out - File.next > (int)max ? max :
                    (unsigned)(strm.next_out - File.next);
                writ = _write(fd, File.next, put);
                if (writ < 0)
                {
                    gz_error( Z_ERRNO, strerror(errno));
                    return -1;
                }
                File.next += writ;
            }
            if (strm.avail_out == 0)
            {
                strm.avail_out = size;
                strm.next_out = out;
                File.next = out;
            }
        }

        /* compress */
        have = strm.avail_out;
        ret = strm.deflate(flush);
        if (ret == Z_STREAM_ERROR)
        {
            gz_error( Z_STREAM_ERROR,
                "internal error: deflate stream corrupt");
            return -1;
        }
        have -= strm.avail_out;
    }
    while (have);

    /* if that completed a deflate stream, allow another to start */
    if (flush == Z_FINISH)
        strm.deflateReset();

    /* all done, no errors */
    return 0;
}

int GZipStateData::gz_zero(__int64 len)
{
    int first;
    unsigned n;

    /* consume whatever's left in the input buffer */
    if (strm.avail_in && gz_comp( Z_NO_FLUSH) == -1)
        return -1;

    /* compress len zeros (len guaranteed > 0) */
    first = 1;
    while (len)
    {
        n = GT_OFF(size) || (__int64)size > len ?
            (unsigned)len : size;
        if (first)
        {
            memset(in, 0, n);
            first = 0;
        }
        strm.avail_in = n;
        strm.next_in = in;
        File.pos += n;
        if (gz_comp( Z_NO_FLUSH) == -1)
            return -1;
        len -= n;
    }
    return 0;
}

unsigned int GZipStateData::gz_write(void const* buf, unsigned int len)
{
    unsigned int put = len;

    /* if len is zero, avoid unnecessary operations */
    if (len == 0)
        return 0;

    /* allocate memory if this is the first time through */
    if (size == 0 && gz_init() == -1)
        return 0;

    /* check for seek request */
    if (seek)
    {
        seek = 0;
        if (gz_zero( skip) == -1)
            return 0;
    }

    /* for small len, copy to input buffer, otherwise compress directly */
    if (len < size)
    {
        /* copy to input buffer, compress when full */
        do
        {
            unsigned have, copy;

            if (strm.avail_in == 0)
                strm.next_in = in;
            have = (unsigned)((strm.next_in + strm.avail_in) -
                in);
            copy = size - have;
            if (copy > len)
                copy = len;
            memcpy(in + have, buf, copy);
            strm.avail_in += copy;
            File.pos += copy;
            buf = (const char*)buf + copy;
            len -= copy;
            if (len && gz_comp( Z_NO_FLUSH) == -1)
                return 0;
        }
        while (len);
    }
    else
    {
        /* consume whatever's left in the input buffer */
        if (strm.avail_in && gz_comp( Z_NO_FLUSH) == -1)
            return 0;

        /* directly compress user buffer to file */
        strm.next_in = (unsigned char*)buf;
        do
        {
            unsigned n = (unsigned)-1;
            if (n > len)
                n = len;
            strm.avail_in = n;
            File.pos += n;
            if (gz_comp( Z_NO_FLUSH) == -1)
                return 0;
            len -= n;
        }
        while (len);
    }

    /* input was all buffered or compressed */
    return put;
}