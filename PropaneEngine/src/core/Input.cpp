#include "core/Input.h"

#include <iostream>

using namespace std;

bool PE::Input::getKeyValue(int keycode)
{
	if (_keyValues.contains(keycode))
		return _keyValues[keycode];
	else
		return false;
}

bool PE::Input::getMouseButton(int mouseButton)
{
	if (_mouseButtonValues.contains(mouseButton))
		return _mouseButtonValues[mouseButton];
	else
		return false;
}

PE::Input::Mouse PE::Input::getMouseData()
{
	return _mouseData;
}

void PE::Input::setCursorMode(PE::Input::CURSOR_MODE mode)
{
	if (_window == nullptr)
		return;

	switch (mode)
	{
	case CURSOR_MODE::HIDDEN:
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		break;
	case CURSOR_MODE::LOCKED:
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		break;
	case CURSOR_MODE::NORMAL:
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		break;
	}
}

void PE::Input::initializeCallbacks(GLFWwindow* window)
{
	_window = window;

	cout << "Binding input callbacks" << endl;

	glfwSetCursorPosCallback(_window, cursorPositionCallback);
	glfwSetMouseButtonCallback(_window, mouseButtonCallback);
	glfwSetScrollCallback(_window, scrollCallback);
	glfwSetKeyCallback(_window, keyCallback);
}

void PE::Input::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	_mouseData.delta = glm::vec2(xpos, ypos) - _mouseData.position;
	_mouseData.position = glm::vec2(xpos, ypos);
}

void PE::Input::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
		_mouseButtonValues[button] = true;
	else if (action == GLFW_RELEASE)
		_mouseButtonValues[button] = false;
}

void PE::Input::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	_mouseData.scrollOffset = glm::vec2(xoffset, yoffset);
}

void PE::Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
		_keyValues[key] = true;
	else if (action == GLFW_RELEASE)
		_keyValues[key] = false;
}

GLFWwindow* PE::Input::_window;
PE::Input::Mouse PE::Input::_mouseData;
std::unordered_map<int, bool> PE::Input::_keyValues;
std::unordered_map<int, bool> PE::Input::_mouseButtonValues;