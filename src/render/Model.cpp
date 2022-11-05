#include "render/Model.h"

#include <gl/glew.h>

#include "render/Shader.h"

void PE::Model::init()
{
	//generate vbo
	glGenBuffers(1, &_vbo);

	//bind vbo to the array buffer to modify it directly
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	//create some temporary vertex data for testing reasons
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.f, 0.5f, 0.0f
	};

	//set the data for the vbo
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//manually load shader
	_shader.compile("./shaders/default.vert", "./shaders/default.frag");
}

void PE::Model::render()
{
}

void PE::Model::cleanUp()
{
	_shader.free();
}
