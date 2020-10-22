#include "FirstPersonCamera.h"

void BF::FirstPersonCamera::Rotate(float x, float y)
{
	const float maxValue = 85.0f;
	const float minValue = -85.0f;
	float movementSpeed = GetViewSpeed();

	CurrentRotation.Yaw -= x * movementSpeed;
	CurrentRotation.Pitch += y * movementSpeed;

	// Cap
	if (CurrentRotation.Pitch > maxValue)
	{
		CurrentRotation.Pitch = maxValue;
	}

	if (CurrentRotation.Pitch < minValue)
	{
		CurrentRotation.Pitch = minValue;
	}

	float pitchRAD = glm::radians(CurrentRotation.Pitch);
	float yawRAD = glm::radians(CurrentRotation.Yaw);

	glm::vec3 temp;

	temp.x = cos(pitchRAD) * cos(yawRAD);
	temp.y = sin(pitchRAD);
	temp.z = cos(pitchRAD) * sin(yawRAD);

	_lookAt = glm::normalize(temp);

	Update();
}

void BF::FirstPersonCamera::Update()
{

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
}

void BF::FirstPersonCamera::Move(Direcion direction)
{
	glm::vec3 movement;
	float movementSpeed = GetWalkSpeed();

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

	_view = glm::translate(_view, movement * (-1.0f));

	Update();
}

BF::FirstPersonCamera::FirstPersonCamera() : Camera()
{
	Settings->Mode = CameraMode::Perspectdive;

	_up = glm::vec3(0.0f, 1.0f, 0.0f);

	Rotate(0,0);
}
