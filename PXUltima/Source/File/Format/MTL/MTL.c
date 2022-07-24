#include "MTL.h"

#include <File/ParsingStream.h>
#include <Text/Text.h>
#include <Container/ClusterShort.h>
#include <Memory/Memory.h>

void MTLConstruct(MTL* mtl)
{
	MemorySet(mtl, sizeof(MTL), 0);
}

void MTLDestruct(MTL* mtl)
{
	// Loop through MaterialListSize

	MemoryRelease(mtl->MaterialList, mtl->MaterialListSize);

	mtl->MaterialListSize = 0;
	mtl->MaterialList = 0;
}

MTLLineType MTLPeekLine(const void* line)
{
	const unsigned short tagID = MakeShort(((unsigned char*)line)[0], ((unsigned char*)line)[1]);

	switch(tagID)
	{
		case MakeShort('m', 'a'): return MTLLineTexture;
		case MakeShort('n', 'e'): return MTLLineName;
		case MakeShort('N', 's'): return MTLLineWeight;
		case MakeShort('N', 'i'): return MTLLineDensity;
		case MakeShort('K', 'a'): return MTLLineColorAmbient;
		case MakeShort('K', 'd'): return MTLLineColorDiffuse;
		case MakeShort('K', 's'): return MTLLineColorSpecular;
		case MakeShort('K', 'e'): return MTLLineEmission;
		case MakeShort('d', ' '): return MTLLineDissolved;
		case MakeShort('i', 'l'): return MTLLineIllumination;
		default:
			return MTLLineInvalid;
	}
}

ActionResult MTLParse(MTL* mtl, const void* data, const size_t dataSize, size_t* dataRead)
{
	ParsingStream parsingStream;

	MTLConstruct(mtl);
	ParsingStreamConstruct(&parsingStream, data, dataSize);
	*dataRead = 0;

	// Count How many materials are needed
	{
		size_t materialCounter = 0;

		do
		{
			const unsigned char* currentLine = ParsingStreamCursorPosition(&parsingStream);
			const unsigned char isNewMaterialUsed = *currentLine == 'n';

			if(isNewMaterialUsed)
			{
				++materialCounter;
			}
		}
		while(ParsingStreamSkipLine(&parsingStream));

		mtl->MaterialListSize = materialCounter;
		mtl->MaterialList = MemoryAllocate(sizeof(MTLMaterial) * materialCounter);

		MemorySet(mtl->MaterialList, sizeof(MTLMaterial) * materialCounter, 0);

		ParsingStreamCursorToBeginning(&parsingStream);
	}

	// Raw Parse
	MTLMaterial* material = 0; // current material, has to be here, its state dependend
	size_t materialIndex = 0;

	do
	{
		const char* currentLine = ParsingStreamCursorPosition(&parsingStream);
		const MTLLineType lineType = MTLPeekLine(currentLine);
			
		ParsingStreamSkipBlock(&parsingStream); // Skip first element

		const char* dataPoint = ParsingStreamCursorPosition(&parsingStream);
		const size_t maxSize = ParsingStreamRemainingSize(&parsingStream);
		const size_t lineSize = TextLengthUntilA(dataPoint, maxSize, '\n');

		switch(lineType)
		{
			default:
			case MTLLineInvalid:
				// Do nothing
				break;

			case MTLLineName:
			{
				material = &mtl->MaterialList[materialIndex++];

				const char internalText[] = "<internal>";
				const size_t internalTextSize = sizeof(internalText);

				TextCopyA(internalText, internalTextSize, material->TextureFilePath, MTLFilePath);

				TextParseA(dataPoint, lineSize, "s", material->Name);

				break;
			}
			case MTLLineTexture:
			{
				TextParseA(dataPoint, lineSize, "s", material->TextureFilePath);
				break;
			}
			case MTLLineWeight:
			{
				TextParseA(dataPoint, lineSize, "f", &material->Weight);
				break;
			}
			case MTLLineColorAmbient:
			case MTLLineColorDiffuse:
			case MTLLineColorSpecular:
			case MTLLineEmission:
			{
				float* colorVector = 0;

				switch(lineType)
				{
					case MTLLineColorAmbient:
						colorVector = material->Ambient;
						break;
					case MTLLineColorDiffuse:
						colorVector = material->Diffuse;
						break;
					case MTLLineColorSpecular:
						colorVector = material->Specular;
						break;
					case MTLLineEmission:
						colorVector = material->Emission;
						break;
				}

				TextParseA(dataPoint, lineSize, "fff", &colorVector[0], &colorVector[1], &colorVector[2]);

				break;
			}
			case MTLLineDissolved:
			{
				TextParseA(dataPoint, lineSize, "f", &material->Dissolved);
				break;
			}
			case MTLLineDensity:
			{
				TextParseA(dataPoint, lineSize, "f", &material->Density);
				break;
			}
			case MTLLineIllumination:
			{
				IlluminationMode mode = IlluminationNone;
				int number = -1;

				TextParseA(dataPoint, lineSize, "i", &number);

				switch(number)
				{
					case 0:
						mode = IlluminationColorAndAmbientDisable;
						break;

					case 1:
						mode = IlluminationColorAndAmbientEnable;
						break;

					case 2:
						mode = IlluminationHighlightEnable;
						break;

					case 3:
						mode = IlluminationReflectionOnRayTraceEnable;
						break;

					case 4:
						mode = IlluminationReflectionOnRayTraceTransparency;
						break;

					case 5:
						mode = IlluminationReflectionOnRayTraceFresnel;
						break;

					case 6:
						mode = IlluminationReflectionOnRayTraceTransparencyFresnel;
						break;

					case 7:
						mode = IlluminationReflectionOnRayTraceFullEnable;
						break;

					case 8:
						mode = IlluminationReflectionEnable;
						break;

					case 9:
						mode = IlluminationTransparencyEnable;
						break;

					case 10:
						mode = IlluminationShadowsEnable;
						break;
				}

				material->Illumination = mode;

				break;
			}
		}
	}
	while(ParsingStreamSkipLine(&parsingStream));

	return ResultSuccessful;
}


/*


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
*/