#pragma once

#ifndef Byte
#define Byte unsigned char
#endif

#define ResourceNameSize 64u
#define ResourceFilePathSize 64u

#define ResourceIDStored 999

#define ResourceIDUndefined (unsigned int)-1

#define ResourceIDLoading (unsigned int)-2
#define ResourceIDLoaded (unsigned int)-3
#define ResourceIDShared (unsigned int)-5

#define ResourceIDFileNotFound (unsigned int)-10
#define ResourceIDOutOfMemory (unsigned int)-20
#define ResourceIDUnsuportedFormat (unsigned int)-30

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

		virtual size_t FullSizeInMemory()
		{
			return sizeof(Resource);
		}
	};
}