#pragma once

#include "MTL.h"
#include "../../../../IO/File/TextFile.h"
#include "../../../../IO/File/FileLoader.h"
#include "../../../../Utility/List.hpp"

namespace BF
{
	class MTLLoader
	{
	private:
		static const char _newMaterialCharacter = 'n';

		static const char _colorCharacter = 'K';
		static const char _ambientCharacter = 'a';
		static const char _diffuseCharacter = 'd';
		static const char _specularCharacter = 's';
		//static const char _newMaterialCharacter = 'e';

		//static const char _newMaterialCharacter = 'N';
		static const char _weightCharacter = 's';
		//static const char _newMaterialCharacter = 'i';

	public:
		static MTL* LoadFromFile(ASCIIString& filePath);
	};
}