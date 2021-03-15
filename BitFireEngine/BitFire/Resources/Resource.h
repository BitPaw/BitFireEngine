#pragma once
#include "../Utility/ASCIIString.h"

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
		Is the resource currently loaded to the GPU?
		*/
		bool LoadedToGPU;

		/*
		Resource index. This Value shall be used as key for dictionarys. Faster lookup.
		*/
		unsigned int ID;

		/* 
		Value that represents how many dependencies this resource has.
		If the Value is '0' this resource shall be unloaded.		
		*/
		unsigned int SharedCounter;

		/*
		Path from where the resource was loaded from.
		Can be used to prevent double loading.
		*/
		ASCIIString FilePath;	
	};
}