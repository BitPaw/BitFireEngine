#pragma once

#include <File/ByteCluster.h>

// Source
#define SourceInvalid	-1
#define SourceMe	-2 // Request the reciever (Server mostly) to fill in data.
#define SourceServer	-3 // Server is the owner of this message

#define SourceLimitMaximum SourceServer

// Target
#define TargetInvalid		-1 
#define TargetMeToServer	-2 // Client(You) -> Server only
#define TargetMeToAll		-3 // Client(You) -> All Clients
#define TargetMeToOthers	-4 // Client(You) -> specific Clients
#define TargetYouOnly		-5 // *Something* -> Client(You)
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
	};
}