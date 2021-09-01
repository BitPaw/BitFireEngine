#pragma once

#include "CameraPerspective.hpp"
#include "../Math/Geometry/Vector3.hpp"
#include "../Math/Geometry/Matrix4x4.hpp"
#include "../Math/Physic/PhysicalBody.hpp"
#include "../../../RenderSystem/Source/RefreshRateMode.h"

namespace BF
{
	class Camera : public PhysicalBody<float>
	{
		protected:
		float _walkSpeed;
		float _viewSpeed;		

		public:
		Vector3<float> LookAtPosition;
		Matrix4x4<float> MatrixModel;
		Matrix4x4<float> MatrixView;
		Matrix4x4<float> MatrixProjection;		


		CameraPerspective Perspective;

		Vector3<float> CurrentRotation;

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