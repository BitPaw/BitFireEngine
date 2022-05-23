#pragma once

#include <File/ByteCluster.h>

// Source
#define SourceInvalid	-1
#define SourceFillData	-2 // Request the reciever (Server mostly) to fill in data.
#define SourceServer	-3 // Server is the owner of this message

// Target
#define TargetInvalid		-1 
#define TargetMeToServer	-2 // Client(You) -> Server only
#define TargetMeToAll		-3 // Client(You) -> All Clients
#define TargetMeToOthers	-4 // Client(You) -> specific Clients
#define TargetYouOnly		-5 // *Something* -> Client(You)
#define TargetYouAndOthers	-6 // *Something* -> pecific Clients + Client (You)
#define TargetEveryBody		-7 // *Something* -> All Clients (You)

namespace BF
{
	struct SilverBulletProtocolData
	{
		public:
		ByteCluster Command;
		unsigned int Source;
		unsigned int Target;		
		unsigned int ID;
		unsigned int DataSize;
		void* Data;

		SilverBulletProtocolData();
		
		void Set(unsigned int command, unsigned int source, unsigned int target, unsigned int id, unsigned int dataSize);
	};
}