#pragma once

#include "CameraSettings.h"
#include "../../System/GameTickData.h"

#include "../../../../ResourceSystem/Source/Math/Geometry/Direction.h"
#include "../../../../ResourceSystem/Source/Math/Geometry/Position.hpp"
#include "../../../../ResourceSystem/Source/Math/Geometry/Vector3.hpp"
#include "../../../../ResourceSystem/Source/Math/Geometry/Matrix4x4.hpp"

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