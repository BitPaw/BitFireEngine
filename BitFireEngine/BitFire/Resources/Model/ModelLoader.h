#pragma once

#include <string>

#include "IModel.h"
#include "Model.h"
#include "ModelType.h"

#include "3DS/A3DSLoader.h"
#include "FBX/FBXLoader.h"
#include "OBJ/OBJLoader.h"
#include "PLY/PLYLoader.h"
#include "STL/STLLoader.h"
#include "WRL/WRLLoader.h"

#include "../../Color/RGBA.h"
#include "../../IO/File/TextFile.h"
#include "../../IO/Message/MessageSystem.h"

namespace BF
{
	class ModelLoader
	{
	public:
		static IModel* LoadFromFile(std::string filePath);
		static void SaveToFile(std::string filePath);

		// Translator
		static Model* OBJToModel(OBJ* waveFront);
	};
}