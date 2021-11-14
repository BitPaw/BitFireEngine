#pragma once

#define ResourceNameSize 32u
#define ResourceFilePathSize 64u

#define ResourceIDStored 999

#define ResourceIDUndefined -1

#define ResourceIDLoading -2
#define ResourceIDLoaded -3
#define ResourceIDShared -5

#define ResourceIDFileNotFound -10
#define ResourceIDOutOfMemory -20
#define ResourceIDUnsuportedFormat -30

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

		// Name
		char Name[ResourceNameSize];

		/*
		Path from where the resource was loaded from.
		Can be used to prevent double loading.
		*/
		char FilePath[ResourceFilePathSize];

		void MarkAsLoading(const char* name, const char* filePath);

		void NameChange(const char* name);
		void FilePathChange(const char* filePath);

		bool IsLoaded() 
		{
			return ID == ResourceIDLoaded || ID == ResourceIDShared;
		}

		bool ShallBeCached()
		{
			return ID == ResourceIDLoaded;
		}
	};
}