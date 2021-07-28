#include "FirstPersonCamera.h"
#include "../../../../RenderSystem/Source/OpenGLAPI.h"
#include "../../../../ResourceSystem/Dependencies/include/glm/ext/matrix_clip_space.hpp"

void BF::FirstPersonCamera::FetchGPUReferences(unsigned int shaderID)
{
	int old_modelViewProjectionID = _matrixModelID;
	int old_inverseModelViewID = _matrixViewID;
	int old_modelViewID = _matrixProjectionID;
	int old_textureID = _materialTextureID;

	_matrixModelID = OpenGLAPI::ShaderGetUniformLocationID(shaderID, "MatrixModel");
	_matrixViewID = OpenGLAPI::ShaderGetUniformLocationID(shaderID, "MatrixView");
	_matrixProjectionID = OpenGLAPI::ShaderGetUniformLocationID(shaderID, "MatrixProjection");
	_materialTextureID = OpenGLAPI::ShaderGetUniformLocationID(shaderID, "MaterialTexture");

	ValidShader = true;

	/*
	if (_matrixModelID == -1 || _matrixViewID == -1 || _matrixProjectionID == -1)
	{
		_matrixModelID = old_modelViewProjectionID;
		_matrixViewID = old_inverseModelViewID;
		_matrixProjectionID = old_modelViewID;
		_materialTextureID = old_textureID;
		ValidShader = false;
	}
	else
	{
		ValidShader = true;
	}*/
}

void BF::FirstPersonCamera::Rotate(float x, float y)
{
	const float maxValue = 85.0f;
	const float minValue = -85.0f;
	float movementSpeed = _viewSpeed;

	CurrentRotation.X -= x * movementSpeed;
	CurrentRotation.Y += y * movementSpeed;

	// Cap
	if (CurrentRotation.Y > maxValue)
	{
		CurrentRotation.Y = maxValue;
	}

	if (CurrentRotation.Y < minValue)
	{
		CurrentRotation.Y = minValue;
	}

	float pitchRAD = glm::radians(CurrentRotation.Y);
	float yawRAD = glm::radians(CurrentRotation.X);


	float rx = cos(pitchRAD) * cos(yawRAD);
	float ry = sin(pitchRAD);
	float rz = cos(pitchRAD) * sin(yawRAD);

	_lookAt.Set(rx, ry, rz);
	_lookAt.Normalize();
}

void BF::FirstPersonCamera::Update(GameTickData gameTickData)
{
	Vector4<float> currentPositionx4 = MatrixModel.CurrentPosition();
	Vector3<float> currentPosition = Vector3<float>(currentPositionx4.Date[0], currentPositionx4.Date[1], currentPositionx4.Date[2]);

	_walkSpeed = gameTickData.GetSmoothDeltaTime() * 30;
	_viewSpeed = gameTickData.GetSmoothDeltaTime() * 350;

	if (!ValidShader)
	{
		return;
	}

	switch (Settings->Mode)
	{
		case CameraMode::Orthographic:
			MatrixProjection.Orthographic(-1.0f, 1.0f, -1.0f, 1.0f, -10.0f, Settings->Far);
			break;

		case CameraMode::Perspectdive:
			MatrixProjection.Perspective(Settings->FieldOfView, 1.0f, Settings->Near, Settings->Far);
			break;
	}

	MatrixView.LookAt(currentPosition, currentPosition + _lookAt, _up);

	//printf("CurrentPosition <%2.2f %2.2f %2.2f>\n", currentPosition.Data[0], currentPosition.Data[1], currentPosition.Data[2]);

	OpenGLAPI::ShaderSetUniformMatrix4x4(_matrixModelID, MatrixModel.Data);
	OpenGLAPI::ShaderSetUniformMatrix4x4(_matrixViewID, MatrixView.Data);
	OpenGLAPI::ShaderSetUniformMatrix4x4(_matrixProjectionID, MatrixProjection.Data);
}

void BF::FirstPersonCamera::Move(Direcion direction)
{
	Vector3<float> movement;
	float movementSpeed = _walkSpeed;

	switch (direction)
	{
	case Direcion::Up:
		movement.Set(0, 1, 0);
		break;

	case Direcion::Down:
		movement.Set(0, -1, 0);
		break;

	case Direcion::Left:		
		movement.CrossProduct(_lookAt, _up);
		movement *= Vector3<float>(-1, 0, -1);
		movement.Normalize();
		break;

	case Direcion::Right:
		movement.CrossProduct(_lookAt, _up);
		movement *= Vector3<float>(1, 0, 1);
		movement.Normalize();
		break;

	case Direcion::Forward:
		movement = _lookAt * Vector3<float>(1, 0, 1); // Remove Y movement
		break;

	case Direcion::Backward:
		movement = _lookAt * Vector3<float>(-1, 0, -1);
		break;
	}

	movement *= -movementSpeed;	

	MatrixModel.Move(movement);
	//MatrixView.Move(movement);
}

BF::FirstPersonCamera::FirstPersonCamera() : Camera()
{
	ValidShader = false;
	Settings->Mode = CameraMode::Perspectdive;

	_up.Set(0.0f, 1.0f, 0.0f);

	Rotate(0,0);
}
