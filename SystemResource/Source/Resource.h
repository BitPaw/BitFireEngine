#pragma once

#define ResourceNameSize 30u
#define ResourceFilePathSize 60u

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