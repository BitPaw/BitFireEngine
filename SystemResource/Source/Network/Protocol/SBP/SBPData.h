#pragma once

#include <cstddef>

#include <Container/ClusterInt.h>
#include <File/File.h>
#include "SBPDataPackageIam.h"

#include "SBPDataPackage.h"

namespace BF
{

#define ConnectionCreateReasonFile 'F'
#define ConnectionCreateReasonData 'D'


#define SBPIDConnectionCreate MakeInt('C', 'o', 'n', '+')
#define SBPIDConnectionResult MakeInt('C', 'o', 'n', '#')
#define SBPIDConnectionKill MakeInt('C', 'o', 'n', '-')

#define SBPIDText MakeInt('T', 'e', 'x', 't')



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

	enum class SBPSource
	{
		Invalid = SourceInvalid,

		// Sending
		Me = SourceMe,
		Server = SourceServer
	};

	// Target
#define TargetInvalid		-1
#define TargetServer		-2 // Client(You) -> Server only
#define TargetAll		-3 // Client(You) -> All Clients
#define TargetSpecific	-4 // Client(You) -> specific Clients
#define TargetYou		-5 // *Something* -> Client(You)
#define TargetYouAndOthers	-6 // *Something* -> pecific Clients + Client (You)
#define TargetEveryBody		-7 // *Something* -> All Clients (You)

#define TargetLimitMaximum TargetEveryBody

#define ResponseID unsigned int

	enum class SBPTarget
	{
		Invalid = TargetInvalid,

		// Sending
		Server = TargetServer,
		All = TargetAll,
		Spesific = TargetSpecific,

		// Recieving
		You = TargetYou,
		YouAndOthers = TargetYouAndOthers,
		Everybody = TargetEveryBody
	};

	struct SBPData
	{
		public:
		ClusterInt CommandID;

		union
		{
			unsigned int SourceID;
			SBPSource Source;
		};

		union
		{
			unsigned int TargetID;
			SBPTarget Target;
		};

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

		void Print();

		static size_t PackageParse(SBPData& data, const void* inputBuffer, const size_t& inputBufferSize);
		static size_t PackageSerialize(const SBPData& data, void* outputBuffer, const size_t outputBufferSize);
		static size_t PackageSerialize
		(
			void* outputBuffer,
			const size_t outputBufferSize,
			const unsigned int source,
			const unsigned int target,
			const SBPDataPackage* dataPackage,
			const ResponseID responseID
		);
	};

	// Recieve custom package, this is only called for unregistered packages
	typedef void (*PackageRecieveEvent)(const SBPData& data);
}
