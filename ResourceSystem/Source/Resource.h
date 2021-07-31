#pragma once

#include "Container/AsciiString.h"

namespace BF
{
	/*
	Base class to all resources that can be loaded/saved
	that will be used in any way with the graphics card.
	*/
	struct Resource
	{
		protected:
		Resource(); // Prevent that this can be an instance on its own (abstract class)

		public:
		/*
		Resource index. This Value shall be used as key for dictionarys. Faster lookup.
		*/
		unsigned int ID;

		/*
		Path from where the resource was loaded from.
		Can be used to prevent double loading.
		*/
		char FilePath[255];

		void FilePathSet(const char* filePath)
		{
			strcpy_s(FilePath, 255, filePath);
		}
	};
}