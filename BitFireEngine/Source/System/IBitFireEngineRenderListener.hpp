#pragma once

#include "../../../SystemResource/Source/Image/Image.h"
#include "../../../SystemResource/Source/Model/Model.h"
#include "../../../SystemResource/Source/Game/SkyBox.h"

namespace BF
{
	class IBitFireEngineRenderListener
	{
		public:
		virtual void Register(SkyBox& skyBox) = 0;
		virtual void Register(Model& model) = 0;
		virtual void Register(Image& image) = 0;

		virtual void Select(SkyBox& skyBox) = 0;
		virtual void Select(Model& model) = 0;
		virtual void Select(Image& image) = 0;

		virtual void UnRegister(SkyBox& skyBox) = 0;
		virtual void UnRegister(Model& model) = 0;
		virtual void UnRegister(Image& image) = 0;
	};
}