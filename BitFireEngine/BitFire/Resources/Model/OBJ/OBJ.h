#pragma once

#include <string>
#include <stdio.h>

#include "OBJElement.h"
#include "MTL/MTL.h"

#include "../IModel.h"

namespace BF
{
	// [.OBJ] Wavefront - 3D model format
	struct OBJ : public IModel
	{
	public:
		std::string Name = "[N/A]";
		List<MTL> Materials;
		List<OBJElement> ElementList;
	};
}