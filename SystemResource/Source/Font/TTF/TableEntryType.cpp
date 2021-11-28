#include "TableEntryType.h"

BF::TTF::TableEntryType BF::TTF::ConvertTableEntryType(char tag[4])
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
                return TableEntryType::AccentAttachment;

            if (b == 'n' && c == 'k' && d == 'r') // ankr
                return TableEntryType::AnchorPoint;

            if (b == 'v' && c == 'a' && d == 'r') // avar
                return TableEntryType::AxisVariation;

            break;
        }
        case 'b':
        {
            if (b == 'd' && c == 'a' && d == 't') // bdat
                return TableEntryType::BitmapData;

            if (b == 'h' && c == 'e' && d == 'd') // bhed
                return TableEntryType::BitmapFontHeader;

            if (b == 'l' && c == 'o' && d == 'c') // bloc
                return TableEntryType::BitmapLocation;

            if (b == 's' && c == 'l' && d == 'n') // bsln
                return TableEntryType::Baseline;

            break;
        }
        case 'c':
        {
            if (b == 'm' && c == 'a' && d == 'p') // cmap
                return TableEntryType::CharacterCodeMapping;

            if (b == 'v' && c == 'a' && d == 'r') // cvar
                return TableEntryType::CVTVariation;

            if (b == 'v' && c == 't' && d == ' ') // cvt
                return TableEntryType::ControlValue;

            break;
        }
        case 'D':
        {
            if (b == 'S' && c == 'I' && d == 'G') // DSIG
                return TableEntryType::DigitalSignature;
        }
        case 'E':
        {
            if (b == 'B' && c == 'S' && d == 'C') // EBSC
                return TableEntryType::EmbeddedBitmapScalingControl;

            break;
        }
        case 'f':
        {
            if (b == 'd' && c == 's' && d == 'c') // fdsc
                return TableEntryType::FontDescriptor;

            if (b == 'e' && c == 'a' && d == 't') // feat
                return TableEntryType::LayoutFeature;

            if (b == 'm' && c == 't' && d == 'x') // fmtx
                return TableEntryType::FontMetrics;

            if (b == 'o' && c == 'n' && d == 'd') // fond
                return TableEntryType::FontFamilyCompatibility;

            if (b == 'p' && c == 'g' && d == 'm') // fpgm
                return TableEntryType::FontProgram;

            if (b == 'v' && c == 'a' && d == 'r') // fvar
                return TableEntryType::FontVariation;

            break;
        }
        case 'g':
        {
            if (b == 'a' && c == 's' && d == 'p') // gasp
                return TableEntryType::GridFittingAndScanConversionProcedure;

            if (b == 'l' && c == 'y' && d == 'f') // glyf
                return TableEntryType::GlyphOutline;

            if (b == 'v' && c == 'a' && d == 'r') // gvar
                return TableEntryType::GlyphVariation;

            break;
        }
        case 'h':
        {
            if (b == 'd' && c == 'm' && d == 'x') // hdmx
                return TableEntryType::HorizontalDeviceMetrics;

            if (b == 'e' && c == 'a' && d == 'd') // head
                return TableEntryType::FontHeader;

            if (b == 'h' && c == 'e' && d == 'a') // hhea
                return TableEntryType::HorizontalHeader;

            if (b == 'm' && c == 't' && d == 'x') // hmtx
                return TableEntryType::HorizontalMetrics;

            break;
        }
        case 'j':
        {
            if (b == 'u' && c == 's' && d == 't') // just
                return TableEntryType::Justification;

            break;
        }
        case 'k':
        {
            if (b == 'e' && c == 'r')
            {
                switch (d)
                {
                    case 'n':  // kern
                        return TableEntryType::Kerning;

                    case 'x':  // kerx
                        return TableEntryType::ExtendedKerning;
                }
            }   
      
            break;
        }
        case 'l':
        {
            if (b == 'c' && c == 'a' && d == 'r') // lcar
                return TableEntryType::LigatureCaret;

            if (b == 'o' && c == 'c' && d == 'a') // loca
                return TableEntryType::GlyphLocation;

            if (b == 't' && c == 'a' && d == 'g') // ltag
                return TableEntryType::LanguageTag;

            break;
        }
        case 'L':
        {
            if (b == 'T' && c == 'S' && d == 'H') // LTSH
                return TableEntryType::LinearThreshold;

            break;
        }
        case 'm':
        {
            if (b == 'a' && c == 'x' && d == 'p') // maxp
                return TableEntryType::MaximumProfile;

            if (b == 'e' && c == 't' && d == 'a') // meta
                return TableEntryType::Metadata;

            if (b == 'o' && c == 'r' && d == 't') // mort
                return TableEntryType::MetamorphosisTabledeprecated;

            if (b == 'o' && c == 't' && d == 'x') // morx
                return TableEntryType::ExtendedMetamorphosis;

            break;
        }
        case 'n':
        {
            if (b == 'a' && c == 'm' && d == 'e') // name
                return TableEntryType::Name;

            break;
        }
        case 'o':
        {
            if (b == 'p' && c == 'b' && d == 'd') // opbd
                return TableEntryType::OpticalBounds;

            break;
        }
        case 'O':
        {
            if (b == 'S' && c == '/' && d == '2') // OS/2
                return TableEntryType::Compatibility;

            break;
        }
        case 'p':
        {
            if (b == 'o' && c == 's' && d == 't') // post
                return TableEntryType::GlyphNameAndPostScriptCompatibility;

            if (b == 'r' && c == 'e' && d == 'p') // prep
                return TableEntryType::ControlValueProgram;

            if (b == 'r' && c == 'o' && d == 'p') // prop
                return TableEntryType::Properties;

            break;
        }
        case 's':
        {
            if (b == 'b' && c == 'i' && d == 'x') // sbix
                return TableEntryType::ExtendedBitmaps;

            break;
        }
        case 't':
        {
            if (b == 'r' && c == 'a' && d == 'k') // trak
                return TableEntryType::Tracking;

            break;
        }
        case 'v':
        {
            if (b == 'h' && c == 'e' && d == 'a') // vhea
                return TableEntryType::VerticalHeader;

            if (b == 'm' && c == 't' && d == 'x') // vmtx
                return TableEntryType::VerticalMetrics;

            break;
        }
        case 'V':
        {
            if (b == 'D' && c == 'M' && d == 'X') // VDMX
                return TableEntryType::VerticalDeviceMetrics;

            break;
        }
        case 'x':
        {
            if (b == 'r' && c == 'e' && d == 'f') // xref
                return TableEntryType::GlyphReference;

            break;
        }
        case 'Z':
        {
            if (b == 'a' && c == 'p' && d == 'f') // Zapf
                return TableEntryType::GlyphReference;

            break;
        }               
	}

    return TableEntryType::UnkownType;
}

void BF::TTF::ConvertTableEntryType(char tag[4], TableEntryType tableEntryType)
{
    
}