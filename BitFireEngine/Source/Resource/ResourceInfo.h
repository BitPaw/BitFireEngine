#pragma once

#include <cwchar>

#define ResourceNameSize 64u
#define ResourceFilePathSize 64u

namespace BF
{
	struct ResourceInfo
	{
		public:
		// Name
		wchar_t Name[ResourceNameSize];

		// Path from where the resource was loaded from.
		// Can be used to prevent double loading.
		wchar_t FilePath[ResourceFilePathSize];

		ResourceInfo();

		void NameChange(const char* name);
		void NameChange(const wchar_t* name);
		void FilePathChange(const char* filePath);
		void FilePathChange(const wchar_t* filePath);
	};
}