#include "MP3.h"

#include "MP3Header.h"
#include "MPEGAudioTag.h"

#include <File/File.h>

#include <Media/ID3/ID3.h>
#include <Media/LAME/LAME.h>
#include <Media/XingInfo/XingInfo.h>

BF::FileActionResult BF::MP3::Load(const char* filePath)
{
	File file;

	{
		const FileActionResult fileLoadingResult = file.MapToVirtualMemory(filePath, MemoryProtectionMode::ReadOnly);
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

BF::FileActionResult BF::MP3::Load(const wchar_t* filePath)
{
	File file;

	{
		const FileActionResult fileLoadingResult = file.MapToVirtualMemory(filePath, MemoryProtectionMode::ReadOnly);
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

BF::FileActionResult BF::MP3::Load(const unsigned char* fileData, const size_t fileDataSize)
{
	ByteStream dataStream(fileData, fileDataSize);

	ID3 id3;

	{
		const Byte__* dataPosition = dataStream.CursorCurrentAdress();
		const size_t dataSize = dataStream.ReadPossibleSize();
		const size_t parsedBytes = id3.Parse(dataPosition, dataSize);

		dataStream.CursorAdvance(parsedBytes);	
	}

	while(!dataStream.IsAtEnd())
	{
		MP3Header mp3Header;
		XingInfo xingInfo;

		size_t cursorPositionPredict = 0;

		// Parse mp3
		{
			const Byte__* dataPosition = dataStream.CursorCurrentAdress();
			const size_t dataSize = dataStream.ReadPossibleSize();
			const size_t parsedBytes = mp3Header.Parse(dataPosition, dataSize);

			if(!parsedBytes)
			{
				return FileActionResult::FormatNotAsExpected;
			}			

			dataStream.CursorAdvance(parsedBytes);		

			cursorPositionPredict = dataStream.DataCursorPosition + mp3Header.FrameLength;

			dataStream.CursorAdvance(32u);

#if 1
			printf
			(
				"[MP3][Frame] Bitrate : %6i | SampleRate : %5i | FrameLength : %5i |\n",
				mp3Header.BitRate,
				mp3Header.SampleRate,
				mp3Header.FrameLength
			);
#endif	
		}	

		// info header
		{
			const Byte__* dataPosition = dataStream.CursorCurrentAdress();
			const size_t dataSize = dataStream.ReadPossibleSize();
			const size_t parsedBytes = xingInfo.Parse(dataPosition, dataSize);

			dataStream.CursorAdvance(parsedBytes);

			if(parsedBytes)
			{
#if 1
				printf
				(
					"[MP3][Info] Number of Frames : %6i | %6i Bytes |\n",
					xingInfo.NumberOfFrames,
					xingInfo.SizeInBytes
				);
#endif	
			}
		}

		// LACA??
		{
			const char tag[] = { 'L','a', 'v', 'c' };
			const size_t tagSize = sizeof(tag);
			const bool isTag = dataStream.ReadAndCompare(tag, tagSize);

			if(isTag)
			{
#if 1
				printf
				(
					"[MP3][???] Lavc chunk... what is that? |\n"
				);
#endif	

				dataStream.CursorAdvance(257u);
				continue; // After this header there is a MP3 header next, so parse it.
			}
			else
			{
				dataStream.CursorRewind(tagSize);
			}
		}
	

		{
			LAME lame;

			const Byte__* dataPosition = dataStream.CursorCurrentAdress();
			const size_t dataSize = cursorPositionPredict - dataStream.DataCursorPosition;
			const size_t parsedBytes = lame.Parse(dataPosition, dataSize);

			dataStream.CursorAdvance(parsedBytes);

			if(parsedBytes)
			{
#if 1
				printf
				(
					"[MP3][LAME] Chunk |\n"
				);
#endif	
			}
		}


		{
			const bool tagDetected = dataStream.ReadAndCompare("TAG", 3u);

			if(tagDetected)
			{
				const size_t offset = dataStream.ReadPossibleSize();

				// I currently dont know what this is.
				// But it comes at the end of the file.. so i am finished?

				dataStream.CursorAdvance(offset);
			}
			else
			{
				dataStream.CursorRewind(3);
			}
		}

		// Check if reader is still alligned
		{
			const bool isAlligned = cursorPositionPredict == dataStream.DataCursorPosition;

			if(!isAlligned)
			{
				int offset = cursorPositionPredict - dataStream.DataCursorPosition;

				printf("[MP3] detected failed allignment! Off by : %i Bytes\n", offset);

				dataStream.DataCursorPosition = cursorPositionPredict;
				//dataStream.CursorAdvance(mp3Header.FrameLength);
			}		
		}
	}

	return FileActionResult::Successful;
}

BF::FileActionResult BF::MP3::Save(const wchar_t* filePath)
{
	return BF::FileActionResult::Successful;
}

BF::FileActionResult BF::MP3::ConvertTo(Sound& sound)
{
	return BF::FileActionResult::Successful;
}

BF::FileActionResult BF::MP3::ConvertFrom(Sound& sound)
{
	return BF::FileActionResult::Successful;
}