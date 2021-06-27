#include "GZipStateData.h"
#include "DeflateStateData.h"

#  define LSEEK _lseeki64

int   GZipFile::gzclose()
{
#ifndef NO_GZCOMPRESS
    GZipStateData* state;

    state = (GZipStateData*)this;

    return state->mode == GZ_READ ? gzclose_r() : gzclose_w();
#else
    return gzclose_r(file);
#endif
}


GZipFile* GZipFile::gz_open(const char* path, int fd, const char* mode)
{
    GZipStateData* state;
    unsigned int len;
    int oflag;
#ifdef O_CLOEXEC
    int cloexec = 0;
#endif
#ifdef O_EXCL
    int exclusive = 0;
#endif

    /* check input */
    if (path == NULL)
        return NULL;

    /* allocate GZipFile* structure to return */
    state = (GZipStateData*)malloc(sizeof(GZipStateData));
    if (state == NULL)
        return NULL;
    state->size = 0;            /* no buffers allocated yet */
    state->want = GZBUFSIZE;    /* requested buffer size */
    state->msg = NULL;          /* no error message yet */

    /* interpret mode */
    state->mode = GZ_NONE;
    state->level = Z_DEFAULT_COMPRESSION;
    state->strategy = Z_DEFAULT_STRATEGY;
    state->direct = 0;
    while (*mode)
    {
        if (*mode >= '0' && *mode <= '9')
            state->level = *mode - '0';
        else
            switch (*mode)
            {
                case 'r':
                    state->mode = GZ_READ;
                    break;
#ifndef NO_GZCOMPRESS
                case 'w':
                    state->mode = GZ_WRITE;
                    break;
                case 'a':
                    state->mode = GZ_APPEND;
                    break;
#endif
                case '+':       /* can't read and write at the same time */
                    free(state);
                    return NULL;
                case 'b':       /* ignore -- will request binary anyway */
                    break;
#ifdef O_CLOEXEC
                case 'e':
                    cloexec = 1;
                    break;
#endif
#ifdef O_EXCL
                case 'File':
                    exclusive = 1;
                    break;
#endif
                case 'f':
                    state->strategy = Z_FILTERED;
                    break;
                case 'h':
                    state->strategy = Z_HUFFMAN_ONLY;
                    break;
                case 'R':
                    state->strategy = Z_RLE;
                    break;
                case 'F':
                    state->strategy = Z_FIXED;
                    break;
                case 'T':
                    state->direct = 1;
                    break;
                default:        /* could consider as an error, but just ignore */
                    ;
            }
        mode++;
    }

    /* must provide an "r", "w", or "a" */
    if (state->mode == GZ_NONE)
    {
        free(state);
        return NULL;
    }

    /* can't force transparent read */
    if (state->mode == GZ_READ)
    {
        if (state->direct)
        {
            free(state);
            return NULL;
        }
        state->direct = 1;      /* for empty file */
    }

    /* save the path name for error messages */
#ifdef WIDECHAR
    if (fd == -2)
    {
        len = wcstombs(NULL, (wchar_t*)path, 0);
        if (len == (unsigned int)-1)
            len = 0;
    }
    else
#endif
        len = strlen((const char*)path);
    state->path = (char*)malloc(len + 1);
    if (state->path == NULL)
    {
        free(state);
        return NULL;
    }
#ifdef WIDECHAR
    if (fd == -2)
        if (len)
            wcstombs(state->path, (wchar_t*)path, len + 1);
        else
            *(state->path) = 0;
    else
#endif
#if !defined(NO_snprintf) && !defined(NO_vsnprintf)
        (void)snprintf(state->path, len + 1, "%s", (const char*)path);
#else
        strcpy(state->path, path);
#endif

    /* compute the flags for open() */
    oflag =
#ifdef O_LARGEFILE
        O_LARGEFILE |
#endif
#ifdef O_BINARY
        O_BINARY |
#endif
#ifdef O_CLOEXEC
        (cloexec ? O_CLOEXEC : 0) |
#endif
        (state->mode == GZ_READ ?
            O_RDONLY :
            (O_WRONLY | O_CREAT |
#ifdef O_EXCL
            (exclusive ? O_EXCL : 0) |
#endif
                (state->mode == GZ_WRITE ? O_TRUNC : O_APPEND)));

    /* open the file with the appropriate flags (or just use fd) */
    state->fd = fd > -1 ? fd : (
#ifdef WIDECHAR
        fd == -2 ? _wopen((wchar_t*)path, oflag, 0666) :
#endif
        _open((const char*)path, oflag, 0666));
    if (state->fd == -1)
    {
        free(state->path);
        free(state);
        return NULL;
    }
    if (state->mode == GZ_APPEND)
    {
        LSEEK(state->fd, 0, SEEK_END);  /* so gzoffset() is correct */
        state->mode = GZ_WRITE;         /* simplify later checks */
    }

    /* save the current position for rewinding (only if reading) */
    if (state->mode == GZ_READ)
    {
        state->start = LSEEK(state->fd, 0, SEEK_CUR);
        if (state->start == -1) state->start = 0;
    }

    /* initialize stream */
    state->gz_reset();

    /* return stream */
    return (GZipFile*)state;
}

GZipFile* GZipFile::gzopen(const char* path, const char* mode)
{
    return gz_open(path, -1, mode);
}

GZipFile* GZipFile::gzopen64(const char* path, const char* mode)
{
    return gz_open(path, -1, mode);
}

GZipFile* GZipFile::gzdopen(int fd, const char* mode)
{
    char* path;         /* identifier for error messages */
    GZipFile* gz;

    if (fd == -1 || (path = (char*)malloc(7 + 3 * sizeof(int))) == NULL)
        return NULL;
#if !defined(NO_snprintf) && !defined(NO_vsnprintf)
    (void)snprintf(path, 7 + 3 * sizeof(int), "<fd:%d>", fd);
#else
    sprintf(path, "<fd:%d>", fd);   /* for debugging */
#endif
    gz = gz_open(path, fd, mode);
    free(path);
    return gz;
}

int   GZipFile::gzbuffer( unsigned int size)
{
    GZipStateData* state;

    /* get internal structure and check integrity */

    state = (GZipStateData*)this;
    if (state->mode != GZ_READ && state->mode != GZ_WRITE)
        return -1;

    /* make sure we haven't already allocated memory */
    if (state->size != 0)
        return -1;

    /* check and set requested size */
    if ((size << 1) < size)
        return -1;              /* need to be able to double it */
    if (size < 2)
        size = 2;               /* need two bytes to check magic header */
    state->want = size;
    return 0;
}

int  GZipFile::gzrewind()
{
    GZipStateData* state;

    /* get internal structure */

    state = (GZipStateData*)this;

    /* check that we're reading and that there's no error */
    if (state->mode != GZ_READ ||
        (state->err != Z_OK && state->err != Z_BUF_ERROR))
        return -1;

    /* back up and start over */
    if (LSEEK(state->fd, state->start, SEEK_SET) == -1)
        return -1;
    state->gz_reset();
    return 0;
}

__int64  GZipFile::gzseek64( __int64 offset, int whence)
{
    unsigned n;
    __int64 ret;
    GZipStateData* state;

    /* get internal structure and check integrity */

    state = (GZipStateData*)this;
    if (state->mode != GZ_READ && state->mode != GZ_WRITE)
        return -1;

    /* check that there's no error */
    if (state->err != Z_OK && state->err != Z_BUF_ERROR)
        return -1;

    /* can only seek from start or relative to current position */
    if (whence != SEEK_SET && whence != SEEK_CUR)
        return -1;

    /* normalize offset to a SEEK_CUR specification */
    if (whence == SEEK_SET)
        offset -= state->File.pos;
    else if (state->seek)
        offset += state->skip;
    state->seek = 0;

    /* if within raw area while reading, just go there */
    if (state->mode == GZ_READ && state->how == COPY &&
        state->File.pos + offset >= 0)
    {
        ret = LSEEK(state->fd, offset - state->File.have, SEEK_CUR);
        if (ret == -1)
            return -1;
        state->File.have = 0;
        state->eof = 0;
        state->past = 0;
        state->seek = 0;
        state->gz_error(Z_OK, NULL);
        state->strm.avail_in = 0;
        state->File.pos += offset;
        return state->File.pos;
    }

    /* calculate skip amount, rewinding if needed for back seek when reading */
    if (offset < 0)
    {
        if (state->mode != GZ_READ)         /* writing -- can't go backwards */
            return -1;
        offset += state->File.pos;
        if (offset < 0)                     /* before start of file! */
            return -1;
        if (gzrewind() == -1)           /* rewind, then skip to offset */
            return -1;
    }

    /* if reading, skip what's in output buffer (one less gzgetc() check) */
    if (state->mode == GZ_READ)
    {
        n = GT_OFF(state->File.have) || (__int64)state->File.have > offset ?
            (unsigned)offset : state->File.have;
        state->File.have -= n;
        state->File.next += n;
        state->File.pos += n;
        offset -= n;
    }

    /* request skip (if not zero) */
    if (offset)
    {
        state->seek = 1;
        state->skip = offset;
    }
    return state->File.pos + offset;
}

long  GZipFile::gzseek( long offset, int whence)
{
    __int64 ret;

    ret = gzseek64((__int64)offset, whence);
    return ret == (long)ret ? (long)ret : -1;
}

__int64  GZipFile::gztell64()
{
    GZipStateData* state;

    /* get internal structure and check integrity */
 
    state = (GZipStateData*)this;
    if (state->mode != GZ_READ && state->mode != GZ_WRITE)
        return -1;

    /* return position */
    return state->File.pos + (state->seek ? state->skip : 0);
}

long GZipFile::gztell()
{
    __int64 ret;

    ret = gztell64();
    return ret == (long)ret ? (long)ret : -1;
}

__int64 GZipFile::gzoffset64()
{
    __int64 offset;
    GZipStateData* state;

    /* get internal structure and check integrity */

    state = (GZipStateData*)this;
    if (state->mode != GZ_READ && state->mode != GZ_WRITE)
        return -1;

    /* compute and return effective offset in file */
    offset = LSEEK(state->fd, 0, SEEK_CUR);
    if (offset == -1)
        return -1;
    if (state->mode == GZ_READ)             /* reading */
        offset -= state->strm.avail_in;     /* don't count buffered input */
    return offset;
}

long  GZipFile::gzoffset()
{
    __int64 ret;

    ret = gzoffset64();
    return ret == (long)ret ? (long)ret : -1;
}

int  GZipFile::gzeof()
{
    GZipStateData* state;

    /* get internal structure and check integrity */

    state = (GZipStateData*)this;
    if (state->mode != GZ_READ && state->mode != GZ_WRITE)
        return 0;

    /* return end-of-file state */
    return state->mode == GZ_READ ? state->past : 0;
}

const char* GZipFile::gzerror( int* errnum)
{
    GZipStateData* state;

    /* get internal structure and check integrity */
 
    state = (GZipStateData*)this;
    if (state->mode != GZ_READ && state->mode != GZ_WRITE)
        return NULL;

    /* return error information */
    if (errnum != NULL)
        *errnum = state->err;
    return state->err == Z_MEM_ERROR ? "out of memory" :
        (state->msg == NULL ? "" : state->msg);
}

void GZipFile::gzclearerr()
{
    GZipStateData* state;

    state = (GZipStateData*)this;
    if (state->mode != GZ_READ && state->mode != GZ_WRITE)
        return;

    /* clear error and end-of-file */
    if (state->mode == GZ_READ)
    {
        state->eof = 0;
        state->past = 0;
    }
    state->gz_error(Z_OK, NULL);
}

int  GZipFile::gzread( void* buf, unsigned int len)
{
    GZipStateData* state;

    /* get internal structure */

    state = (GZipStateData*)this;

    /* check that we're reading and that there's no (serious) error */
    if (state->mode != GZ_READ ||
        (state->err != Z_OK && state->err != Z_BUF_ERROR))
        return -1;

    /* since an int is returned, make sure len fits in one, otherwise return
       with an error (this avoids a flaw in the interface) */
    if ((int)len < 0)
    {
        state->gz_error(Z_STREAM_ERROR, "request does not fit in an int");
        return -1;
    }

    /* read len or fewer bytes to buf */
    len = state->gz_read(buf, len);

    /* check for an error */
    if (len == 0 && state->err != Z_OK && state->err != Z_BUF_ERROR)
        return -1;

    /* return the number of bytes read (this is assured to fit in an int) */
    return (int)len;
}

unsigned int GZipFile::gzfread(void* buf, unsigned int size, unsigned int nitems)
{
    unsigned int len;
    GZipStateData* state;

    /* get internal structure */

    state = (GZipStateData*)this;

    /* check that we're reading and that there's no (serious) error */
    if (state->mode != GZ_READ ||
        (state->err != Z_OK && state->err != Z_BUF_ERROR))
        return 0;

    /* compute bytes to read -- error on overflow */
    len = nitems * size;
    if (size && len / size != nitems)
    {
        state->gz_error(Z_STREAM_ERROR, "request does not fit in a size_t");
        return 0;
    }

    /* read len or fewer bytes to buf, return the number of full items read */
    return len ? state->gz_read(buf, len) / size : 0;
}

#ifdef Z_PREFIX_SET
#  undef z_gzgetc
#else
#  undef gzgetc
#endif
int  GZipFile::gzgetc()
{
    int ret;
    unsigned char buf[1];
    GZipStateData* state;

    state = (GZipStateData*)this;

    /* check that we're reading and that there's no (serious) error */
    if (state->mode != GZ_READ ||
        (state->err != Z_OK && state->err != Z_BUF_ERROR))
        return -1;

    /* try output buffer (no need to check for skip request) */
    if (state->File.have)
    {
        state->File.have--;
        state->File.pos++;
        return *(state->File.next)++;
    }

    /* nothing there -- try gz_read() */
    ret = state->gz_read(buf, 1);
    return ret < 1 ? -1 : buf[0];
}

int  GZipFile::gzgetc_()
{
    return gzgetc();
}

int  GZipFile::gzungetc(int c)
{
    GZipStateData* state;

    state = (GZipStateData*)this;

    /* check that we're reading and that there's no (serious) error */
    if (state->mode != GZ_READ ||
        (state->err != Z_OK && state->err != Z_BUF_ERROR))
        return -1;

    /* process a skip request */
    if (state->seek)
    {
        state->seek = 0;
        if (state->gz_skip(state->skip) == -1)
            return -1;
    }

    /* can't push EOF */
    if (c < 0)
        return -1;

    /* if output buffer empty, put byte at end (allows more pushing) */
    if (state->File.have == 0)
    {
        state->File.have = 1;
        state->File.next = state->out + (state->size << 1) - 1;
        state->File.next[0] = (unsigned char)c;
        state->File.pos--;
        state->past = 0;
        return c;
    }

    /* if no room, give up (must have already done a gzungetc()) */
    if (state->File.have == (state->size << 1))
    {
        state->gz_error(Z_DATA_ERROR, "out of room to push characters");
        return -1;
    }

    /* slide output data if needed and insert byte before existing data */
    if (state->File.next == state->out)
    {
        unsigned char* src = state->out + state->File.have;
        unsigned char* dest = state->out + (state->size << 1);
        while (src > state->out)
            *--dest = *--src;
        state->File.next = dest;
    }
    state->File.have++;
    state->File.next--;
    state->File.next[0] = (unsigned char)c;
    state->File.pos--;
    state->past = 0;
    return c;
}

char* GZipFile::gzgets( char* buf, int len)
{
    unsigned left, n;
    char* str;
    unsigned char* eol;
    GZipStateData* state;

    /* check parameters and get internal structure */
    if (buf == NULL || len < 1)
        return NULL;
    state = (GZipStateData*)this;

    /* check that we're reading and that there's no (serious) error */
    if (state->mode != GZ_READ ||
        (state->err != Z_OK && state->err != Z_BUF_ERROR))
        return NULL;

    /* process a skip request */
    if (state->seek)
    {
        state->seek = 0;
        if (state->gz_skip(state->skip) == -1)
            return NULL;
    }

    /* copy output bytes up to new line or len - 1, whichever comes first --
       append a terminating zero to the string (we don't check for a zero in
       the contents, let the user worry about that) */
    str = buf;
    left = (unsigned)len - 1;
    if (left) do
    {
        /* assure that something is in the output buffer */
        if (state->File.have == 0 && state->gz_fetch() == -1)
            return NULL;                /* error */
        if (state->File.have == 0)
        {       /* end of file */
            state->past = 1;            /* read past end */
            break;                      /* return what we have */
        }

        /* look for end-of-line in current output buffer */
        n = state->File.have > left ? left : state->File.have;
        eol = (unsigned char*)memchr(state->File.next, '\n', n);
        if (eol != NULL)
            n = (unsigned)(eol - state->File.next) + 1;

        /* copy through end-of-line, or remainder if not found */
        memcpy(buf, state->File.next, n);
        state->File.have -= n;
        state->File.next += n;
        state->File.pos += n;
        left -= n;
        buf += n;
    }
    while (left && eol == NULL);

    /* return terminated string, or if nothing, end of file */
    if (buf == str)
        return NULL;
    buf[0] = 0;
    return str;
}

int   GZipFile::gzdirect()
{
    GZipStateData* state;

    
    state = (GZipStateData*)this;

    /* if the state is not known, but we can find out, then do so (this is
       mainly for right after a gzopen() or gzdopen()) */
    if (state->mode == GZ_READ && state->how == LOOK && state->File.have == 0)
        state->gz_look();

    /* return 1 if transparent, 0 if processing a gzip stream */
    return state->direct;
}

int  GZipFile::gzclose_r()
{
    int ret, err;
    GZipStateData* state;

    state = (GZipStateData*)this;

    /* check that we're reading */
    if (state->mode != GZ_READ)
        return Z_STREAM_ERROR;

    /* free memory and close file */
    if (state->size)
    {
        state->strm.inflateEnd();
        free(state->out);
        free(state->in);
    }
    err = state->err == Z_BUF_ERROR ? Z_BUF_ERROR : Z_OK;
    state->gz_error(Z_OK, NULL);
    free(state->path);
    ret = _close(state->fd);
    free(state);
    return ret ? Z_ERRNO : err;
}

int   GZipFile::gzwrite( void const* buf, unsigned int len)
{
    GZipStateData* state;

    state = (GZipStateData*)this;

    /* check that we're writing and that there's no error */
    if (state->mode != GZ_WRITE || state->err != Z_OK)
        return 0;

    /* since an int is returned, make sure len fits in one, otherwise return
       with an error (this avoids a flaw in the interface) */
    if ((int)len < 0)
    {
        state->gz_error(Z_DATA_ERROR, "requested length does not fit in int");
        return 0;
    }

    /* write len bytes from buf (the return value will fit in an int) */
    return (int)state->gz_write(buf, len);
}

unsigned int  GZipFile::gzfwrite(void const* buf, unsigned int size, unsigned int nitems)
{
    unsigned int len;
    GZipStateData* state;

    state = (GZipStateData*)this;

    /* check that we're writing and that there's no error */
    if (state->mode != GZ_WRITE || state->err != Z_OK)
        return 0;

    /* compute bytes to read -- error on overflow */
    len = nitems * size;
    if (size && len / size != nitems)
    {
        state->gz_error(Z_STREAM_ERROR, "request does not fit in a size_t");
        return 0;
    }

    /* write len bytes to buf, return the number of full items written */
    return len ? state->gz_write(buf, len) / size : 0;
}

int GZipFile::gzputc( int c)
{
    unsigned have;
    unsigned char buf[1];
    GZipStateData* state = (GZipStateData*)this;;
    ZLibStream* strm = &state->strm;


    /* check that we're writing and that there's no error */
    if (state->mode != GZ_WRITE || state->err != Z_OK)
        return -1;

    /* check for seek request */
    if (state->seek)
    {
        state->seek = 0;
        if (state->gz_zero(state->skip) == -1)
            return -1;
    }

    /* try writing to input buffer for speed (state->size == 0 if buffer not
       initialized) */
    if (state->size)
    {
        if (strm->avail_in == 0)
            strm->next_in = state->in;
        have = (unsigned)((strm->next_in + strm->avail_in) - state->in);
        if (have < state->size)
        {
            state->in[have] = (unsigned char)c;
            strm->avail_in++;
            state->File.pos++;
            return c & 0xff;
        }
    }

    /* no room in buffer or not initialized, use gz_write() */
    buf[0] = (unsigned char)c;
    if (state->gz_write(buf, 1) != 1)
        return -1;
    return c & 0xff;
}

int GZipFile::gzputs( const char* str)
{
    int ret;
    unsigned int len;
    GZipStateData* state;

    state = (GZipStateData*)this;

    /* check that we're writing and that there's no error */
    if (state->mode != GZ_WRITE || state->err != Z_OK)
        return -1;

    /* write string */
    len = strlen(str);
    ret = state->gz_write(str, len);
    return ret == 0 && len != 0 ? -1 : ret;
}

int GZipFile::gzvprintf( const char* format, va_list va)
{
    int len;
    unsigned left;
    char* next;
    GZipStateData* state;
    
    
    state = (GZipStateData*)this;

    /* check that we're writing and that there's no error */
    if (state->mode != GZ_WRITE || state->err != Z_OK)
        return Z_STREAM_ERROR;

    /* make sure we have some buffer space */
    if (state->size == 0 && state->gz_init() == -1)
        return state->err;

    /* check for seek request */
    if (state->seek)
    {
        state->seek = 0;
        if (state->gz_zero(state->skip) == -1)
            return state->err;
    }

    /* do the printf() into the input buffer, put length in len -- the input
       buffer is double-sized just for this function, so there is guaranteed to
       be state->size bytes available after the current contents */
    if (state->strm.avail_in == 0)
        state->strm.next_in = state->in;
    next = (char*)(state->in + (state->strm.next_in - state->in) + state->strm.avail_in);
    next[state->size - 1] = 0;
#ifdef NO_vsnprintf
#  ifdef HAS_vsprintf_void
    (void)vsprintf(next, format, va);
    for (len = 0; len < state->size; len++)
        if (next[len] == 0) break;
#  else
    len = vsprintf(next, format, va);
#  endif
#else
#  ifdef HAS_vsnprintf_void
    (void)vsnprintf(next, state->size, format, va);
    len = strlen(next);
#  else
    len = vsnprintf(next, state->size, format, va);
#  endif
#endif

    /* check that printf() results fit in buffer */
    if (len == 0 || (unsigned)len >= state->size || next[state->size - 1] != 0)
        return 0;

    /* update buffer and position, compress first half if past that */
    state->strm.avail_in += (unsigned)len;
    state->File.pos += len;
    if (state->strm.avail_in >= state->size)
    {
        left = state->strm.avail_in - state->size;
        state->strm.avail_in = state->size;
        if (state->gz_comp(Z_NO_FLUSH) == -1)
            return state->err;
        memcpy(state->in, state->in + state->size, left);
        state->strm.next_in = state->in;
        state->strm.avail_in = left;
    }
    return len;
}

/*
int   gzprintf( const char* format, ...)
{
    va_list va;
    int ret;

    va_start(va, format);
    ret = gzvprintf(file, format, va);
    va_end(va);
    return ret;
}*/

int GZipFile::gzprintf( const char* format, int a1, int a2, int a3, int a4, int  a5, int a6, int  a7, int  a8, int a9, int  a10, int  a11, int a12, int  a13, int a14, int  a15, int a16, int a17, int  a18, int a19, int a20)
{
    unsigned len, left;
    char* next;
    GZipStateData* state = (GZipStateData*)this;;
    ZLibStream* strm = &state->strm;  


    /* check that can really pass pointer in ints */
    if (sizeof(int) != sizeof(void*))
        return Z_STREAM_ERROR;

    /* check that we're writing and that there's no error */
    if (state->mode != GZ_WRITE || state->err != Z_OK)
        return Z_STREAM_ERROR;

    /* make sure we have some buffer space */
    if (state->size == 0 && state->gz_init() == -1)
        return state->err;

    /* check for seek request */
    if (state->seek)
    {
        state->seek = 0;
        if (state->gz_zero( state->skip) == -1)
            return state->err;
    }

    /* do the printf() into the input buffer, put length in len -- the input
       buffer is double-sized just for this function, so there is guaranteed to
       be state->size bytes available after the current contents */
    if (strm->avail_in == 0)
        strm->next_in = state->in;
    next = (char*)(strm->next_in + strm->avail_in);
    next[state->size - 1] = 0;
#ifdef NO_snprintf
#  ifdef HAS_sprintf_void
    sprintf(next, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12,
        a13, a14, a15, a16, a17, a18, a19, a20);
    for (len = 0; len < size; len++)
        if (next[len] == 0)
            break;
#  else
    len = sprintf(next, format, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11,
        a12, a13, a14, a15, a16, a17, a18, a19, a20);
#  endif
#else
#  ifdef HAS_snprintf_void
    snprintf(next, state->size, format, a1, a2, a3, a4, a5, a6, a7, a8, a9,
        a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20);
    len = strlen(next);
#  else
    len = snprintf(next, state->size, format, a1, a2, a3, a4, a5, a6, a7, a8,
        a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20);
#  endif
#endif

    /* check that printf() results fit in buffer */
    if (len == 0 || len >= state->size || next[state->size - 1] != 0)
        return 0;

    /* update buffer and position, compress first half if past that */
    strm->avail_in += len;
    state->File.pos += len;
    if (strm->avail_in >= state->size)
    {
        left = strm->avail_in - state->size;
        strm->avail_in = state->size;
        if (state->gz_comp(Z_NO_FLUSH) == -1)
            return state->err;
        memcpy(state->in, state->in + state->size, left);
        strm->next_in = state->in;
        strm->avail_in = left;
    }
    return (int)len;
}

int   GZipFile::gzflush( int flush)
{
    GZipStateData* state;

    state = (GZipStateData*)this;

    /* check that we're writing and that there's no error */
    if (state->mode != GZ_WRITE || state->err != Z_OK)
        return Z_STREAM_ERROR;

    /* check flush parameter */
    if (flush < 0 || flush > Z_FINISH)
        return Z_STREAM_ERROR;

    /* check for seek request */
    if (state->seek)
    {
        state->seek = 0;
        if (state->gz_zero(state->skip) == -1)
            return state->err;
    }

    /* compress remaining data with requested flush */
    state->gz_comp(flush);
    return state->err;
}

int  GZipFile::gzsetparams( int level, int strategy)
{ 

    GZipStateData* state = (GZipStateData*)this;;
    ZLibStream* strm = &state->strm;
    /* check that we're writing and that there's no error */
    if (state->mode != GZ_WRITE || state->err != Z_OK)
        return Z_STREAM_ERROR;

    /* if no change is requested, then do nothing */
    if (level == state->level && strategy == state->strategy)
        return Z_OK;

    /* check for seek request */
    if (state->seek)
    {
        state->seek = 0;
        if (state->gz_zero(state->skip) == -1)
            return state->err;
    }

    /* change compression parameters for subsequent input */
    if (state->size)
    {
        /* flush previous input with previous parameters before changing */
        if (strm->avail_in && state->gz_comp(Z_BLOCK) == -1)
            return state->err;
        strm->deflateParams(level, strategy);
    }
    state->level = level;
    state->strategy = strategy;
    return Z_OK;
}

int  GZipFile::gzclose_w()
{
    int ret = Z_OK;
    GZipStateData* state = (GZipStateData*)this;;
    ZLibStream* strm = &state->strm;

    /* check that we're writing */
    if (state->mode != GZ_WRITE)
        return Z_STREAM_ERROR;

    /* check for seek request */
    if (state->seek)
    {
        state->seek = 0;
        if (state->gz_zero(state->skip) == -1)
            ret = state->err;
    }

    /* flush, free memory, and close file */
    if (state->gz_comp(Z_FINISH) == -1)
        ret = state->err;
    if (state->size)
    {
        if (!state->direct)
        {
            strm->deflateEnd();
            free(state->out);
        }
        free(state->in);
    }
    state->gz_error(Z_OK, NULL);
    free(state->path);
    if (_close(state->fd) == -1)
        ret = Z_ERRNO;
    free(state);
    return ret;
}