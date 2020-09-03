#pragma once

#include "MaterialLibrary.h"

class MaterialLibraryLoader
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
	static MaterialLibrary LoadFromFile(const char* path);
};