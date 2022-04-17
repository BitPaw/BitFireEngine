#pragma once

#include "CameraPerspective.hpp"

#include <Math/Geometry/Vector3.hpp>
#include <Math/Geometry/Matrix4x4.hpp>
#include <Math/Physic/PhysicsDynamic.hpp>
#include <Media/Video/RefreshRateMode.h>

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
			
		//---<Follow>---
		Vector3<float> Offset;
		Matrix4x4<float>* Target;
		float FollowSpeed = 0.98f; // Ranges from 0 to 1

		CameraPerspective Perspective;

		float FieldOfView;
		unsigned int Height;
		unsigned int Width;
		float Near;
		float Far;	

		Camera();

		void Rotate(float x, float y);
		void Move(const float x, const float y, const float z);
		void Move(Vector3<float> movement);
		void Update(float deltaTime);
		float AspectRatioGet();
		void AspectRatioSet(float width, float height);

		void ViewChange(const CameraPerspective cameraPerspective);
		void ViewChangeOrthographic(const float width, const float height, const float nearPlane, const float farPlane);
		void ViewChangePerspective(const float fieldOfView, const float aspectRatio, const float near, const float far);

		void Follow(float deltaTime);
	};
}