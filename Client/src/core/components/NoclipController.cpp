#include "core/components/NoclipController.h"

#include <iostream>

#include <glm/gtx/string_cast.hpp>

#include "Application.h"

#include "core/input.h"

PE::NoclipController::NoclipController():
	_speed(1.0f),
	_sensitivity(1.0f)
{

}

void PE::NoclipController::onStart()
{

}

void PE::NoclipController::update()
{
	//handle looking
	if (Input::getMouseButton(GLFW_MOUSE_BUTTON_1))
	{
		Input::setCursorMode(Input::CURSOR_MODE::LOCKED);
		_yaw -= Input::getMouseData().delta.x * _sensitivity.x;
		_pitch -= Input::getMouseData().delta.y * _sensitivity.y;
		_pitch = glm::clamp(_pitch, -89.99f, 89.99f);
		glm::vec3 rotation(0.0f);
		rotation.y = _yaw;
		//rotation.z = _pitch;
		getTransform()->setRotation(glm::quat(glm::radians(rotation)));
	}
	else
	{
		Input::setCursorMode(Input::CURSOR_MODE::NORMAL);
	}

	//movement controls
	glm::vec3 currentPos = getTransform()->getPosition();
	glm::vec3 desiredVelocity = glm::vec3(0.0f);
	if (Input::getKeyValue(GLFW_KEY_W))
	{
		desiredVelocity += getTransform()->getForward();
	}
	if (Input::getKeyValue(GLFW_KEY_S))
	{
		desiredVelocity += getTransform()->getBackward();
	}
	if (Input::getKeyValue(GLFW_KEY_A))
	{
		desiredVelocity += getTransform()->getLeft();
	}
	if (Input::getKeyValue(GLFW_KEY_D))
	{
		desiredVelocity += getTransform()->getRight();
	}
	if (Input::getKeyValue(GLFW_KEY_SPACE))
	{
		desiredVelocity += getTransform()->getUp();
	}
	if (Input::getKeyValue(GLFW_KEY_LEFT_CONTROL))
	{
		desiredVelocity += getTransform()->getDown();
	}
	desiredVelocity = desiredVelocity * _speed;
	getTransform()->setPosition(currentPos + getDeltaTime() * desiredVelocity);
}

void PE::NoclipController::onDestroy()
{

}

void PE::NoclipController::setSpeed(float speed)
{
	_speed = speed;
}

void PE::NoclipController::setSensitivity(glm::vec2 sensitivity)
{
	_sensitivity = sensitivity;
}