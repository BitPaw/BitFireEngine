#pragma once

#define ResourceNameSize 30u
#define ResourceFilePathSize 60u

#define ResourceIDUndefined -1
#define ResourceIDFileNotFound -2
#define ResourceIDCurrentlyLoading -3
#define ResourceIDReadyToBeCached -4
#define ResourceIDReadyToUpload -6
#define ResourceIDUnused -5

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
	};
}