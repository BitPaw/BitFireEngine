#pragma once

#include "Model.h"
#include "../IFileFormat.hpp"

namespace BF
{
	struct IModelFormat : public IFileFormat
	{
		virtual FileActionResult ConvertTo(Model& model) = 0;
		virtual FileActionResult ConvertFrom(Model& model) = 0;
	};
}