#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <unordered_map>

namespace PE {
	class Input {
	public:
		struct Mouse {
			glm::vec2 delta;
			glm::vec2 position;
			glm::vec2 scrollOffset;
		};

		enum CURSOR_MODE{LOCKED, HIDDEN, NORMAL};
		
		static bool getKeyValue(int keycode);
		static bool getMouseButton(int mouseButton);

		static Mouse getMouseData();

		static void setCursorMode(CURSOR_MODE mode);

		static void initializeCallbacks(GLFWwindow* window);

	private:
		static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

		friend class Application;

		static GLFWwindow* _window;
		static Mouse _mouseData;
		static std::unordered_map<int, bool> _keyValues;
		static std::unordered_map<int, bool> _mouseButtonValues;
	};
}