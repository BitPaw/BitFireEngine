#pragma once

#include "IModel.h"
#include "Model.h"
#include "ModelType.h"

#include "FBX/FBX.h"
#include "OBJ/OBJ.h"
#include "PLY/PLY.h"
#include "STL/STL.h"
#include "WRL/WRL.h"

#include "../../Color/RGBA.hpp"
#include "../../Mathematic/Geometry/Shape/Shape.h"
#include "../../Mathematic/Geometry/Form/Form.h"

#include "../ErrorCode.h"

namespace BF
{
	class ModelLoader
	{
	public:
		static ModelType ParseModelType(AsciiString& extension);

		static bool IsModelFile(AsciiString& extension);

		static ErrorCode LoadFromFile(AsciiString& filePath, Model& model);

		// Translator
		static void ToModel(Shape& form, Model& model);
	};
}