#include "render/Material.h"

#include <gl/glew.h>
#include <glm/gtc/type_ptr.hpp>

PE::Material::Material(Texture& diffuse, glm::vec4 color, Shader& shader):
	_shader(shader),
	_diffuse(diffuse),
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
	if (_shader.getUniformLocation("diffuseTex") != -1)
	{
		//set the diffuse texture to point to texture 0
		glUniform1i(_shader.getUniformLocation("diffuseTex"), 0);

		//bind the first texture to be the diffuse
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _diffuse.getTexture());
	}
}

PE::Shader& PE::Material::getShader() const
{
	return _shader;
}

PE::Texture& PE::Material::getDiffuseTexture() const
{
	return _diffuse;
}