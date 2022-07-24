#include "TTF.h"

#include "TTFTableEntry.h"
#include "Chunks/TTFOffsetTable.h"
#include "Chunks/OS2/Panose/TTFPanose.h"

#include <File/File.h>
#include <Hardware/Memory/Memory.h>

#include <cassert>
#include <File/ByteStream.h>

BF::FileActionResult BF::TTF::Load(const char* filePath)
{
	File file;

	{
		const ActionResult fileLoadingResult = FileMapToVirtualMemoryA(&file, filePath, MemoryReadOnly);
		const bool sucessful = fileLoadingResult == ResultSuccessful;

		if(!sucessful)
		{
			return FileActionResult::Invalid;
		}
	}

	{
		const FileActionResult fileParsingResult = Load(file.Data, file.DataSize);

		return fileParsingResult;
	}
}

BF::FileActionResult BF::TTF::Load(const wchar_t* filePath)
{
	File file;

	{
		const ActionResult fileLoadingResult = FileMapToVirtualMemoryW(&file, filePath, MemoryReadOnly);
		const bool sucessful = fileLoadingResult == ResultSuccessful;

		if(!sucessful)
		{
			return FileActionResult::Invalid;
		}
	}

	{
		const FileActionResult fileParsingResult = Load(file.Data, file.DataSize);

		return fileParsingResult;
	}	
}

BF::FileActionResult BF::TTF::Load(const unsigned char* fileData, const size_t fileDataSize)
{
	ByteStream dataStream(fileData, fileDataSize);

	TTFOffsetTable offsetTable;

	dataStream.Read(offsetTable.Version.Major, EndianBig);
	dataStream.Read(offsetTable.Version.Minor, EndianBig);
	dataStream.Read(offsetTable.NumberOfTables, EndianBig);
	dataStream.Read(offsetTable.SearchRange, EndianBig);
	dataStream.Read(offsetTable.EntrySelctor, EndianBig);
	dataStream.Read(offsetTable.RangeShift, EndianBig);

	for(size_t i = 0; i < offsetTable.NumberOfTables; i++)
	{
		TTFTableEntry tableEntry;
		ByteStream chunkData;

		dataStream.Read(tableEntry.TypeRaw, 4u);
		dataStream.Read(tableEntry.CheckSum, EndianBig);
		dataStream.Read(tableEntry.Offset, EndianBig);
		dataStream.Read(tableEntry.Length, EndianBig);

		tableEntry.Type = ConvertTableEntryType(tableEntry.TypeRaw);

		chunkData.DataSet(dataStream.Data + tableEntry.Offset, tableEntry.Length);

		printf
		(
			"[TTF][i] Chunk:[%c%c%c%c], Known:%c, Offset:%6i, Length:%6i\n",
			tableEntry.TypeRaw[0],
			tableEntry.TypeRaw[1],
			tableEntry.TypeRaw[2],
			tableEntry.TypeRaw[3],
			tableEntry.Type == TTFTableEntryType::UnkownType ? '-' : 'x',
			tableEntry.Offset,
			tableEntry.Length
		);

		switch(tableEntry.Type)
		{
			//---<Essential>---------------------------------------------------		
			case TTFTableEntryType::FontHeader:
			{
				chunkData.Read(Header.Version.Major, EndianBig);
				chunkData.Read(Header.Version.Minor, EndianLittle);
				chunkData.Read(Header.Revision.Major, EndianBig);
				chunkData.Read(Header.Revision.Minor, EndianLittle);

				chunkData.Read(Header.CheckSumAdjustment, EndianBig);
				chunkData.Read(Header.MagicNumber, EndianBig);
				chunkData.Read(Header.Flags, EndianBig);
				chunkData.Read(Header.UnitsPerEM, EndianBig);
				chunkData.Read(Header.Created, EndianBig);
				chunkData.Read(Header.Modified, EndianBig);
				chunkData.Read(Header.Minimum[0], EndianBig);
				chunkData.Read(Header.Minimum[1], EndianBig);
				chunkData.Read(Header.Maximum[0], EndianBig);
				chunkData.Read(Header.Maximum[1], EndianBig);
				chunkData.Read(Header.MacStyle, EndianBig);
				chunkData.Read(Header.LowestRecPpem, EndianBig);
				chunkData.Read(Header.FontDirectionHint, EndianBig);
				chunkData.Read(Header.IndexToLocFormat, EndianBig);
				chunkData.Read(Header.GlyphDataFormat, EndianBig);

				break;
			}
			case TTFTableEntryType::HorizontalHeader:
			{
				chunkData.Read(HorizontalHeader.Version.Major, EndianBig);
				chunkData.Read(HorizontalHeader.Version.Minor, EndianLittle);
				chunkData.Read(HorizontalHeader.Ascender, EndianBig);
				chunkData.Read(HorizontalHeader.Descender, EndianBig);
				chunkData.Read(HorizontalHeader.LineGap, EndianBig);
				chunkData.Read(HorizontalHeader.AdvanceWidthMaximum, EndianBig);
				chunkData.Read(HorizontalHeader.MinimumLeftSideBearing, EndianBig);
				chunkData.Read(HorizontalHeader.MinimumRightSideBearing, EndianBig);
				chunkData.Read(HorizontalHeader.MaximalExtendX, EndianBig);
				chunkData.Read(HorizontalHeader.CaretSlopeRun, EndianBig);
				chunkData.Read(HorizontalHeader.CaretSlopeRise, EndianBig);
				chunkData.Read(HorizontalHeader.Reserved, 10u);
				chunkData.Read(HorizontalHeader.MetricDataFormat, EndianBig);
				chunkData.Read(HorizontalHeader.NumberOfHorizontalMetrics, EndianBig);

				break;
			}
			case TTFTableEntryType::MaximumProfile:
			{
				chunkData.Read(MaximumProfile.Version.Major, EndianBig);
				chunkData.Read(MaximumProfile.Version.Minor, EndianLittle);

				bool trustedTypeFonts = MaximumProfile.Version.Major == 1 && MaximumProfile.Version.Minor == 0;
				bool openTypeFonts = MaximumProfile.Version.Major == 0 && MaximumProfile.Version.Minor == 5;
				bool validVersion = trustedTypeFonts || openTypeFonts;

				chunkData.Read(MaximumProfile.NumberOfGlyphs, EndianBig);

				assert(validVersion);

				if(trustedTypeFonts && !openTypeFonts)
				{
					chunkData.Read(MaximumProfile.PointsMaximal, EndianBig);
					chunkData.Read(MaximumProfile.ContoursMaximal, EndianBig);
					chunkData.Read(MaximumProfile.ComponentPointsMaximal, EndianBig);
					chunkData.Read(MaximumProfile.ComponentContoursMaximal, EndianBig);
					chunkData.Read(MaximumProfile.ZonesMaximal, EndianBig);
					chunkData.Read(MaximumProfile.TwilightPointsMaximal, EndianBig);
					chunkData.Read(MaximumProfile.StorageMaximal, EndianBig);
					chunkData.Read(MaximumProfile.FunctionDefsMaximal, EndianBig);
					chunkData.Read(MaximumProfile.InstructionDefsMaximal, EndianBig);
					chunkData.Read(MaximumProfile.StackElementsMaximal, EndianBig);
					chunkData.Read(MaximumProfile.SizeOfInstructionsMaximal, EndianBig);
					chunkData.Read(MaximumProfile.ComponentElementsMaximal, EndianBig);
					chunkData.Read(MaximumProfile.ComponentDepthMaximal, EndianBig);
				}

				break;
			}
			case TTFTableEntryType::Compatibility:
			{
				chunkData.Read(Compatibility.Version, EndianBig);
				chunkData.Read(Compatibility.xAvgCharWidth, EndianBig);
				chunkData.Read(Compatibility.usWeightClass, EndianBig);
				chunkData.Read(Compatibility.usWidthClass, EndianBig);
				chunkData.Read(Compatibility.fsType, EndianBig);
				chunkData.Read(Compatibility.ySubscriptXSize, EndianBig);
				chunkData.Read(Compatibility.ySubscriptYSize, EndianBig);
				chunkData.Read(Compatibility.ySubscriptXOffset, EndianBig);
				chunkData.Read(Compatibility.ySubscriptYOffset, EndianBig);
				chunkData.Read(Compatibility.ySuperscriptXSize, EndianBig);
				chunkData.Read(Compatibility.ySuperscriptYSize, EndianBig);
				chunkData.Read(Compatibility.ySuperscriptXOffset, EndianBig);
				chunkData.Read(Compatibility.ySuperscriptYOffset, EndianBig);
				chunkData.Read(Compatibility.yStrikeoutPosition, EndianBig);
				chunkData.Read(Compatibility.sFamilyClass, EndianBig);

				// Parse PANROSE
				{
					TTFPanose& panrose = Compatibility.Panose;
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

					chunkData.Read(bFamilyType);
					chunkData.Read(bSerifStyle);
					chunkData.Read(bWeight);
					chunkData.Read(bProportion);
					chunkData.Read(bContrast);
					chunkData.Read(bStrokeVariation);
					chunkData.Read(bArmStyle);
					chunkData.Read(bLetterform);
					chunkData.Read(bMidline);
					chunkData.Read(bXHeight);

					panrose.FamilyType = ConvertTTFFamilyType(bFamilyType);
					panrose.SerifStyle = ConvertTTFSerifStyle(bSerifStyle);
					panrose.Weight = ConvertTTFWeight(bWeight);
					panrose.Proportion = ConvertTTFProportion(bProportion);
					panrose.Contrast = ConvertTTFContrast(bContrast);
					panrose.StrokeVariation = ConvertTTFStrokeVariatoon(bStrokeVariation);
					panrose.ArmStyle = ConvertTTFArmStyle(bArmStyle);
					panrose.Letterform = ConvertTTFLetterform(bLetterform);
					panrose.Midline = ConvertTTFMidline(bMidline);
					panrose.HeightX = ConvertTTFHeightX(bXHeight);
				}

				chunkData.Read(Compatibility.ulUnicodeRange[0], EndianBig);
				chunkData.Read(Compatibility.ulUnicodeRange[1], EndianBig);
				chunkData.Read(Compatibility.ulUnicodeRange[2], EndianBig);
				chunkData.Read(Compatibility.ulUnicodeRange[3], EndianBig);

				chunkData.Read(Compatibility.achVendID[0]);
				chunkData.Read(Compatibility.achVendID[1]);
				chunkData.Read(Compatibility.achVendID[2]);
				chunkData.Read(Compatibility.achVendID[3]);

				chunkData.Read(Compatibility.fsSelection, EndianBig);
				chunkData.Read(Compatibility.fsFirstCharIndex, EndianBig);
				chunkData.Read(Compatibility.fsLastCharIndex, EndianBig);

				if(Compatibility.Version > 0)
				{
					chunkData.Read(Compatibility.sTypoAscender, EndianBig);
					chunkData.Read(Compatibility.sTypoDescender, EndianBig);
					chunkData.Read(Compatibility.sTypoLineGap, EndianBig);
					chunkData.Read(Compatibility.usWinAscent, EndianBig);
					chunkData.Read(Compatibility.usWinDescent, EndianBig);
					chunkData.Read(Compatibility.ulCodePageRange1, EndianBig);
					chunkData.Read(Compatibility.ulCodePageRange2, EndianBig);
					chunkData.Read(Compatibility.sxHeight, EndianBig);
					chunkData.Read(Compatibility.sCapHeight, EndianBig);
					chunkData.Read(Compatibility.usDefaultChar, EndianBig);
					chunkData.Read(Compatibility.usBreakChar, EndianBig);
					chunkData.Read(Compatibility.usMaxContext, EndianBig);
					chunkData.Read(Compatibility.usLowerPointSize, EndianBig);
					chunkData.Read(Compatibility.usUpperPointSize, EndianBig);
				}

				break;
			}

			case TTFTableEntryType::ControlValue: // cvt
			{
				// FWORD[ n ] 	List of n values referenceable by instructions. n is the number of FWORD items that fit in the size of the table.
				break;
			}
			case TTFTableEntryType::GlyphNameAndPostScriptCompatibility: // post
			{
				chunkData.Read(PostScript.Version.Major, EndianBig);
				chunkData.Read(PostScript.Version.Minor, EndianLittle);

				PostScript.Version.Check();

				switch(PostScript.Version.Type)
				{
					case TTFVersionType::Invalid:
						break;

					case TTFVersionType::Version1Dot0:
						break;

					case TTFVersionType::Version2Dot0:
					{
						chunkData.Read(PostScript.NumberOfGlyphs, EndianBig);
						break;
					}
					case TTFVersionType::Version2Dot5:
					{
						chunkData.Read(PostScript.NumberOfGlyphs, EndianBig);
						break;
					}
					case TTFVersionType::Version3Dot0:
						break;

					default:
						printf("Illegal Version");
						break;
				}

				break;
			}
			case TTFTableEntryType::Kerning: // kern
			{
				chunkData.Read(Kerning.Version, EndianBig);
				chunkData.Read(Kerning.NumberOfSubtables, EndianBig);

				Kerning.KerningSubtableList = new TTFKerningSubtable[Kerning.NumberOfSubtables];

				for(size_t i = 0; i < Kerning.NumberOfSubtables; i++)
				{
					TTFKerningSubtable& kerningTable = Kerning.KerningSubtableList[i];

					unsigned short coverage = 0;

					chunkData.Read(kerningTable.Version, EndianBig);
					chunkData.Read(kerningTable.Length, EndianBig);
					chunkData.Read(coverage, EndianBig);

					kerningTable.ParseCoverageValue(coverage);

					switch(kerningTable.Version)
					{
						case 0:
						{
							TTFSubtableFormat0& subtableFormat = kerningTable.SubtableFormat0;

							chunkData.Read(subtableFormat.NumberOfPairs, EndianBig);
							chunkData.Read(subtableFormat.SearchRange, EndianBig);
							chunkData.Read(subtableFormat.EntrySelector, EndianBig);
							chunkData.Read(subtableFormat.RangeShift, EndianBig);

							subtableFormat.KerningPairList = new TTFKerningPair[subtableFormat.NumberOfPairs];

							for(size_t i = 0; i < subtableFormat.NumberOfPairs; i++)
							{
								TTFKerningPair& kerningPair = subtableFormat.KerningPairList[i];

								chunkData.Read(kerningPair.Left, EndianBig);
								chunkData.Read(kerningPair.Right, EndianBig);
								chunkData.Read(kerningPair.Value, EndianBig);
							}

							break;
						}
						case 2:
						{
							TTFSubtableFormat2& subtableFormat = kerningTable.SubtableFormat2;

							chunkData.Read(subtableFormat.RowWidth, EndianBig);
							chunkData.Read(subtableFormat.LeftClassOffset, EndianBig);
							chunkData.Read(subtableFormat.RightClassOffset, EndianBig);
							chunkData.Read(subtableFormat.KerningArrayOffset, EndianBig);

							break;
						}
					}
				}

				break;
			}
			case TTFTableEntryType::ControlValueProgram: // prep
			{
				// The name 'prep' is anachronistic (the table used to be known as the Pre Program table.)
				// unsigned char[N]
				break;
			}
			case TTFTableEntryType::GlyphOutline: // glyf
			{
				break;
			}
			case TTFTableEntryType::FontProgram: // fpgm
			{
				break;
			}
			//-----------------------------------------------------------------

			// Windows 
			case TTFTableEntryType::CharacterCodeMapping:
			{
				chunkData.Read(CharacterMapping.Version, EndianBig);
				chunkData.Read(CharacterMapping.NumberOfTables, EndianBig);

				CharacterMapping.EncodingRecordList = new EncodingRecord[CharacterMapping.NumberOfTables];

				for(size_t i = 0; i < CharacterMapping.NumberOfTables; i++)
				{
					EncodingRecord& encodingRecord = CharacterMapping.EncodingRecordList[i];

					unsigned short platformID;
					unsigned short encodingID;

					chunkData.Read(platformID, EndianBig);
					chunkData.Read(encodingID, EndianBig);
					chunkData.Read(encodingRecord.SubtableOffset, EndianBig);

					encodingRecord.Platform = ConvertPlatformID(platformID);
					encodingRecord.Encoding = ConvertEncodingID(encodingRecord.Platform, encodingID);
				}

				break;
			}
			case TTFTableEntryType::LinearThreshold:
			{
				chunkData.Read(LinearThreshold.Version, EndianBig);
				chunkData.Read(LinearThreshold.NumberOfGlyphs, EndianBig);

				LinearThreshold.PelsHeightList = Memory::Allocate<Byte__>(LinearThreshold.NumberOfGlyphs);

				chunkData.Read(LinearThreshold.PelsHeightList, LinearThreshold.NumberOfGlyphs);

				break;
			}
			case TTFTableEntryType::DigitalSignature:
			{
				Byte__* startPointer = chunkData.Data + chunkData.DataCursor;

				chunkData.Read(DigitalSignature.Version, EndianBig);
				chunkData.Read(DigitalSignature.NumberOfSignatures, EndianBig);
				chunkData.Read(DigitalSignature.Flags, EndianBig);

				DigitalSignature.SignatureRecordList = new TTFDigitalSignatureRecord[DigitalSignature.NumberOfSignatures];
				DigitalSignature.SignatureBlockList = new TTFDigitalSignatureBlock[DigitalSignature.NumberOfSignatures];

				for(size_t i = 0; i < DigitalSignature.NumberOfSignatures; i++)
				{
					TTFDigitalSignatureRecord& signatureRecord = DigitalSignature.SignatureRecordList[i];

					chunkData.Read(signatureRecord.Format, EndianBig);
					chunkData.Read(signatureRecord.Length, EndianBig);
					chunkData.Read(signatureRecord.SignatureBlockOffset, EndianBig);

					{
						ByteStream byteSteam(startPointer + signatureRecord.SignatureBlockOffset, signatureRecord.Length);
						TTFDigitalSignatureBlock& signatureBlock = DigitalSignature.SignatureBlockList[i];

						chunkData.Read(signatureBlock.Reserved1, EndianBig);
						chunkData.Read(signatureBlock.Reserved2, EndianBig);
						chunkData.Read(signatureBlock.SignatureLength, EndianBig);

						signatureBlock.Signature = (char*)malloc(signatureBlock.SignatureLength);

						chunkData.Read(signatureBlock.Signature, signatureBlock.SignatureLength);

						for(size_t w = 0; w < signatureBlock.SignatureLength - 2; w++)
						{
							if(signatureBlock.Signature[w] == 0)
							{
								signatureBlock.Signature[w] = '#';
							}
						}
					}
				}

				break;
			}
		}
	}

	return FileActionResult::Successful;
}

BF::FileActionResult BF::TTF::TTF::Save(const wchar_t* filePath)
{
    return FileActionResult::Successful;
}

BF::FileActionResult BF::TTF::TTF::ConvertTo(Font& font)
{
    return FileActionResult::Successful;
}

BF::FileActionResult BF::TTF::TTF::ConvertFrom(Font& font)
{
    return FileActionResult::Successful;
}