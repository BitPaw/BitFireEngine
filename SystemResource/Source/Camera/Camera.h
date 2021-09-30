#pragma once

#include "CameraPerspective.hpp"
#include "../Math/Geometry/Vector3.hpp"
#include "../Math/Geometry/Matrix4x4.hpp"
#include "../Math/Physic/PhysicsDynamic.hpp"
#include "../../../SystemRender/Source/RefreshRateMode.h"

namespace BF
{
	class Camera : public PhysicsDynamic<float>
	{
		protected:
		float _walkSpeed;
		float _viewSpeed;		

		public:
		Vector3<float> LookAtPosition;
		Vector3<float> CurrentRotation;

		Matrix4x4<float> MatrixView;
		Matrix4x4<float> MatrixProjection;		

		CameraPerspective Perspective;

		float FieldOfView;
		unsigned int Height;
		unsigned int Width;
		float Near;
		float Far;	

		Camera();

		void Rotate(float x, float y);
		void Move(Vector3<float> movement);
		void Update(float deltaTime);
		float GetAspectRatio();
		void PerspectiveChange(CameraPerspective cmeraPerspective);
	};
}