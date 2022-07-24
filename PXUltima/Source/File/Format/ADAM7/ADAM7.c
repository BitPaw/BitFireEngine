#include "ADAM7.h"

/*Try the code, if it returns error, also return the error.*/
#define CERROR_TRY_RETURN(call){\
  unsigned error = call;\
  if(error) return error;\
}

 /*shared values used by multiple Adam7 related functions*/

static const unsigned ADAM7_IX[7] = { 0, 4, 0, 2, 0, 1, 0 }; /*x start values*/
static const unsigned ADAM7_IY[7] = { 0, 0, 4, 0, 2, 0, 1 }; /*y start values*/
static const unsigned ADAM7_DX[7] = { 8, 8, 4, 4, 2, 2, 1 }; /*x delta values*/
static const unsigned ADAM7_DY[7] = { 8, 8, 8, 4, 4, 2, 2 }; /*y delta values*/

unsigned int ADAM7ScanlinesDecode(unsigned char* out, unsigned char* in, size_t width, size_t height, size_t bpp, PNGInterlaceMethod interlaceMethod)
{
    /*
     This function converts the filtered-padded-interlaced data into pure 2D image buffer with the PNG's colortype.
     Steps:
     *) if no Adam7: 1) unfilter 2) remove padding bits (= possible extra bits per scanline if bpp < 8)
     *) if adam7: 1) 7x unfilter 2) 7x remove padding bits 3) Adam7_deinterlace
     NOTE: the in buffer will be overwritten with intermediate data!
     */
    if (bpp == 0) return 31; /*error: invalid colortype*/



    switch (interlaceMethod)
    {
        default:
        case PNGInterlaceInvalid:
            break;

        case PNGInterlaceNone:
        {
            const unsigned char additionalStep = bpp < 8 && width * bpp != ((width * bpp + 7u) / 8u) * 8u;

            if (additionalStep)
            {
                CERROR_TRY_RETURN(ADAM7unfilter(in, in, width, height, bpp));
                ADAM7removePaddingBits(out, in, width * bpp, ((width * bpp + 7u) / 8u) * 8u, height);
            }

            /*we can immediately filter into the out buffer, no other steps needed*/
            else CERROR_TRY_RETURN(ADAM7unfilter(out, in, width, height, bpp));

            break;
        }    
        case PNGInterlaceADAM7:
        {
            unsigned passw[7], passh[7]; size_t filter_passstart[8], padded_passstart[8], passstart[8];
            unsigned i;

            ADAM7_getpassvalues(passw, passh, filter_passstart, padded_passstart, passstart, width, height, bpp);

            for (i = 0; i != 7; ++i)
            {
                CERROR_TRY_RETURN(ADAM7unfilter(&in[padded_passstart[i]], &in[filter_passstart[i]], passw[i], passh[i], bpp));
                /*TODO: possible efficiency improvement: if in this reduced image the bits fit nicely in 1 scanline,
                move bytes instead of bits or move not at all*/
                if (bpp < 8)
                {
                    /*remove padding bits in scanlines; after this there still may be padding
                    bits between the different reduced images: each reduced image still starts nicely at a byte*/
                    ADAM7removePaddingBits(&in[passstart[i]], &in[padded_passstart[i]], passw[i] * bpp, ((passw[i] * bpp + 7u) / 8u) * 8u, passh[i]);
                }
            }

            ADAM7_deinterlace(out, in, width, height, bpp);

            break; 
        }
    }

    return 0;
}

unsigned int ADAM7ScanlinesEncode(unsigned char* out, unsigned char* in, size_t width, size_t height, size_t bbp, PNGInterlaceMethod interlaceMethod)
{
    return 0;
}

size_t ADAM7CaluclateExpectedSize(size_t width, size_t height, size_t bpp)
{
    size_t n = width * height;
    return ((n / 8u) * bpp) + ((n & 7u) * bpp + 7u) / 8u;
}

unsigned char ADAM7paethPredictor(short a, short b, short c)
{
#define LODEPNG_MAX(a, b) (((a) > (b)) ? (a) : (b))
#define LODEPNG_MIN(a, b) (((a) < (b)) ? (a) : (b))
#define LODEPNG_ABS(x) ((x) < 0 ? -(x) : (x))

    short pa = LODEPNG_ABS(b - c);
    short pb = LODEPNG_ABS(a - c);
    short pc = LODEPNG_ABS(a + b - c - c);
    /* return input value associated with smallest of pa, pb, pc (with certain priority if equal) */
    if (pb < pa) { a = b; pa = pb; }
    return (pc < pa) ? c : a;
}

unsigned ADAM7unfilterScanline(unsigned char* recon, const unsigned char* scanline, const unsigned char* precon, size_t bytewidth, unsigned char filterType, size_t length)
{
    /*
 For PNG filter method 0
 unfilter a PNG image scanline by scanline. when the pixels are smaller than 1 byte,
 the filter works byte per byte (bytewidth = 1)
 precon is the previous unfiltered scanline, recon the result, scanline the current one
 the incoming scanlines do NOT include the filtertype byte, that one is given in the parameter filterType instead
 recon and scanline MAY be the same memory address! precon must be disjoint.
 */

    switch (filterType)
    {
        case 0:
            for (size_t i = 0; i != length; ++i) recon[i] = scanline[i];
            break;
        case 1:
        {
            size_t j = 0;
            for (size_t i = 0; i != bytewidth; ++i) recon[i] = scanline[i];
            for (size_t i = bytewidth; i != length; ++i, ++j) recon[i] = scanline[i] + recon[j];
            break;
        }
        case 2:
            if (precon)
            {
                for (size_t i = 0; i != length; ++i) recon[i] = scanline[i] + precon[i];
            }
            else
            {
                for (size_t i = 0; i != length; ++i) recon[i] = scanline[i];
            }
            break;
        case 3:
            if (precon)
            {
                size_t j = 0;
                size_t i = 0;
                for (i = 0; i != bytewidth; ++i) recon[i] = scanline[i] + (precon[i] >> 1u);
                /* Unroll independent paths of this predictor. A 6x and 8x version is also possible but that adds
                too much code. Whether this speeds up anything depends on compiler and settings. */
                if (bytewidth >= 4)
                {
                    for (; i + 3 < length; i += 4, j += 4)
                    {
                        unsigned char s0 = scanline[i + 0], r0 = recon[j + 0], p0 = precon[i + 0];
                        unsigned char s1 = scanline[i + 1], r1 = recon[j + 1], p1 = precon[i + 1];
                        unsigned char s2 = scanline[i + 2], r2 = recon[j + 2], p2 = precon[i + 2];
                        unsigned char s3 = scanline[i + 3], r3 = recon[j + 3], p3 = precon[i + 3];
                        recon[i + 0] = s0 + ((r0 + p0) >> 1u);
                        recon[i + 1] = s1 + ((r1 + p1) >> 1u);
                        recon[i + 2] = s2 + ((r2 + p2) >> 1u);
                        recon[i + 3] = s3 + ((r3 + p3) >> 1u);
                    }
                }
                else if (bytewidth >= 3)
                {
                    for (; i + 2 < length; i += 3, j += 3)
                    {
                        unsigned char s0 = scanline[i + 0], r0 = recon[j + 0], p0 = precon[i + 0];
                        unsigned char s1 = scanline[i + 1], r1 = recon[j + 1], p1 = precon[i + 1];
                        unsigned char s2 = scanline[i + 2], r2 = recon[j + 2], p2 = precon[i + 2];
                        recon[i + 0] = s0 + ((r0 + p0) >> 1u);
                        recon[i + 1] = s1 + ((r1 + p1) >> 1u);
                        recon[i + 2] = s2 + ((r2 + p2) >> 1u);
                    }
                }
                else if (bytewidth >= 2)
                {
                    for (; i + 1 < length; i += 2, j += 2)
                    {
                        unsigned char s0 = scanline[i + 0], r0 = recon[j + 0], p0 = precon[i + 0];
                        unsigned char s1 = scanline[i + 1], r1 = recon[j + 1], p1 = precon[i + 1];
                        recon[i + 0] = s0 + ((r0 + p0) >> 1u);
                        recon[i + 1] = s1 + ((r1 + p1) >> 1u);
                    }
                }
                for (; i != length; ++i, ++j) recon[i] = scanline[i] + ((recon[j] + precon[i]) >> 1u);
            }
            else
            {
                size_t j = 0;
                for (size_t i = 0; i != bytewidth; ++i) recon[i] = scanline[i];
                for (size_t i = bytewidth; i != length; ++i, ++j) recon[i] = scanline[i] + (recon[j] >> 1u);
            }
            break;
        case 4:
            if (precon)
            {
                size_t j = 0;
                size_t i = 0;
                for (i = 0; i != bytewidth; ++i)
                {
                    recon[i] = (scanline[i] + precon[i]); /*paethPredictor(0, precon[i], 0) is always precon[i]*/
                }

                /* Unroll independent paths of the paeth predictor. A 6x and 8x version is also possible but that
                adds too much code. Whether this speeds up anything depends on compiler and settings. */
                if (bytewidth >= 4)
                {
                    for (; i + 3 < length; i += 4, j += 4)
                    {
                        unsigned char s0 = scanline[i + 0], s1 = scanline[i + 1], s2 = scanline[i + 2], s3 = scanline[i + 3];
                        unsigned char r0 = recon[j + 0], r1 = recon[j + 1], r2 = recon[j + 2], r3 = recon[j + 3];
                        unsigned char p0 = precon[i + 0], p1 = precon[i + 1], p2 = precon[i + 2], p3 = precon[i + 3];
                        unsigned char q0 = precon[j + 0], q1 = precon[j + 1], q2 = precon[j + 2], q3 = precon[j + 3];
                        recon[i + 0] = s0 + ADAM7paethPredictor(r0, p0, q0);
                        recon[i + 1] = s1 + ADAM7paethPredictor(r1, p1, q1);
                        recon[i + 2] = s2 + ADAM7paethPredictor(r2, p2, q2);
                        recon[i + 3] = s3 + ADAM7paethPredictor(r3, p3, q3);
                    }
                }
                else if (bytewidth >= 3)
                {
                    for (; i + 2 < length; i += 3, j += 3)
                    {
                        unsigned char s0 = scanline[i + 0], s1 = scanline[i + 1], s2 = scanline[i + 2];
                        unsigned char r0 = recon[j + 0], r1 = recon[j + 1], r2 = recon[j + 2];
                        unsigned char p0 = precon[i + 0], p1 = precon[i + 1], p2 = precon[i + 2];
                        unsigned char q0 = precon[j + 0], q1 = precon[j + 1], q2 = precon[j + 2];
                        recon[i + 0] = s0 + ADAM7paethPredictor(r0, p0, q0);
                        recon[i + 1] = s1 + ADAM7paethPredictor(r1, p1, q1);
                        recon[i + 2] = s2 + ADAM7paethPredictor(r2, p2, q2);
                    }
                }
                else if (bytewidth >= 2)
                {
                    for (; i + 1 < length; i += 2, j += 2)
                    {
                        unsigned char s0 = scanline[i + 0], s1 = scanline[i + 1];
                        unsigned char r0 = recon[j + 0], r1 = recon[j + 1];
                        unsigned char p0 = precon[i + 0], p1 = precon[i + 1];
                        unsigned char q0 = precon[j + 0], q1 = precon[j + 1];
                        recon[i + 0] = s0 + ADAM7paethPredictor(r0, p0, q0);
                        recon[i + 1] = s1 + ADAM7paethPredictor(r1, p1, q1);
                    }
                }

                for (; i != length; ++i, ++j)
                {
                    recon[i] = (scanline[i] + ADAM7paethPredictor(recon[i - bytewidth], precon[i], precon[j]));
                }
            }
            else
            {
                size_t j = 0;
                for (size_t i = 0; i != bytewidth; ++i)
                {
                    recon[i] = scanline[i];
                }
                for (size_t i = bytewidth; i != length; ++i, ++j)
                {
                    /*paethPredictor(recon[i - bytewidth], 0, 0) is always recon[i - bytewidth]*/
                    recon[i] = (scanline[i] + recon[j]);
                }
            }
            break;
        default: return 36; /*error: invalid filter type given*/
    }
    return 0;
}

size_t ADAM7lodepng_get_raw_size_idat(size_t w, size_t h, size_t bpp)
{
    /* + 1 for the filter byte, and possibly plus padding bits per line. */
  /* Ignoring casts, the expression is equal to (w * bpp + 7) / 8 + 1, but avoids overflow of w * bpp */
    size_t line = ((size_t)(w / 8u) * bpp) + 1u + ((w & 7u) * bpp + 7u) / 8u;
    return (size_t)h * line;
}

unsigned ADAM7unfilter(unsigned char* out, const unsigned char* in, size_t w, size_t h, size_t bpp)
{
    /*
  For PNG filter method 0
  this function unfilters a single image (e.g. without interlacing this is called once, with Adam7 seven times)
  out must have enough bytes allocated already, in must have the scanlines + 1 filtertype byte per scanline
  w and h are image dimensions or dimensions of reduced image, bpp is bits per pixel
  in and out are allowed to be the same memory address (but aren't the same size since in has the extra filter bytes)
  */
  

    /*bytewidth is used for filtering, is 1 when bpp < 8, number of bytes per pixel otherwise*/
    const size_t bytewidth = (bpp + 7u) / 8u;
    /*the width of a scanline in bytes, not including the filter type*/
    const size_t linebytes = ADAM7lodepng_get_raw_size_idat(w, 1, bpp) - 1u;

    unsigned char* prevline = 0;

    for (size_t y = 0; y < h; ++y)
    {
        const size_t outindex = linebytes * y;
        const size_t inindex = (1 + linebytes) * y; /*the extra filterbyte added to each row*/
        const unsigned char filterType = in[inindex];

        CERROR_TRY_RETURN(ADAM7unfilterScanline(&out[outindex], &in[inindex + 1], prevline, bytewidth, filterType, linebytes));

        prevline = &out[outindex];
    }

    return 0;
}

void ADAM7removePaddingBits(unsigned char* out, const unsigned char* in, size_t olinebits, size_t ilinebits, size_t h)
{
    /*
  After filtering there are still padding bits if scanlines have non multiple of 8 bit amounts. They need
  to be removed (except at last scanline of (Adam7-reduced) image) before working with pure image buffers
  for the Adam7 code, the color convert code and the output to the user.
  in and out are allowed to be the same buffer, in may also be higher but still overlapping; in must
  have >= ilinebits*h bits, out must have >= olinebits*h bits, olinebits must be <= ilinebits
  also used to move bits after earlier such operations happened, e.g. in a sequence of reduced images from Adam7
  only useful if (ilinebits - olinebits) is a value in the range 1..7
  */

    size_t diff = ilinebits - olinebits;
    size_t ibp = 0;
    size_t obp = 0; /*input and output bit pointers*/

    for (size_t y = 0; y < h; ++y)
    {
        for (size_t x = 0; x < olinebits; ++x)
        {
            unsigned char bit = readBitFromReversedStream(&ibp, in);
            ADAM7setBitOfReversedStream(&obp, out, bit);
        }
        ibp += diff;
    }
}

unsigned char ADAM7readBitFromReversedStream(size_t* bitpointer, const unsigned char* bitstream)
{
    unsigned char result = (unsigned char)((bitstream[(*bitpointer) >> 3] >> (7 - ((*bitpointer) & 0x7))) & 1);
    ++(*bitpointer);
    return result;
}

void ADAM7setBitOfReversedStream(size_t* bitpointer, unsigned char* bitstream, unsigned char bit)
{
    /*the current bit in bitstream may be 0 or 1 for this to work*/
    if (bit == 0) bitstream[(*bitpointer) >> 3u] &= (unsigned char)(~(1u << (7u - ((*bitpointer) & 7u))));
    else         bitstream[(*bitpointer) >> 3u] |= (1u << (7u - ((*bitpointer) & 7u)));
    ++(*bitpointer);
}

void ADAM7_getpassvalues(unsigned passw[7], unsigned passh[7], size_t filter_passstart[8], size_t padded_passstart[8], size_t passstart[8], size_t w, size_t h, size_t bpp)
{
   

    /*the passstart values have 8 values: the 8th one indicates the byte after the end of the 7th (= last) pass*/
    //unsigned i;

    /*calculate width and height in pixels of each pass*/
    for (size_t i = 0; i != 7; ++i)
    {
        passw[i] = (w + ADAM7_DX[i] - ADAM7_IX[i] - 1) / ADAM7_DX[i];
        passh[i] = (h + ADAM7_DY[i] - ADAM7_IY[i] - 1) / ADAM7_DY[i];
        if (passw[i] == 0) passh[i] = 0;
        if (passh[i] == 0) passw[i] = 0;
    }

    filter_passstart[0] = padded_passstart[0] = passstart[0] = 0;

    for (size_t i = 0; i != 7; ++i)
    {
        /*if passw[i] is 0, it's 0 bytes, not 1 (no filtertype-byte)*/
        filter_passstart[i + 1] = filter_passstart[i] + ((passw[i] && passh[i]) ? passh[i] * (1u + (passw[i] * bpp + 7u) / 8u) : 0);
        /*bits padded if needed to fill full byte at end of each scanline*/
        padded_passstart[i + 1] = padded_passstart[i] + passh[i] * ((passw[i] * bpp + 7u) / 8u);
        /*only padded at end of reduced image*/
        passstart[i + 1] = passstart[i] + (passh[i] * passw[i] * bpp + 7u) / 8u;
    }
}

void ADAM7_deinterlace(unsigned char* out, const unsigned char* in, size_t w, unsigned h, unsigned bpp)
{
    unsigned int passw[7];
    unsigned int passh[7];
    size_t filter_passstart[8], padded_passstart[8], passstart[8];

    ADAM7_getpassvalues(passw, passh, filter_passstart, padded_passstart, passstart, w, h, bpp);

    if (bpp >= 8)
    {
        for (size_t i = 0; i != 7; ++i)
        {
            size_t bytewidth = bpp / 8u;

            for (size_t y = 0; y < passh[i]; ++y)
            {
                for (size_t x = 0; x < passw[i]; ++x)
                {
                    size_t pixelinstart = passstart[i] + (y * passw[i] + x) * bytewidth;
                    size_t pixeloutstart = ((ADAM7_IY[i] + y * ADAM7_DY[i]) * w + ADAM7_IX[i] + x * ADAM7_DX[i]) * bytewidth;
                  
                    for (size_t b = 0; b < bytewidth; ++b)
                    {
                        out[pixeloutstart + b] = in[pixelinstart + b];
                    }
                }
            }                
        }
    }
    else /*bpp < 8: Adam7 with pixels < 8 bit is a bit trickier: with bit pointers*/
    {
        for (size_t i = 0; i != 7; ++i)
        {
            unsigned x, y, b;
            unsigned ilinebits = bpp * passw[i];
            unsigned olinebits = bpp * w;
            size_t obp, ibp; /*bit pointers (for out and in buffer)*/
            for (y = 0; y < passh[i]; ++y)
                for (x = 0; x < passw[i]; ++x)
                {
                    ibp = (8 * passstart[i]) + (y * ilinebits + x * bpp);
                    obp = (ADAM7_IY[i] + (size_t)y * ADAM7_DY[i]) * olinebits + (ADAM7_IX[i] + (size_t)x * ADAM7_DX[i]) * bpp;
                    for (b = 0; b < bpp; ++b)
                    {
                        unsigned char bit = readBitFromReversedStream(&ibp, in);
                        ADAM7setBitOfReversedStream(&obp, out, bit);
                    }
                }
        }
    }
}