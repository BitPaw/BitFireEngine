#include "MP3.h"

#include "MP3Header.h"
#include "MPEGAudioTag.h"

#include <File/File.h>

#include <Media/ID3/ID3.h>

BF::FileActionResult BF::MP3::Load(const char* filePath)
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

BF::FileActionResult BF::MP3::Load(const wchar_t* filePath)
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

BF::FileActionResult BF::MP3::Load(const unsigned char* fileData, const size_t fileDataSize)
{
	ByteStream dataStream(fileData, fileDataSize);

	ID3 id3;

	{
		const Byte* dataPosition = dataStream.CursorCurrentAdress();
		const size_t dataSize = dataStream.ReadPossibleSize();
		const size_t parsedBytes = id3.Parse(dataPosition, dataSize);

		dataStream.CursorAdvance(parsedBytes);	
	}

	while(!dataStream.IsAtEnd())
	{		
		MP3Header mp3Header;

		// Parse header
		{
			const Byte* dataPosition = dataStream.CursorCurrentAdress();
			const size_t dataSize = dataStream.ReadPossibleSize();
			const size_t parsedBytes = mp3Header.Parse(dataPosition, dataSize);
			const bool parsingSucessful = parsedBytes != 0;

			if(parsingSucessful)
			{
				dataStream.CursorAdvance(parsedBytes);

#if 0
				printf
				(
					"[MP3][Frame] Bitrate : %6i | SampleRate : %5i | FrameLength : %5i |\n",
					mp3Header.BitRate,
					mp3Header.SampleRate,
					mp3Header.FrameLength
				);
#endif

				dataStream.CursorAdvance(mp3Header.FrameLength);
			}
			else
			{
				const bool tagDetected = dataStream.ReadAndCompare("TAG", 3u);

				if(tagDetected)
				{
					const size_t offset = dataStream.ReadPossibleSize();

					// I currently dont know what this is.
					// But it comes at the end of the file.. so i am finished?

					dataStream.CursorAdvance(offset);
				}
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