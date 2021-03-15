#pragma once

#include "IModel.h"
#include "Model.h"
#include "ModelType.h"

#include "3DS/A3DSLoader.h"
#include "FBX/FBXLoader.h"
#include "OBJ/OBJLoader.h"
#include "PLY/PLYLoader.h"
#include "STL/STLLoader.h"
#include "WRL/WRLLoader.h"

#include "../../Color/RGBA.hpp"
#include "../../IO/File/TextFile.h"
#include "../../IO/Log/Log.h"
#include "../../Mathematic/Geometry/Shape/Shape.h"
#include "../../Mathematic/Geometry/Form/Form.h"

namespace BF
{
	class ModelLoader
	{
	public:
		static ModelType ParseModelType(ASCIIString& extension);

		static bool IsModelFile(ASCIIString& extension);

		static Model* LoadFromFile(ASCIIString& filePath);
		static void LoadFromFile(Model& model, ASCIIString& filePath);
		static void SaveToFile(Model& model, ASCIIString& filePath);

		// Translator
		static void ToModel(OBJ& waveFront, Model& model);
		static void ToModel(Shape& form, Model& model);
	};
}