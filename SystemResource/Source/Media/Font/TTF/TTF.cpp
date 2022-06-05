#include "TTF.h"

#include "TTFTableEntry.h"
#include "Chunks/TTFOffsetTable.h"
#include "Chunks/OS2/Panose/TTFPanose.h"

#include <File/File.h>
#include <Hardware/Memory/Memory.h>

#include <cassert>

BF::FileActionResult BF::TTF::Load(const char* filePath)
{
	File file;

	{
		const FileActionResult fileLoadingResult = file.MapToVirtualMemory(filePath);
		const bool sucessful = fileLoadingResult == FileActionResult::Successful;

		if(!sucessful)
		{
			return fileLoadingResult;
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
		const FileActionResult fileLoadingResult = file.MapToVirtualMemory(filePath);
		const bool sucessful = fileLoadingResult == FileActionResult::Successful;

		if(!sucessful)
		{
			return fileLoadingResult;
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

	dataStream.Read(offsetTable.Version.Major, Endian::Big);
	dataStream.Read(offsetTable.Version.Minor, Endian::Big);
	dataStream.Read(offsetTable.NumberOfTables, Endian::Big);
	dataStream.Read(offsetTable.SearchRange, Endian::Big);
	dataStream.Read(offsetTable.EntrySelctor, Endian::Big);
	dataStream.Read(offsetTable.RangeShift, Endian::Big);

	for(size_t i = 0; i < offsetTable.NumberOfTables; i++)
	{
		TTFTableEntry tableEntry;
		ByteStream chunkData;

		dataStream.Read(tableEntry.TypeRaw, 4u);
		dataStream.Read(tableEntry.CheckSum, Endian::Big);
		dataStream.Read(tableEntry.Offset, Endian::Big);
		dataStream.Read(tableEntry.Length, Endian::Big);

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
				chunkData.Read(Header.Version.Major, Endian::Big);
				chunkData.Read(Header.Version.Minor, Endian::Little);
				chunkData.Read(Header.Revision.Major, Endian::Big);
				chunkData.Read(Header.Revision.Minor, Endian::Little);

				chunkData.Read(Header.CheckSumAdjustment, Endian::Big);
				chunkData.Read(Header.MagicNumber, Endian::Big);
				chunkData.Read(Header.Flags, Endian::Big);
				chunkData.Read(Header.UnitsPerEM, Endian::Big);
				chunkData.Read(Header.Created, Endian::Big);
				chunkData.Read(Header.Modified, Endian::Big);
				chunkData.Read(Header.Minimum[0], Endian::Big);
				chunkData.Read(Header.Minimum[1], Endian::Big);
				chunkData.Read(Header.Maximum[0], Endian::Big);
				chunkData.Read(Header.Maximum[1], Endian::Big);
				chunkData.Read(Header.MacStyle, Endian::Big);
				chunkData.Read(Header.LowestRecPpem, Endian::Big);
				chunkData.Read(Header.FontDirectionHint, Endian::Big);
				chunkData.Read(Header.IndexToLocFormat, Endian::Big);
				chunkData.Read(Header.GlyphDataFormat, Endian::Big);

				break;
			}
			case TTFTableEntryType::HorizontalHeader:
			{
				chunkData.Read(HorizontalHeader.Version.Major, Endian::Big);
				chunkData.Read(HorizontalHeader.Version.Minor, Endian::Little);
				chunkData.Read(HorizontalHeader.Ascender, Endian::Big);
				chunkData.Read(HorizontalHeader.Descender, Endian::Big);
				chunkData.Read(HorizontalHeader.LineGap, Endian::Big);
				chunkData.Read(HorizontalHeader.AdvanceWidthMaximum, Endian::Big);
				chunkData.Read(HorizontalHeader.MinimumLeftSideBearing, Endian::Big);
				chunkData.Read(HorizontalHeader.MinimumRightSideBearing, Endian::Big);
				chunkData.Read(HorizontalHeader.MaximalExtendX, Endian::Big);
				chunkData.Read(HorizontalHeader.CaretSlopeRun, Endian::Big);
				chunkData.Read(HorizontalHeader.CaretSlopeRise, Endian::Big);
				chunkData.Read(HorizontalHeader.Reserved, 10u);
				chunkData.Read(HorizontalHeader.MetricDataFormat, Endian::Big);
				chunkData.Read(HorizontalHeader.NumberOfHorizontalMetrics, Endian::Big);

				break;
			}
			case TTFTableEntryType::MaximumProfile:
			{
				chunkData.Read(MaximumProfile.Version.Major, Endian::Big);
				chunkData.Read(MaximumProfile.Version.Minor, Endian::Little);

				bool trustedTypeFonts = MaximumProfile.Version.Major == 1 && MaximumProfile.Version.Minor == 0;
				bool openTypeFonts = MaximumProfile.Version.Major == 0 && MaximumProfile.Version.Minor == 5;
				bool validVersion = trustedTypeFonts || openTypeFonts;

				chunkData.Read(MaximumProfile.NumberOfGlyphs, Endian::Big);

				assert(validVersion);

				if(trustedTypeFonts && !openTypeFonts)
				{
					chunkData.Read(MaximumProfile.PointsMaximal, Endian::Big);
					chunkData.Read(MaximumProfile.ContoursMaximal, Endian::Big);
					chunkData.Read(MaximumProfile.ComponentPointsMaximal, Endian::Big);
					chunkData.Read(MaximumProfile.ComponentContoursMaximal, Endian::Big);
					chunkData.Read(MaximumProfile.ZonesMaximal, Endian::Big);
					chunkData.Read(MaximumProfile.TwilightPointsMaximal, Endian::Big);
					chunkData.Read(MaximumProfile.StorageMaximal, Endian::Big);
					chunkData.Read(MaximumProfile.FunctionDefsMaximal, Endian::Big);
					chunkData.Read(MaximumProfile.InstructionDefsMaximal, Endian::Big);
					chunkData.Read(MaximumProfile.StackElementsMaximal, Endian::Big);
					chunkData.Read(MaximumProfile.SizeOfInstructionsMaximal, Endian::Big);
					chunkData.Read(MaximumProfile.ComponentElementsMaximal, Endian::Big);
					chunkData.Read(MaximumProfile.ComponentDepthMaximal, Endian::Big);
				}

				break;
			}
			case TTFTableEntryType::Compatibility:
			{
				chunkData.Read(Compatibility.Version, Endian::Big);
				chunkData.Read(Compatibility.xAvgCharWidth, Endian::Big);
				chunkData.Read(Compatibility.usWeightClass, Endian::Big);
				chunkData.Read(Compatibility.usWidthClass, Endian::Big);
				chunkData.Read(Compatibility.fsType, Endian::Big);
				chunkData.Read(Compatibility.ySubscriptXSize, Endian::Big);
				chunkData.Read(Compatibility.ySubscriptYSize, Endian::Big);
				chunkData.Read(Compatibility.ySubscriptXOffset, Endian::Big);
				chunkData.Read(Compatibility.ySubscriptYOffset, Endian::Big);
				chunkData.Read(Compatibility.ySuperscriptXSize, Endian::Big);
				chunkData.Read(Compatibility.ySuperscriptYSize, Endian::Big);
				chunkData.Read(Compatibility.ySuperscriptXOffset, Endian::Big);
				chunkData.Read(Compatibility.ySuperscriptYOffset, Endian::Big);
				chunkData.Read(Compatibility.yStrikeoutPosition, Endian::Big);
				chunkData.Read(Compatibility.sFamilyClass, Endian::Big);

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

				chunkData.Read(Compatibility.ulUnicodeRange[0], Endian::Big);
				chunkData.Read(Compatibility.ulUnicodeRange[1], Endian::Big);
				chunkData.Read(Compatibility.ulUnicodeRange[2], Endian::Big);
				chunkData.Read(Compatibility.ulUnicodeRange[3], Endian::Big);

				chunkData.Read(Compatibility.achVendID[0]);
				chunkData.Read(Compatibility.achVendID[1]);
				chunkData.Read(Compatibility.achVendID[2]);
				chunkData.Read(Compatibility.achVendID[3]);

				chunkData.Read(Compatibility.fsSelection, Endian::Big);
				chunkData.Read(Compatibility.fsFirstCharIndex, Endian::Big);
				chunkData.Read(Compatibility.fsLastCharIndex, Endian::Big);

				if(Compatibility.Version > 0)
				{
					chunkData.Read(Compatibility.sTypoAscender, Endian::Big);
					chunkData.Read(Compatibility.sTypoDescender, Endian::Big);
					chunkData.Read(Compatibility.sTypoLineGap, Endian::Big);
					chunkData.Read(Compatibility.usWinAscent, Endian::Big);
					chunkData.Read(Compatibility.usWinDescent, Endian::Big);
					chunkData.Read(Compatibility.ulCodePageRange1, Endian::Big);
					chunkData.Read(Compatibility.ulCodePageRange2, Endian::Big);
					chunkData.Read(Compatibility.sxHeight, Endian::Big);
					chunkData.Read(Compatibility.sCapHeight, Endian::Big);
					chunkData.Read(Compatibility.usDefaultChar, Endian::Big);
					chunkData.Read(Compatibility.usBreakChar, Endian::Big);
					chunkData.Read(Compatibility.usMaxContext, Endian::Big);
					chunkData.Read(Compatibility.usLowerPointSize, Endian::Big);
					chunkData.Read(Compatibility.usUpperPointSize, Endian::Big);
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
				chunkData.Read(PostScript.Version.Major, Endian::Big);
				chunkData.Read(PostScript.Version.Minor, Endian::Little);

				PostScript.Version.Check();

				switch(PostScript.Version.Type)
				{
					case TTFVersionType::Invalid:
						break;

					case TTFVersionType::Version1Dot0:
						break;

					case TTFVersionType::Version2Dot0:
					{
						chunkData.Read(PostScript.NumberOfGlyphs, Endian::Big);
						break;
					}
					case TTFVersionType::Version2Dot5:
					{
						chunkData.Read(PostScript.NumberOfGlyphs, Endian::Big);
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
				chunkData.Read(Kerning.Version, Endian::Big);
				chunkData.Read(Kerning.NumberOfSubtables, Endian::Big);

				Kerning.KerningSubtableList = new TTFKerningSubtable[Kerning.NumberOfSubtables];

				for(size_t i = 0; i < Kerning.NumberOfSubtables; i++)
				{
					TTFKerningSubtable& kerningTable = Kerning.KerningSubtableList[i];

					unsigned short coverage = 0;

					chunkData.Read(kerningTable.Version, Endian::Big);
					chunkData.Read(kerningTable.Length, Endian::Big);
					chunkData.Read(coverage, Endian::Big);

					kerningTable.ParseCoverageValue(coverage);

					switch(kerningTable.Version)
					{
						case 0:
						{
							TTFSubtableFormat0& subtableFormat = kerningTable.SubtableFormat0;

							chunkData.Read(subtableFormat.NumberOfPairs, Endian::Big);
							chunkData.Read(subtableFormat.SearchRange, Endian::Big);
							chunkData.Read(subtableFormat.EntrySelector, Endian::Big);
							chunkData.Read(subtableFormat.RangeShift, Endian::Big);

							subtableFormat.KerningPairList = new TTFKerningPair[subtableFormat.NumberOfPairs];

							for(size_t i = 0; i < subtableFormat.NumberOfPairs; i++)
							{
								TTFKerningPair& kerningPair = subtableFormat.KerningPairList[i];

								chunkData.Read(kerningPair.Left, Endian::Big);
								chunkData.Read(kerningPair.Right, Endian::Big);
								chunkData.Read(kerningPair.Value, Endian::Big);
							}

							break;
						}
						case 2:
						{
							TTFSubtableFormat2& subtableFormat = kerningTable.SubtableFormat2;

							chunkData.Read(subtableFormat.RowWidth, Endian::Big);
							chunkData.Read(subtableFormat.LeftClassOffset, Endian::Big);
							chunkData.Read(subtableFormat.RightClassOffset, Endian::Big);
							chunkData.Read(subtableFormat.KerningArrayOffset, Endian::Big);

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
				chunkData.Read(CharacterMapping.Version, Endian::Big);
				chunkData.Read(CharacterMapping.NumberOfTables, Endian::Big);

				CharacterMapping.EncodingRecordList = new EncodingRecord[CharacterMapping.NumberOfTables];

				for(size_t i = 0; i < CharacterMapping.NumberOfTables; i++)
				{
					EncodingRecord& encodingRecord = CharacterMapping.EncodingRecordList[i];

					unsigned short platformID;
					unsigned short encodingID;

					chunkData.Read(platformID, Endian::Big);
					chunkData.Read(encodingID, Endian::Big);
					chunkData.Read(encodingRecord.SubtableOffset, Endian::Big);

					encodingRecord.Platform = ConvertPlatformID(platformID);
					encodingRecord.Encoding = ConvertEncodingID(encodingRecord.Platform, encodingID);
				}

				break;
			}
			case TTFTableEntryType::LinearThreshold:
			{
				chunkData.Read(LinearThreshold.Version, Endian::Big);
				chunkData.Read(LinearThreshold.NumberOfGlyphs, Endian::Big);

				LinearThreshold.PelsHeightList = Memory::Allocate<Byte>(LinearThreshold.NumberOfGlyphs);

				chunkData.Read(LinearThreshold.PelsHeightList, LinearThreshold.NumberOfGlyphs);

				break;
			}
			case TTFTableEntryType::DigitalSignature:
			{
				Byte* startPointer = chunkData.Data + chunkData.DataCursorPosition;

				chunkData.Read(DigitalSignature.Version, Endian::Big);
				chunkData.Read(DigitalSignature.NumberOfSignatures, Endian::Big);
				chunkData.Read(DigitalSignature.Flags, Endian::Big);

				DigitalSignature.SignatureRecordList = new TTFDigitalSignatureRecord[DigitalSignature.NumberOfSignatures];
				DigitalSignature.SignatureBlockList = new TTFDigitalSignatureBlock[DigitalSignature.NumberOfSignatures];

				for(size_t i = 0; i < DigitalSignature.NumberOfSignatures; i++)
				{
					TTFDigitalSignatureRecord& signatureRecord = DigitalSignature.SignatureRecordList[i];

					chunkData.Read(signatureRecord.Format, Endian::Big);
					chunkData.Read(signatureRecord.Length, Endian::Big);
					chunkData.Read(signatureRecord.SignatureBlockOffset, Endian::Big);

					{
						ByteStream byteSteam(startPointer + signatureRecord.SignatureBlockOffset, signatureRecord.Length);
						TTFDigitalSignatureBlock& signatureBlock = DigitalSignature.SignatureBlockList[i];

						chunkData.Read(signatureBlock.Reserved1, Endian::Big);
						chunkData.Read(signatureBlock.Reserved2, Endian::Big);
						chunkData.Read(signatureBlock.SignatureLength, Endian::Big);

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