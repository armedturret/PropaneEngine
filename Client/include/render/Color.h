#pragma once

#include <glm/glm.hpp>

namespace PE {
	struct Color {
		Color(glm::uint8_t r, glm::uint8_t g, glm::uint8_t b):
			Color(r, g, b, 255)
		{
		}
		Color(glm::uint8_t r, glm::uint8_t g, glm::uint8_t b, glm::uint8_t a):
			Color(glm::u8vec4(r,g,b,a))
		{
		}
		Color(glm::u8vec4 rgba):
			rgba(rgba)
		{

		}

		glm::vec4 normalized()
		{
			return glm::vec4(rgba) / 255.0f;
		}

		glm::u8vec4 rgba;
	};

	const Color WHITE(255, 255, 255);
	const Color BLACK(0, 0, 0);
	const Color RED(255, 0, 0);
	const Color GREEN(0, 255, 0);
	const Color BLUE(0, 0, 255);
}