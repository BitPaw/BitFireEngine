#pragma once

#include "CameraPerspective.hpp"
#include "../Math/Geometry/Direction.h"
#include "../Math/Geometry/Vector3.hpp"
#include "../Math/Geometry/Matrix4x4.hpp"
#include "../../../RenderSystem/Source/RefreshRateMode.h"

namespace BF
{
	class Camera
	{
		private:
		Vector3<float> _up;
		Vector3<float> _lookAt;

		protected:
		float _walkSpeed;
		float _viewSpeed;		

		public:
		Matrix4x4<float> MatrixModel;
		Matrix4x4<float> MatrixView;
		Matrix4x4<float> MatrixProjection;		

		CameraPerspective Perspective;

		Position<float> CurrentRotation;

		float FieldOfView;
		unsigned int Height;
		unsigned int Width;
		float Near;
		float Far;	

		Camera();

		void Rotate(float x, float y);
		void Move(Direcion direction);
		void Update(float deltaTime);
		float GetAspectRatio();
	};
}