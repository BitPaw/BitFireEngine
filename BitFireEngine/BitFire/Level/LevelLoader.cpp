#include "LevelLoader.h"

#include "../Resources/Model/ModelLoader.h"
#include "../System/GameSystem.h"
#include "../Resources/File/File.h"

void BF::LevelLoader::ParseModelFile(Model& model, AsciiString& line)
{
	List<AsciiString> lines;
	AsciiString path;
	AsciiString positionText;
	AsciiString rotationText;
	AsciiString scaleText;
	Position<float> position;
	Position<float> rotation;
	Position<float> scale;

	line.Splitt(' ', lines);

	// Get raw Data-------------------------
	path.Copy(lines[1]);
	positionText.Copy(lines[2]);
	rotationText.Copy(lines[3]);
	scaleText.Copy(lines[4]);
	
	positionText.Splitt('|', lines);

	position.Set
	(
		lines[0].ToFloat(),
		lines[1].ToFloat(),
		lines[2].ToFloat()
	);

	rotationText.Splitt('|', lines);

	rotation.Set
	(
		lines[0].ToFloat(),
		lines[1].ToFloat(),
		lines[2].ToFloat()
	);

	scaleText.Splitt('|', lines);

	scale.Set
	(
		lines[0].ToFloat(),
		lines[1].ToFloat(),
		lines[2].ToFloat()
	);
	//------------------------------------------------

	// Load Model----------------
	ModelLoader::LoadFromFile(path, model);
	//-------------------

	//--[Apply Data]-------------
	model.MoveTo(position);
	model.RotateTo(rotation);
	model.Scale(scale);
	//-----------------------
}

void BF::LevelLoader::ParseImageFile(Image& image, AsciiString& line)
{

}

void BF::LevelLoader::ParseSoundFile(Sound& sound, AsciiString& line)
{

}

void BF::LevelLoader::ParseFontFile(Font& font, AsciiString& line)
{

}

void BF::LevelLoader::ParseShaderFile(Shader& shader, AsciiString& line)
{

}

void BF::LevelLoader::ParseDialogFile(Dialog& dialog, AsciiString& line)
{

}

bool BF::LevelLoader::IsLevelFile(AsciiString& fileExtension)
{
	return fileExtension.CompareIgnoreCase("lev");
}

void BF::LevelLoader::LoadFromFile(Level& level, AsciiString& filePath)
{
	List<AsciiString> fileLines;
	File file(filePath);
	unsigned int modelCounter = 0;
	unsigned int imageCounter = 0;
	unsigned int soundCounter = 0;
	unsigned int fontCounter = 0;
	unsigned int shaderCounter = 0;
	unsigned int dialogCounter = 0;
	unsigned int amountOfLines;

	file.ReadAsLines(fileLines);

	amountOfLines = fileLines.Size();

	// Step I - Count objects
	for (unsigned int i = 0; i < amountOfLines; i++)
	{
		AsciiString& line = fileLines[i];
		char character = line.GetFirstNonEmpty();

		switch (character)
		{
		case _modelToken:
			modelCounter++;
			break;

		case _textureToken:
			imageCounter++;
			break;

		case _musicToken:
			soundCounter++;
			break;

		case _fontToken:
			fontCounter++;
			break;

		case _shaderToken:
			shaderCounter++;
			break;

		case _dialogToken:
			dialogCounter++;
			break;

		case _commentToken:
		case _emptyToken:
		default:
			// Do nothinf
			break;
		}
	}

	// Step II - Reserve space
	level.ModelList.ReSize(modelCounter);
	level.ImageList.ReSize(imageCounter);
	level.SoundList.ReSize(soundCounter);
	level.FontList.ReSize(fontCounter);
	level.ShaderList.ReSize(shaderCounter);
	level.DialogList.ReSize(dialogCounter);

	modelCounter = 0;
	imageCounter = 0;
	soundCounter = 0;
	fontCounter = 0;
	shaderCounter = 0;
	dialogCounter = 0;

	// Step II - Parse and Load
	for (unsigned int i = 0; i < amountOfLines; i++)
	{
		AsciiString& line = fileLines[i];
		char character = line.GetFirstNonEmpty();	

		switch (character)
		{
		case _modelToken:
			ParseModelFile(level.ModelList[modelCounter++], line);
			break;

		case _textureToken:
			ParseImageFile(level.ImageList[imageCounter++], line);
			break;

		case _musicToken:
			ParseSoundFile(level.SoundList[soundCounter++], line);
			break;

		case _fontToken:
			ParseFontFile(level.FontList[fontCounter++], line);
			break;

		case _shaderToken:
			ParseShaderFile(level.ShaderList[shaderCounter++], line);
			break;

		case _dialogToken:
			ParseDialogFile(level.DialogList[dialogCounter++], line);
			break;

		case _commentToken:
		case _emptyToken:
		default:
			// Do nothinf
			break;
		}
	}
}

void BF::LevelLoader::SaveFromFile(Level& level, AsciiString& filePath)
{

}

void BF::LevelLoader::PrintLevelInfo(Level& level, bool detailed)
{

}