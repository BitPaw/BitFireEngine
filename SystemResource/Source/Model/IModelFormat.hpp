#pragma once

#include "Model.h"
#include "../IFileFormat.hpp"

namespace BF
{
	struct IModelFormat : public IFileFormat
	{
		virtual ActionResult ConvertTo(Model& model) = 0;
		virtual ActionResult ConvertFrom(Model& model) = 0;
	};
}