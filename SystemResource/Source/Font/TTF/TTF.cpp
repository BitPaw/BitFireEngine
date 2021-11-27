#include "TTF.h"

#include "TTFTableEntry.h"
#include "Chunks/TTFOffsetTable.h"
#include "../../File/FileStream.h"

#include <cassert>

BF::FileActionResult BF::TTF::Load(const char* filePath)
{
	FileStream file;
	FileActionResult fileActionResult = file.ReadFromDisk(filePath);

	if (fileActionResult != FileActionResult::Successful)
	{
		return fileActionResult;
	}

	TTFOffsetTable offsetTable;

	file.Read(offsetTable.Version.Major, Endian::Big);
	file.Read(offsetTable.Version.Minor, Endian::Big);
	file.Read(offsetTable.NumberOfTables, Endian::Big);
	file.Read(offsetTable.SearchRange, Endian::Big);
	file.Read(offsetTable.EntrySelctor, Endian::Big);
	file.Read(offsetTable.RangeShift, Endian::Big);

	for (size_t i = 0; i < offsetTable.NumberOfTables; i++)
	{
		TTFTableEntry tableEntry;
		ByteStream chunkData;

		file.Read(tableEntry.TypeRaw, 4u);
		file.Read(tableEntry.CheckSum, Endian::Big);
		file.Read(tableEntry.Offset, Endian::Big);
		file.Read(tableEntry.Length, Endian::Big);

		tableEntry.Type = ConvertTTFTableEntryType(tableEntry.TypeRaw);

		chunkData.DataSet(file.Data + tableEntry.Offset, tableEntry.Length);

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

		switch (tableEntry.Type)
		{
			case BF::TTFTableEntryType::DigitalSignature:
			{
				Byte* startPointer = chunkData.Data + chunkData.DataCursorPosition;

				chunkData.Read(DigitalSignature.Version, Endian::Big);
				chunkData.Read(DigitalSignature.NumberOfSignatures, Endian::Big);
				chunkData.Read(DigitalSignature.Flags, Endian::Big);
				
				DigitalSignature.SignatureRecordList = new TTFDigitalSignatureRecord[DigitalSignature.NumberOfSignatures];
				DigitalSignature.SignatureBlockList = new TTFDigitalSignatureBlock[DigitalSignature.NumberOfSignatures];

				for (size_t i = 0; i < DigitalSignature.NumberOfSignatures; i++)
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

						for (size_t w = 0; w < signatureBlock.SignatureLength-2; w++)
						{
							if (signatureBlock.Signature[w] == 0)
							{
								signatureBlock.Signature[w] = '#';
							}
						}
					}	
				}

				break;
			}
			case BF::TTFTableEntryType::FontHeader:
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
			case BF::TTFTableEntryType::HorizontalHeader:
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
			case BF::TTFTableEntryType::MaximumProfile:
			{
				chunkData.Read(MaximumProfile.Version.Major, Endian::Big);
				chunkData.Read(MaximumProfile.Version.Minor, Endian::Little);

				bool trustedTypeFonts = MaximumProfile.Version.Major == 1 && MaximumProfile.Version.Minor == 0;
				bool openTypeFonts = MaximumProfile.Version.Major == 0 && MaximumProfile.Version.Minor == 5;
				bool validVersion = trustedTypeFonts || openTypeFonts;

				chunkData.Read(MaximumProfile.NumberOfGlyphs, Endian::Big);

				assert(validVersion);

				if (trustedTypeFonts && !openTypeFonts)
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
			case BF::TTFTableEntryType::Compatibility:
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

				if (Compatibility.Version > 0)
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
		}
	}	

    return FileActionResult::Successful;
}

BF::FileActionResult BF::TTF::Save(const char* filePath)
{
    return FileActionResult::Successful;
}

BF::FileActionResult BF::TTF::ConvertTo(Font& font)
{
    return FileActionResult::Successful;
}

BF::FileActionResult BF::TTF::ConvertFrom(Font& font)
{
    return FileActionResult::Successful;
}