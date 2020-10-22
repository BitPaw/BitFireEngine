#include "MTLLoader.h"


BF::MTL* BF::MTLLoader::LoadFromFile(std::string filePath)
{
    MTL* materialLibrary = new MTL();
	List<std::string> lines = FileLoader::ReadFileByLines(filePath);
	unsigned int materialIndex = 0;

	// Count How many materials are needed
	{
		unsigned int materialCounter = 0;

		for (unsigned int line = 0; line < lines.Size.Value; line++)
		{
			std::string lineCommand = lines[line];
			char commandChar = lineCommand.length() > 0 ? lineCommand.at(0) : ' ';

			if (commandChar == 'n')
			{
				materialCounter++;
			}
		}

		materialLibrary->MaterialList.ReSize(materialCounter);
	}

	// Raw Parse
	
	Material* material = nullptr;

		for (unsigned int line = 0; line < lines.Size.Value; line++)
		{
			std::string lineCommand = lines[line];
			
			char commandChar = lineCommand.length() > 0 ? lineCommand.at(0) : ' ';

			switch (commandChar)
			{
			case 'n':
			{
				StringSplitter ss = StringSplitter::Split(lineCommand, ' ');

				material = &materialLibrary->MaterialList[materialIndex++];
				material->Name = ss.Lines[1];

				break;
			}
				
			case 'N':
			{
				commandChar = lineCommand.at(1);

				switch (commandChar)
				{
				case 's':
				{
					StringSplitter ss = StringSplitter::Split(lineCommand, ' ');
					material->Weight = stof(ss.Lines[1]);

					break;
				}

				case 'i':
				{
					StringSplitter ss = StringSplitter::Split(lineCommand, ' ');

					material->Density = stof(ss.Lines[1]);

					break;
				}

				}

				break;
			}
				
			case 'K':
			{
				commandChar = lineCommand.at(1);

				switch (commandChar)
				{
				case 'a':
				{
					StringSplitter ss = StringSplitter::Split(lineCommand, ' ');

					material->Ambient.X = stof(ss.Lines[1]);
					material->Ambient.Y = stof(ss.Lines[2]);
					material->Ambient.Z = stof(ss.Lines[3]);

					break;
				}				

				case 'd':
				{
					StringSplitter ss = StringSplitter::Split(lineCommand, ' ');

					material->Diffuse.X = stof(ss.Lines[1]);
					material->Diffuse.Y = stof(ss.Lines[2]);
					material->Diffuse.Z = stof(ss.Lines[3]);

					break;
				}				

				case 's':
				{
					StringSplitter ss = StringSplitter::Split(lineCommand, ' ');

					material->Specular.X = stof(ss.Lines[1]);
					material->Specular.Y = stof(ss.Lines[2]);
					material->Specular.Z = stof(ss.Lines[3]);

					break;
				}
				

				case 'e':
				{
					StringSplitter ss = StringSplitter::Split(lineCommand, ' ');

					material->Emission.X = stof(ss.Lines[1]);
					material->Emission.Y = stof(ss.Lines[2]);
					material->Emission.Z = stof(ss.Lines[3]);

					break;
				}
				
				}

				break;
			}

			case 'd':
			{
				StringSplitter ss = StringSplitter::Split(lineCommand, ' ');

				material->Dissolved = stof(ss.Lines[1]);

				break;
			}				

			case 'i':
			{
				StringSplitter ss = StringSplitter::Split(lineCommand, ' ');
				IlluminationMode mode = IlluminationMode::None;
				int number = stoi(ss.Lines[1]);

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
