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

		int _matrixModelID;
		int _matrixViewID;
		int _matrixProjectionID;
		int _materialTextureID;

		public:
		Matrix4x4<float> MatrixModel;
		Matrix4x4<float> MatrixProjection;
		Matrix4x4<float> MatrixView;

		CameraSettings* Settings;

		Camera();
		Camera(CameraSettings* settings);

		void UpdateSystemLink();

		virtual void Move(Direcion direction);
		virtual void Update(GameTickData gameTickData);
	};
}