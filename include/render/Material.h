#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "Texture.h"
#include "Shader.h"

namespace PE {
	class Material {
	public:
		Material(Texture& diffuse, glm::vec4 color, Shader& shader);

		void useMaterial();

		Shader& getShader() const;
		Texture& getDiffuseTexture() const;

		//define the move operator because compiler is whining
		Material& operator=(const Material& other)
		{
			return *this;
		}
	private:
		glm::vec4 _color;
		Shader& _shader;
		Texture& _diffuse;
	};
}