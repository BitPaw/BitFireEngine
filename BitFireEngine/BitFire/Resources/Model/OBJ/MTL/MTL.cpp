#include "MTL.h"

#include "../../../File/File.h"

void BF::MTL::Load(AsciiString& filePath)
{
	unsigned int materialIndex = 0;
	const char _newMaterialCharacter = 'n';
	const char _colorCharacter = 'K';
	const char _ambientCharacter = 'a';
	const char _diffuseCharacter = 'd';
	const char _specularCharacter = 's';
	//static const char _newMaterialCharacter = 'e';
	//static const char _newMaterialCharacter = 'N';
	const char _weightCharacter = 's';
	//static const char _newMaterialCharacter = 'i';
	List<AsciiString> lineList;
	File file(filePath);

	file.Read();

	// Count How many materials are needed
	{
		unsigned int materialCounter = 0;

		for (unsigned int line = 0; line < lineList.Size(); line++)
		{
			AsciiString lineCommand = lineList[line];
			char commandChar = lineCommand.Empty() ? ' ' : lineCommand[0];

			if (commandChar == 'n')
			{
				materialCounter++;
			}
		}

		MaterialList.ReSize(materialCounter);
	}

	// Raw Parse

	Material* material = nullptr;

	for (unsigned int line = 0; line < lineList.Size(); line++)
	{
		AsciiString lineCommand = lineList[line];
		char commandChar = lineCommand.Empty() ? ' ' : lineCommand[0];

		switch (commandChar)
		{
			case 'n':
			{
				List<AsciiString> lines;

				lineCommand.Splitt(' ', lines);

				material = &MaterialList[materialIndex++];
				material->Name.Copy(lines[1]);

				break;
			}

			case 'N':
			{
				commandChar = lineCommand[1];

				switch (commandChar)
				{
					case 's':
					{
						List<AsciiString> lines;

						lineCommand.Splitt(' ', lines);
						material->Weight = lines[1].ToFloat();

						break;
					}

					case 'i':
					{
						List<AsciiString> lines;

						lineCommand.Splitt(' ', lines);

						material->Density = lines[1].ToFloat();

						break;
					}

				}

				break;
			}

			case 'K':
			{
				commandChar = lineCommand[1];

				switch (commandChar)
				{
					case 'a':
					{
						List<AsciiString> lines;

						lineCommand.Splitt(' ', lines);

						material->Ambient.X = lines[1].ToFloat();
						material->Ambient.Y = lines[2].ToFloat();
						material->Ambient.Z = lines[3].ToFloat();

						break;
					}

					case 'd':
					{
						List<AsciiString> lines;

						lineCommand.Splitt(' ', lines);

						material->Diffuse.X = lines[1].ToFloat();
						material->Diffuse.Y = lines[2].ToFloat();
						material->Diffuse.Z = lines[3].ToFloat();

						break;
					}

					case 's':
					{
						List<AsciiString> lines;

						lineCommand.Splitt(' ', lines);

						material->Specular.X = lines[1].ToFloat();
						material->Specular.Y = lines[2].ToFloat();
						material->Specular.Z = lines[3].ToFloat();

						break;
					}


					case 'e':
					{
						List<AsciiString> lines;

						lineCommand.Splitt(' ', lines);

						material->Emission.X = lines[1].ToFloat();
						material->Emission.Y = lines[2].ToFloat();
						material->Emission.Z = lines[3].ToFloat();

						break;
					}

				}

				break;
			}

			case 'd':
			{
				List<AsciiString> lines;

				lineCommand.Splitt(' ', lines);

				material->Dissolved = lines[1].ToFloat();

				break;
			}

			case 'i':
			{
				List<AsciiString> lines;

				lineCommand.Splitt(' ', lines);
				IlluminationMode mode = IlluminationMode::None;
				int number = lines[1].ToInt();

				switch (number)
				{
					case '0':
						mode = IlluminationMode::ColorAndAmbientDisable;
						break;

					case '1':
						mode = IlluminationMode::ColorAndAmbientEnable;
						break;

					case '2':
						mode = IlluminationMode::HighlightEnable;
						break;

					case '3':
						mode = IlluminationMode::ReflectionOnRayTraceEnable;
						break;

					case '4':
						mode = IlluminationMode::ReflectionOnRayTraceTransparency;
						break;

					case '5':
						mode = IlluminationMode::ReflectionOnRayTraceFresnel;
						break;

					case '6':
						mode = IlluminationMode::ReflectionOnRayTraceTransparencyFresnel;
						break;

					case '7':
						mode = IlluminationMode::ReflectionOnRayTraceFullEnable;
						break;

					case '8':
						mode = IlluminationMode::ReflectionEnable;
						break;

					case '9':
						mode = IlluminationMode::TransparencyEnable;
						break;

					case '10':
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
}
