#pragma once

#include <File/ByteCluster.h>


#define ConnectionCreateReasonFile 'F'
#define ConnectionCreateReasonData 'D'

#define SBPIDIAM MakeInt('I', '\'', 'a', 'm')
#define SBPIDConnectionCreate MakeInt('C', 'o', 'n', '+')
#define SBPIDConnectionResult MakeInt('C', 'o', 'n', '#')
#define SBPIDConnectionKill MakeInt('C', 'o', 'n', '-')

#define SBPIDText MakeInt('T', 'e', 'x', 't')
#define SBPIDFile MakeInt('F', 'i', 'l', 'e')

#define SBPFilePathSizeMaskTextType 0b1000000000000000 // 0=char* 1=wchar_t*
#define SBPFilePathSizeMaskA        0b0100000000000000
#define SBPFilePathSizeMaskB		0b0010000000000000 
#define SBPFilePathSizeMaskC		0b0001000000000000 
#define SBPFilePathSizeMask			0b1111000000000000

// Source
#define SourceInvalid	-1
#define SourceMe	-2 // Request the reciever (Server mostly) to fill in data.
#define SourceServer	-3 // Server is the owner of this message

#define SourceLimitMaximum SourceServer

// Target
#define TargetInvalid		-1 
#define TargetServer		-2 // Client(You) -> Server only
#define TargetAll		-3 // Client(You) -> All Clients
#define TargetSpecific	-4 // Client(You) -> specific Clients
#define TargetYou		-5 // *Something* -> Client(You)
#define TargetYouAndOthers	-6 // *Something* -> pecific Clients + Client (You)
#define TargetEveryBody		-7 // *Something* -> All Clients (You)

#define TargetLimitMaximum TargetEveryBody

namespace BF
{
	struct SBPData
	{
		public:
		ByteCluster Command;
		unsigned int Source;
		unsigned int Target;		
		unsigned int ID;
		unsigned int DataSize;
		void* Data;

		SBPData();
		SBPData
		(
			const unsigned int command,
			const unsigned int source,
			const unsigned int target,
			const unsigned int id,
			const unsigned int dataSize,
			const void* adress
		);
		
		void Set
		(
			const unsigned int command,
			const unsigned int source,
			const unsigned int target,
			const unsigned int id,
			const unsigned int dataSize,
			const void* adress
		);

		unsigned int Size();

		void Clear();

		static void GenerateMessage
		(
			const SBPData& data,
			unsigned char* buffer,
			size_t& bufferSize,
			const size_t bufferSizeMax
		);
	};
}