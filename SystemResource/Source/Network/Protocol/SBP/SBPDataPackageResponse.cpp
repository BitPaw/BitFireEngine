#include "SBPDataPackageResponse.h"

#include <File/ParsingStreamX.h>

#define SBPDataPackageResponseTypeOKID 0x01 
#define SBPDataPackageResponseTypeNoPermissionID 0x02 
#define SBPDataPackageResponseTypeDeniedID 0x03 

BF::SBPDataPackageResponse::SBPDataPackageResponse()
{
	Type = SBPDataPackageResponseType::Invalid;
	SymbolID.Value = SBPDataPackageResponseID;
}

size_t BF::SBPDataPackageResponse::Parse(const void* inputData, const size_t inputDataSize)
{
	ParsingStreamX parsingStream(inputData, inputDataSize);

	{
		unsigned char typeID = 0;

		parsingStream.Read(typeID);

		switch(typeID)
		{
			case SBPDataPackageResponseTypeOKID:
				Type = BF::SBPDataPackageResponseType::OK;
				break;

			case SBPDataPackageResponseTypeNoPermissionID:
				Type = BF::SBPDataPackageResponseType::NoPermission;
				break;

			case SBPDataPackageResponseTypeDeniedID:
				Type = BF::SBPDataPackageResponseType::Denied;
				break;

			default:
				Type = BF::SBPDataPackageResponseType::Invalid;
				break;
		}
	}

	return parsingStream.DataCursor;
}

size_t BF::SBPDataPackageResponse::Serialize(void* outputData, const size_t outputDataSize) const
{
	ParsingStreamX parsingStream(outputData, outputDataSize);

	unsigned char typeID = 0;

	switch(Type)
	{
		default:
		case BF::SBPDataPackageResponseType::Invalid:
			return 0;

		case BF::SBPDataPackageResponseType::OK:
			typeID = SBPDataPackageResponseTypeOKID;
			break;

		case BF::SBPDataPackageResponseType::NoPermission:
			typeID = SBPDataPackageResponseTypeNoPermissionID;
			break;

		case BF::SBPDataPackageResponseType::Denied:
			typeID = SBPDataPackageResponseTypeDeniedID;
			break;
	}

	parsingStream.Write(typeID);

	return parsingStream.DataCursor;
}