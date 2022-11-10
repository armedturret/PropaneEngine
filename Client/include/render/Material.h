#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <vector>

#include "Texture.h"
#include "Shader.h"

namespace PE {
	class Material {
	public:
		Material(std::vector<Texture> diffuseTextures, std::vector<Texture> specularTextures, glm::vec4 color, Shader shader);

		void useMaterial();

		Shader getShader() const;
		std::vector<Texture> getDiffuseTextures() const;
		std::vector<Texture> getSpecularTextures() const;
	private:
		glm::vec4 _color;
		Shader _shader;
		std::vector<Texture> _diffuseTextures;
		std::vector<Texture> _specularTextures;
	};
}