#include "PNG.h"

#include <File/ParsingStream.h>
#include <Memory/Memory.h>
#include <File/Endian.h>
#include <Container/ClusterInt.h>
#include <File/Format/ZLIB/ZLIB.h>
#include <File/Format/ADAM7/ADAM7.h>
#include <Algorithm/CRC32/CRC32.h>
#include <File/Image.h>
#include <Time/Time.h>

#define PNGHeaderSequenz { 0x89, 'P', 'N', 'G', '\r', '\n', 0x1A, '\n' }
#define PNGDebugInfo false

unsigned int color_tree_add(PNGColorTree* tree, unsigned char r, unsigned char g, unsigned char b, unsigned char a, unsigned index)
{
    for(size_t bit = 0; bit < 8; ++bit)
    {
        int i = 8 * ((r >> bit) & 1) + 4 * ((g >> bit) & 1) + 2 * ((b >> bit) & 1) + 1 * ((a >> bit) & 1);
        if(!tree->children[i])
        {
            tree->children[i] = MemoryAllocate(sizeof(PNGColorTree) * 1);

            if(!tree->children[i]) return 83; /*alloc fail*/
        }
        tree = tree->children[i];
    }
    tree->index = (int)index;
    return 0;
}

unsigned int Decompress(const unsigned char* pixelDataIn, unsigned char* pixelDataOut, size_t width, size_t height, unsigned char bitDepth, PNGColorType colorType)
{
    LodePNGColorMode colorModeIn;
    LodePNGColorMode colorModeOut;
   
    MemorySet(&colorModeIn, sizeof(LodePNGColorMode), 0);
    MemorySet(&colorModeOut, sizeof(LodePNGColorMode), 0);

    colorModeIn.bitdepth = bitDepth;
    colorModeIn.colortype = LCT_RGBA;

    colorModeOut.bitdepth = bitDepth;
    colorModeOut.colortype = LCT_RGBA;

    switch(colorType)
    {
        default:
        case PNGColorInvalid:
            colorModeIn.colortype = LCT_MAX_OCTET_VALUE;
            break;

        case PNGColorGrayscale:
            colorModeIn.colortype = LCT_GREY;
            break;

        case PNGColorTruecolor:
            colorModeIn.colortype = LCT_RGB;
            break;

        case PNGColorIndexedColor:
            colorModeIn.colortype = LCT_PALETTE;
            break;

        case PNGColorGrayscaleWithAlphaChannel:
            colorModeIn.colortype = LCT_GREY_ALPHA;
            break;

        case PNGColorTruecolorWithAlphaChannel:
            colorModeIn.colortype = LCT_RGBA;
            break;
    }

    colorModeOut.bitdepth = colorModeIn.bitdepth;
    colorModeOut.colortype = colorModeIn.colortype;

    size_t i;
    PNGColorTree tree;
    size_t numpixels = width * height;
    unsigned error = 0;

    if(colorModeIn.colortype == LCT_PALETTE && !colorModeIn.palette)
    {
        return 107; /* error: must provide palette if input mode is palette */
    }

    if(lodepng_color_mode_equal(&colorModeOut, &colorModeIn))
    {
        size_t numbytes = lodepng_get_raw_size(width, height, &colorModeIn);
        MemoryCopy(pixelDataIn, numbytes, pixelDataOut, numbytes);
        return 0;
    }

    if(colorModeOut.colortype == LCT_PALETTE)
    {
        size_t palettesize = colorModeOut.palettesize;
        const unsigned char* palette = colorModeOut.palette;
        size_t palsize = (size_t)1u << colorModeOut.bitdepth;
        /*if the user specified output palette but did not give the values, assume
        they want the values of the input color type (assuming that one is palette).
        Note that we never create a new palette ourselves.*/
        if(palettesize == 0)
        {
            palettesize = colorModeIn.palettesize;
            palette = colorModeIn.palette;
            /*if the input was also palette with same bitdepth, then the color types are also
            equal, so copy literally. This to preserve the exact indices that were in the PNG
            even in case there are duplicate colors in the palette.*/
            if(colorModeIn.colortype == LCT_PALETTE && colorModeIn.bitdepth == colorModeOut.bitdepth)
            {
                size_t numbytes = lodepng_get_raw_size(width, height, &colorModeIn);
                memcpy(pixelDataOut, pixelDataIn, numbytes);
                return 0;
            }
        }
        if(palettesize < palsize) palsize = palettesize;

        // color_tree_init(&tree);

        for(i = 0; i != palsize; ++i)
        {
            const unsigned char* p = &palette[i * 4];
            error = color_tree_add(&tree, p[0], p[1], p[2], p[3], (unsigned)i);
            if(error) break;
        }
    }

    if(!error)
    {
        if(colorModeIn.bitdepth == 16 && colorModeOut.bitdepth == 16)
        {
            for(i = 0; i != numpixels; ++i)
            {
                unsigned short r = 0, g = 0, b = 0, a = 0;
                getPixelColorRGBA16(&r, &g, &b, &a, pixelDataIn, i, &colorModeIn);
                rgba16ToPixel(pixelDataOut, i, &colorModeOut, r, g, b, a);
            }
        }
        else if(colorModeOut.bitdepth == 8 && colorModeOut.colortype == LCT_RGBA)
        {
            getPixelColorsRGBA8(pixelDataOut, numpixels, pixelDataIn, &colorModeIn);
        }
        else if(colorModeOut.bitdepth == 8 && colorModeOut.colortype == LCT_RGB)
        {
            getPixelColorsRGB8(pixelDataOut, numpixels, pixelDataIn, &colorModeIn);
        }
        else
        {
            unsigned char r = 0, g = 0, b = 0, a = 0;
            for(i = 0; i != numpixels; ++i)
            {
                getPixelColorRGBA8(&r, &g, &b, &a, pixelDataIn, i, &colorModeIn);
                error = rgba8ToPixel(pixelDataOut, i, &colorModeOut, &tree, r, g, b, a);
                if(error) break;
            }
        }
    }

    /*
    if (colorModeOut.colortype == LCT_PALETTE)
    {
       // color_tree_cleanup(&tree);
    }*/

    return error;
}

unsigned getNumColorChannels(LodePNGColorType colortype)
{
    switch(colortype)
    {
        case LCT_GREY: return 1;
        case LCT_RGB: return 3;
        case LCT_PALETTE: return 1;
        case LCT_GREY_ALPHA: return 2;
        case LCT_RGBA: return 4;
        case LCT_MAX_OCTET_VALUE: return 0; /* invalid color type */
        default: return 0; /*invalid color type*/
    }
}

size_t lodepng_get_bpp_lct(LodePNGColorType colortype, size_t bitdepth)
{
    /*bits per pixel is amount of channels * bits per channel*/
    return getNumColorChannels(colortype) * bitdepth;
}

int lodepng_color_mode_equal(const LodePNGColorMode* a, const LodePNGColorMode* b)
{
    size_t i;
    if(a->colortype != b->colortype) return 0;
    if(a->bitdepth != b->bitdepth) return 0;
    if(a->key_defined != b->key_defined) return 0;
    if(a->key_defined)
    {
        if(a->key_r != b->key_r) return 0;
        if(a->key_g != b->key_g) return 0;
        if(a->key_b != b->key_b) return 0;
    }
    if(a->palettesize != b->palettesize) return 0;
    for(i = 0; i != a->palettesize * 4; ++i)
    {
        if(a->palette[i] != b->palette[i]) return 0;
    }
    return 1;
}

void getPixelColorRGBA16(unsigned short* r, unsigned short* g, unsigned short* b, unsigned short* a, const unsigned char* in, size_t i, const LodePNGColorMode* mode)
{
    if(mode->colortype == LCT_GREY)
    {
        *r = *g = *b = 256 * in[i * 2 + 0] + in[i * 2 + 1];
        if(mode->key_defined && 256U * in[i * 2 + 0] + in[i * 2 + 1] == mode->key_r) *a = 0;
        else *a = 65535;
    }
    else if(mode->colortype == LCT_RGB)
    {
        *r = 256u * in[i * 6 + 0] + in[i * 6 + 1];
        *g = 256u * in[i * 6 + 2] + in[i * 6 + 3];
        *b = 256u * in[i * 6 + 4] + in[i * 6 + 5];
        if(mode->key_defined
           && 256u * in[i * 6 + 0] + in[i * 6 + 1] == mode->key_r
           && 256u * in[i * 6 + 2] + in[i * 6 + 3] == mode->key_g
           && 256u * in[i * 6 + 4] + in[i * 6 + 5] == mode->key_b) *a = 0;
        else *a = 65535;
    }
    else if(mode->colortype == LCT_GREY_ALPHA)
    {
        *r = *g = *b = 256u * in[i * 4 + 0] + in[i * 4 + 1];
        *a = 256u * in[i * 4 + 2] + in[i * 4 + 3];
    }
    else if(mode->colortype == LCT_RGBA)
    {
        *r = 256u * in[i * 8 + 0] + in[i * 8 + 1];
        *g = 256u * in[i * 8 + 2] + in[i * 8 + 3];
        *b = 256u * in[i * 8 + 4] + in[i * 8 + 5];
        *a = 256u * in[i * 8 + 6] + in[i * 8 + 7];
    }
}

void rgba16ToPixel(unsigned char* out, size_t i, const LodePNGColorMode* mode, unsigned short r, unsigned short g, unsigned short b, unsigned short a)
{
    if(mode->colortype == LCT_GREY)
    {
        unsigned short gray = r; /*((unsigned)r + g + b) / 3u;*/
        out[i * 2 + 0] = (gray >> 8) & 255;
        out[i * 2 + 1] = gray & 255;
    }
    else if(mode->colortype == LCT_RGB)
    {
        out[i * 6 + 0] = (r >> 8) & 255;
        out[i * 6 + 1] = r & 255;
        out[i * 6 + 2] = (g >> 8) & 255;
        out[i * 6 + 3] = g & 255;
        out[i * 6 + 4] = (b >> 8) & 255;
        out[i * 6 + 5] = b & 255;
    }
    else if(mode->colortype == LCT_GREY_ALPHA)
    {
        unsigned short gray = r; /*((unsigned)r + g + b) / 3u;*/
        out[i * 4 + 0] = (gray >> 8) & 255;
        out[i * 4 + 1] = gray & 255;
        out[i * 4 + 2] = (a >> 8) & 255;
        out[i * 4 + 3] = a & 255;
    }
    else if(mode->colortype == LCT_RGBA)
    {
        out[i * 8 + 0] = (r >> 8) & 255;
        out[i * 8 + 1] = r & 255;
        out[i * 8 + 2] = (g >> 8) & 255;
        out[i * 8 + 3] = g & 255;
        out[i * 8 + 4] = (b >> 8) & 255;
        out[i * 8 + 5] = b & 255;
        out[i * 8 + 6] = (a >> 8) & 255;
        out[i * 8 + 7] = a & 255;
    }
}

void getPixelColorsRGBA8(unsigned char* buffer, size_t numpixels, const unsigned char* in, const LodePNGColorMode* mode)
{
    unsigned num_channels = 4;
    size_t i;
    if(mode->colortype == LCT_GREY)
    {
        if(mode->bitdepth == 8)
        {
            for(i = 0; i != numpixels; ++i, buffer += num_channels)
            {
                buffer[0] = buffer[1] = buffer[2] = in[i];
                buffer[3] = 255;
            }
            if(mode->key_defined)
            {
                buffer -= numpixels * num_channels;
                for(i = 0; i != numpixels; ++i, buffer += num_channels)
                {
                    if(buffer[0] == mode->key_r) buffer[3] = 0;
                }
            }
        }
        else if(mode->bitdepth == 16)
        {
            for(i = 0; i != numpixels; ++i, buffer += num_channels)
            {
                buffer[0] = buffer[1] = buffer[2] = in[i * 2];
                buffer[3] = mode->key_defined && 256U * in[i * 2 + 0] + in[i * 2 + 1] == mode->key_r ? 0 : 255;
            }
        }
        else
        {
            unsigned highest = ((1U << mode->bitdepth) - 1U); /*highest possible value for this bit depth*/
            size_t j = 0;
            for(i = 0; i != numpixels; ++i, buffer += num_channels)
            {
                unsigned value = readBitsFromReversedStream(&j, in, mode->bitdepth);
                buffer[0] = buffer[1] = buffer[2] = (value * 255) / highest;
                buffer[3] = mode->key_defined && value == mode->key_r ? 0 : 255;
            }
        }
    }
    else if(mode->colortype == LCT_RGB)
    {
        if(mode->bitdepth == 8)
        {
            for(i = 0; i != numpixels; ++i, buffer += num_channels)
            {
                memcpy(buffer, &in[i * 3], 3);
                buffer[3] = 255;
            }
            if(mode->key_defined)
            {
                buffer -= numpixels * num_channels;
                for(i = 0; i != numpixels; ++i, buffer += num_channels)
                {
                    if(buffer[0] == mode->key_r && buffer[1] == mode->key_g && buffer[2] == mode->key_b) buffer[3] = 0;
                }
            }
        }
        else
        {
            for(i = 0; i != numpixels; ++i, buffer += num_channels)
            {
                buffer[0] = in[i * 6 + 0];
                buffer[1] = in[i * 6 + 2];
                buffer[2] = in[i * 6 + 4];
                buffer[3] = mode->key_defined
                    && 256U * in[i * 6 + 0] + in[i * 6 + 1] == mode->key_r
                    && 256U * in[i * 6 + 2] + in[i * 6 + 3] == mode->key_g
                    && 256U * in[i * 6 + 4] + in[i * 6 + 5] == mode->key_b ? 0 : 255;
            }
        }
    }
    else if(mode->colortype == LCT_PALETTE)
    {
        if(mode->bitdepth == 8)
        {
            for(i = 0; i != numpixels; ++i, buffer += num_channels)
            {
                unsigned index = in[i];
                /*out of bounds of palette not checked: see lodepng_color_mode_alloc_palette.*/
                memcpy(buffer, &mode->palette[index * 4], 4);
            }
        }
        else
        {
            size_t j = 0;
            for(i = 0; i != numpixels; ++i, buffer += num_channels)
            {
                unsigned index = readBitsFromReversedStream(&j, in, mode->bitdepth);
                /*out of bounds of palette not checked: see lodepng_color_mode_alloc_palette.*/
                memcpy(buffer, &mode->palette[index * 4], 4);
            }
        }
    }
    else if(mode->colortype == LCT_GREY_ALPHA)
    {
        if(mode->bitdepth == 8)
        {
            for(i = 0; i != numpixels; ++i, buffer += num_channels)
            {
                buffer[0] = buffer[1] = buffer[2] = in[i * 2 + 0];
                buffer[3] = in[i * 2 + 1];
            }
        }
        else
        {
            for(i = 0; i != numpixels; ++i, buffer += num_channels)
            {
                buffer[0] = buffer[1] = buffer[2] = in[i * 4 + 0];
                buffer[3] = in[i * 4 + 2];
            }
        }
    }
    else if(mode->colortype == LCT_RGBA)
    {
        if(mode->bitdepth == 8)
        {
            memcpy(buffer, in, numpixels * 4);
        }
        else
        {
            for(i = 0; i != numpixels; ++i, buffer += num_channels)
            {
                buffer[0] = in[i * 8 + 0];
                buffer[1] = in[i * 8 + 2];
                buffer[2] = in[i * 8 + 4];
                buffer[3] = in[i * 8 + 6];
            }
        }
    }
}

void getPixelColorsRGB8(unsigned char* buffer, size_t numpixels, const unsigned char* in, const LodePNGColorMode* mode)
{
    const unsigned num_channels = 3;
    size_t i;
    if(mode->colortype == LCT_GREY)
    {
        if(mode->bitdepth == 8)
        {
            for(i = 0; i != numpixels; ++i, buffer += num_channels)
            {
                buffer[0] = buffer[1] = buffer[2] = in[i];
            }
        }
        else if(mode->bitdepth == 16)
        {
            for(i = 0; i != numpixels; ++i, buffer += num_channels)
            {
                buffer[0] = buffer[1] = buffer[2] = in[i * 2];
            }
        }
        else
        {
            unsigned highest = ((1U << mode->bitdepth) - 1U); /*highest possible value for this bit depth*/
            size_t j = 0;
            for(i = 0; i != numpixels; ++i, buffer += num_channels)
            {
                unsigned value = readBitsFromReversedStream(&j, in, mode->bitdepth);
                buffer[0] = buffer[1] = buffer[2] = (value * 255) / highest;
            }
        }
    }
    else if(mode->colortype == LCT_RGB)
    {
        if(mode->bitdepth == 8)
        {
            memcpy(buffer, in, numpixels * 3);
        }
        else
        {
            for(i = 0; i != numpixels; ++i, buffer += num_channels)
            {
                buffer[0] = in[i * 6 + 0];
                buffer[1] = in[i * 6 + 2];
                buffer[2] = in[i * 6 + 4];
            }
        }
    }
    else if(mode->colortype == LCT_PALETTE)
    {
        if(mode->bitdepth == 8)
        {
            for(i = 0; i != numpixels; ++i, buffer += num_channels)
            {
                unsigned index = in[i];
                /*out of bounds of palette not checked: see lodepng_color_mode_alloc_palette.*/
                memcpy(buffer, &mode->palette[index * 4], 3);
            }
        }
        else
        {
            size_t j = 0;
            for(i = 0; i != numpixels; ++i, buffer += num_channels)
            {
                unsigned index = readBitsFromReversedStream(&j, in, mode->bitdepth);
                /*out of bounds of palette not checked: see lodepng_color_mode_alloc_palette.*/
                memcpy(buffer, &mode->palette[index * 4], 3);
            }
        }
    }
    else if(mode->colortype == LCT_GREY_ALPHA)
    {
        if(mode->bitdepth == 8)
        {
            for(i = 0; i != numpixels; ++i, buffer += num_channels)
            {
                buffer[0] = buffer[1] = buffer[2] = in[i * 2 + 0];
            }
        }
        else
        {
            for(i = 0; i != numpixels; ++i, buffer += num_channels)
            {
                buffer[0] = buffer[1] = buffer[2] = in[i * 4 + 0];
            }
        }
    }
    else if(mode->colortype == LCT_RGBA)
    {
        if(mode->bitdepth == 8)
        {
            for(i = 0; i != numpixels; ++i, buffer += num_channels)
            {
                memcpy(buffer, &in[i * 4], 3);
            }
        }
        else
        {
            for(i = 0; i != numpixels; ++i, buffer += num_channels)
            {
                buffer[0] = in[i * 8 + 0];
                buffer[1] = in[i * 8 + 2];
                buffer[2] = in[i * 8 + 4];
            }
        }
    }
}

void getPixelColorRGBA8(unsigned char* r, unsigned char* g, unsigned char* b, unsigned char* a, const unsigned char* in, size_t i, const LodePNGColorMode* mode)
{
    if(mode->colortype == LCT_GREY)
    {
        if(mode->bitdepth == 8)
        {
            *r = *g = *b = in[i];
            if(mode->key_defined && *r == mode->key_r) *a = 0;
            else *a = 255;
        }
        else if(mode->bitdepth == 16)
        {
            *r = *g = *b = in[i * 2 + 0];
            if(mode->key_defined && 256U * in[i * 2 + 0] + in[i * 2 + 1] == mode->key_r) *a = 0;
            else *a = 255;
        }
        else
        {
            unsigned highest = ((1U << mode->bitdepth) - 1U); /*highest possible value for this bit depth*/
            size_t j = i * mode->bitdepth;
            unsigned value = readBitsFromReversedStream(&j, in, mode->bitdepth);
            *r = *g = *b = (value * 255) / highest;
            if(mode->key_defined && value == mode->key_r) *a = 0;
            else *a = 255;
        }
    }
    else if(mode->colortype == LCT_RGB)
    {
        if(mode->bitdepth == 8)
        {
            *r = in[i * 3 + 0]; *g = in[i * 3 + 1]; *b = in[i * 3 + 2];
            if(mode->key_defined && *r == mode->key_r && *g == mode->key_g && *b == mode->key_b) *a = 0;
            else *a = 255;
        }
        else
        {
            *r = in[i * 6 + 0];
            *g = in[i * 6 + 2];
            *b = in[i * 6 + 4];
            if(mode->key_defined && 256U * in[i * 6 + 0] + in[i * 6 + 1] == mode->key_r
               && 256U * in[i * 6 + 2] + in[i * 6 + 3] == mode->key_g
               && 256U * in[i * 6 + 4] + in[i * 6 + 5] == mode->key_b) *a = 0;
            else *a = 255;
        }
    }
    else if(mode->colortype == LCT_PALETTE)
    {
        unsigned index;
        if(mode->bitdepth == 8) index = in[i];
        else
        {
            size_t j = i * mode->bitdepth;
            index = readBitsFromReversedStream(&j, in, mode->bitdepth);
        }
        /*out of bounds of palette not checked: see lodepng_color_mode_alloc_palette.*/
        *r = mode->palette[index * 4 + 0];
        *g = mode->palette[index * 4 + 1];
        *b = mode->palette[index * 4 + 2];
        *a = mode->palette[index * 4 + 3];
    }
    else if(mode->colortype == LCT_GREY_ALPHA)
    {
        if(mode->bitdepth == 8)
        {
            *r = *g = *b = in[i * 2 + 0];
            *a = in[i * 2 + 1];
        }
        else
        {
            *r = *g = *b = in[i * 4 + 0];
            *a = in[i * 4 + 2];
        }
    }
    else if(mode->colortype == LCT_RGBA)
    {
        if(mode->bitdepth == 8)
        {
            *r = in[i * 4 + 0];
            *g = in[i * 4 + 1];
            *b = in[i * 4 + 2];
            *a = in[i * 4 + 3];
        }
        else
        {
            *r = in[i * 8 + 0];
            *g = in[i * 8 + 2];
            *b = in[i * 8 + 4];
            *a = in[i * 8 + 6];
        }
    }
}

unsigned rgba8ToPixel(unsigned char* out, size_t i, const LodePNGColorMode* mode, PNGColorTree* tree, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    if(mode->colortype == LCT_GREY)
    {
        unsigned char gray = r; /*((unsigned short)r + g + b) / 3u;*/
        if(mode->bitdepth == 8) out[i] = gray;
        else if(mode->bitdepth == 16) out[i * 2 + 0] = out[i * 2 + 1] = gray;
        else
        {
            /*take the most significant bits of gray*/
            gray = ((unsigned)gray >> (8u - mode->bitdepth)) & ((1u << mode->bitdepth) - 1u);
            addColorBits(out, i, mode->bitdepth, gray);
        }
    }
    else if(mode->colortype == LCT_RGB)
    {
        if(mode->bitdepth == 8)
        {
            out[i * 3 + 0] = r;
            out[i * 3 + 1] = g;
            out[i * 3 + 2] = b;
        }
        else
        {
            out[i * 6 + 0] = out[i * 6 + 1] = r;
            out[i * 6 + 2] = out[i * 6 + 3] = g;
            out[i * 6 + 4] = out[i * 6 + 5] = b;
        }
    }
    else if(mode->colortype == LCT_PALETTE)
    {
        int index = color_tree_get(tree, r, g, b, a);
        if(index < 0) return 82; /*color not in palette*/
        if(mode->bitdepth == 8) out[i] = index;
        else addColorBits(out, i, mode->bitdepth, (unsigned)index);
    }
    else if(mode->colortype == LCT_GREY_ALPHA)
    {
        unsigned char gray = r; /*((unsigned short)r + g + b) / 3u;*/
        if(mode->bitdepth == 8)
        {
            out[i * 2 + 0] = gray;
            out[i * 2 + 1] = a;
        }
        else if(mode->bitdepth == 16)
        {
            out[i * 4 + 0] = out[i * 4 + 1] = gray;
            out[i * 4 + 2] = out[i * 4 + 3] = a;
        }
    }
    else if(mode->colortype == LCT_RGBA)
    {
        if(mode->bitdepth == 8)
        {
            out[i * 4 + 0] = r;
            out[i * 4 + 1] = g;
            out[i * 4 + 2] = b;
            out[i * 4 + 3] = a;
        }
        else
        {
            out[i * 8 + 0] = out[i * 8 + 1] = r;
            out[i * 8 + 2] = out[i * 8 + 3] = g;
            out[i * 8 + 4] = out[i * 8 + 5] = b;
            out[i * 8 + 6] = out[i * 8 + 7] = a;
        }
    }

    return 0; /*no error*/
}

size_t lodepng_get_raw_size_lct(size_t w, size_t h, LodePNGColorType colortype, size_t bitdepth)
{
    size_t bpp = lodepng_get_bpp_lct(colortype, bitdepth);
    size_t n = w * h;

    return ((n / 8u) * bpp) + ((n & 7u) * bpp + 7u) / 8u;
}

size_t lodepng_get_raw_size(size_t w, size_t h, const LodePNGColorMode* color)
{
    return lodepng_get_raw_size_lct(w, h, color->colortype, color->bitdepth);
}

int color_tree_get(PNGColorTree* tree, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    int bit = 0;
    for(bit = 0; bit < 8; ++bit)
    {
        int i = 8 * ((r >> bit) & 1) + 4 * ((g >> bit) & 1) + 2 * ((b >> bit) & 1) + 1 * ((a >> bit) & 1);
        if(!tree->children[i]) return -1;
        else tree = tree->children[i];
    }
    return tree ? tree->index : -1;
}

void addColorBits(unsigned char* out, size_t index, unsigned int bits, unsigned int in)
{
    unsigned int m = bits == 1 ? 7 : bits == 2 ? 3 : 1; /*8 / bits - 1*/
/*p = the partial index in the byte, e.g. with 4 palettebits it is 0 for first half or 1 for second half*/
    unsigned int p = index & m;

    in &= (1u << bits) - 1u; /*filter out any other bits of the input value*/
    in = in << (bits * (m - p));

    if(p == 0)
    {
        out[index * bits / 8u] = in;
    }
    else
    {
        out[index * bits / 8u] |= in;
    }
}

unsigned char readBitFromReversedStream(size_t* bitpointer, const unsigned char* bitstream)
{
    unsigned char result = (unsigned char)((bitstream[(*bitpointer) >> 3] >> (7 - ((*bitpointer) & 0x7))) & 1);
    ++(*bitpointer);
    return result;
}

unsigned readBitsFromReversedStream(size_t* bitpointer, const unsigned char* bitstream, size_t nbits)
{
    unsigned result = 0;
    size_t i;
    for(i = 0; i < nbits; ++i)
    {
        result <<= 1u;
        result |= (unsigned)readBitFromReversedStream(bitpointer, bitstream);
    }
    return result;
}

PNGChunkType ConvertToChunkType(const unsigned int pngchunkType)
{
    switch(pngchunkType)
    {
        case MakeInt('I', 'H', 'D', 'R'): return PNGChunkImageHeader; // IHDR
        case MakeInt('I', 'D', 'A', 'T'): return PNGChunkImageData; // PLTE
        case MakeInt('I', 'E', 'N', 'D'): return PNGChunkImageEnd; // IEND
        case MakeInt('i', 'C', 'C', 'P'): return PNGChunkEmbeddedICCProfile; // iCCP
        case MakeInt('i', 'T', 'X', 't'): return PNGChunkTransparency; // tRNS
        case MakeInt('s', 'B', 'I', 'T'): return PNGChunkSignificantBits; // sBIT
        case MakeInt('s', 'R', 'G', 'B'): return PNGChunkStandardRGBColorSpace; // sRGB
        case MakeInt('t', 'R', 'N', 'S'): return PNGChunkTransparency; // tRNS
        case MakeInt('t', 'E', 'X', 't'): return PNGChunkTextualData; // tEXt
        case MakeInt('t', 'I', 'M', 'E'): return PNGChunkLastModificationTime; // tIME
        case MakeInt('P', 'L', 'T', 'E'): return PNGChunkPalette; // PLTE
        case MakeInt('c', 'H', 'R', 'M'): return PNGChunkPrimaryChromaticities; // cHRM
        case MakeInt('g', 'A', 'M', 'A'): return PNGChunkImageGamma;// gAMA
        case MakeInt('b', 'K', 'G', 'D'): return PNGChunkBackgroundColor;// bKGD
        case MakeInt('h', 'I', 'S', 'T'): return PNGChunkPaletteHistogram;// hIST   
        case MakeInt('p', 'H', 'Y', 's'): return PNGChunkPhysicalPixelDimensions; //pHYs
        case MakeInt('s', 'P', 'L', 'T'): return PNGChunkSuggestedPalette;// sPLT   
        case MakeInt('z', 'T', 'X', 't'): return PNGChunkCompressedTextualData;// zTXt

        default: return PNGChunkInvalid;
    }
}

unsigned int ConvertFromChunkType(const PNGChunkType pngchunkType)
{
    return 0;
}

PNGColorType ConvertToPNGColorType(const unsigned int colorType)
{
    switch(colorType)
    {
        case 0u:
            return PNGColorGrayscale;

        case 2u:
            return PNGColorTruecolor;

        case 3u:
            return PNGColorIndexedColor;

        case 4u:
            return PNGColorGrayscaleWithAlphaChannel;

        case 6u:
            return PNGColorTruecolorWithAlphaChannel;

        default:
            return PNGColorInvalid;
    }
}

unsigned int ConvertFromPNGColorType(const PNGColorType colorType)
{
    switch(colorType)
    {
        default:
        case PNGColorInvalid:
            return -1;

        case PNGColorGrayscale:
            return 0u;

        case PNGColorTruecolor:
            return 2u;

        case PNGColorIndexedColor:
            return 3u;

        case PNGColorGrayscaleWithAlphaChannel:
            return 4u;

        case PNGColorTruecolorWithAlphaChannel:
            return 6u;
    }
}

PNGInterlaceMethod ConvertToPNGInterlaceMethod(const unsigned char interlaceMethod)
{
    switch(interlaceMethod)
    {
        case 0u:
            return PNGInterlaceNone;

        case 1u:
            return PNGInterlaceADAM7;

        default:
            return PNGInterlaceInvalid;
    }
}

unsigned char ConvertFromPNGInterlaceMethod(const PNGInterlaceMethod interlaceMethod)
{
    switch(interlaceMethod)
    {
        default:
        case PNGInterlaceInvalid:
            return (unsigned char)-1;

        case PNGInterlaceNone:
            return 0u;

        case PNGInterlaceADAM7:
            return 1u;
    }
}

void PNGConstruct(PNG* png)
{
    MemorySet(png, sizeof(PNG), 0);
}

void PNGDestruct(PNG* png)
{
    MemoryRelease(png->PixelData, png->PixelDataSize);

    png->PixelDataSize = 0;
    png->PixelData = 0;
}

size_t NumberOfColorChannels(const PNGColorType pngColorType)
{
    switch(pngColorType)
    {
        default:
        case PNGColorInvalid:
            return -1;

        case PNGColorGrayscale:
            return 1;

        case PNGColorTruecolor:
            return 3;

        case PNGColorIndexedColor:
            return 1;

        case PNGColorGrayscaleWithAlphaChannel:
            return 2;

        case PNGColorTruecolorWithAlphaChannel:
            return 4;
    }
}

size_t BitsPerPixel(PNG* png)
{
    size_t numberOfColorChannels = NumberOfColorChannels(png->ImageHeader.ColorType);

    return png->ImageHeader.BitDepth * numberOfColorChannels;
}

size_t PNGFilePredictSize(const size_t width, const size_t height, const size_t bbp)
{
    const size_t signature = 8;
    const size_t header = 25;
    const size_t time = 19;
    const size_t end = 12;

    const size_t sum = signature + header + time + end;

    return sum;
}

ActionResult PNGParse(PNG* png, const void* data, const size_t dataSize, size_t* dataRead)
{
    ParsingStream parsingStream;

    ParsingStreamConstruct(&parsingStream, data, dataSize);
    PNGConstruct(png);
    *dataRead = 0;

    size_t imageDataCounter = 0;
    size_t imageDataChunkCacheSizeUSED = 0;
    size_t imageDataChunkCacheSizeMAX = 0u;
    unsigned char* imageDataChunkCache = 0; 

    //---<Parse PNG File>------------------------------------------------------
    {
        unsigned char parseFinished = 0;

        //---<Check PNG Header>------------------------------------------------
        {
            const unsigned char pngFileHeader[8] = PNGHeaderSequenz;
            const size_t pngFileHeaderSize = sizeof(pngFileHeader);
            const unsigned char isValidHeader = ParsingStreamReadAndCompare(&parsingStream, pngFileHeader, pngFileHeaderSize);

            if(!isValidHeader)
            {
                return ResultInvalidHeaderSignature;
            }
        }

        // Allocate Memory for later ImageData Chunks
        imageDataChunkCacheSizeMAX = parsingStream.DataSize - 0u;
        imageDataChunkCache = MemoryAllocate(sizeof(unsigned char) * imageDataChunkCacheSizeMAX);

        //---------------------------------------------------------------------

#if PNGDebugInfo
        printf
        (
            "+------+--------------------------------------------+---+---+---+-------+-----+\n"
            "| ID   | Name                                       | E | R | S | Bytes | CRC |\n"
            "+------+--------------------------------------------+---+---+---+-------+-----+\n"
        );
#endif

        // Parse every chunk until finished.
        while(!parseFinished)
        {
            PNGChunk chunk;
            size_t predictedOffset = 0;

            MemorySet(&chunk, sizeof(PNGChunk), 0);

            //chunk.ChunkData = dataStream.Data + dataStream.DataCursor;

            ParsingStreamReadIU(&parsingStream, &chunk.Lengh, EndianBig);
            ParsingStreamReadD(&parsingStream, chunk.ChunkTypeRaw, 4u);

            // Check
            {
                // Ancillary bit : bit 5 of first byte
                 // 0 (uppercase) = critical, 1 (lowercase) = ancillary.
                chunk.IsEssential = !((chunk.ChunkTypeRaw[0] & 0b00100000) >> 5);

                // Private bit: bit 5 of second byte
                // Must be 0 (uppercase)in files conforming to this version of PNG.
                chunk.IsRegisteredStandard = !((chunk.ChunkTypeRaw[1] & 0b00100000) >> 5);

                // Safe-to-copy bit: bit 5 of fourth byte
                // 0 (uppercase) = unsafe to copy, 1 (lowercase) = safe to copy.
                chunk.IsSafeToCopy = !((chunk.ChunkTypeRaw[3] & 0b00100000) >> 5);

                const unsigned int ChunkTypeID = MakeInt(chunk.ChunkTypeRaw[0], chunk.ChunkTypeRaw[1], chunk.ChunkTypeRaw[2], chunk.ChunkTypeRaw[3]);

                chunk.ChunkType = ConvertToChunkType(ChunkTypeID);

                predictedOffset = parsingStream.DataCursor + chunk.Lengh;
            }

#if PNGDebugInfo
            printf
            (
                "| %c%c%c%c | %-42s | %c | %c | %c | %5i | Yes |\n",
                chunk.ChunkTypeRaw[0],
                chunk.ChunkTypeRaw[1],
                chunk.ChunkTypeRaw[2],
                chunk.ChunkTypeRaw[3],
                ChunkTypeToString(chunk.ChunkType),
                chunk.IsEssential ? 'x' : '-',
                chunk.IsRegisteredStandard ? 'x' : '-',
                chunk.IsSafeToCopy ? 'x' : '-',
                chunk.Lengh
            );
#endif

            //---Get Chunk Data------------------------------------------
            switch(chunk.ChunkType)
            {
                case PNGChunkImageHeader:
                {
                    unsigned char colorTypeRaw = 0;
                    unsigned char interlaceMethodRaw = 0;

                    ParsingStreamReadIU(&parsingStream, &png->ImageHeader.Width, EndianBig); // 4 Bytes
                    ParsingStreamReadIU(&parsingStream, &png->ImageHeader.Height, EndianBig); // 4 Bytes

                    ParsingStreamReadCU(&parsingStream, &png->ImageHeader.BitDepth); // 1 Byte__
                    ParsingStreamReadCU(&parsingStream, &colorTypeRaw); // 1 Byte__
                    ParsingStreamReadCU(&parsingStream, &png->ImageHeader.CompressionMethod); // 1 Byte__
                    ParsingStreamReadCU(&parsingStream, &png->ImageHeader.FilterMethod); // 1 Byte__
                    ParsingStreamReadCU(&parsingStream, &interlaceMethodRaw); // 1 Byte__

                    png->ImageHeader.ColorType = ConvertToPNGColorType(colorTypeRaw);
                    png->ImageHeader.InterlaceMethod = ConvertToPNGInterlaceMethod(interlaceMethodRaw);

                    break;
                }
                case PNGChunkPalette:
                {
                    // Red 	1 byte
                    // Green 1 byte
                    // Blue 	1 byte

                    //dataStream.Read(&Palette, 3u);

                    break;
                }
                case PNGChunkImageData:
                {
                    /*
                    ZLIB zlib(dataStream.Data + dataStream.DataCursor, chunk.Lengh);

                    // Dump content into buffer
                    // There may be multiple IDAT chunks; if so, they shall appear consecutively with no other intervening chunks.
                    // the compressed datastream is then the concatenation of the contents of the data fields of all the IDAT chunks.

                    printf
                    (
                        "| [ZLIB Header]          |\n"
                        "| CompressionMethod : %7s |\n"
                        "| CompressionInfo   : %7i |\n"
                        "| WindowSize        : %7i |\n"
                        "| CheckFlag         : %7i |\n"
                        "| DictionaryPresent : %7i |\n"
                        "| CompressionLevel  : %7s |\n",
                        CompressionMethodToString(zlib.Header.CompressionMethod),
                        zlib.Header.CompressionInfo,
                        zlib.Header.WindowSize,
                        zlib.Header.CheckFlag,
                        zlib.Header.DictionaryPresent,
                        CompressionLevelToString(zlib.Header.CompressionLevel)
                    );

                    printf
                    (
                        "| [DEFLATE]                 |\n"
                        "| IsLastBlock          : %15i |\n"
                        "| EncodingMethod       : %15s |\n"
                        "| BitStreamDataRawSize : %15i |\n",
                        zlib.DeflateData.IsLastBlock,
                        DeflateEncodingMethodToString(zlib.DeflateData.EncodingMethod),
                        zlib.DeflateData.BitStreamDataRawSize
                    );*/


                    //zlib.Unpack(imageDataChunkCache, imageDataChunkCacheSizeUSED);


                    ParsingStreamReadD(&parsingStream, imageDataChunkCache + imageDataChunkCacheSizeUSED, chunk.Lengh);
                    
                    imageDataChunkCacheSizeUSED += chunk.Lengh;

                    ++imageDataCounter;

                    break;
                }
                case PNGChunkImageEnd:
                {
                    parseFinished = 1;
                    break;
                }
                case PNGChunkTransparency:
                {
                    ParsingStreamCursorAdvance(&parsingStream, chunk.Lengh); // not handled

                    break;
                }
                case PNGChunkImageGamma:
                {
                    ParsingStreamReadIU(&parsingStream, &png->Gamma, EndianBig);

                    break;
                }
                case PNGChunkPrimaryChromaticities:
                {
                    ParsingStreamReadIU(&parsingStream, &png->PrimaryChromatics.WhiteX, EndianBig);
                    ParsingStreamReadIU(&parsingStream, &png->PrimaryChromatics.WhiteY, EndianBig);
                    ParsingStreamReadIU(&parsingStream, &png->PrimaryChromatics.RedX, EndianBig);
                    ParsingStreamReadIU(&parsingStream, &png->PrimaryChromatics.RedY, EndianBig);
                    ParsingStreamReadIU(&parsingStream, &png->PrimaryChromatics.GreenX, EndianBig);
                    ParsingStreamReadIU(&parsingStream, &png->PrimaryChromatics.GreenY, EndianBig);
                    ParsingStreamReadIU(&parsingStream, &png->PrimaryChromatics.BlueX, EndianBig);
                    ParsingStreamReadIU(&parsingStream, &png->PrimaryChromatics.BlueY, EndianBig);

                    break;
                }
                case PNGChunkStandardRGBColorSpace:
                {
                   // dataStream.Read(RenderingIntent);

                    break;
                }
                case PNGChunkEmbeddedICCProfile:
                {
                  //  dataStream.DataCursor += chunk.Lengh;

                    break;
                }
                case PNGChunkTextualData:
                {
                  //  dataStream.DataCursor += chunk.Lengh;

           
                    break;
                }
                case PNGChunkCompressedTextualData:
                {
                    // Keyword 	                    1 - 79 bytes(character string)
                    // Null separator 	            1 byte(null character)
                    // Compression method 	        1 byte
                    // Compressed text datastream 	n bytes

                  //  dataStream.DataCursor += chunk.Lengh;

                    break;
                }
                case PNGChunkInternationalTextualData:
                {
                  //  dataStream.DataCursor += chunk.Lengh;

                    break;
                }
                case PNGChunkBackgroundColor:
                {
                    switch(png->ImageHeader.ColorType)
                    {
                        default:
                        case PNGColorInvalid:
                            break; // ERROR

                        case PNGColorGrayscale:
                        case PNGColorGrayscaleWithAlphaChannel:
                        {
                          //  dataStream.Read(png->BackgroundColor.GreyScale, EndianBig);
                            break;
                        }
                        case PNGColorTruecolor:
                        case PNGColorTruecolorWithAlphaChannel:
                        {
                           // dataStream.Read(png->BackgroundColor.Red, EndianBig);
                           // dataStream.Read(png->BackgroundColor.Green, EndianBig);
                           // dataStream.Read(png->BackgroundColor.Blue, EndianBig);
                            break;
                        }
                        case PNGColorIndexedColor:
                        {
                            //dataStream.Read(png->BackgroundColor.PaletteIndex);
                            break;
                        }
                    }

                    break;
                }
                case PNGChunkPhysicalPixelDimensions:
                {
                    //dataStream.Read(PhysicalPixelDimension.PixelsPerUnit[0], EndianBig);
                   // dataStream.Read(PhysicalPixelDimension.PixelsPerUnit[1], EndianBig);
                   // dataStream.Read(PhysicalPixelDimension.UnitSpecifier);

                    break;
                }
                case PNGChunkSignificantBits:
                {
                    /*
                    unsigned int byteLength = 0;
                    unsigned int result = 0;

                    switch (ColorType)
                    {
                        case PNGColorGrayscale: // single byte,
                            byteLength = 1;
                            break;

                        case PNGColorTruecolor: // three bytes,
                        case PNGColorIndexedColor:
                            byteLength = 3;
                            break;

                        case PNGColorGrayscaleWithAlphaChannel: // two bytes
                            byteLength = 2;
                            break;

                        case PNGColorTruecolorWithAlphaChannel: //  four bytes,
                            byteLength = 4;
                            break;
                    }

                    for (unsigned int i = 0; i < byteLength; i++)
                    {
                        char calcbyte;

                        dataStream.Read(calcbyte);

                        result = (result << (i * 8)) | calcbyte;
                    }

                    SignificantBits = result;*/          

                    break;
                }
                case PNGChunkSuggestedPalette:
                {
                    break;
                }
                case PNGChunkPaletteHistogram:
                {
                    const size_t listSize = chunk.Lengh / 2;

                    unsigned short* list = MemoryAllocate(sizeof(unsigned short) * listSize);

                    png->PaletteHistogram.ColorFrequencyListSize = listSize;
                    png->PaletteHistogram.ColorFrequencyList = list;

                    for(size_t i = 0; i < listSize; i++)
                    {
                        ParsingStreamReadSU(&parsingStream, &list[i], EndianBig);
                    }

                    break;
                }
                case PNGChunkLastModificationTime:
                {
                    ParsingStreamReadSU(&parsingStream, &png->LastModificationTime.Year, EndianBig);
                    ParsingStreamReadCU(&parsingStream, &png->LastModificationTime.Month);
                    ParsingStreamReadCU(&parsingStream, &png->LastModificationTime.Day);
                    ParsingStreamReadCU(&parsingStream, &png->LastModificationTime.Hour);
                    ParsingStreamReadCU(&parsingStream, &png->LastModificationTime.Minute);
                    ParsingStreamReadCU(&parsingStream, &png->LastModificationTime.Second);

                    break;
                }
                case PNGChunkCustom:
                default:
                {
                    ParsingStreamCursorAdvance(&parsingStream, chunk.Lengh);
                    break;
                }
            }
            //---------------------------------------------------------------

#if PNGDebugInfo
            if(parsingStream.DataCursor != predictedOffset)
            {
                printf("[i][PNG] Chunk did not handle all Bytes\n");
            }
#endif
            parsingStream.DataCursor = predictedOffset;

            ParsingStreamReadIU(&parsingStream, &chunk.CRC, EndianBig); // 4 Bytes

            //---<Check CRC>---
            // TODO: Yes
            //-----------------
        }
    }

    //---<Allocate>------------------------------------------------------------
    png->PixelDataSize = png->ImageHeader.Width * png->ImageHeader.Height * NumberOfColorChannels(png->ImageHeader.ColorType);
    png->PixelData = MemoryAllocate(sizeof(unsigned char) * png->PixelDataSize);
    //-------------------------------------------------------------------------    


    //---<Unpack compressed data>----------------------------------------------
    
    unsigned char* workingMemory = 0;
    size_t workingMemorySize = 0;
    const size_t bitsPerPixel = BitsPerPixel(png);

    // ZLIB
    {
        size_t writtenBytes = 0;

        const size_t expectedzlibCacheSize = ZLIBCalculateExpectedSize(png->ImageHeader.Width, png->ImageHeader.Height, bitsPerPixel, png->ImageHeader.InterlaceMethod);

        workingMemorySize = expectedzlibCacheSize;
        workingMemory = MemoryReallocate(workingMemory, sizeof(unsigned char) * expectedzlibCacheSize);
              
        const ActionResult actionResult = ZLIBDecompress(imageDataChunkCache, imageDataChunkCacheSizeUSED, workingMemory, &writtenBytes);
        const unsigned char sucess = actionResult == ResultSuccessful;

        if(!sucess)
        {
            return actionResult;
        }
    }  

    // ADAM
    const size_t expectedadam7CacheSize = ADAM7CaluclateExpectedSize(png->ImageHeader.Width, png->ImageHeader.Height, bitsPerPixel);

    unsigned char* adam7Cache = MemoryAllocate(sizeof(unsigned char) * expectedadam7CacheSize);

    const unsigned int scanDecodeResult = ADAM7ScanlinesDecode(adam7Cache, workingMemory, png->ImageHeader.Width, png->ImageHeader.Height, bitsPerPixel, png->ImageHeader.InterlaceMethod);


    // Color COmprerss
    const unsigned int decompress = Decompress(adam7Cache, png->PixelData, png->ImageHeader.Width, png->ImageHeader.Height, png->ImageHeader.BitDepth, png->ImageHeader.ColorType);


    MemoryRelease(workingMemory, workingMemorySize);
    MemoryRelease(adam7Cache, expectedadam7CacheSize);
    //-------------------------------------------------------------------------


    return ResultSuccessful;
}

ActionResult PNGSerialize(PNG* png, void* data, const size_t dataSize, size_t* dataWritten)
{
    ParsingStream parsingStream;

    ParsingStreamConstruct(&parsingStream, data, dataSize);

    *dataWritten = 0;

    //---<Signature>---
    {
        const unsigned char pngFileHeader[8] = PNGHeaderSequenz;
        const size_t pngFileHeaderSize = sizeof(pngFileHeader);

        ParsingStreamWriteD(&parsingStream, pngFileHeader, pngFileHeaderSize);
    }

    //---<IHDR> (Image Header)---
    {
        const unsigned char colorType = ConvertFromPNGColorType(png->ImageHeader.ColorType);
        const unsigned char interlaceMethod = ConvertFromPNGInterlaceMethod(png->ImageHeader.InterlaceMethod);
        const unsigned char* chunkStart = ParsingStreamCursorPosition(&parsingStream);

        ParsingStreamWriteIU(&parsingStream, 13u, EndianBig);
        ParsingStreamWriteD(&parsingStream, "IHDR", 4u);

        ParsingStreamWriteIU(&parsingStream, png->ImageHeader.Width, EndianBig);
        ParsingStreamWriteIU(&parsingStream, png->ImageHeader.Height, EndianBig);

        ParsingStreamWriteCU(&parsingStream, png->ImageHeader.BitDepth);
        ParsingStreamWriteCU(&parsingStream, colorType);
        ParsingStreamWriteCU(&parsingStream, png->ImageHeader.CompressionMethod);
        ParsingStreamWriteCU(&parsingStream, png->ImageHeader.FilterMethod);
        ParsingStreamWriteCU(&parsingStream, interlaceMethod);

        const unsigned int crc = CRC32Generate(chunkStart, 13 + 4);

        ParsingStreamWriteIU(&parsingStream, crc, EndianBig);
    }

    // iCCP
    // sRGB
    // gAMA
    // cHRM
    // PLTE
    // tRNS
    // bKGD
    // pHYs
    // IDAT
    {
   

        // ZLIB comprssion
    }   
     
    // tIME
    // zTXt
    // tEXt

    //---<>---
    {   
        ParsingStreamWriteIU(&parsingStream, 0u, EndianBig);
        ParsingStreamWriteD(&parsingStream, "IEND", 4u);
        ParsingStreamWriteIU(&parsingStream, 2923585666u, EndianBig);
    }

    *dataWritten = parsingStream.DataCursor;

    return ResultSuccessful;
}

ActionResult PNGSerializeFromImage(const Image* const image, void* data, const size_t dataSize, size_t* dataWritten)
{
    ParsingStream parsingStream;

    ParsingStreamConstruct(&parsingStream, data, dataSize);

    *dataWritten = 0;

    //---<Signature>--- 8 Bytes
    {
        const unsigned char pngFileHeader[8] = PNGHeaderSequenz;
        const size_t pngFileHeaderSize = sizeof(pngFileHeader);

        ParsingStreamWriteD(&parsingStream, pngFileHeader, pngFileHeaderSize);
    }

    //---<IHDR> (Image Header)--- 21 Bytes
        {
        unsigned char colorType = 0;
        const unsigned char interlaceMethod = ConvertFromPNGInterlaceMethod(PNGInterlaceADAM7);
        const unsigned char* chunkStart = ParsingStreamCursorPosition(&parsingStream);
        const unsigned char bbp = ImageBytePerPixel(image->Format);
        const unsigned char compressionMethod = 0;
        const unsigned char filterMethod = 0;

        switch(image->Format)
        {
            case ImageDataFormatInvalid:
                return ResultFormatInvalid;

            case ImageDataFormatAlphaMask:
                colorType = PNGColorGrayscaleWithAlphaChannel;
                break;

            case ImageDataFormatBGR:
            case ImageDataFormatRGB:
                colorType = PNGColorTruecolor;
                break;

            case ImageDataFormatRGBA:
            case ImageDataFormatBGRA:
                colorType = PNGColorTruecolorWithAlphaChannel;
                break;
        }

        ParsingStreamWriteIU(&parsingStream, 13u, EndianBig);
        ParsingStreamWriteD(&parsingStream, "IHDR", 4u);

        ParsingStreamWriteIU(&parsingStream, image->Width, EndianBig);
        ParsingStreamWriteIU(&parsingStream, image->Height, EndianBig);

        ParsingStreamWriteCU(&parsingStream, bbp);
        ParsingStreamWriteCU(&parsingStream, colorType);
        ParsingStreamWriteCU(&parsingStream, compressionMethod);
        ParsingStreamWriteCU(&parsingStream, filterMethod);
        ParsingStreamWriteCU(&parsingStream, interlaceMethod);

        const unsigned int crc = CRC32Generate(chunkStart, 13 + 4);

        ParsingStreamWriteIU(&parsingStream, crc, EndianBig);
    
        // Header End

        // [PLTE] Palette	
    
        // 0 = NoShow
        // 1 = Maybe
        // 2 = definitly
        unsigned char shouldPrint = 0;

        switch(colorType)
        {
            default:
            case PNGColorInvalid:
                return ResultInvalid;

            case PNGColorGrayscale: // ColorType = 0
            case PNGColorGrayscaleWithAlphaChannel:  // ColorType = 4
                shouldPrint = 0;
                break;

            case PNGColorTruecolor:  // ColorType = 2
            case PNGColorTruecolorWithAlphaChannel:  // ColorType = 6
                shouldPrint = 1;
                break;

            case PNGColorIndexedColor:  // ColorType = 3;
                shouldPrint = 2;
                break;
        }
    }

    // [tRNS] Transparency
    {

    }

    // [gAMA] Image gamma
    {

    }
    
    // [cHRM] -  
    {

    }
    // [sRGB] -
    {

    }
    // [iCCP] - 
    {

    }

    // [tEXt] - 		
    {

    }

    // [zTXt] - 	
    {

    }

    // [iTXt] - 
    {

    }

    // [bKGD] - 	
    {

    }

    // [pHYs] - 
    {

    }

    // [sBIT] - 
    {

    }

    // [sPLT] - 	
    {

    }

    // [hIST] -
    {

    }

    // [tIME] - 19 Bytes
    {
        Time time;
        PNGLastModificationTime pngLastModificationTime;

        TimeNow(&time);

        pngLastModificationTime.Year = time.Year;
        pngLastModificationTime.Month = time.Month;
        pngLastModificationTime.Day = time.Day;
        pngLastModificationTime.Hour = time.Hour;
        pngLastModificationTime.Minute = time.Minute;
        pngLastModificationTime.Second = time.Second;

        ParsingStreamWriteIU(&parsingStream, 7u, EndianBig);
        ParsingStreamWriteD(&parsingStream, "tIME", 4u);
        ParsingStreamWriteSU(&parsingStream, pngLastModificationTime.Year, EndianBig);
        ParsingStreamWriteCU(&parsingStream, pngLastModificationTime.Month);
        ParsingStreamWriteCU(&parsingStream, pngLastModificationTime.Day);
        ParsingStreamWriteCU(&parsingStream, pngLastModificationTime.Hour);
        ParsingStreamWriteCU(&parsingStream, pngLastModificationTime.Minute);
        ParsingStreamWriteCU(&parsingStream, pngLastModificationTime.Second);

        ParsingStreamWriteIU(&parsingStream, 0, EndianBig); // CRC
    }

    // [IDAT] Image data	
    {

    }

    //---<IEND>---------------------------------------------------------------- 12 Bytes
    {
        ParsingStreamWriteIU(&parsingStream, 0u, EndianBig); // Length
        ParsingStreamWriteD(&parsingStream, "IEND", 4u);
        ParsingStreamWriteIU(&parsingStream, 0u, EndianBig); // CRC
    }

    *dataWritten = parsingStream.DataCursor;

    return ResultSuccessful;
}