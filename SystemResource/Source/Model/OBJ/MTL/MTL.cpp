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

BF::FileActionResult BF::MTL::Load(const wchar_t* filePath)
{
	size_t materialIndex = 0;
	const char _newMaterialCharacter = 'n';
	const char _colorCharacter = 'K';
	const char _ambientCharacter = 'a';
	const char _diffuseCharacter = 'd';
	const char _specularCharacter = 's';
	//static const char _newMaterialCharacter = 'e';
	//static const char _newMaterialCharacter = 'N';
	const char _weightCharacter = 's';
	//static const char _newMaterialCharacter = 'i';


	File file;

	{		
		const FileActionResult fileActionResult = file.ReadFromDisk(filePath);

		if(fileActionResult != FileActionResult::Successful)
		{
			return fileActionResult;
		}
	}

	const size_t currentLineBufferSize = 512;
	char currentLineBuffer[currentLineBufferSize];

	// Count How many materials are needed
	{

		while (file.ReadNextLineInto(currentLineBuffer))
		{			
			const char commandChar = currentLineBuffer[0];
			const bool isNewMaterialUsed = commandChar == 'n';

			if (isNewMaterialUsed)
			{
				MaterialListSize++;
			}
		}

		MaterialList = new MTLMaterial[MaterialListSize];
	}

	// Raw Parse
	MTLMaterial* material = nullptr; // current material, has to be here, its state dependend

	file.CursorToBeginning();

	while (file.ReadNextLineInto(currentLineBuffer))
	{
		char commandChar = currentLineBuffer[0];

		switch (commandChar)
		{
			case 'm':
			{
				Text::Parse(currentLineBuffer, currentLineBufferSize, "§s", material->TextureFilePath);
				break;
			}

			case 'n':
			{
				material = &MaterialList[materialIndex++];

				const char internalText[] = "<internal>";
				const size_t internalTextSize = sizeof(internalText);

				Text::Copy(internalText, internalTextSize, material->TextureFilePath, MTLFilePath);

				Text::Parse(currentLineBuffer, currentLineBufferSize, "§s", material->Name);

				break;
			}

			case 'N':
			{
				float* value = nullptr;
				commandChar = currentLineBuffer[1];

				switch (commandChar)
				{
					case 's':
					{
						value = &material->Weight;
						break;
					}

					case 'i':
					{
						value = &material->Density;
						break;
					}					
				}

				Text::Parse(currentLineBuffer, currentLineBufferSize, "§f", value);

				break;
			}

			case 'K':
			{
				float* colorVector = nullptr;

				commandChar = currentLineBuffer[1];

				switch (commandChar)
				{
					case 'a':
					{
						colorVector = material->Ambient;
						break;
					}

					case 'd':
					{
						colorVector = material->Diffuse;
						break;
					}

					case 's':
					{
						colorVector = material->Specular;
						break;
					}

					case 'e':
					{
						colorVector = material->Emission;
						break;
					}
				}

				Text::Parse(currentLineBuffer, currentLineBufferSize, "§fff", &colorVector[0], &colorVector[1], &colorVector[2]);

				break;
			}

			case 'd':
			{
				Text::Parse(currentLineBuffer, currentLineBufferSize, "§f", &material->Dissolved);
				break;
			}

			case 'i':
			{
				IlluminationMode mode = IlluminationMode::None;
				int number = -1;

				Text::Parse(currentLineBuffer, currentLineBufferSize, "§i", &number);

				switch (number)
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

			case ' ':
			case '#':
			default:
				break;
		}
	}

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