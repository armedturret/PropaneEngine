#include "render/Material.h"

#include <iostream>

#include <gl/glew.h>
#include <glm/gtc/type_ptr.hpp>

PE::Material::Material(std::vector<Texture> diffuseTextures, std::vector<Texture> specularTextures, glm::vec4 color, Shader shader):
	_diffuseTextures(diffuseTextures),
	_specularTextures(specularTextures),
	_shader(shader),
	_color(color)
{
}

void PE::Material::useMaterial()
{
	//enable the shader
	_shader.useShader();
	
	//set the color property if it exists
	if (_shader.getUniformLocation("color") != -1)
	{
		glUniform4fv(_shader.getUniformLocation("color"), 1, glm::value_ptr(_color));
	}

	//use the textures if they exist
	int texIndex = 0;
	for (int i = 0; i < _diffuseTextures.size(); i++)
	{
		std::string target = "diffuseTex" + std::to_string(i);
		if (_shader.getUniformLocation(target) != -1)
		{
			//set the diffuse texture to point to texture 0
			glUniform1i(_shader.getUniformLocation(target), 0);

			//bind the current texture to a diffuse texture
			glActiveTexture(GL_TEXTURE0 + texIndex);
			glBindTexture(GL_TEXTURE_2D, _diffuseTextures[i].getTexture());
			texIndex++;
		}
	}

	for (int i = 0; i < _specularTextures.size(); i++)
	{
		std::string target = "target" + std::to_string(i);
		if (_shader.getUniformLocation(target) != -1)
		{
			//set the diffuse texture to point to texture 0
			glUniform1i(_shader.getUniformLocation(target), 0);

			//bind the current texture to a specular texture
			glActiveTexture(GL_TEXTURE0 + texIndex);
			glBindTexture(GL_TEXTURE_2D, _specularTextures[i].getTexture());
			texIndex++;
		}
	}

	glActiveTexture(GL_TEXTURE0);
}

PE::Shader PE::Material::getShader() const
{
	return _shader;
}

std::vector<PE::Texture> PE::Material::getDiffuseTextures() const
{
	return _diffuseTextures;
}

std::vector<PE::Texture> PE::Material::getSpecularTextures() const
{
	return _specularTextures;
}