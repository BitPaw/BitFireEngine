#pragma once

#include "Dialog.h"

#include <cstddef>

namespace BF
{
	struct DialogBox
	{
		void DataFill(Dialog* dialogList, size_t dialogListSize);
		void DataClear();
	};
}
