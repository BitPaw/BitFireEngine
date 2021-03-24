#include "PNG.h"

void BF::PNG::PrintData()
{
	/*
	printf
	(
	    "+---------------------------+\n"
		"| PNG File                  |\n"
		"+---------------------------+\n"
		"| Width             : %5i |\n"
		"| Height            : %5i |\n"
		"| BitDepth          : %5u |\n"
		"| ColorType         : %5u |\n"
		"| CompressionMethod : %5u |\n"
		"| FilterMethod      : %5u |\n"
		"| InterlaceMethod   : %5u |\n"
		"+---------------------------+\n"
		"| Chunks                    |\n"
		"+---------------------------+\n"
		"| Type %4 s Lengh %4 i      |\n",
		Width,
		Height,
		BitDepth,
		ColorType,
		CompressionMethod,
		FilterMethod,
		InterlaceMethod
	);
	/*
	for (unsigned int i = 0; i < ChunkList.Size(); i++)
	{
		PNGChunk* chunk = &ChunkList[i];

		printf
		(
			"| Type %4s Lengh %4i      |\n",
			
			&chunk->ChunkType,
			chunk->Lengh
		);
	}

	printf("+---------------------------+\n");
	*/
}
