#pragma once

#include "Level.h"

#include "../Utility/ASCIIString.h"
#include "../Resources/Font/Font.h"
#include "../Resources/Dialog/Dialog.h"

namespace BF
{
	class LevelLoader
	{
	private:
		static const char _modelToken = 'O';
		static const char _textureToken = 'T';
		static const char _musicToken = 'M';
		static const char _fontToken = 'F';
		static const char _shaderToken = 'S';
		static const char _dialogToken = 'D';
		static const char _emptyToken = ' ';
		static const char _commentToken = '#';

		static void ParseModelFile(Model& model, ASCIIString& line);
		static void ParseImageFile(Image& image, ASCIIString& line);
		static void ParseSoundFile(Sound& sound, ASCIIString& line);
		static void ParseFontFile(Font& font, ASCIIString& line);
		static void ParseShaderFile(Shader& shader, ASCIIString& line);
		static void ParseDialogFile(Dialog& dialog, ASCIIString& line);

	public:
		static bool IsLevelFile(ASCIIString& fileExtension);

		static void LoadFromFile(Level& level, ASCIIString& filePath);
		static void SaveFromFile(Level& level, ASCIIString& filePath);
		static void PrintLevelInfo(Level& level, bool detailed);
	};
}