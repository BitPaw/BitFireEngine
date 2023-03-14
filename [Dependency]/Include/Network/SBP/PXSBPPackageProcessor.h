#ifndef PXSBPSocketINCLUDE
#define PXSBPSocketINCLUDE

#include <Format/Type.h>
#include <Container/Dictionary/PXDictionary.h>

#include <OS/Network/PXSocket.h>

#include "SBPDataChunk.h"
#include "SBPProtocol.h"

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct PXSBPPackageProcessor_
	{
		// Private
		SBPPackageHeaderCache DataCache;
		PXDictionary ChannalEntryLookup; // Look for active channels

		// Public
		void* Owner;
	}
	PXSBPPackageProcessor;

	//---<Events>--------------------------------------------------------------
	PXPublic void PXSBPPackageProcessorOnDataRawSend(const PXSocket* const pxSocket, const void* message, const PXSize messageSize);
	PXPublic void PXSBPPackageProcessorOnDataRawReceive(const PXSocket* const pxSocket, const void* const message, const PXSize messageSize);

	PXPublic void PXSBPPackageProcessorOnChunkRecived(PXSBPPackageProcessor* const pxSBPPackageProcessor, SBPPackageHeaderCache* const sbpDataCache, const SBPPackageHeaderChunk* const sbpDataChunk);

	PXPublic void PXSBPPackageProcessorOnPackageRecived(PXSBPPackageProcessor* const pxSBPPackageProcessor, const SBPPackageHeader* const sbpDataPackage);

	PXPublic void PXSBPPackageProcessorPackageHandle(PXSBPPackageProcessor* const pxSBPPackageProcessor, const SBPPackageHeader* const sbpDataPackage);

	PXPublic void PXSBPPackageProcessorPackageExport(PXSBPPackageProcessor* const pxSBPPackageProcessor, const SBPPackageHeader* const sbpDataPackage);
	//-------------------------------------------------------------------------


	//-------------------------------------------------------------------------
	PXPublic void PXSBPPackageProcessorConstruct(PXSBPPackageProcessor* const pxSBPPackageProcessor);
	PXPublic void PXSBPPackageProcessorDestruct(PXSBPPackageProcessor* const pxSBPPackageProcessor);
	//-------------------------------------------------------------------------



	//-------------------------------------------------------------------------
	//PXPublic void PXSBPPackageBuildIAM();
	//-------------------------------------------------------------------------


#ifdef __cplusplus
}
#endif

#endif
