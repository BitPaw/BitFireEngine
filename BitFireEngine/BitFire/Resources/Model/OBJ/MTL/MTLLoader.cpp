#include "MTLLoader.h"


BF::MTL* BF::MTLLoader::LoadFromFile(AsciiString& filePath)
{
    MTL* materialLibrary = new MTL();
	List<AsciiString> lines;
	FileLoader::ReadFileByLines(filePath, lines);
	unsigned int materialIndex = 0;

	// Count How many materials are needed
	{
		unsigned int materialCounter = 0;

		for (unsigned int line = 0; line < lines.Size(); line++)
		{
			AsciiString lineCommand = lines[line];
			char commandChar = lineCommand.Empty() ? ' ' : lineCommand[0];

			if (commandChar == 'n')
			{
				materialCounter++;
			}
		}

		materialLibrary->MaterialList.ReSize(materialCounter);
	}

	// Raw Parse
	
	Material* material = nullptr;

		for (unsigned int line = 0; line < lines.Size(); line++)
		{
			AsciiString lineCommand = lines[line];			
			char commandChar = lineCommand.Empty() ? ' ' : lineCommand[0];

			switch (commandChar)
			{
			case 'n':
			{
				List<AsciiString> lines;

				lineCommand.Splitt(' ', lines);

				material = &materialLibrary->MaterialList[materialIndex++];
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
	

    return materialLibrary;
}
