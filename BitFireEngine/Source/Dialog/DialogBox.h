#pragma once

#include "Dialog.h"

namespace BF
{
	struct DialogBox
	{
		void DataFill(Dialog* dialogList, size_t dialogListSize);
		void DataClear();
	};
}