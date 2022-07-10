#pragma once

#include <cstddef>

#include "SBPDataPackage.h"

#include <File/FilePath.h>
#include <Text/TextFormat.h>

namespace BF
{
	enum class SBPDataPackageFileMode
	{
		Invalid,

		Create, // Create a file and upload data to it
		Delete, // Remove a file
		Update, // override data from the file
		Move, // Move the file form one place to another
		Copy, // Copy a file
		Rename // rename the file, no not change data
	};

	struct SBPDataPackageFile : public SBPDataPackage
	{
		SBPDataPackageFileMode Mode;
			
		TextFormat FilePathSourceFormat;
		size_t FilePathSourceSize;
		union
		{
			char FilePathSourceA[PathMaxSize];
			wchar_t FilePathSourceW[PathMaxSize];
		};

		TextFormat FilePathTargetFormat;
		size_t FilePathTargetSize;
		union
		{
			char FilePathTargetA[PathMaxSize];
			wchar_t FilePathTargetW[PathMaxSize];
		};		

		size_t FileSize; // HAs to be 8 Byte__!

		// S:N T:N => Invalid
		// S:N T:Y => Create
		// S:Y T:N => Delete
		// S:Y T:Y => Copy

		void Fill(const SBPDataPackageFileMode mode, const char* source, const char* target);

		virtual size_t Parse(const void* inputData, const size_t inputDataSize) override;
		virtual size_t Serialize(void* outputData, const size_t outputDataSize) const override;
	};
}