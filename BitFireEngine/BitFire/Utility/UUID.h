#pragma once

namespace BF
{
	struct UUID
	{
		/*
		Name 								Length (bytes) 	Length (hex digits) 	Contents 
		time_low 							4 	8 	integer giving the low 32 bits of the time
		time_mid 							2 	4 	integer giving the middle 16 bits of the time
		time_hi_and_version 				2 	4 	4-bit "version" in the most significant bits, followed by the high 12 bits of the time
		clock_seq_hi_and_res clock_seq_low 	2 	4 	1 to 3-bit "variant" in the most significant bits, followed by the 13 to 15-bit clock sequence
		node 								6 	12 	the 48-bit node id 
		
		
		*/


		public:
		char Data[32];

		int TimeLow()
		{
			return	static_cast<int>(Data[0]) + 
				    static_cast<int>(Data[1]) + 
				    static_cast<int>(Data[2]) +
				    static_cast<int>(Data[3]);
		}

		
	}; 
}
