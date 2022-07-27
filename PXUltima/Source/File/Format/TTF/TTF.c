#include "TTF.h"

#include <File/File.h>
#include <Memory/Memory.h>
#include <File/ParsingStream.h>
#include <Container/ClusterInt.h>

EncodingID ConvertToEncodingID(const PlatformID platformID, unsigned char encodingID)
{
	switch(platformID)
	{
		case PlatformUnicode:
		{
			switch(encodingID)
			{
				case 0: return EncodingUnicode10;
				case 1:	return EncodingUnicode11;
				case 2:	return EncodingISOIEC10646;
				case 3:	return EncodingUnicode20BMPOnly;
				case 4: return EncodingUnicode20FullRepertoire;
				case 5: return EncodingUnicodeVariation;
				case 6: return EncodingUnicodeFullRepertoire;
			}

			break;
		}
		case PlatformMacintosh:
		{
			// ???
			break;
		}
		case PlatformISO:
		{
			switch(encodingID)
			{
				case 0:	return EncodingSevenBitASCII;
				case 1:	return EncodingISO10646;
				case 2:	return EncodingISO8858;
			}

			break;
		}
		case PlatformWindows:
		{
			switch(encodingID)
			{
				case 0: return EncodingSymbol;
				case 1: return EncodingUnicodeBMP;
				case 2: return EncodingShiftJIS;
				case 3: return EncodingPRC;
				case 4: return EncodingBig5;
				case 5: return EncodingWansung;
				case 6: return EncodingJohab;

				case 7: // fall through
				case 8: // fall through
				case 9: // fall through
					return EncodingReserved;

				case 10: return EncodingUnicodeFullRepertoire;
			}

			break;
		}
		case PlatformCustom:
			return EncodingOTFWindowsNTCompatibilityMapping;

		case PlatformInvalid:
			return EncodingInvalid;
	}

	return EncodingInvalid;
}

TTFVersionType ConvertFromVersionType(unsigned short major, unsigned short minor)
{
	switch(minor)
	{
		case 0:
		{
			switch(major)
			{
				case 1: return TTFVersion1Dot0;
				case 2: return TTFVersion2Dot0;
				case 3: return TTFVersion3Dot0;
			}

			break;
		}
		case 5:
		{
			if(major == 2)
			{
				return TTFVersion2Dot5;
			}

			break;
		}
	}

	return TTFVersionInvalid;
}

void ConvertToVersionType(unsigned short* major, unsigned short* minor, const TTFVersionType versionType)
{
}

TTFTableEntryType ConvertTableEntryType(const unsigned int tableEntryType)
{
	switch(tableEntryType)
	{
		case MakeInt('a', 'c', 'n', 't'): return TTFTableEntryAccentAttachment;
		case MakeInt('a', 'n', 'k', 'r'): return TTFTableEntryAnchorPoint;
		case MakeInt('a', 'v', 'a', 'r'): return TTFTableEntryAxisVariation;
		case MakeInt('b', 'd', 'a', 't'): return TTFTableEntryBitmapData;
		case MakeInt('b', 'h', 'e', 'd'): return TTFTableEntryBitmapFontHeader;
		case MakeInt('b', 'l', 'o', 'c'): return TTFTableEntryBitmapLocation;
		case MakeInt('b', 's', 'l', 'n'): return TTFTableEntryBaseline;
		case MakeInt('c', 'm', 'a', 'p'): return TTFTableEntryCharacterCodeMapping;
		case MakeInt('c', 'v', 'a', 'r'): return TTFTableEntryCVTVariation;
		case MakeInt('c', 'v', 't', ' '): return TTFTableEntryControlValue;
		case MakeInt('D', 'S', 'I', 'G'): return TTFTableEntryDigitalSignature;
		case MakeInt('E', 'B', 'S', 'C'): return TTFTableEntryEmbeddedBitmapScalingControl;
		case MakeInt('f', 'd', 's', 'c'): return TTFTableEntryFontDescriptor;
		case MakeInt('f', 'e', 'a', 't'): return TTFTableEntryLayoutFeature;
		case MakeInt('f', 'm', 't', 'x'): return TTFTableEntryFontMetrics;
		case MakeInt('f', 'o', 'n', 'd'): return TTFTableEntryFontFamilyCompatibility;
		case MakeInt('f', 'p', 'g', 'm'): return TTFTableEntryFontProgram;
		case MakeInt('f', 'v', 'a', 'r'): return TTFTableEntryFontVariation;
		case MakeInt('g', 'a', 's', 'p'): return TTFTableEntryGridFittingAndScanConversionProcedure;
		case MakeInt('g', 'l', 'y', 'f'): return TTFTableEntryGlyphOutline;
		case MakeInt('g', 'v', 'a', 'r'): return TTFTableEntryGlyphVariation;
		case MakeInt('h', 'd', 'm', 'x'): return TTFTableEntryHorizontalDeviceMetrics;
		case MakeInt('h', 'e', 'a', 'd'): return TTFTableEntryFontHeader;
		case MakeInt('h', 'h', 'e', 'a'): return TTFTableEntryHorizontalHeader;
		case MakeInt('h', 'm', 't', 'x'): return TTFTableEntryHorizontalMetrics;
		case MakeInt('j', 'u', 's', 't'): return TTFTableEntryJustification;
		case MakeInt('k', 'e', 'r', 'n'): return TTFTableEntryKerning;
		case MakeInt('k', 'e', 'r', 'x'): return TTFTableEntryExtendedKerning;
		case MakeInt('l', 'c', 'a', 'r'): return TTFTableEntryLigatureCaret;
		case MakeInt('l', 'o', 'c', 'a'): return TTFTableEntryGlyphLocation;
		case MakeInt('l', 't', 'a', 'g'): return TTFTableEntryLanguageTag;
		case MakeInt('L', 'T', 'S', 'H'): return TTFTableEntryLinearThreshold;
		case MakeInt('m', 'a', 'x', 'p'): return TTFTableEntryMaximumProfile;
		case MakeInt('m', 'e', 't', 'a'): return TTFTableEntryMetadata;
		case MakeInt('m', 'o', 'r', 't'): return TTFTableEntryMetamorphosisTabledeprecated;
		case MakeInt('m', 'o', 'r', 'x'): return TTFTableEntryExtendedMetamorphosis;
		case MakeInt('n', 'a', 'm', 'e'): return TTFTableEntryName;
		case MakeInt('o', 'p', 'b', 'd'): return TTFTableEntryOpticalBounds;
		case MakeInt('O', 'S', '/', '2'): return TTFTableEntryCompatibility;
		case MakeInt('p', 'o', 's', 't'): return TTFTableEntryGlyphNameAndPostScriptCompatibility;
		case MakeInt('p', 'r', 'e', 'p'): return TTFTableEntryControlValueProgram;
		case MakeInt('p', 'r', 'o', 'p'): return TTFTableEntryProperties;
		case MakeInt('s', 'b', 'i', 'x'): return TTFTableEntryExtendedBitmaps;
		case MakeInt('t', 'r', 'a', 'k'): return TTFTableEntryTracking;
		case MakeInt('v', 'h', 'e', 'a'): return TTFTableEntryVerticalHeader;
		case MakeInt('v', 'm', 't', 'x'): return TTFTableEntryVerticalMetrics;
		case MakeInt('V', 'D', 'M', 'X'): return TTFTableEntryVerticalDeviceMetrics;
		case MakeInt('x', 'r', 'e', 'f'): return TTFTableEntryCrossReference;
		case MakeInt('Z', 'a', 'p', 'f'): return TTFTableEntryGlyphReference;
		default: return TTFTableEntryUnkown;
	}
}

void TTFConstruct(TTF* ttf)
{
	MemorySet(ttf, sizeof(TTF), 0);
}

void TTFDestruct(TTF* ttf)
{
	// TODO
}

ActionResult TTFParse(TTF* ttf, const void* data, const size_t dataSize, size_t* dataRead)
{
	ParsingStream parsingStream;
	TTFOffsetTable offsetTable;

	ParsingStreamConstruct(&parsingStream, data, dataSize);
	

	ParsingStreamRead(&parsingStream, &offsetTable.Version.Major, EndianBig);
	ParsingStreamRead(&parsingStream, &offsetTable.Version.Minor, EndianBig);
	ParsingStreamRead(&parsingStream, &offsetTable.NumberOfTables, EndianBig);
	ParsingStreamRead(&parsingStream, &offsetTable.SearchRange, EndianBig);
	ParsingStreamRead(&parsingStream, &offsetTable.EntrySelctor, EndianBig);
	ParsingStreamRead(&parsingStream, &offsetTable.RangeShift, EndianBig);

	for(size_t i = 0; i < offsetTable.NumberOfTables; i++)
	{
		TTFTableEntry tableEntry;

		ParsingStreamRead(&parsingStream, tableEntry.TypeRaw, 4u);
		ParsingStreamRead(&parsingStream, tableEntry.CheckSum, EndianBig);
		ParsingStreamRead(&parsingStream, tableEntry.Offset, EndianBig);
		ParsingStreamRead(&parsingStream, tableEntry.Length, EndianBig);

		const unsigned int typeID = MakeInt(tableEntry.TypeRaw[0], tableEntry.TypeRaw[1], tableEntry.TypeRaw[2], tableEntry.TypeRaw[3]);

		tableEntry.Type = ConvertTableEntryType(typeID);

		printf
		(
			"[TTF][i] Chunk:[%c%c%c%c], Known:%c, Offset:%6i, Length:%6i\n",
			tableEntry.TypeRaw[0],
			tableEntry.TypeRaw[1],
			tableEntry.TypeRaw[2],
			tableEntry.TypeRaw[3],
			tableEntry.Type == TTFTableEntryUnkown ? '-' : 'x',
			tableEntry.Offset,
			tableEntry.Length
		);

		switch(tableEntry.Type)
		{
			//---<Essential>---------------------------------------------------		
			case TTFTableEntryFontHeader:
			{
				ParsingStreamReadSU(&parsingStream, &ttf->Header.Version.Major, EndianBig);
				ParsingStreamReadSU(&parsingStream, &ttf->Header.Version.Minor, EndianLittle);
				ParsingStreamReadSU(&parsingStream, &ttf->Header.Revision.Major, EndianBig);
				ParsingStreamReadSU(&parsingStream, &ttf->Header.Revision.Minor, EndianLittle);
				ParsingStreamReadIU(&parsingStream, &ttf->Header.CheckSumAdjustment, EndianBig);
				ParsingStreamReadIU(&parsingStream, &ttf->Header.MagicNumber, EndianBig);
				ParsingStreamReadSU(&parsingStream, &ttf->Header.Flags, EndianBig);
				ParsingStreamReadSU(&parsingStream, &ttf->Header.UnitsPerEM, EndianBig);
				ParsingStreamReadLLU(&parsingStream, &ttf->Header.Created, EndianBig);
				ParsingStreamReadLLU(&parsingStream, &ttf->Header.Modified, EndianBig);
				ParsingStreamReadS(&parsingStream, &ttf->Header.Minimum[0], EndianBig);
				ParsingStreamReadS(&parsingStream, &ttf->Header.Minimum[1], EndianBig);
				ParsingStreamReadS(&parsingStream, &ttf->Header.Maximum[0], EndianBig);
				ParsingStreamReadS(&parsingStream, &ttf->Header.Maximum[1], EndianBig);
				ParsingStreamReadSU(&parsingStream, &ttf->Header.MacStyle, EndianBig);
				ParsingStreamReadSU(&parsingStream, &ttf->Header.LowestRecPpem, EndianBig);
				ParsingStreamReadS(&parsingStream, &ttf->Header.FontDirectionHint, EndianBig);
				ParsingStreamReadS(&parsingStream, &ttf->Header.IndexToLocFormat, EndianBig);
				ParsingStreamReadS(&parsingStream, &ttf->Header.GlyphDataFormat, EndianBig);
				break;
			}
			case TTFTableEntryHorizontalHeader:
			{
				ParsingStreamReadSU(&parsingStream, &ttf->HorizontalHeader.Version.Major, EndianBig);
				ParsingStreamReadSU(&parsingStream, &ttf->HorizontalHeader.Version.Minor, EndianLittle);
				ParsingStreamReadS(&parsingStream, &ttf->HorizontalHeader.Ascender, EndianBig);
				ParsingStreamReadS(&parsingStream, &ttf->HorizontalHeader.Descender, EndianBig);
				ParsingStreamReadS(&parsingStream, &ttf->HorizontalHeader.LineGap, EndianBig);
				ParsingStreamReadSU(&parsingStream, &ttf->HorizontalHeader.AdvanceWidthMaximum, EndianBig);
				ParsingStreamReadS(&parsingStream, &ttf->HorizontalHeader.MinimumLeftSideBearing, EndianBig);
				ParsingStreamReadS(&parsingStream, &ttf->HorizontalHeader.MinimumRightSideBearing, EndianBig);
				ParsingStreamReadS(&parsingStream, &ttf->HorizontalHeader.MaximalExtendX, EndianBig);
				ParsingStreamReadS(&parsingStream, &ttf->HorizontalHeader.CaretSlopeRun, EndianBig);
				ParsingStreamReadS(&parsingStream, &ttf->HorizontalHeader.CaretSlopeRise, EndianBig);
				ParsingStreamReadD(&parsingStream, &ttf->HorizontalHeader.Reserved, 10u);
				ParsingStreamReadS(&parsingStream, &ttf->HorizontalHeader.MetricDataFormat, EndianBig);
				ParsingStreamReadSU(&parsingStream, &ttf->HorizontalHeader.NumberOfHorizontalMetrics, EndianBig);
				break;
			}
			case TTFTableEntryMaximumProfile:
			{
				ParsingStreamReadSU(&parsingStream, &ttf->MaximumProfile.Version.Major, EndianBig);
				ParsingStreamReadSU(&parsingStream, &ttf->MaximumProfile.Version.Minor, EndianLittle);

				const unsigned char trustedTypeFonts = ttf->MaximumProfile.Version.Major == 1 && ttf->MaximumProfile.Version.Minor == 0;
				const unsigned char openTypeFonts = ttf->MaximumProfile.Version.Major == 0 && ttf->MaximumProfile.Version.Minor == 5;
				const unsigned char validVersion = trustedTypeFonts || openTypeFonts;

				ParsingStreamReadSU(&parsingStream, &ttf->MaximumProfile.NumberOfGlyphs, EndianBig);

				assert(validVersion);

				if(trustedTypeFonts && !openTypeFonts)
				{
					ParsingStreamReadSU(&parsingStream, &ttf->MaximumProfile.PointsMaximal, EndianBig);
					ParsingStreamReadSU(&parsingStream, &ttf->MaximumProfile.ContoursMaximal, EndianBig);
					ParsingStreamReadSU(&parsingStream, &ttf->MaximumProfile.ComponentPointsMaximal, EndianBig);
					ParsingStreamReadSU(&parsingStream, &ttf->MaximumProfile.ComponentContoursMaximal, EndianBig);
					ParsingStreamReadSU(&parsingStream, &ttf->MaximumProfile.ZonesMaximal, EndianBig);
					ParsingStreamReadSU(&parsingStream, &ttf->MaximumProfile.TwilightPointsMaximal, EndianBig);
					ParsingStreamReadSU(&parsingStream, &ttf->MaximumProfile.StorageMaximal, EndianBig);
					ParsingStreamReadSU(&parsingStream, &ttf->MaximumProfile.FunctionDefsMaximal, EndianBig);
					ParsingStreamReadSU(&parsingStream, &ttf->MaximumProfile.InstructionDefsMaximal, EndianBig);
					ParsingStreamReadSU(&parsingStream, &ttf->MaximumProfile.StackElementsMaximal, EndianBig);
					ParsingStreamReadSU(&parsingStream, &ttf->MaximumProfile.SizeOfInstructionsMaximal, EndianBig);
					ParsingStreamReadSU(&parsingStream, &ttf->MaximumProfile.ComponentElementsMaximal, EndianBig);
					ParsingStreamReadSU(&parsingStream, &ttf->MaximumProfile.ComponentDepthMaximal, EndianBig);
				}

				break;
			}
			case TTFTableEntryCompatibility:
			{
				ParsingStreamReadSU(&parsingStream, &ttf->Compatibility.Version, EndianBig);
				ParsingStreamReadS(&parsingStream, &ttf->Compatibility.xAvgCharWidth, EndianBig);
				ParsingStreamReadSU(&parsingStream, &ttf->Compatibility.usWeightClass, EndianBig);
				ParsingStreamReadSU(&parsingStream, &ttf->Compatibility.usWidthClass, EndianBig);
				ParsingStreamReadS(&parsingStream, &ttf->Compatibility.fsType, EndianBig);
				ParsingStreamReadS(&parsingStream, &ttf->Compatibility.ySubscriptXSize, EndianBig);
				ParsingStreamReadS(&parsingStream, &ttf->Compatibility.ySubscriptYSize, EndianBig);
				ParsingStreamReadS(&parsingStream, &ttf->Compatibility.ySubscriptXOffset, EndianBig);
				ParsingStreamReadS(&parsingStream, &ttf->Compatibility.ySubscriptYOffset, EndianBig);
				ParsingStreamReadS(&parsingStream, &ttf->Compatibility.ySuperscriptXSize, EndianBig);
				ParsingStreamReadS(&parsingStream, &ttf->Compatibility.ySuperscriptYSize, EndianBig);
				ParsingStreamReadS(&parsingStream, &ttf->Compatibility.ySuperscriptXOffset, EndianBig);
				ParsingStreamReadS(&parsingStream, &ttf->Compatibility.ySuperscriptYOffset, EndianBig);
				ParsingStreamReadS(&parsingStream, &ttf->Compatibility.yStrikeoutPosition, EndianBig);
				ParsingStreamReadS(&parsingStream, &ttf->Compatibility.sFamilyClass, EndianBig);

				// Parse PANROSE
				{
					TTFPanose* panrose = &ttf->Compatibility.Panose;
					unsigned char bFamilyType;
					unsigned char bSerifStyle;
					unsigned char bWeight;
					unsigned char bProportion;
					unsigned char bContrast;
					unsigned char bStrokeVariation;
					unsigned char bArmStyle;
					unsigned char bLetterform;
					unsigned char bMidline;
					unsigned char bXHeight;

					ParsingStreamReadCU(&parsingStream, &bFamilyType);
					ParsingStreamReadCU(&parsingStream, &bSerifStyle);
					ParsingStreamReadCU(&parsingStream, &bWeight);
					ParsingStreamReadCU(&parsingStream, &bProportion);
					ParsingStreamReadCU(&parsingStream, &bContrast);
					ParsingStreamReadCU(&parsingStream, &bStrokeVariation);
					ParsingStreamReadCU(&parsingStream, &bArmStyle);
					ParsingStreamReadCU(&parsingStream, &bLetterform);
					ParsingStreamReadCU(&parsingStream, &bMidline);
					ParsingStreamReadCU(&parsingStream, &bXHeight);

					//panrose.FamilyType = ConvertTTFFamilyType(bFamilyType);
					//panrose.SerifStyle = ConvertTTFSerifStyle(bSerifStyle);
					//panrose.Weight = ConvertTTFWeight(bWeight);
					//panrose.Proportion = ConvertTTFProportion(bProportion);
					//panrose.Contrast = ConvertTTFContrast(bContrast);
					//panrose.StrokeVariation = ConvertTTFStrokeVariatoon(bStrokeVariation);
					//panrose.ArmStyle = ConvertTTFArmStyle(bArmStyle);
					//panrose.Letterform = ConvertTTFLetterform(bLetterform);
					//panrose.Midline = ConvertTTFMidline(bMidline);
					//panrose.HeightX = ConvertTTFHeightX(bXHeight);
				}

				ParsingStreamReadSU(&parsingStream, &ttf->Compatibility.ulUnicodeRange[0], EndianBig);
				ParsingStreamReadSU(&parsingStream, &ttf->Compatibility.ulUnicodeRange[1], EndianBig);
				ParsingStreamReadSU(&parsingStream, &ttf->Compatibility.ulUnicodeRange[2], EndianBig);
				ParsingStreamReadSU(&parsingStream, &ttf->Compatibility.ulUnicodeRange[3], EndianBig);

				ParsingStreamReadD(&parsingStream, &ttf->Compatibility.achVendID, 4u);

				ParsingStreamReadSU(&parsingStream, &ttf->Compatibility.fsSelection, EndianBig);
				ParsingStreamReadSU(&parsingStream, &ttf->Compatibility.fsFirstCharIndex, EndianBig);
				ParsingStreamReadSU(&parsingStream, &ttf->Compatibility.fsLastCharIndex, EndianBig);

				if(ttf->Compatibility.Version > 0)
				{
					ParsingStreamReadSU(&parsingStream, &ttf->Compatibility.sTypoAscender, EndianBig);
					ParsingStreamReadSU(&parsingStream, &ttf->Compatibility.sTypoDescender, EndianBig);
					ParsingStreamReadSU(&parsingStream, &ttf->Compatibility.sTypoLineGap, EndianBig);
					ParsingStreamReadSU(&parsingStream, &ttf->Compatibility.usWinAscent, EndianBig);
					ParsingStreamReadSU(&parsingStream, &ttf->Compatibility.usWinDescent, EndianBig);
					ParsingStreamReadSU(&parsingStream, &ttf->Compatibility.ulCodePageRange1, EndianBig);
					ParsingStreamReadSU(&parsingStream, &ttf->Compatibility.ulCodePageRange2, EndianBig);
					ParsingStreamReadSU(&parsingStream, &ttf->Compatibility.sxHeight, EndianBig);
					ParsingStreamReadSU(&parsingStream, &ttf->Compatibility.sCapHeight, EndianBig);
					ParsingStreamReadSU(&parsingStream, &ttf->Compatibility.usDefaultChar, EndianBig);
					ParsingStreamReadSU(&parsingStream, &ttf->Compatibility.usBreakChar, EndianBig);
					ParsingStreamReadSU(&parsingStream, &ttf->Compatibility.usMaxContext, EndianBig);
					ParsingStreamReadSU(&parsingStream, &ttf->Compatibility.usLowerPointSize, EndianBig);
					ParsingStreamReadSU(&parsingStream, &ttf->Compatibility.usUpperPointSize, EndianBig);
				}

				break;
			}

			case TTFTableEntryControlValue: // cvt
			{
				// FWORD[ n ] 	List of n values referenceable by instructions. n is the number of FWORD items that fit in the size of the table.
				break;
			}
			case TTFTableEntryGlyphNameAndPostScriptCompatibility: // post
			{
				ParsingStreamReadSU(&parsingStream, &ttf->PostScript.Version.Major, EndianBig);
				ParsingStreamReadSU(&parsingStream, &ttf->PostScript.Version.Minor, EndianLittle);

				//PostScript.Version.Check();

				/*

				switch(PostScript.Version.Type)
				{
					case TTFVersionInvalid:
						break;

					case TTFVersion1Dot0:
						break;

					case TTFVersion2Dot0:
					{
						ParsingStreamReadSU(&parsingStream, &ttf->PostScript.NumberOfGlyphs, EndianBig);
						break;
					}
					case TTFVersion2Dot5:
					{
						ParsingStreamReadSU(&parsingStream, &ttf->PostScript.NumberOfGlyphs, EndianBig);
						break;
					}
					case TTFVersion3Dot0:
						break;

					default:
						printf("Illegal Version");
						break;
				}*/

				break;
			}
			case TTFTableEntryKerning: // kern
			{
				ParsingStreamReadSU(&parsingStream, &ttf->Kerning.Version, EndianBig);
				ParsingStreamReadSU(&parsingStream, &ttf->Kerning.NumberOfSubtables, EndianBig);

				/*

				Kerning.KerningSubtableList = new TTFKerningSubtable[Kerning.NumberOfSubtables];

				for(size_t i = 0; i < Kerning.NumberOfSubtables; i++)
				{
					TTFKerningSubtable& kerningTable = Kerning.KerningSubtableList[i];

					unsigned short coverage = 0;

					ParsingStreamReadSU(&parsingStream, &ttf->kerningTable.Version, EndianBig);
					ParsingStreamReadSU(&parsingStream, &ttf->kerningTable.Length, EndianBig);
					ParsingStreamReadSU(&parsingStream, &ttf->coverage, EndianBig);

					kerningTable.ParseCoverageValue(coverage);

					switch(kerningTable.Version)
					{
						case 0:
						{
							TTFSubtableFormat0& subtableFormat = kerningTable.SubtableFormat0;

							ParsingStreamReadSU(&parsingStream, &ttf->subtableFormat.NumberOfPairs, EndianBig);
							ParsingStreamReadSU(&parsingStream, &ttf->subtableFormat.SearchRange, EndianBig);
							ParsingStreamReadSU(&parsingStream, &ttf->subtableFormat.EntrySelector, EndianBig);
							ParsingStreamReadSU(&parsingStream, &ttf->subtableFormat.RangeShift, EndianBig);

							subtableFormat.KerningPairList = new TTFKerningPair[subtableFormat.NumberOfPairs];

							for(size_t i = 0; i < subtableFormat.NumberOfPairs; i++)
							{
								TTFKerningPair& kerningPair = subtableFormat.KerningPairList[i];

								ParsingStreamReadSU(&parsingStream, &ttf->kerningPair.Left, EndianBig);
								ParsingStreamReadSU(&parsingStream, &ttf->kerningPair.Right, EndianBig);
								ParsingStreamReadSU(&parsingStream, &ttf->kerningPair.Value, EndianBig);
							}

							break;
						}
						case 2:
						{
							TTFSubtableFormat2& subtableFormat = kerningTable.SubtableFormat2;

							ParsingStreamReadSU(&parsingStream, &ttf->subtableFormat.RowWidth, EndianBig);
							ParsingStreamReadSU(&parsingStream, &ttf->subtableFormat.LeftClassOffset, EndianBig);
							ParsingStreamReadSU(&parsingStream, &ttf->subtableFormat.RightClassOffset, EndianBig);
							ParsingStreamReadSU(&parsingStream, &ttf->subtableFormat.KerningArrayOffset, EndianBig);

							break;
						}
					}
				}*/

				break;
			}
			case TTFTableEntryControlValueProgram: // prep
			{
				// The name 'prep' is anachronistic (the table used to be known as the Pre Program table.)
				// unsigned char[N]
				break;
			}
			case TTFTableEntryGlyphOutline: // glyf
			{
				break;
			}
			case TTFTableEntryFontProgram: // fpgm
			{
				break;
			}
			//-----------------------------------------------------------------

			// Windows 
			case TTFTableEntryCharacterCodeMapping:
			{
				/*
				ParsingStreamReadSU(&parsingStream, &ttf->CharacterMapping.Version, EndianBig);
				ParsingStreamReadSU(&parsingStream, &ttf->CharacterMapping.NumberOfTables, EndianBig);

				CharacterMapping.EncodingRecordList = new EncodingRecord[CharacterMapping.NumberOfTables];

				for(size_t i = 0; i < CharacterMapping.NumberOfTables; i++)
				{
					EncodingRecord& encodingRecord = CharacterMapping.EncodingRecordList[i];

					unsigned short platformID;
					unsigned short encodingID;

					ParsingStreamReadSU(&parsingStream, &ttf->platformID, EndianBig);
					ParsingStreamReadSU(&parsingStream, &ttf->encodingID, EndianBig);
					ParsingStreamReadSU(&parsingStream, &ttf->encodingRecord.SubtableOffset, EndianBig);

					encodingRecord.Platform = ConvertPlatformID(platformID);
					encodingRecord.Encoding = ConvertEncodingID(encodingRecord.Platform, encodingID);
				}
				*/
				break;
			}
			case TTFTableEntryLinearThreshold:
			{
				/*
				ParsingStreamReadSU(&parsingStream, &ttf->LinearThreshold.Version, EndianBig);
				ParsingStreamReadSU(&parsingStream, &ttf->LinearThreshold.NumberOfGlyphs, EndianBig);

				LinearThreshold.PelsHeightList = Memory::Allocate<Byte__>(LinearThreshold.NumberOfGlyphs);

				ParsingStreamReadSU(&parsingStream, &ttf->LinearThreshold.PelsHeightList, LinearThreshold.NumberOfGlyphs);*/

				break;
			}
			case TTFTableEntryDigitalSignature:
			{
				/*
				Byte__* startPointer = chunkData.Data + chunkData.DataCursor;

				ParsingStreamReadSU(&parsingStream, &ttf->DigitalSignature.Version, EndianBig);
				ParsingStreamReadSU(&parsingStream, &ttf->DigitalSignature.NumberOfSignatures, EndianBig);
				ParsingStreamReadSU(&parsingStream, &ttf->DigitalSignature.Flags, EndianBig);

				DigitalSignature.SignatureRecordList = new TTFDigitalSignatureRecord[DigitalSignature.NumberOfSignatures];
				DigitalSignature.SignatureBlockList = new TTFDigitalSignatureBlock[DigitalSignature.NumberOfSignatures];

				for(size_t i = 0; i < DigitalSignature.NumberOfSignatures; i++)
				{
					TTFDigitalSignatureRecord& signatureRecord = DigitalSignature.SignatureRecordList[i];

					ParsingStreamReadSU(&parsingStream, &ttf->signatureRecord.Format, EndianBig);
					ParsingStreamReadSU(&parsingStream, &ttf->signatureRecord.Length, EndianBig);
					ParsingStreamReadSU(&parsingStream, &ttf->signatureRecord.SignatureBlockOffset, EndianBig);

					{
						ParsingStreamX byteSteam(startPointer + signatureRecord.SignatureBlockOffset, signatureRecord.Length);
						TTFDigitalSignatureBlock& signatureBlock = DigitalSignature.SignatureBlockList[i];

						ParsingStreamReadSU(&parsingStream, &ttf->signatureBlock.Reserved1, EndianBig);
						ParsingStreamReadSU(&parsingStream, &ttf->signatureBlock.Reserved2, EndianBig);
						ParsingStreamReadSU(&parsingStream, &ttf->signatureBlock.SignatureLength, EndianBig);

						signatureBlock.Signature = (char*)malloc(signatureBlock.SignatureLength);

						ParsingStreamReadSU(&parsingStream, &ttf->signatureBlock.Signature, signatureBlock.SignatureLength);

						for(size_t w = 0; w < signatureBlock.SignatureLength - 2; w++)
						{
							if(signatureBlock.Signature[w] == 0)
							{
								signatureBlock.Signature[w] = '#';
							}
						}
					}
				}*/

				break;
			}
		}
	}

	return ResultSuccessful;
}