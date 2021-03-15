#include "PNG.h"

void BF::PNG::PrintData()
{
	printf
	(
	    "+---------------------------+\n"
		"| PNG File                  |\n"
		"+---------------------------+\n"
		"| Width             : %5i |\n"
		"| Height            : %5i |\n"
		"| BitDepth          : %5c |\n"
		"| ColorType         : %5c |\n"
		"| CompressionMethod : %5c |\n"
		"| FilterMethod      : %5c |\n"
		"| InterlaceMethod   : %5c |\n"
		"+---------------------------+\n"
		"| Chunks                    |\n"
		"+---------------------------+\n"
		"| Type %4 s Lengh %4 i      |\n",
		Header.Width,
		Header.Height,
		Header.BitDepth,
		Header.ColorType,
		Header.CompressionMethod,
		Header.FilterMethod,
		Header.InterlaceMethod
	);

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
}
