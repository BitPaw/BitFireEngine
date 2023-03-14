#ifndef HardDriveINCLUDE
#define HardDriveINCLUDE

#include <Format/Type.h>

#include <OS/Error/PXActionResult.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct HardDrive_
	{
		unsigned char Letter; // Windows Only

		PXSize ClustersTotal;      // The total number of clusters, both used and available, on the disk.
		PXSize ClustersFree;      // The number of unused clusters on the disk.
		PXSize ClusterSectors; // The number of sectors in each cluster.
		PXSize ClusterSectorSize;    // The size of each sector in bytes.
	}
	HardDrive;

	PXPublic PXSize HardDriveListSize();

	PXPublic PXActionResult HardDriveFetchAll(HardDrive* const hardDriveList, const PXSize hardDriveListMaxSize, PXSize* hardDriveListSize);

#ifdef __cplusplus
}
#endif

#endif