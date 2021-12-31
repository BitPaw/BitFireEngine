#include "ProgramExecuteInfo.h"

BF::ProgramExecuteInfo::ProgramExecuteInfo()
{
	for (size_t i = 0; i < sizeof(FilePath); i++)
	{
		FilePath[i] = '#';
	}

	CallBack = nullptr;
	ParameterList = nullptr;
	ParameterListSize = 0;
}