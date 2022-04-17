#include "TTFTableEntryType.h"

BF::TTFTableEntryType BF::ConvertTableEntryType(char tag[4])
{
	char a = tag[0];
	char b = tag[1];
	char c = tag[2];
	char d = tag[3];

	switch (a)
	{
        case 'a':
        {
            if (b == 'c' && c == 'n' && d == 't') // acnt
                return TTFTableEntryType::AccentAttachment;

            if (b == 'n' && c == 'k' && d == 'r') // ankr
                return TTFTableEntryType::AnchorPoint;

            if (b == 'v' && c == 'a' && d == 'r') // avar
                return TTFTableEntryType::AxisVariation;

            break;
        }
        case 'b':
        {
            if (b == 'd' && c == 'a' && d == 't') // bdat
                return TTFTableEntryType::BitmapData;

            if (b == 'h' && c == 'e' && d == 'd') // bhed
                return TTFTableEntryType::BitmapFontHeader;

            if (b == 'l' && c == 'o' && d == 'c') // bloc
                return TTFTableEntryType::BitmapLocation;

            if (b == 's' && c == 'l' && d == 'n') // bsln
                return TTFTableEntryType::Baseline;

            break;
        }
        case 'c':
        {
            if (b == 'm' && c == 'a' && d == 'p') // cmap
                return TTFTableEntryType::CharacterCodeMapping;

            if (b == 'v' && c == 'a' && d == 'r') // cvar
                return TTFTableEntryType::CVTVariation;

            if (b == 'v' && c == 't' && d == ' ') // cvt
                return TTFTableEntryType::ControlValue;

            break;
        }
        case 'D':
        {
            if (b == 'S' && c == 'I' && d == 'G') // DSIG
                return TTFTableEntryType::DigitalSignature;

            break;
        }
        case 'E':
        {
            if (b == 'B' && c == 'S' && d == 'C') // EBSC
                return TTFTableEntryType::EmbeddedBitmapScalingControl;

            break;
        }
        case 'f':
        {
            if (b == 'd' && c == 's' && d == 'c') // fdsc
                return TTFTableEntryType::FontDescriptor;

            if (b == 'e' && c == 'a' && d == 't') // feat
                return TTFTableEntryType::LayoutFeature;

            if (b == 'm' && c == 't' && d == 'x') // fmtx
                return TTFTableEntryType::FontMetrics;

            if (b == 'o' && c == 'n' && d == 'd') // fond
                return TTFTableEntryType::FontFamilyCompatibility;

            if (b == 'p' && c == 'g' && d == 'm') // fpgm
                return TTFTableEntryType::FontProgram;

            if (b == 'v' && c == 'a' && d == 'r') // fvar
                return TTFTableEntryType::FontVariation;

            break;
        }
        case 'g':
        {
            if (b == 'a' && c == 's' && d == 'p') // gasp
                return TTFTableEntryType::GridFittingAndScanConversionProcedure;

            if (b == 'l' && c == 'y' && d == 'f') // glyf
                return TTFTableEntryType::GlyphOutline;

            if (b == 'v' && c == 'a' && d == 'r') // gvar
                return TTFTableEntryType::GlyphVariation;

            break;
        }
        case 'h':
        {
            if (b == 'd' && c == 'm' && d == 'x') // hdmx
                return TTFTableEntryType::HorizontalDeviceMetrics;

            if (b == 'e' && c == 'a' && d == 'd') // head
                return TTFTableEntryType::FontHeader;

            if (b == 'h' && c == 'e' && d == 'a') // hhea
                return TTFTableEntryType::HorizontalHeader;

            if (b == 'm' && c == 't' && d == 'x') // hmtx
                return TTFTableEntryType::HorizontalMetrics;

            break;
        }
        case 'j':
        {
            if (b == 'u' && c == 's' && d == 't') // just
                return TTFTableEntryType::Justification;

            break;
        }
        case 'k':
        {
            if (b == 'e' && c == 'r')
            {
                switch (d)
                {
                    case 'n':  // kern
                        return TTFTableEntryType::Kerning;

                    case 'x':  // kerx
                        return TTFTableEntryType::ExtendedKerning;
                }
            }   
      
            break;
        }
        case 'l':
        {
            if (b == 'c' && c == 'a' && d == 'r') // lcar
                return TTFTableEntryType::LigatureCaret;

            if (b == 'o' && c == 'c' && d == 'a') // loca
                return TTFTableEntryType::GlyphLocation;

            if (b == 't' && c == 'a' && d == 'g') // ltag
                return TTFTableEntryType::LanguageTag;

            break;
        }
        case 'L':
        {
            if (b == 'T' && c == 'S' && d == 'H') // LTSH
                return TTFTableEntryType::LinearThreshold;

            break;
        }
        case 'm':
        {
            if (b == 'a' && c == 'x' && d == 'p') // maxp
                return TTFTableEntryType::MaximumProfile;

            if (b == 'e' && c == 't' && d == 'a') // meta
                return TTFTableEntryType::Metadata;

            if (b == 'o' && c == 'r' && d == 't') // mort
                return TTFTableEntryType::MetamorphosisTabledeprecated;

            if (b == 'o' && c == 't' && d == 'x') // morx
                return TTFTableEntryType::ExtendedMetamorphosis;

            break;
        }
        case 'n':
        {
            if (b == 'a' && c == 'm' && d == 'e') // name
                return TTFTableEntryType::Name;

            break;
        }
        case 'o':
        {
            if (b == 'p' && c == 'b' && d == 'd') // opbd
                return TTFTableEntryType::OpticalBounds;

            break;
        }
        case 'O':
        {
            if (b == 'S' && c == '/' && d == '2') // OS/2
                return TTFTableEntryType::Compatibility;

            break;
        }
        case 'p':
        {
            if (b == 'o' && c == 's' && d == 't') // post
                return TTFTableEntryType::GlyphNameAndPostScriptCompatibility;

            if (b == 'r' && c == 'e' && d == 'p') // prep
                return TTFTableEntryType::ControlValueProgram;

            if (b == 'r' && c == 'o' && d == 'p') // prop
                return TTFTableEntryType::Properties;

            break;
        }
        case 's':
        {
            if (b == 'b' && c == 'i' && d == 'x') // sbix
                return TTFTableEntryType::ExtendedBitmaps;

            break;
        }
        case 't':
        {
            if (b == 'r' && c == 'a' && d == 'k') // trak
                return TTFTableEntryType::Tracking;

            break;
        }
        case 'v':
        {
            if (b == 'h' && c == 'e' && d == 'a') // vhea
                return TTFTableEntryType::VerticalHeader;

            if (b == 'm' && c == 't' && d == 'x') // vmtx
                return TTFTableEntryType::VerticalMetrics;

            break;
        }
        case 'V':
        {
            if (b == 'D' && c == 'M' && d == 'X') // VDMX
                return TTFTableEntryType::VerticalDeviceMetrics;

            break;
        }
        case 'x':
        {
            if (b == 'r' && c == 'e' && d == 'f') // xref
                return TTFTableEntryType::GlyphReference;

            break;
        }
        case 'Z':
        {
            if (b == 'a' && c == 'p' && d == 'f') // Zapf
                return TTFTableEntryType::GlyphReference;

            break;
        }               
	}

    return TTFTableEntryType::UnkownType;
}

void BF::ConvertTableEntryType(char tag[4], TTFTableEntryType TTFTableEntryType)
{
    
}