#pragma once


#include "Camera.h"
#include "../../../../MathSystem/Dependencies/include/glm/ext/matrix_float4x4.hpp"
#include "../../../../MathSystem/Source/Geometry/Direction.h"

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