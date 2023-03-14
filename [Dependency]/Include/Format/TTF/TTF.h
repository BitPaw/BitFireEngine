#ifndef PXTTFINCLUDE
#define PXTTFINCLUDE

#include <File/PXDataStream.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef enum TTFTableEntryType_
    {
        TTFTableEntryUnkown,
        TTFTableEntryAccentAttachment, // acnt
        TTFTableEntryAnchorPoint, // ankr
        TTFTableEntryAxisVariation, // avar
        TTFTableEntryBitmapData, // bdat
        TTFTableEntryBitmapFontHeader, // bhed
        TTFTableEntryBitmapLocation, // bloc
        TTFTableEntryBaseline, // bsln
        TTFTableEntryCharacterCodeMapping, // cmap
        TTFTableEntryCVTVariation, // cvar
        TTFTableEntryControlValue, // cvt
        TTFTableEntryEmbeddedBitmapScalingControl, // EBSC
        TTFTableEntryFontDescriptor, // fdsc
        TTFTableEntryLayoutFeature, // feat
        TTFTableEntryFontMetrics, // fmtx
        TTFTableEntryFontFamilyCompatibility, // fond
        TTFTableEntryFontProgram, // fpgm
        TTFTableEntryFontVariation, // fvar
        TTFTableEntryGridFittingAndScanConversionProcedure, // gasp
        TTFTableEntryGlyphOutline, // glyf
        TTFTableEntryGlyphVariation, // gvar
        TTFTableEntryHorizontalDeviceMetrics, // hdmx
        TTFTableEntryFontHeader, // head
        TTFTableEntryHorizontalHeader, // hhea
        TTFTableEntryHorizontalMetrics, // hmtx
        TTFTableEntryJustification, // just
        TTFTableEntryKerning, // kern
        TTFTableEntryExtendedKerning, // kerx
        TTFTableEntryLigatureCaret, // lcar
        TTFTableEntryGlyphLocation, // loca
        TTFTableEntryLanguageTag, // ltag
        TTFTableEntryMaximumProfile,  // maxp
        TTFTableEntryMetadata,  // meta
        TTFTableEntryMetamorphosisTabledeprecated,  // mort
        TTFTableEntryExtendedMetamorphosis,  // morx
        TTFTableEntryName,  // name
        TTFTableEntryOpticalBounds, // opbd
        TTFTableEntryCompatibility, //  OS/2
        TTFTableEntryGlyphNameAndPostScriptCompatibility, // post
        TTFTableEntryControlValueProgram, // prep
        TTFTableEntryProperties, // prop
        TTFTableEntryExtendedBitmaps, // sbix
        TTFTableEntryTracking, // trak
        TTFTableEntryVerticalHeader, // vhea
        TTFTableEntryVerticalMetrics, // vmtx
        TTFTableEntryCrossReference, // xref
        TTFTableEntryGlyphReference, // Zapf

        // Additional
        TTFTableEntryDigitalSignature, // DSIG 
        TTFTableEntryLinearThreshold, // LTSH
        TTFTableEntryVerticalDeviceMetrics // VDMX
    }
    TTFTableEntryType;


    typedef enum TTFVersionType_
    {
        TTFVersionInvalid,
        TTFVersion1Dot0,
        TTFVersion2Dot0,
        TTFVersion2Dot5,
        TTFVersion3Dot0
    }
    TTFVersionType;

    typedef struct TTFVersion_
    {
        unsigned short Major;
        unsigned short Minor;
        TTFVersionType Type;
    }
    TTFVersion;

    typedef struct TTFLinearThreshold_
    {
        unsigned short Version; // Version number(starts at 0).
        unsigned short NumberOfGlyphs; // Number of glyphs(from “numGlyphs” in 'maxp' table).
        unsigned char* PelsHeightList; // The vertical pel height at which the glyph can be assumed to scale linearly.On a per glyph basis.
    }
    TTFLinearThreshold;


    typedef struct TTFHorizontalHeader_
    {
        TTFVersion Version;
        short Ascender;
        short Descender;
        short LineGap;
        unsigned short AdvanceWidthMaximum;
        short MinimumLeftSideBearing;
        short MinimumRightSideBearing;
        short MaximalExtendX;
        short CaretSlopeRise;
        short CaretSlopeRun;
        unsigned char Reserved[10];
        short MetricDataFormat;
        unsigned short NumberOfHorizontalMetrics;
    }
    TTFHorizontalHeader;


	typedef struct TTFTableEntry_
	{
		char TypeRaw[4];
		TTFTableEntryType Type;
		unsigned int CheckSum;
		unsigned int Offset;
		unsigned int Length;
	}
	TTFTableEntry;


    typedef struct TTFVerticalDeviceMetrics_
    {
        unsigned short Version; // Version number(0 or 1).
        unsigned short numRecs; // Number of VDMX groups present
        unsigned short numRatios; // Number of aspect ratio groupings
        //	RatioRange 	ratRange[numRatios];// 	Ratio record array.
        //Offset16 	vdmxGroupOffsets[numRatios];// 	Offset from start of this table to the VDMXGroup table for a corresponding RatioRange record.
    }
    TTFVerticalDeviceMetrics;





    //-----<CMAP>--------------------------------------------------------------
    typedef enum EncodingID_
    {
        EncodingInvalid,

        // (platform ID = 0)

        EncodingUnicode10,// semantics—deprecated,
        EncodingUnicode11,// semantics—deprecated,
        EncodingISOIEC10646,// semantics—deprecated,
        EncodingUnicode20BMPOnly,
        EncodingUnicode20FullRepertoire,
        EncodingUnicodeVariation,// Sequences—for use with subtable format 14,
        EncodingUnicodefull,// repertoire—for use with subtable format 13,

        // Macintosh platform (platform ID = 1)

        // (platform ID = 2)

        EncodingSevenBitASCII,
        EncodingISO10646,
        EncodingISO8858,

        // Windows platform (platform ID = 3)
        EncodingSymbol,
        EncodingUnicodeBMP,
        EncodingShiftJIS,
        EncodingPRC,
        EncodingBig5,
        EncodingWansung,
        EncodingJohab,
        EncodingReserved,
        EncodingUnicodeFullRepertoire,

        // Custom platform (platform ID = 4) and OTF Windows NT compatibility mapping
        EncodingOTFWindowsNTCompatibilityMapping
    }
    EncodingID;

    typedef enum PlatformID_
    {
        PlatformInvalid,
        PlatformUnicode,// Various
        PlatformMacintosh,// Script manager code
        PlatformISO,// ISO encoding[deprecated]
        PlatformWindows,// Windows encoding
        PlatformCustom
    }
    PlatformID;

    typedef struct EncodingRecord_
    {
        PlatformID Platform;
        EncodingID Encoding; // Platform specific.
        unsigned int SubtableOffset;// 	Byte__ offset from beginning of table to the subtable for this encoding.
    }
    EncodingRecord;    
    
    typedef struct TTFCharacterMapping_
    {
        unsigned short Version; // Table version number(0).
        unsigned short NumberOfTables; // Number of encoding tables that follow.
        EncodingRecord* EncodingRecordList;
    }
    TTFCharacterMapping;
    //-------------------------------------------------------------------------

    //-----<DSIG>--------------------------------------------------------------
    typedef struct TTFDigitalSignatureBlock_
    {
        unsigned short Reserved1; // Reserved for future use; set to zero.
        unsigned short Reserved2; // Reserved for future use; set to zero.
        unsigned int SignatureLength; // Length(in bytes) of the PKCS#7 packet in the signature field.
        char* Signature; // PKCS#7 packet
    }
    TTFDigitalSignatureBlock;

    typedef struct TTFDigitalSignatureRecord_
    {
        unsigned int Format; // Format of the signature
        unsigned int Length; // Length of signature in bytes
        unsigned int SignatureBlockOffset; // Offset to the signature block from the beginning of the table
    }
    TTFDigitalSignatureRecord;

    typedef struct TTFDigitalSignature_
    {
        unsigned int Version;
        unsigned short NumberOfSignatures;
        unsigned short Flags;
        TTFDigitalSignatureRecord* SignatureRecordList;
        TTFDigitalSignatureBlock* SignatureBlockList;
    }
    TTFDigitalSignature;
    //-------------------------------------------------------------------------

    //------------------
    typedef struct TTFKerningPair_
    {
        unsigned short Left;// 	The glyph index for the left - hand glyph in the kerning pair.
        unsigned short Right;// 	The glyph index for the right - hand glyph in the kerning pair.
        short Value;// 	The kerning value for the above pair, in FUnits.If this value is greater than zero, the characters will be moved apart.If this value is less than zero, the character will be moved closer together.
    }
    TTFKerningPair;

    typedef struct TTFSubtableFormat0_
    {
        unsigned short NumberOfPairs; // This gives the number of kerning pairs in the table.
        unsigned short SearchRange; // The largest power of two less than or equal to the value of nPairs, multiplied by the size in bytes of an entry in the table.
        unsigned short EntrySelector; // This is calculated as log2 of the largest power of two less than or equal to the value of nPairs.This value indicates how many iterations of the search loop will have to be made. (For example, in a list of eight items, there would have to be three iterations of the loop).
        unsigned short RangeShift; // The value of nPairs minus the largest power of two less than or equal to nPairs, and then multiplied by the size in bytes of an entry in the table.

        TTFKerningPair* KerningPairList;
    }
    TTFSubtableFormat0;

    typedef struct TTFSubtableFormat2_
    {
        unsigned short RowWidth;// 	The width, in bytes, of a row in the table.
        unsigned short LeftClassOffset;// 	Offset from beginning of this subtable to left - hand class table.
        unsigned short RightClassOffset;// 	Offset from beginning of this subtable to right - hand class table.
        unsigned short KerningArrayOffset;// 	Offset from beginning of this subtable to the start of the kerning array.
    }
    TTFSubtableFormat2;

    typedef struct TTFKerningSubtable_
    {
        unsigned short Version;// 	Kern subtable version number
        unsigned short Length;// 	Length of the subtable, in bytes(including this header).
        //unsigned short Coverage;// 	What type of information is contained in this table.

        unsigned char Horizontal;// 	0 	1 	1 if table has horizontal data, 0 if vertical.
        unsigned char Minimum;// 	1 	1 	If this bit is set to 1, the table has minimum values.If set to 0, the table has kerning values.
        unsigned char Cross;// - stream 	2 	1 	If set to 1, kerning is perpendicular to the flow of the text.
        unsigned char Override;//	3 	1 	If this bit is set to 1 the value in this table should replace the value currently being accumulated.
        unsigned char Reserved;// 	4 - 7 	4 	Reserved.This should be set to zero.
        unsigned char Format;// 	8 - 15 	8 	Format of the subtable.Only formats 0 and 2 have been defined.Formats 1 and 3 through 255 are reserved for future use.

        TTFSubtableFormat0 SubtableFormat0;
        TTFSubtableFormat2 SubtableFormat2;
    }
    TTFKerningSubtable;

    typedef struct TTFKerning_
    {
        unsigned short Version;// Table version number(0)
        unsigned short NumberOfSubtables;// Number of subtables in the kerning table.
        TTFKerningSubtable* KerningSubtableList;
    }
    TTFKerning;

    PXPublic void TTFKerningSubtableCoverageValueParse(unsigned short coverage);
    //----------------


    // OS2
    typedef enum TTFArmStyle_
    {
        TTFArmStyleInvalid,
        TTFArmStyleAny,
        TTFArmStyleNoFit,
        TTFArmStyleStraightArmsHorizontal,
        TTFArmStyleStraightArmsWedge,
        TTFArmStyleStraightArmsVertical,
        TTFArmStyleStraightArmsSingleSerif,
        TTFArmStyleStraightArmsDoubleSerif,
        TTFArmStyleNonStraightArmsHorizontal,
        TTFArmStyleNonStraightArmsWedge,
        TTFArmStyleNonStraightArmsVertical,
        TTFArmStyleNonStraightArmsSingleSerif,
        TTFArmStyleNonStraightArmsDoubleSerif
    }
    TTFArmStyle;

    typedef enum TTFContrast_
    {
        TTFContrastInvalid,
        TTFContrastAny,
        TTFContrastNoFit,
        TTFContrastNoneContrast,
        TTFContrastVeryLow,
        TTFContrastLow,
        TTFContrastMediumLow,
        TTFContrastMedium,
        TTFContrastMediumHigh,
        TTFContrastHigh,
        TTFContrastVeryHigh
    }
    TTFContrast;

    typedef enum TTFFamilyType_
    {
        TTFFamilyInvalid,
        TTFFamilyAny,
        TTFFamilyNoFit,
        TTFFamilyTextAndDisplay,
        TTFFamilyScript,
        TTFFamilyDecorative,
        TTFFamilyPictorial
    }
    TTFFamilyType;

    typedef enum TTFHeightX_
    {
        TTFHeightInvalid,
        TTFHeightAny,
        TTFHeightNoFit,
        TTFHeightConstantSmall,
        TTFHeightConstantStandard,
        TTFHeightConstantLarge,
        TTFHeightDuckingSmall,
        TTFHeightDuckingStandard,
        TTFHeightDuckingLarge
    }
    TTFHeightX;

    typedef enum TTFLetterform_
    {
        TTFLetterformInvalid,
        TTFLetterformAny,
        TTFLetterformNoFit,
        TTFLetterformNormalContact,
        TTFLetterformNormalWeighted,
        TTFLetterformNormalBoxed,
        TTFLetterformNormalFlattened,
        TTFLetterformNormalRounded,
        TTFLetterformNormalOffCenter,
        TTFLetterformNormalSquare,
        TTFLetterformObliqueContact,
        TTFLetterformObliqueWeighted,
        TTFLetterformObliqueBoxed,
        TTFLetterformObliqueFlattened,
        TTFLetterformObliqueRounded,
        TTFLetterformObliqueOffCenter,
        TTFLetterformObliqueSquare
    }
    TTFLetterform;

    typedef enum TTFMidline_
    {
        TTFMidlineInvalid,
        TTFMidlineAny,
        TTFMidlineNoFit,
        TTFMidlineStandardTrimmed,
        TTFMidlineStandardPointed,
        TTFMidlineStandardSerifed,
        TTFMidlineHighTrimmed,
        TTFMidlineHighPointed,
        TTFMidlineHighSerifed,
        TTFMidlineConstantTrimmed,
        TTFMidlineConstantPointed,
        TTFMidlineConstantSerifed,
        TTFMidlineLowTrimmed,
        TTFMidlineLowPointed,
        TTFMidlineLowSerifed
    }
    TTFMidline;

    typedef enum TTFProportion_
    {
        TTFProportionInvalid,
        TTFProportionAny,
        TTFProportionNoFit,
        TTFProportionOldStyle,
        TTFProportionModern,
        TTFProportionEvenWidth,
        TTFProportionExpanded,
        TTFProportionCondensed,
        TTFProportionVeryExpanded,
        TTFProportionVeryCondensed,
        TTFProportionMonospaced
    }
    TTFProportion;
    
    typedef enum TTFSerifStyle_
    {
        TTFSerifStyleInvalid,
        TTFSerifStyleAny,
        TTFSerifStyleNoFit,
        TTFSerifStyleCove,
        TTFSerifStyleObtuseCove,
        TTFSerifStyleSquareCove,
        TTFSerifStyleObtuseSquareCove,
        TTFSerifStyleSquare,
        TTFSerifStyleThin,
        TTFSerifStyleBone,
        TTFSerifStyleExaggerated,
        TTFSerifStyleTriangle,
        TTFSerifStyleNormalSans,
        TTFSerifStyleObtuseSans,
        TTFSerifStylePerpSans,
        TTFSerifStyleFlared,
        TTFSerifStyleRounded
    }
    TTFSerifStyle;

    typedef enum TTFStrokeVariatoon_
    {
        TTFStrokeVariatoonInvalid,
        TTFStrokeVariatoonAny,
        TTFStrokeVariatoonNoFit,
        TTFStrokeVariatoonGradualDiagonal,
        TTFStrokeVariatoonGradualTransitional,
        TTFStrokeVariatoonGradualVertical,
        TTFStrokeVariatoonGradualHorizontal,
        TTFStrokeVariatoonRapidVertical,
        TTFStrokeVariatoonRapidHorizontal,
        TTFStrokeVariatoonInstantVertical
    }
    TTFStrokeVariatoon;

    typedef enum TTFWeight_
    {
        TTFWeightInvalid,
        TTFWeightAny,
        TTFWeightNoFit,
        TTFWeightVeryLight,
        TTFWeightLight,
        TTFWeightThin,
        TTFWeightBook,
        TTFWeightMedium,
        TTFWeightDemi,
        TTFWeightBold,
        TTFWeightHeavy,
        TTFWeightBlack,
        TTFWeightNord
    }
    TTFWeight;

    typedef struct TTFPanose_
    {
        TTFFamilyType FamilyType;
        TTFSerifStyle SerifStyle;
        TTFWeight Weight;
        TTFProportion Proportion;
        TTFContrast Contrast;
        TTFStrokeVariatoon StrokeVariation;
        TTFArmStyle ArmStyle;
        TTFLetterform Letterform;
        TTFMidline Midline;
        TTFHeightX HeightX;
    }
    TTFPanose;

    typedef struct TTFCompatibility_
    {
        // Base
        unsigned short Version;// table version number(set to 0)
        short xAvgCharWidth;// average weighted advance width of lower case lettersand space
        unsigned short usWeightClass;// visual weight(degree of blackness or thickness) of stroke in glyphs
        unsigned short usWidthClass;//relative change from the normal aspect ratio(width to height ratio) as specified by a font designer for the glyphs in the font
        short fsType;// characteristicsand properties of this font(set undefined bits to zero)
        short ySubscriptXSize;// recommended horizontal size in pixels for subscripts
        short ySubscriptYSize;// recommended vertical size in pixels for subscripts
        short ySubscriptXOffset;// recommended horizontal offset for subscripts
        short ySubscriptYOffset;//recommended vertical offset form the baseline for subscripts
        short ySuperscriptXSize;//recommended horizontal size in pixels for superscripts
        short ySuperscriptYSize;// recommended vertical size in pixels for superscripts
        short ySuperscriptXOffset;//recommended horizontal offset for superscripts
        short ySuperscriptYOffset;//recommended vertical offset from the baseline for superscripts
        short yStrikeoutSize;// width of the strikeout stroke
        short yStrikeoutPosition;// position of the strikeout stroke relative to the baseline
        short sFamilyClass;//classification of font - family design.
        TTFPanose Panose;//10 byte series of number used to describe the visual characteristics of a given typeface
        unsigned int ulUnicodeRange[4];//Field is split into two bit fields of 96 and 36 bits each.The low 96 bits are used to specify the Unicode blocks encompassed by the font file.The high 32 bits are used to specify the character or script sets covered by the font file.Bit assignments are pending.Set to 0
        char achVendID[4];//four character identifier for the font vendor
        unsigned short fsSelection;//2 - byte bit field containing information concerning the nature of the font patterns
        unsigned short fsFirstCharIndex;//The minimum Unicode index in this font.
        unsigned short fsLastCharIndex;//The maximum Unicode index in this font.

        // Additional Fields

        short sTypoAscender;//The typographic ascender for this font.This is not necessarily the same as the ascender value in the 'hhea' table.
        short sTypoDescender;// The typographic descender for this font.This is not necessarily the same as the descender value in the 'hhea' table.
        short sTypoLineGap;//The typographic line gap for this font.This is not necessarily the same as the line gap value in the 'hhea' table.
        unsigned short usWinAscent;//The ascender metric for Windows.usWinAscent is computed as the yMax for all characters in the Windows ANSI character set.
        unsigned short usWinDescent;//The descender metric for Windows.usWinDescent is computed as the - yMin for all characters in the Windows ANSI character set.
        unsigned int ulCodePageRange1;//Bits 0 - 31
        unsigned int ulCodePageRange2;//Bits 32 - 63
        short sxHeight;//The distance between the baseline and the approximate height of non - ascending lowercase letters measured in FUnits.
        short sCapHeight;//The distance between the baseline and the approximate height of uppercase letters measured in FUnits.
        unsigned short usDefaultChar;// The default character displayed by Windows to represent an unsupported character. (Typically this should be 0.)
        unsigned short usBreakChar;//The break character used by Windows.
        unsigned short usMaxContext;//The maximum length of a target glyph OpenType context for any feature in this font.
        unsigned short usLowerPointSize;//Proposed for version 5 The lowest size(in twentieths of a typographic point), at which the font starts to be used.This is an inclusive value.
        unsigned short usUpperPointSize;//Proposed for version 5 The highest size(in twentieths of a typographic point), at which the font starts to be used.This is an exclusive value.Use 0xFFFFU to indicate no upper limit.
    }
    TTFCompatibility;
    //-------------------


    typedef struct TTFHeader_
    {
        TTFVersion Version;
        TTFVersion Revision;

        unsigned int CheckSumAdjustment;
        unsigned int MagicNumber;
        unsigned short Flags;
        unsigned short UnitsPerEM;
        unsigned long long Created;
        unsigned long long Modified;
        short Minimum[2];
        short Maximum[2];
        unsigned short MacStyle;
        unsigned short LowestRecPpem;
        short FontDirectionHint;
        short IndexToLocFormat;
        short GlyphDataFormat;
    }
    TTFHeader;




  


    typedef struct TTFPostScript_
    {
        // 0x00010000 for version 1.0
        // 0x00020000 for version 2.0
        // 0x00025000 for version 2.5 (deprecated)
        // 0x00030000 for version 3.0
        TTFVersion Version;

        //Fixed 	italicAngle;// 	Italic angle in counter - clockwise degrees from the vertical.Zero for upright text, negative for text that leans to the right(forward).
        //FWord 	underlinePosition;// 	This is the suggested distance of the top of the underline from the baseline(negative values indicate below baseline).
        // The PostScript definition of this FontInfo dictionary key(the y coordinate of the center of the stroke) is not used for historical reasons.The value of the PostScript key may be calculated by subtracting half the underlineThickness from the value of this field.
        //FWord 	underlineThickness;// 	Suggested values for the underline thickness.In general, the underline thickness should match the thickness of the underscore character(U + 005F LOW LINE), and should also match the strikeout thickness, which is specified in the OS / 2 table.
        unsigned int  isFixedPitch;// 	Set to 0 if the font is proportionally spaced, non - zero if the font is not proportionally spaced(i.e.monospaced).
        unsigned int  minMemType42;// 	Minimum memory usage when an OpenType font is downloaded.
        unsigned int  maxMemType42;// 	Maximum memory usage when an OpenType font is downloaded.
        unsigned int  minMemType1;// 	Minimum memory usage when an OpenType font is downloaded as a Type 1 font.
        unsigned int maxMemType1;// 	Maximum memory usage when an OpenType font is downloaded as a Type 1 font.

        // Version 1.0

        // Version 2.0
        unsigned short NumberOfGlyphs; // Number of glyphs(this should be the same as numGlyphs in 'maxp' table).
        unsigned short* GlyphNameIndex; // (NumberOfGlyphs) Array of indices into the string data.See below for details.
        char* StringData; // (variable) Storage for the string data.

        // Version 2.5
        // uint16 	numGlyphs 	Number of glyphs
        char* Offset; // (numGlyphs) Difference between graphic indexand standard order of glyph

        // Version 3.0
    }
    TTFPostScript;


    typedef struct TTFOffsetTable_
    {
        TTFVersion Version;
        unsigned short NumberOfTables;
        unsigned short SearchRange;
        unsigned short EntrySelctor;
        unsigned short RangeShift;
    }
    TTFOffsetTable;


    typedef struct TTFMaximumProfile_
    {
        TTFVersion Version;
        unsigned short NumberOfGlyphs; // the number of glyphs in the font
        unsigned short PointsMaximal; // points in non - compound glyph
        unsigned short ContoursMaximal; // contours in non - compound glyph
        unsigned short ComponentPointsMaximal; //points in compound glyph
        unsigned short ComponentContoursMaximal; //	contours in compound glyph
        unsigned short ZonesMaximal; // set to 2
        unsigned short TwilightPointsMaximal;//points used in Twilight Zone(Z0)
        unsigned short StorageMaximal; // number of Storage Area locations
        unsigned short FunctionDefsMaximal; // number of FDEFs
        unsigned short InstructionDefsMaximal; // number of IDEFs
        unsigned short StackElementsMaximal; // maximum stack depth
        unsigned short SizeOfInstructionsMaximal; // byte count for glyph instructions
        unsigned short ComponentElementsMaximal; // number of glyphs referenced at top level
        unsigned short ComponentDepthMaximal; // levels of recursion, set to 0 if font has only simple glyphs
    }
    TTFMaximumProfile;


	// Tag Image File Format
	typedef struct TTF_
	{
		TTFHeader Header;
		TTFHorizontalHeader HorizontalHeader;
		TTFMaximumProfile MaximumProfile;
		TTFCompatibility Compatibility;

		TTFCharacterMapping CharacterMapping;
		TTFPostScript PostScript;
		TTFKerning Kerning;
		//---------------------------------------------------------------------

		//---<Windows Standard>------------------------------------------------
		TTFDigitalSignature DigitalSignature;
		TTFLinearThreshold LinearThreshold;
		TTFVerticalDeviceMetrics VerticalDeviceMetrics;
		//---------------------------------------------------------------------
	}
	TTF;


    PXPublic EncodingID ConvertToEncodingID(const PlatformID platformID, unsigned char encodingID);

    PXPublic TTFVersionType ConvertFromVersionType(unsigned short major, unsigned short minor);
    PXPublic void ConvertToVersionType(unsigned short* major, unsigned short* minor, const TTFVersionType versionType);

    PXPublic TTFTableEntryType ConvertTableEntryType(const unsigned int tableEntryType);
    PXPublic unsigned int ConvertTableEntryType(const TTFTableEntryType tableEntryType);

    PXPublic void TTFConstruct(TTF* const ttf);
    PXPublic void TTFDestruct(TTF* const ttf);

	PXPublic PXActionResult TTFParse(TTF* const ttf, PXDataStream* const dataStream);

#ifdef __cplusplus
}
#endif

#endif