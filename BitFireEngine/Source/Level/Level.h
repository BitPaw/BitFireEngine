#pragma once

#include <Error/ActionResult.h>
#include <Graphic/PXCamera.h>

#include "../Dialog/Dialog.h"
#include <Graphic/Graphic.h>


namespace BF
{
	class Level// : public Resource
	{
		public:
		// Physics Container
		//List<Model*> ModelList;
		//List<Texture*> TextureList;
		//List<Sound*> SoundList;
		//List<PXFont*> FontList;
		//List<Shader*> ShaderList;
		//List<Dialog*> DialogList;
		//List<PXCamera*> CameraList;

		static bool IsLevelFile(const wchar_t* filePath);

		ActionResult Load(const wchar_t* filePath);

		size_t FullSizeInMemory();
	};
}
