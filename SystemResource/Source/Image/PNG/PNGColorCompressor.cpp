#include "PNGColorCompressor.h"

#include <string.h>

unsigned int BF::PNGColorCompressor::Decompress(unsigned char* out, const unsigned char* in,
    const LodePNGColorMode* mode_out, const LodePNGColorMode* mode_in, size_t width, size_t height)
{
    size_t i;
    PNGColorTree tree;
    size_t numpixels = width * height;
    unsigned error = 0;

    if (mode_in->colortype == LCT_PALETTE && !mode_in->palette)
    {
        return 107; /* error: must provide palette if input mode is palette */
    }

    if (lodepng_color_mode_equal(mode_out, mode_in))
    {
        size_t numbytes = lodepng_get_raw_size(width, height, mode_in);
        memcpy(out, in, numbytes);
        return 0;
    }

    if (mode_out->colortype == LCT_PALETTE)
    {
        size_t palettesize = mode_out->palettesize;
        const unsigned char* palette = mode_out->palette;
        size_t palsize = (size_t)1u << mode_out->bitdepth;
        /*if the user specified output palette but did not give the values, assume
        they want the values of the input color type (assuming that one is palette).
        Note that we never create a new palette ourselves.*/
        if (palettesize == 0)
        {
            palettesize = mode_in->palettesize;
            palette = mode_in->palette;
            /*if the input was also palette with same bitdepth, then the color types are also
            equal, so copy literally. This to preserve the exact indices that were in the PNG
            even in case there are duplicate colors in the palette.*/
            if (mode_in->colortype == LCT_PALETTE && mode_in->bitdepth == mode_out->bitdepth)
            {
                size_t numbytes = lodepng_get_raw_size(width, height, mode_in);
                memcpy(out, in, numbytes);
                return 0;
            }
        }
        if (palettesize < palsize) palsize = palettesize;

       // color_tree_init(&tree);
      
        for (i = 0; i != palsize; ++i)
        {
            const unsigned char* p = &palette[i * 4];
            error = PNGColorTree::color_tree_add(&tree, p[0], p[1], p[2], p[3], (unsigned)i);
            if (error) break;
        }
    }

    if (!error)
    {
        if (mode_in->bitdepth == 16 && mode_out->bitdepth == 16)
        {
            for (i = 0; i != numpixels; ++i)
            {
                unsigned short r = 0, g = 0, b = 0, a = 0;
                getPixelColorRGBA16(&r, &g, &b, &a, in, i, mode_in);
                rgba16ToPixel(out, i, mode_out, r, g, b, a);
            }
        }
        else if (mode_out->bitdepth == 8 && mode_out->colortype == LCT_RGBA)
        {
            getPixelColorsRGBA8(out, numpixels, in, mode_in);
        }
        else if (mode_out->bitdepth == 8 && mode_out->colortype == LCT_RGB)
        {
            getPixelColorsRGB8(out, numpixels, in, mode_in);
        }
        else
        {
            unsigned char r = 0, g = 0, b = 0, a = 0;
            for (i = 0; i != numpixels; ++i)
            {
                getPixelColorRGBA8(&r, &g, &b, &a, in, i, mode_in);
                error = rgba8ToPixel(out, i, mode_out, &tree, r, g, b, a);
                if (error) break;
            }
        }
    }

    if (mode_out->colortype == LCT_PALETTE)
    {
       // color_tree_cleanup(&tree);
    }

    return error;
}

unsigned BF::PNGColorCompressor::getNumColorChannels(LodePNGColorType colortype)
{
    switch (colortype)
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

unsigned BF::PNGColorCompressor::lodepng_get_bpp_lct(LodePNGColorType colortype, unsigned bitdepth)
{
    /*bits per pixel is amount of channels * bits per channel*/
    return getNumColorChannels(colortype) * bitdepth;
}

int BF::PNGColorCompressor::lodepng_color_mode_equal(const LodePNGColorMode* a, const LodePNGColorMode* b)
{
    size_t i;
    if (a->colortype != b->colortype) return 0;
    if (a->bitdepth != b->bitdepth) return 0;
    if (a->key_defined != b->key_defined) return 0;
    if (a->key_defined)
    {
        if (a->key_r != b->key_r) return 0;
        if (a->key_g != b->key_g) return 0;
        if (a->key_b != b->key_b) return 0;
    }
    if (a->palettesize != b->palettesize) return 0;
    for (i = 0; i != a->palettesize * 4; ++i)
    {
        if (a->palette[i] != b->palette[i]) return 0;
    }
    return 1;
}

void BF::PNGColorCompressor::getPixelColorRGBA16(unsigned short* r, unsigned short* g, unsigned short* b, unsigned short* a, const unsigned char* in, size_t i, const LodePNGColorMode* mode)
{
    if (mode->colortype == LCT_GREY)
    {
        *r = *g = *b = 256 * in[i * 2 + 0] + in[i * 2 + 1];
        if (mode->key_defined && 256U * in[i * 2 + 0] + in[i * 2 + 1] == mode->key_r) *a = 0;
        else *a = 65535;
    }
    else if (mode->colortype == LCT_RGB)
    {
        *r = 256u * in[i * 6 + 0] + in[i * 6 + 1];
        *g = 256u * in[i * 6 + 2] + in[i * 6 + 3];
        *b = 256u * in[i * 6 + 4] + in[i * 6 + 5];
        if (mode->key_defined
            && 256u * in[i * 6 + 0] + in[i * 6 + 1] == mode->key_r
            && 256u * in[i * 6 + 2] + in[i * 6 + 3] == mode->key_g
            && 256u * in[i * 6 + 4] + in[i * 6 + 5] == mode->key_b) *a = 0;
        else *a = 65535;
    }
    else if (mode->colortype == LCT_GREY_ALPHA)
    {
        *r = *g = *b = 256u * in[i * 4 + 0] + in[i * 4 + 1];
        *a = 256u * in[i * 4 + 2] + in[i * 4 + 3];
    }
    else if (mode->colortype == LCT_RGBA)
    {
        *r = 256u * in[i * 8 + 0] + in[i * 8 + 1];
        *g = 256u * in[i * 8 + 2] + in[i * 8 + 3];
        *b = 256u * in[i * 8 + 4] + in[i * 8 + 5];
        *a = 256u * in[i * 8 + 6] + in[i * 8 + 7];
    }
}

void BF::PNGColorCompressor::rgba16ToPixel(unsigned char* out, size_t i, const LodePNGColorMode* mode, unsigned short r, unsigned short g, unsigned short b, unsigned short a)
{
    if (mode->colortype == LCT_GREY)
    {
        unsigned short gray = r; /*((unsigned)r + g + b) / 3u;*/
        out[i * 2 + 0] = (gray >> 8) & 255;
        out[i * 2 + 1] = gray & 255;
    }
    else if (mode->colortype == LCT_RGB)
    {
        out[i * 6 + 0] = (r >> 8) & 255;
        out[i * 6 + 1] = r & 255;
        out[i * 6 + 2] = (g >> 8) & 255;
        out[i * 6 + 3] = g & 255;
        out[i * 6 + 4] = (b >> 8) & 255;
        out[i * 6 + 5] = b & 255;
    }
    else if (mode->colortype == LCT_GREY_ALPHA)
    {
        unsigned short gray = r; /*((unsigned)r + g + b) / 3u;*/
        out[i * 4 + 0] = (gray >> 8) & 255;
        out[i * 4 + 1] = gray & 255;
        out[i * 4 + 2] = (a >> 8) & 255;
        out[i * 4 + 3] = a & 255;
    }
    else if (mode->colortype == LCT_RGBA)
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

void BF::PNGColorCompressor::getPixelColorsRGBA8(unsigned char* buffer, size_t numpixels, const unsigned char* in, const LodePNGColorMode* mode)
{
    unsigned num_channels = 4;
    size_t i;
    if (mode->colortype == LCT_GREY)
    {
        if (mode->bitdepth == 8)
        {
            for (i = 0; i != numpixels; ++i, buffer += num_channels)
            {
                buffer[0] = buffer[1] = buffer[2] = in[i];
                buffer[3] = 255;
            }
            if (mode->key_defined)
            {
                buffer -= numpixels * num_channels;
                for (i = 0; i != numpixels; ++i, buffer += num_channels)
                {
                    if (buffer[0] == mode->key_r) buffer[3] = 0;
                }
            }
        }
        else if (mode->bitdepth == 16)
        {
            for (i = 0; i != numpixels; ++i, buffer += num_channels)
            {
                buffer[0] = buffer[1] = buffer[2] = in[i * 2];
                buffer[3] = mode->key_defined && 256U * in[i * 2 + 0] + in[i * 2 + 1] == mode->key_r ? 0 : 255;
            }
        }
        else
        {
            unsigned highest = ((1U << mode->bitdepth) - 1U); /*highest possible value for this bit depth*/
            size_t j = 0;
            for (i = 0; i != numpixels; ++i, buffer += num_channels)
            {
                unsigned value = readBitsFromReversedStream(&j, in, mode->bitdepth);
                buffer[0] = buffer[1] = buffer[2] = (value * 255) / highest;
                buffer[3] = mode->key_defined && value == mode->key_r ? 0 : 255;
            }
        }
    }
    else if (mode->colortype == LCT_RGB)
    {
        if (mode->bitdepth == 8)
        {
            for (i = 0; i != numpixels; ++i, buffer += num_channels)
            {
                memcpy(buffer, &in[i * 3], 3);
                buffer[3] = 255;
            }
            if (mode->key_defined)
            {
                buffer -= numpixels * num_channels;
                for (i = 0; i != numpixels; ++i, buffer += num_channels)
                {
                    if (buffer[0] == mode->key_r && buffer[1] == mode->key_g && buffer[2] == mode->key_b) buffer[3] = 0;
                }
            }
        }
        else
        {
            for (i = 0; i != numpixels; ++i, buffer += num_channels)
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
    else if (mode->colortype == LCT_PALETTE)
    {
        if (mode->bitdepth == 8)
        {
            for (i = 0; i != numpixels; ++i, buffer += num_channels)
            {
                unsigned index = in[i];
                /*out of bounds of palette not checked: see lodepng_color_mode_alloc_palette.*/
                memcpy(buffer, &mode->palette[index * 4], 4);
            }
        }
        else
        {
            size_t j = 0;
            for (i = 0; i != numpixels; ++i, buffer += num_channels)
            {
                unsigned index = readBitsFromReversedStream(&j, in, mode->bitdepth);
                /*out of bounds of palette not checked: see lodepng_color_mode_alloc_palette.*/
                memcpy(buffer, &mode->palette[index * 4], 4);
            }
        }
    }
    else if (mode->colortype == LCT_GREY_ALPHA)
    {
        if (mode->bitdepth == 8)
        {
            for (i = 0; i != numpixels; ++i, buffer += num_channels)
            {
                buffer[0] = buffer[1] = buffer[2] = in[i * 2 + 0];
                buffer[3] = in[i * 2 + 1];
            }
        }
        else
        {
            for (i = 0; i != numpixels; ++i, buffer += num_channels)
            {
                buffer[0] = buffer[1] = buffer[2] = in[i * 4 + 0];
                buffer[3] = in[i * 4 + 2];
            }
        }
    }
    else if (mode->colortype == LCT_RGBA)
    {
        if (mode->bitdepth == 8)
        {
            memcpy(buffer, in, numpixels * 4);
        }
        else
        {
            for (i = 0; i != numpixels; ++i, buffer += num_channels)
            {
                buffer[0] = in[i * 8 + 0];
                buffer[1] = in[i * 8 + 2];
                buffer[2] = in[i * 8 + 4];
                buffer[3] = in[i * 8 + 6];
            }
        }
    }
}

void BF::PNGColorCompressor::getPixelColorsRGB8(unsigned char* buffer, size_t numpixels, const unsigned char* in, const LodePNGColorMode* mode)
{
    const unsigned num_channels = 3;
    size_t i;
    if (mode->colortype == LCT_GREY)
    {
        if (mode->bitdepth == 8)
        {
            for (i = 0; i != numpixels; ++i, buffer += num_channels)
            {
                buffer[0] = buffer[1] = buffer[2] = in[i];
            }
        }
        else if (mode->bitdepth == 16)
        {
            for (i = 0; i != numpixels; ++i, buffer += num_channels)
            {
                buffer[0] = buffer[1] = buffer[2] = in[i * 2];
            }
        }
        else
        {
            unsigned highest = ((1U << mode->bitdepth) - 1U); /*highest possible value for this bit depth*/
            size_t j = 0;
            for (i = 0; i != numpixels; ++i, buffer += num_channels)
            {
                unsigned value = readBitsFromReversedStream(&j, in, mode->bitdepth);
                buffer[0] = buffer[1] = buffer[2] = (value * 255) / highest;
            }
        }
    }
    else if (mode->colortype == LCT_RGB)
    {
        if (mode->bitdepth == 8)
        {
            memcpy(buffer, in, numpixels * 3);
        }
        else
        {
            for (i = 0; i != numpixels; ++i, buffer += num_channels)
            {
                buffer[0] = in[i * 6 + 0];
                buffer[1] = in[i * 6 + 2];
                buffer[2] = in[i * 6 + 4];
            }
        }
    }
    else if (mode->colortype == LCT_PALETTE)
    {
        if (mode->bitdepth == 8)
        {
            for (i = 0; i != numpixels; ++i, buffer += num_channels)
            {
                unsigned index = in[i];
                /*out of bounds of palette not checked: see lodepng_color_mode_alloc_palette.*/
                memcpy(buffer, &mode->palette[index * 4], 3);
            }
        }
        else
        {
            size_t j = 0;
            for (i = 0; i != numpixels; ++i, buffer += num_channels)
            {
                unsigned index = readBitsFromReversedStream(&j, in, mode->bitdepth);
                /*out of bounds of palette not checked: see lodepng_color_mode_alloc_palette.*/
                memcpy(buffer, &mode->palette[index * 4], 3);
            }
        }
    }
    else if (mode->colortype == LCT_GREY_ALPHA)
    {
        if (mode->bitdepth == 8)
        {
            for (i = 0; i != numpixels; ++i, buffer += num_channels)
            {
                buffer[0] = buffer[1] = buffer[2] = in[i * 2 + 0];
            }
        }
        else
        {
            for (i = 0; i != numpixels; ++i, buffer += num_channels)
            {
                buffer[0] = buffer[1] = buffer[2] = in[i * 4 + 0];
            }
        }
    }
    else if (mode->colortype == LCT_RGBA)
    {
        if (mode->bitdepth == 8)
        {
            for (i = 0; i != numpixels; ++i, buffer += num_channels)
            {
                memcpy(buffer, &in[i * 4], 3);
            }
        }
        else
        {
            for (i = 0; i != numpixels; ++i, buffer += num_channels)
            {
                buffer[0] = in[i * 8 + 0];
                buffer[1] = in[i * 8 + 2];
                buffer[2] = in[i * 8 + 4];
            }
        }
    }
}

void BF::PNGColorCompressor::getPixelColorRGBA8(unsigned char* r, unsigned char* g, unsigned char* b, unsigned char* a, const unsigned char* in, size_t i, const LodePNGColorMode* mode)
{
    if (mode->colortype == LCT_GREY)
    {
        if (mode->bitdepth == 8)
        {
            *r = *g = *b = in[i];
            if (mode->key_defined && *r == mode->key_r) *a = 0;
            else *a = 255;
        }
        else if (mode->bitdepth == 16)
        {
            *r = *g = *b = in[i * 2 + 0];
            if (mode->key_defined && 256U * in[i * 2 + 0] + in[i * 2 + 1] == mode->key_r) *a = 0;
            else *a = 255;
        }
        else
        {
            unsigned highest = ((1U << mode->bitdepth) - 1U); /*highest possible value for this bit depth*/
            size_t j = i * mode->bitdepth;
            unsigned value = readBitsFromReversedStream(&j, in, mode->bitdepth);
            *r = *g = *b = (value * 255) / highest;
            if (mode->key_defined && value == mode->key_r) *a = 0;
            else *a = 255;
        }
    }
    else if (mode->colortype == LCT_RGB)
    {
        if (mode->bitdepth == 8)
        {
            *r = in[i * 3 + 0]; *g = in[i * 3 + 1]; *b = in[i * 3 + 2];
            if (mode->key_defined && *r == mode->key_r && *g == mode->key_g && *b == mode->key_b) *a = 0;
            else *a = 255;
        }
        else
        {
            *r = in[i * 6 + 0];
            *g = in[i * 6 + 2];
            *b = in[i * 6 + 4];
            if (mode->key_defined && 256U * in[i * 6 + 0] + in[i * 6 + 1] == mode->key_r
                && 256U * in[i * 6 + 2] + in[i * 6 + 3] == mode->key_g
                && 256U * in[i * 6 + 4] + in[i * 6 + 5] == mode->key_b) *a = 0;
            else *a = 255;
        }
    }
    else if (mode->colortype == LCT_PALETTE)
    {
        unsigned index;
        if (mode->bitdepth == 8) index = in[i];
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
    else if (mode->colortype == LCT_GREY_ALPHA)
    {
        if (mode->bitdepth == 8)
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
    else if (mode->colortype == LCT_RGBA)
    {
        if (mode->bitdepth == 8)
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

unsigned BF::PNGColorCompressor::rgba8ToPixel(unsigned char* out, size_t i, const LodePNGColorMode* mode, PNGColorTree* tree, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    if (mode->colortype == LCT_GREY)
    {
        unsigned char gray = r; /*((unsigned short)r + g + b) / 3u;*/
        if (mode->bitdepth == 8) out[i] = gray;
        else if (mode->bitdepth == 16) out[i * 2 + 0] = out[i * 2 + 1] = gray;
        else
        {
            /*take the most significant bits of gray*/
            gray = ((unsigned)gray >> (8u - mode->bitdepth)) & ((1u << mode->bitdepth) - 1u);
            addColorBits(out, i, mode->bitdepth, gray);
        }
    }
    else if (mode->colortype == LCT_RGB)
    {
        if (mode->bitdepth == 8)
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
    else if (mode->colortype == LCT_PALETTE)
    {
        int index = color_tree_get(tree, r, g, b, a);
        if (index < 0) return 82; /*color not in palette*/
        if (mode->bitdepth == 8) out[i] = index;
        else addColorBits(out, i, mode->bitdepth, (unsigned)index);
    }
    else if (mode->colortype == LCT_GREY_ALPHA)
    {
        unsigned char gray = r; /*((unsigned short)r + g + b) / 3u;*/
        if (mode->bitdepth == 8)
        {
            out[i * 2 + 0] = gray;
            out[i * 2 + 1] = a;
        }
        else if (mode->bitdepth == 16)
        {
            out[i * 4 + 0] = out[i * 4 + 1] = gray;
            out[i * 4 + 2] = out[i * 4 + 3] = a;
        }
    }
    else if (mode->colortype == LCT_RGBA)
    {
        if (mode->bitdepth == 8)
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

size_t BF::PNGColorCompressor::lodepng_get_raw_size_lct(unsigned w, unsigned h, LodePNGColorType colortype, unsigned bitdepth)
{
    size_t bpp = lodepng_get_bpp_lct(colortype, bitdepth);
    size_t n = (size_t)w * (size_t)h;
    return ((n / 8u) * bpp) + ((n & 7u) * bpp + 7u) / 8u;
}

size_t BF::PNGColorCompressor::lodepng_get_raw_size(unsigned w, unsigned h, const LodePNGColorMode* color)
{
    return lodepng_get_raw_size_lct(w, h, color->colortype, color->bitdepth);
}

int BF::PNGColorCompressor::color_tree_get(PNGColorTree* tree, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    int bit = 0;
    for (bit = 0; bit < 8; ++bit)
    {
        int i = 8 * ((r >> bit) & 1) + 4 * ((g >> bit) & 1) + 2 * ((b >> bit) & 1) + 1 * ((a >> bit) & 1);
        if (!tree->children[i]) return -1;
        else tree = tree->children[i];
    }
    return tree ? tree->index : -1;
}

void BF::PNGColorCompressor::addColorBits(unsigned char* out, size_t index, unsigned bits, unsigned in)
{
    unsigned m = bits == 1 ? 7 : bits == 2 ? 3 : 1; /*8 / bits - 1*/
  /*p = the partial index in the byte, e.g. with 4 palettebits it is 0 for first half or 1 for second half*/
    unsigned p = index & m;
    in &= (1u << bits) - 1u; /*filter out any other bits of the input value*/
    in = in << (bits * (m - p));
    if (p == 0) out[index * bits / 8u] = in;
    else out[index * bits / 8u] |= in;
}

unsigned char BF::PNGColorCompressor::readBitFromReversedStream(size_t* bitpointer, const unsigned char* bitstream)
{
    unsigned char result = (unsigned char)((bitstream[(*bitpointer) >> 3] >> (7 - ((*bitpointer) & 0x7))) & 1);
    ++(*bitpointer);
    return result;
}

unsigned BF::PNGColorCompressor::readBitsFromReversedStream(size_t* bitpointer, const unsigned char* bitstream, size_t nbits)
{
    unsigned result = 0;
    size_t i;
    for (i = 0; i < nbits; ++i)
    {
        result <<= 1u;
        result |= (unsigned)readBitFromReversedStream(bitpointer, bitstream);
    }
    return result;
}
