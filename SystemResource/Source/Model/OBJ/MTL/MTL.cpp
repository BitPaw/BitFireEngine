#include "MTL.h"

#include <File/File.h>
#include <Text/Text.h>

BF::MTL::MTL()
{
	MaterialListSize = 0;
	MaterialList = 0;
}

BF::MTL::~MTL()
{
	free(MaterialList);
}

BF::MTLLineType BF::MTL::PeekLine(const char* data) const
{
	const unsigned short tagID = MakeShort(data[0], data[1]);

	switch(tagID)
	{
		case MakeShort('m', 'a'): return MTLLineType::Texture;
		case MakeShort('n', 'e'): return MTLLineType::Name;
		case MakeShort('N', 's'): return MTLLineType::Weight;
		case MakeShort('N', 'i'): return MTLLineType::Density;		 
		case MakeShort('K', 'a'): return MTLLineType::Ambient;
		case MakeShort('K', 'd'): return MTLLineType::Diffuse;
		case MakeShort('K', 's'): return MTLLineType::Specular;
		case MakeShort('K', 'e'): return MTLLineType::Emission;
		case MakeShort('d', ' '): return MTLLineType::Dissolved;
		case MakeShort('i', 'l'): return MTLLineType::Illumination;
		default: 
			return MTLLineType::Invalid;
	}	
}

BF::FileActionResult BF::MTL::Load(const char* filePath)
{
	File file;

	{
		const FileActionResult fileLoadingResult = file.MapToVirtualMemory(filePath, MemoryProtectionMode::ReadOnly);
		const bool sucessful = fileLoadingResult == FileActionResult::Successful;

		if(!sucessful)
		{
			return fileLoadingResult;
		}
	}

	{
		const FileActionResult fileParsingResult = Load(file.Data, file.DataSize);

		return fileParsingResult;
	}
}

BF::FileActionResult BF::MTL::Load(const wchar_t* filePath)
{
	File file;

	{
		const FileActionResult fileLoadingResult = file.MapToVirtualMemory(filePath, MemoryProtectionMode::ReadOnly);
		const bool sucessful = fileLoadingResult == FileActionResult::Successful;

		if(!sucessful)
		{
			return fileLoadingResult;
		}
	}

	{
		const FileActionResult fileParsingResult = Load(file.Data, file.DataSize);

		return fileParsingResult;
	}
}

BF::FileActionResult BF::MTL::Load(const unsigned char* data, const size_t dataSize)
{
	ByteStream byteStream(data, dataSize);

	// Count How many materials are needed
	{
		size_t materialCounter = 0;

		do
		{
			const Byte* currentLine = byteStream.CursorCurrentAdress();
			const bool isNewMaterialUsed = *currentLine == 'n';

			if(isNewMaterialUsed)
			{
				++materialCounter;
			}
		}
		while(byteStream.SkipLine());
				
		MaterialListSize = materialCounter;
		MaterialList = new MTLMaterial[materialCounter];

		byteStream.CursorToBeginning();
	}

	// Raw Parse
	MTLMaterial* material = nullptr; // current material, has to be here, its state dependend
	size_t materialIndex = 0;

	do
	{
		const char* currentLine = (char*)byteStream.CursorCurrentAdress();
		const MTLLineType lineType = PeekLine(currentLine);

		// Skip forst element
		byteStream.SkipBlock();

		const char* dataPoint = (char*)byteStream.CursorCurrentAdress();
		const size_t maxSize = byteStream.ReadPossibleSize();
		const size_t lineSize = Text::LengthUntil(dataPoint, maxSize, '\n');

		switch(lineType)
		{
			default:
			case BF::MTLLineType::Invalid:
				// Do nothing
				break;

			case BF::MTLLineType::Name:
			{
				material = &MaterialList[materialIndex++];

				const char internalText[] = "<internal>";
				const size_t internalTextSize = sizeof(internalText);

				Text::Copy(internalText, internalTextSize, material->TextureFilePath, MTLFilePath);

				Text::Parse(dataPoint, lineSize, "s", material->Name);

				break;
			}
			case BF::MTLLineType::Texture:
			{
				Text::Parse(dataPoint, lineSize, "s", material->TextureFilePath);
				break;
			}		
			case BF::MTLLineType::Weight:
			{
				Text::Parse(dataPoint, lineSize, "f", &material->Weight);
				break;
			}
			case BF::MTLLineType::Ambient:
			case BF::MTLLineType::Diffuse:
			case BF::MTLLineType::Specular:
			case BF::MTLLineType::Emission:
			{
				float* colorVector = nullptr;

				switch(lineType)
				{
					case BF::MTLLineType::Ambient:
						colorVector = material->Ambient;
						break;
					case BF::MTLLineType::Diffuse:
						colorVector = material->Diffuse;
						break;
					case BF::MTLLineType::Specular:
						colorVector = material->Specular;
						break;
					case BF::MTLLineType::Emission:
						colorVector = material->Emission;
						break;
				}

				Text::Parse(dataPoint, lineSize, "fff", &colorVector[0], &colorVector[1], &colorVector[2]);

				break;
			}
			case BF::MTLLineType::Dissolved:
			{
				Text::Parse(dataPoint, lineSize, "f", &material->Dissolved);
				break;
			}
			case BF::MTLLineType::Density:
			{
				Text::Parse(dataPoint, lineSize, "f", &material->Density);
				break;
			}
			case BF::MTLLineType::Illumination:
			{
				IlluminationMode mode = IlluminationMode::None;
				int number = -1;

				Text::Parse(dataPoint, lineSize, "i", &number);

				switch(number)
				{
					case 0:
						mode = IlluminationMode::ColorAndAmbientDisable;
						break;

					case 1:
						mode = IlluminationMode::ColorAndAmbientEnable;
						break;

					case 2:
						mode = IlluminationMode::HighlightEnable;
						break;

					case 3:
						mode = IlluminationMode::ReflectionOnRayTraceEnable;
						break;

					case 4:
						mode = IlluminationMode::ReflectionOnRayTraceTransparency;
						break;

					case 5:
						mode = IlluminationMode::ReflectionOnRayTraceFresnel;
						break;

					case 6:
						mode = IlluminationMode::ReflectionOnRayTraceTransparencyFresnel;
						break;

					case 7:
						mode = IlluminationMode::ReflectionOnRayTraceFullEnable;
						break;

					case 8:
						mode = IlluminationMode::ReflectionEnable;
						break;

					case 9:
						mode = IlluminationMode::TransparencyEnable;
						break;

					case 10:
						mode = IlluminationMode::ShadowsEnable;
						break;
				}

				material->Illumination = mode;

				break;
			}
		}
	}
	while(byteStream.SkipLine());

	return FileActionResult::Successful;
}

void BF::MTL::PrintContent()
{
	printf("===[Material]===\n");

	for (size_t i = 0; i < MaterialListSize; i++)
	{
		MTLMaterial& material = MaterialList[i];

		if (i > 0)
		{
			printf("+--------------------+\n");
		}

		printf
		(
			"| ID        : %u\n"
			"| Name      : %s\n"
			"| FilePath  : %s\n"
			"| Weight    : %f\n"
			"| Ambient   : <%f|%f|%f>\n"
			"| Diffuse   : <%f|%f|%f>\n"
			"| Specular  : <%f|%f|%f>\n"
			"| Emmission : <%f|%f|%f>\n"
			"| Dissolved : %f\n"
			"| Density   : %f\n",
			i,
			material.Name,
			material.TextureFilePath,
			material.Weight,
			material.Ambient[0],
			material.Ambient[1],
			material.Ambient[2],
			material.Diffuse[0],
			material.Diffuse[1],
			material.Diffuse[2],
			material.Specular[0],
			material.Specular[1],
			material.Specular[2],
			material.Emission[0],
			material.Emission[1],
			material.Emission[2],
			material.Dissolved,
			material.Density
		);
	}

	printf("================\n");
}