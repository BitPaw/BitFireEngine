#pragma once

namespace BF
{
    union PNGChunkTypeID
    {
        public:
        struct
        {
            public:
            char A;
            char B;
            char C;
            char D;
        };

        char Data[4];
        
        unsigned int Value;
    };

    // Chunk Specifications
    enum class PNGChunkType
    {
        Invalid,

        //--------------------------------------------------------------------------
        // [Critical chunks]
        //--------------------------------------------------------------------------

        // [IHDR] The chunk will appear first.
        ImageHeader,

        // [PLTE] Palette
        Palette,

        // [IDAT] Image data
        ImageData,

        // [IEND] The chunk appears LAST. It marks the end of the PNG datastream.
        ImageEnd,

        //--------------------------------------------------------------------------
        // [Ancillary chunks]
        //--------------------------------------------------------------------------
        // Transparency information
        //--------------------------------------------------------------------------

        // [tRNS] Transparency
        Transparency,

        //--------------------------------------------------------------------------
        // Color space information
        //--------------------------------------------------------------------------

        // [gAMA] Image gamma
        ImageGamma,

        // [cHRM] - 
        PrimaryChromaticities,

        // [sRGB] - 
        StandardRGBColorSpace,

        // [iCCP] - 
        EmbeddedICCProfile,

        //--------------------------------------------------------------------------
        // Textual, information
        //--------------------------------------------------------------------------

        // [tEXt] - 
        TextualData,

        // [zTXt] - 
        CompressedTextualData,

        // [iTXt] - 
        InternationalTextualData,

        //--------------------------------------------------------------------------
        // Miscellaneous information
        //--------------------------------------------------------------------------

        // [bKGD] - 
        BackgroundColor,

        // [pHYs] - 
        PhysicalPixelDimensions,

        // [sBIT] - 
        SignificantBits,

        // [sPLT] - 
        SuggestedPalette,

        // [hIST] - 
        PaletteHistogram,

        // [tIME] - 
        LastModificationTime,

        //--------------------------------------------------------------------------
        // Additional chunk types
        //--------------------------------------------------------------------------

        // Unkown type, placegolder for future types or a midified PNG standard
        Custom
    };

    constexpr const unsigned int PNGChunkTypeIDMake(const char a, const char b, const char c, const char d);
    
    PNGChunkType ConvertChunkType(const PNGChunkTypeID chunkTypeID);
    void ConvertChunkType(PNGChunkTypeID& chunkTypeID, const PNGChunkType pngchunkType);

    const char* ChunkTypeToString(PNGChunkType pngchunkType);
}