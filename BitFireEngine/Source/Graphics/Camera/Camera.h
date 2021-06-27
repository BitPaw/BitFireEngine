#pragma once

#include "CameraSettings.h"
#include "../../System/GameTickData.h"

#include "../../../../MathSystem/Source/Geometry/Direction.h"

#include "../../../../MathSystem/Source/Geometry/Position.hpp"
#include "../../../../MathSystem/Source/Geometry/Vector3.hpp"
#include "../../../../MathSystem/Source/Geometry/Matrix4x4.hpp"

namespace BF
{
	class Camera
	{
		protected:
		float _walkSpeed;
		float _viewSpeed;

		public:


		Matrix4x4 _projection;
		Matrix4x4 _view;
		Matrix4x4 _viewProjection;
		Vector3 _position;

		CameraSettings* Settings;
		Position<float> CurrentPosition;

		Camera();
		Camera(CameraSettings* settings);

		void UpdateSystemLink();

		virtual void Move(Direcion direction);
		virtual void Update(GameTickData gameTickData);

		Matrix4x4 GetUpdatedViewProjection()
		{
			return _viewProjection;
		}
	};
}