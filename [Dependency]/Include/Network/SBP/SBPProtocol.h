#ifndef SBPProtocolINCLUDE
#define SBPProtocolINCLUDE

#include <File/PXDataStream.h>
#include <Text/PXText.h>
#include <Container/ClusterValue.h>

#ifdef __cplusplus
extern "C"
{
#endif


#define SBPIDConnectionCreate MakeInt('C', 'o', 'n', '+')
#define SBPIDConnectionResult MakeInt('C', 'o', 'n', '#')
#define SBPIDConnectionKill MakeInt('C', 'o', 'n', '-')
#define SBPIDText MakeInt('T', 'e', 'x', 't')
#define SBPPackageHeaderPackageIamID MakeInt('I', '\'', 'a', 'm')
#define SBPPackageHeaderPackageFileID MakeInt('F', 'i', 'l', 'e')


#define ConnectionCreateReasonFile 'F'
#define ConnectionCreateReasonData 'D'

	typedef enum SBPResult_
	{
		SBPResultInvalid,

		SBPResultPackageSendingFailure,

		// Nobody is listening for a result
		SBPResultPackageSendSucessfulButNoResponder,

		SBPResultPackageAnswered,
		SBPResultPackageTimeout,

		SBPResultPackageDetectedRegistered,
		SBPResultPackageDetectedCustom,

		SBPResultInvalidHeader
	}
	SBPResult;








#define SBPFilePathSizeMaskTextType 0b1000000000000000 // 0=char* 1=wchar_t*
#define SBPFilePathSizeMaskA        0b0100000000000000
#define SBPFilePathSizeMaskB		0b0010000000000000
#define SBPFilePathSizeMaskC		0b0001000000000000
#define SBPFilePathSizeMask			0b1111000000000000

	// Source

#define SourceInvalid	-1
#define SourceMe	-2 // Request the reciever (Server mostly) to fill in data.
#define SourceServer	-3 // PXServer is the owner of this message

#define SourceLimitMaximum SourceServer

	typedef enum SBPSource_
	{
		SBPSourceInvalid = SourceInvalid,

		// Sending
		SBPSourceMe = SourceMe,
		SBPSourceServer = SourceServer
	}
	SBPSource;

	// Target
#define TargetInvalid		-1
#define TargetServer		-2 // PXClient(You) -> PXServer only
#define TargetAll		-3 // PXClient(You) -> All PXClients
#define TargetSpecific	-4 // PXClient(You) -> specific PXClients
#define TargetYou		-5 // *Something* -> PXClient(You)
#define TargetYouAndOthers	-6 // *Something* -> pecific PXClients + PXClient (You)
#define TargetEveryBody		-7 // *Something* -> All PXClients (You)

#define TargetLimitMaximum TargetEveryBody

#define ResponseID unsigned int

	typedef enum SBPTarget_
	{
		SBPTargetInvalid = TargetInvalid,

		// Sending
		SBPTargetServer = TargetServer,
		SBPTargetAll = TargetAll,
		SBPTargetSpesific = TargetSpecific,

		// Recieving
		SBPTargetYou = TargetYou,
		SBPTargetYouAndOthers = TargetYouAndOthers,
		SBPTargetEverybody = TargetEveryBody
	}
	SBPTarget;


	// Size: 24 Byte
	typedef struct PXSBPChannelHeader_
	{
		PXInt8U ID;
		PXInt16U Size;
		void* Data;
	}
	PXSBPChannelHeader;

	PXPublic PXSize PXSBPChannelHeaderParse(PXSBPChannelHeader* const sbpChannelHeader, PXDataStream* const dataStream);
	PXPublic PXSize PXSBPChannelHeaderSerialize(PXSBPChannelHeader* const sbpChannelHeader, PXDataStream* const dataStream);

	// 32-Bit: Size: 20 Byte
	// 64-Bit: Size: 28 Byte
	typedef struct SBPPackageHeader_
	{
		//--------------------------------------- Location info
		union
		{
			unsigned int SourceID; // Where is it from?
			SBPSource Source;
		};

		union
		{
			unsigned int TargetID; // Who is the reciever
			SBPTarget Target;
		};
		//---------------------------------------

		//--------------------------------------- Payload
		ClusterInt CommandID;
		PXSize CommandSize;
		void* Command;
		//---------------------------------------
	}
	SBPPackageHeader;

	PXPublic void SBPPackageHeaderConstruct(SBPPackageHeader* const sbpPackageHeader);
	PXPublic void SBPPackageHeaderDestruct(SBPPackageHeader* const sbpPackageHeader);

	PXPublic void SBPPackageHeaderSet
	(
		SBPPackageHeader* const sbpPackageHeader,
		const unsigned int command,
		const unsigned int source,
		const unsigned int target,
		const unsigned int dataSize,
		const void* adress
	);

	PXPublic void SBPPackageHeaderPrint(SBPPackageHeader* const sbpData);

	PXPublic PXSize PXSBPPackageParse(SBPPackageHeader* const sbpPackageHeader, PXDataStream* const dataStream);
	PXPublic PXSize PXSBPPackageSerialize(const SBPPackageHeader* const data, PXDataStream* const dataStream);
	/*
	CPublic PXSize PackageSerialize
	(
		void* outputBuffer,
		const PXSize outputBufferSize,
		const unsigned int source,
		const unsigned int target,
		const SBPPackageHeaderPackage* dataPackage,
		const ResponseID responseID
	);*/

	// Recieve custom package, this is only called for unregistered packages
	typedef void (*PackageRecieveEvent)(const SBPPackageHeader* sbpData);










	//---<Pre-Defined packages>----------------------------------------------

	typedef enum SBPConnectionCreateReason_
	{
		SBPConnectionCreateInvalid,
		SBPConnectionCreateVoiceChat,
		SBPConnectionCreateVideoChat,
		SBPConnectionCreateFileTransfer
	}
	SBPConnectionCreateReason;

	typedef struct SBPPackageHeaderPackageConnectionCreate_
	{
		SBPConnectionCreateReason Reason;
	}
	SBPPackageHeaderPackageConnectionCreate;

	PXPublic void SBPPackageHeaderPackageConnectionCreateFill(const SBPConnectionCreateReason reason);

	PXPublic PXSize SBPPackageHeaderPackageConnectionCreateParse(const void* inputData, const PXSize inputDataSize);
	PXPublic PXSize SBPPackageHeaderPackageConnectionCreateSerialize(void* outputData, const PXSize outputDataSize);






#define SBPPackageHeaderPackageFileModeIDCreate 0x01
#define SBPPackageHeaderPackageFileModeIDDelete 0x02
#define SBPPackageHeaderPackageFileModeIDUpdate 0x03
#define SBPPackageHeaderPackageFileModeIDMove 0x04
#define SBPPackageHeaderPackageFileModeIDCopy 0x05
#define SBPPackageHeaderPackageFileModeIDRename 0x06

		typedef enum SBPPackageHeaderPackageFileMode
		{
			Invalid,
			Create, // Create a file and upload data to it
			Delete, // Remove a file
			Update, // override data from the file
			Move, // Move the file form one place to another
			Copy, // Copy a file
			Rename // rename the file, no not change data
		}
		SBPPackageHeaderPackageFileMode;

		typedef struct SBPPackageHeaderPackageFile_
		{
			SBPPackageHeaderPackageFileMode Mode;

			PXTextFormat FilePathSourceFormat;
			PXSize FilePathSourceSize;
			union
			{
				char FilePathSourceA[PathMaxSize];
				wchar_t FilePathSourceW[PathMaxSize];
			};

			PXTextFormat FilePathTargetFormat;
			PXSize FilePathTargetSize;
			union
			{
				char FilePathTargetA[PathMaxSize];
				wchar_t FilePathTargetW[PathMaxSize];
			};

			PXSize FileSize; // HAs to be 8 Byte__!
		}
		SBPPackageHeaderPackageFile;



		PXPublic void SBPPackageHeaderPackageFileConstruct(SBPPackageHeaderPackageFile* const sbpDataPackageFile);

		// S:N T:N => Invalid
		// S:N T:Y => Create
		// S:Y T:N => Delete
		// S:Y T:Y => Copy

		PXPublic void SBPPackageHeaderPackageFileFill(SBPPackageHeaderPackageFile* const sbpDataPackageFile, const SBPPackageHeaderPackageFileMode mode, const char* source, const char* target);

		PXPublic PXSize SBPPackageHeaderPackageFileParse(SBPPackageHeaderPackageFile* const sbpDataPackageFile, const void* inputData, const PXSize inputDataSize);
		PXPublic PXSize SBPPackageHeaderPackageFileSerialize(SBPPackageHeaderPackageFile* const sbpDataPackageFile, void* outputData, const PXSize outputDataSize);






	//-------------------------------------------------------------------------

	typedef struct SBPPackageHeaderPackageIam_
	{
		PXText Name;
	}
	SBPPackageHeaderPackageIam;

	PXPublic PXSize SBPPackageHeaderPackageIamParse(SBPPackageHeader* const sbpDataPackage, SBPPackageHeaderPackageIam* const sbpDataPackageIam);
	PXPublic PXSize SBPPackageHeaderPackageIamSerialize(SBPPackageHeader* const sbpDataPackage, SBPPackageHeaderPackageIam* const sbpDataPackageIam);
	//-------------------------------------------------------------------------


#define SBPPackageHeaderPackageResponseID MakeInt('R', 'e', 's', 'p')

#define SBPPackageHeaderPackageResponseTypeOKID 0x01
#define SBPPackageHeaderPackageResponseTypeNoPermissionID 0x02
#define SBPPackageHeaderPackageResponseTypeDeniedID 0x03

		typedef enum SBPPackageHeaderPackageResponseType_
		{
			SBPResponseInvalid,
			SBPResponseOK,
			SBPResponseNoPermission,
			SBPResponseDenied
		}
		SBPPackageHeaderPackageResponseType;

		typedef struct SBPPackageHeaderPackageResponse_
		{
			SBPPackageHeaderPackageResponseType Type;
		}
		SBPPackageHeaderPackageResponse;

		PXPublic void SBPPackageHeaderPackageResponseConstruct(SBPPackageHeaderPackageResponse* const sbpDataPackageResponse);

		PXPublic PXSize SBPPackageHeaderPackageResponseParse(SBPPackageHeaderPackageResponse* const sbpDataPackageResponse, const void* inputData, const PXSize inputDataSize);
		PXPublic PXSize SBPPackageHeaderPackageResponseSerialize(SBPPackageHeaderPackageResponse* const sbpDataPackageResponse, void* outputData, const PXSize outputDataSize);



#define SBPPackageHeaderPackageTextID MakeInt('T', 'e', 'x', 't')

	typedef struct SBPPackageHeaderPackageText_
	{
		PXText TextData;
	}
	SBPPackageHeaderPackageText;

	PXPublic void SBPPackageHeaderPackageTextConstruct(SBPPackageHeaderPackageText* const sbpDataPackageText);
	PXPublic void SBPPackageHeaderPackageTextDestruct(SBPPackageHeaderPackageText* const sbpDataPackageText);

	PXPublic PXSize SBPPackageHeaderPackageTextParse(SBPPackageHeaderPackageText* const sbpDataPackageText, const void* inputData, const PXSize inputDataSize);
	PXPublic PXSize SBPPackageHeaderPackageTextSerialize(SBPPackageHeaderPackageText* const sbpDataPackageText, void* outputData, const PXSize outputDataSize);




#ifdef __cplusplus
}
#endif

#endif
