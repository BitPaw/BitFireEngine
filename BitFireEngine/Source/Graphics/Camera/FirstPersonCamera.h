#pragma once

#include "Camera.h"

#include "../../../../ResourceSystem/Source/Math/Geometry/Vector3.hpp"
#include "../../../../ResourceSystem/Source/Math/Geometry/Direction.h"

namespace BF
{
	class FirstPersonCamera : public Camera
	{
		private:
		Vector3<float> _up;
		Vector3<float> _lookAt;

		bool ValidShader;

		public:
		Position<float> CurrentRotation;

		void FetchGPUReferences(unsigned int shaderID);

		void Rotate(float x, float y);
		void Update(GameTickData gameTickData) override;
		void Move(Direcion direction) override;

		FirstPersonCamera();
	};
}