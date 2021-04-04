#include "FirstPersonCamera.h"

void BF::FirstPersonCamera::FetchGPUReferences(unsigned int shaderID)
{
	int old_modelViewProjectionID = _modelViewProjectionID;
	int old_inverseModelViewID = _inverseModelViewID;
	int old_modelViewID = _modelViewID;
	int old_textureID = _textureID;

	_modelViewProjectionID = glGetUniformLocation(shaderID, "ModelViewProjection");
	_inverseModelViewID = glGetUniformLocation(shaderID, "ModelView");
	_modelViewID = glGetUniformLocation(shaderID, "InverseModelView");
	_textureID = glGetUniformLocation(shaderID, "objtexture");

	if (_modelViewProjectionID == -1 || _inverseModelViewID == -1 || _modelViewID == -1)
	{
		_modelViewProjectionID = old_modelViewProjectionID;
		_inverseModelViewID = old_inverseModelViewID;
		_modelViewID = old_modelViewID;
		_textureID = old_textureID;
		ValidShader = false;
	}
	else
	{
		ValidShader = true;
	}
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

	glm::vec3 temp;

	temp.x = cos(pitchRAD) * cos(yawRAD);
	temp.y = sin(pitchRAD);
	temp.z = cos(pitchRAD) * sin(yawRAD);

	_lookAt = glm::normalize(temp);
}

void BF::FirstPersonCamera::Update(GameTickData gameTickData)
{
	_walkSpeed = gameTickData.GetSmoothDeltaTime() * 30;
	_viewSpeed = gameTickData.GetSmoothDeltaTime() * 350;

	if (!ValidShader)
	{
		return;
	}

	switch (Settings->Mode)
	{
		case CameraMode::Orthographic:
			_projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -10.0f, Settings->Far);
			break;

		case CameraMode::Perspectdive:
			_projection = glm::perspective(glm::radians(Settings->FieldOfView), 1.0f, Settings->Near, Settings->Far);
			break;
	}

	_view = glm::lookAt(_position, _position + _lookAt, _up);

	_viewProjection = _projection * _view;

	//----
	glm::mat4 cameraView = _view;
	glm::mat4 cameraProjection = _projection;

	_modelView = cameraView * glm::mat4(1.0f);
	_invModelView = glm::transpose(glm::inverse(_modelView));

	glm::vec3 offset = glm::vec3(0, 0, 0);
	glm::mat4 diff = glm::translate(cameraView, offset);

	_completematrix = cameraProjection * diff * glm::mat4(1.0f);

	glUniformMatrix4fv(_modelViewID, 1, GL_FALSE, &_modelView[0][0]);
	glUniformMatrix4fv(_modelViewProjectionID, 1, GL_FALSE, &_completematrix[0][0]);
	glUniformMatrix4fv(_inverseModelViewID, 1, GL_FALSE, &_invModelView[0][0]);
	// -----
}

void BF::FirstPersonCamera::Move(Direcion direction)
{
	glm::vec3 movement;
	float movementSpeed = _walkSpeed;

	switch (direction)
	{
	case Direcion::Up:
		movement = glm::vec3(0, movementSpeed, 0);
		break;

	case Direcion::Down:
		movement = glm::vec3(0, -movementSpeed, 0);
		break;

	case Direcion::Left:
		movement = glm::normalize(glm::cross(_lookAt, _up)) * -movementSpeed;
		break;

	case Direcion::Right:
		movement = glm::normalize(glm::cross(_lookAt, _up)) * movementSpeed;
		break;

	case Direcion::Forward:
		movement = glm::normalize(_lookAt) * glm::vec3(movementSpeed,0, movementSpeed);
		break;

	case Direcion::Backward:
		movement = glm::normalize(_lookAt) * glm::vec3(-movementSpeed, 0, -movementSpeed);
		break;
	}

	_position += movement;

	CurrentPosition.Add(movement.x, movement.y, movement.z);

	_view = glm::translate(_view, movement * (-1.0f));
}

BF::FirstPersonCamera::FirstPersonCamera() : Camera()
{
	ValidShader = false;
	Settings->Mode = CameraMode::Perspectdive;

	_up = glm::vec3(0.0f, 1.0f, 0.0f);

	Rotate(0,0);
}
