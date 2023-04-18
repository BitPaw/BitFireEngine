#ifndef BFDialogSystemINCLUDE
#define BFDialogSystemINCLUDE

#include <Media/PXType.h>

#ifdef __cplusplus
extern "C"
{
#endif

	typedef struct BFDialog_
	{
		unsigned int SourceID;
		unsigned int TargetID;

		// 

		char* Message;
	}
	BFDialog;



	typedef struct BFDialogBox_
	{
		int dummy;
	}
	BFDialogBox;

	//PXPublic void DataFill(Dialog* dialogList, size_t dialogListSize);
	//PXPublic void DataClear();

#ifdef __cplusplus
}
#endif

#endif