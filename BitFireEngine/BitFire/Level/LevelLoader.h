#pragma once

#include "Level.h"

#include "../Utility/AsciiString.h"
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

		static void ParseModelFile(Model& model, AsciiString& line);
		static void ParseImageFile(Image& image, AsciiString& line);
		static void ParseSoundFile(Sound& sound, AsciiString& line);
		static void ParseFontFile(Font& font, AsciiString& line);
		static void ParseShaderFile(Shader& shader, AsciiString& line);
		static void ParseDialogFile(Dialog& dialog, AsciiString& line);

	public:
		static bool IsLevelFile(AsciiString& fileExtension);

		static void LoadFromFile(Level& level, AsciiString& filePath);
		static void SaveFromFile(Level& level, AsciiString& filePath);
		static void PrintLevelInfo(Level& level, bool detailed);
	};
}