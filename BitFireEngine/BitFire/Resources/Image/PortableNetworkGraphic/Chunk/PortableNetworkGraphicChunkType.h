#pragma once

// Chunk Specifications
enum class PortableNetworkGraphicChunkType
{
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