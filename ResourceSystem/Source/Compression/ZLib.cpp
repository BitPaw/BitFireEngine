#include "ZLib.h"
#include "ZLibStream.h"
#include <cstdio>
#include "DeflateStateData.h"
#include <cassert>

int ZLib::Compress(const char* source, const char* target)
{
    return Compress(source, target, -1);
}

int ZLib::Compress(const char* source, const char* target, int level)
{
    ZLibStream strm;
    const int chunkSize = strm.ChunkSize;
    int ret;
    int flush;
    unsigned int have;
    unsigned char* in = new unsigned char[chunkSize];
    unsigned char* out = new unsigned char[chunkSize];
    FILE* input = fopen(source, "r");
    FILE* output = fopen(target, "a");

    /* allocate deflate state */
    strm.zalloc = 0;
    strm.zfree = 0;
    strm.opaque = 0;

    ret = deflateInit((&strm), level);

    if (ret != Z_OK)
        return -1;  // <--- ungenau

    /* compress until end of file */
    do
    {
        strm.avail_in = fread(in, 1, chunkSize, input);
        if (ferror(input))
        {
            (void)strm.deflateEnd();
            return -1;
        }
        flush = feof(input) ? Z_FINISH : Z_NO_FLUSH;
        strm.next_in = in;

        /* run deflate() on input until output buffer not full, finish
           compression if all of source has been read in */
        do
        {
            strm.avail_out = chunkSize;
            strm.next_out = out;
            ret = strm.deflate(flush);    /* no bad return value */
            assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
            have = chunkSize - strm.avail_out;
            if (fwrite(out, 1, have, output) != have || ferror(output))
            {
                strm.deflateEnd();
                return -1;
            }
        }
        while (strm.avail_out == 0);
        assert(strm.avail_in == 0);     /* all input will be used */

        /* done when last data in file processed */
    }
    while (flush != Z_FINISH);
    assert(ret == Z_STREAM_END);        /* stream will be complete */

    /* clean up and return */
    strm.deflateEnd();

    delete[] in;
    delete[] out;

    return 0;
}

int ZLib::Decompress(const char* source, const char* target)
{
    ZLibStream strm;
    const int chunkSize = strm.ChunkSize;
    int ret;
    unsigned int have;
    unsigned char* in = new unsigned char[chunkSize];
    unsigned char* out = new unsigned char[chunkSize];
    FILE* input = fopen(source, "r");
    FILE* output = fopen(target, "a");
  

    /* allocate inflate state */
    strm.zalloc = 0;
    strm.zfree = 0;
    strm.opaque = 0;
    strm.avail_in = 0;
    strm.next_in = 0;
    ret = inflateInit((&strm));


    if (ret != Z_OK)
        return -1; // <--- ungenau

    /* decompress until deflate stream ends or end of file */
    do
    {
        strm.avail_in = fread(in, 1, chunkSize, input);
       
        if (ferror(input))
        {
            strm.inflateEnd();
            return -1;
        }

        if (strm.avail_in == 0)
            break;

        strm.next_in = in;

        /* run inflate() on input until output buffer not full */
        do
        {
            strm.avail_out = chunkSize;
            strm.next_out = out;
            ret = strm.inflate(Z_NO_FLUSH);
            assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
            switch (ret)
            {
                case Z_NEED_DICT:
                    ret = Z_DATA_ERROR;     /* and fall through */
                case Z_DATA_ERROR:
                case Z_MEM_ERROR:
                    strm.inflateEnd();
                    return -1; // <--- ungenau
            }
            have = chunkSize - strm.avail_out;
            if (fwrite(out, 1, have, output) != have || ferror(output))
            {
                strm.inflateEnd();
                return -1;
            }
        }
        while (strm.avail_out == 0);

        /* done when inflate() says it's done */
    }
    while (ret != Z_STREAM_END);

    /* clean up and return */
    strm.inflateEnd();

    fclose(input);
    fclose(output);

    delete[] in;
    delete[] out;

    return ret == Z_STREAM_END ? 0 : -2;
}
