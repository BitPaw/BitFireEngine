#pragma once

namespace BF
{
	enum class TTFTableEntryType
	{
        UnkownType,

        AccentAttachment, // acnt
        AnchorPoint, // ankr
        AxisVariation, // avar
        BitmapData, // bdat
        BitmapFontHeader, // bhed
        BitmapLocation, // bloc
        Baseline, // bsln
        CharacterCodeMapping, // cmap
        CVTVariation, // cvar
        ControlValue, // cvt
        EmbeddedBitmapScalingControl, // EBSC
        FontDescriptor, // fdsc
        LayoutFeature, // feat
        FontMetrics, // fmtx
        FontFamilyCompatibility, // fond
        FontProgram, // fpgm
        FontVariation, // fvar
        GridFittingAndScanConversionProcedure, // gasp
        GlyphOutline, // glyf
        GlyphVariation, // gvar
        HorizontalDeviceMetrics, // hdmx
        FontHeader, // head
        HorizontalHeader, // hhea
        HorizontalMetrics, // hmtx
        Justification, // just
        Kerning, // kern
        ExtendedKerning, // kerx
        LigatureCaret, // lcar
        GlyphLocation, // loca
        LanguageTag, // ltag
        MaximumProfile,  // maxp
        Metadata,  // meta
        MetamorphosisTabledeprecated,  // mort
        ExtendedMetamorphosis,  // morx
        Name,  // name
        OpticalBounds, // opbd
        Compatibility, //  OS/2
        GlyphNameAndPostScriptCompatibility, // post
        ControlValueProgram, // prep
        Properties, // prop
        ExtendedBitmaps, // sbix
        Tracking, // trak
        VerticalHeader, // vhea
        VerticalMetrics, // vmtx
        CrossReference, // xref
        GlyphReference, // Zapf


        // Additional
        DigitalSignature, // DSIG 
        LinearThreshold, // LTSH
        VerticalDeviceMetrics // VDMX
	};

    TTFTableEntryType ConvertTableEntryType(char tag[4]);
    void ConvertTableEntryType(char tag[4], TTFTableEntryType tableEntryType);
}