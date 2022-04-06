#pragma once

namespace BF
{
	// Resource Interchange File Format. 
	struct RIFF
	{
		public:
			union
			{
				struct
				{
					char A;
					char B;
					char C;
					char D;
				};
				char Data[4];
				unsigned int Value;
			}ChunkID;

		unsigned int ChunkSize;
		char Format[4];

		RIFF();
	};
}