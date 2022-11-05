#include "render/Model.h"

#include <iostream>

#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>

#include <GLFW/glfw3.h>

#include "render/Shader.h"

using namespace std;

PE::Model::Model(bool drawStatic):
	_drawStatic(drawStatic),
	_shader(),
	_vao(0),
	_vbo(0),
	_transform()
{
}

void PE::Model::init()
{
	//manually load shader
	_shader.compile("./shaders/default.vert", "./shaders/default.frag");

	//generate vaos for storing pointer properties once (and only once)
	glGenVertexArrays(1, &_vao);
	//generate vbo
	glGenBuffers(1, &_vbo);

	//bind vao for storage of subsequent data
	glBindVertexArray(_vao);
	//bind vbo to the array buffer to modify it directly
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);

	//create some temporary vertex data for testing reasons
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.f, 0.5f, 0.0f
	};

	//set the data for the vbo to be the verts
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, _drawStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);

	//determine if position data needs to be written
	int vertPos = _shader.getAttribLocation("vertPos");
	if (vertPos != -1) {
		//3 values of type float, no normalized with a gap of 3 floats with no offset for first data piece
		glVertexAttribPointer(vertPos, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(vertPos);
	}

	//unbind the vbo since the vao now associates with it
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//unuse the vao to prevent accidental modification
	glBindVertexArray(0);
}

void PE::Model::render()
{
	_transform.setRotation(glm::angleAxis(glm::radians(90.0f * (float)glfwGetTime()), glm::vec3(0.0f, 0.0f, 1.0f)));
	_transform.setScale(glm::vec3(1.0f, ((sin(glfwGetTime()) + 1.0f) / 2.0f) * 2.0f, 1.0f));

	//enable the shader and vao
	_shader.useShader();
	glBindVertexArray(_vao);

	//find the mvp and calculate the camera
	int mvpLocation = _shader.getUniformLocation("mvp");
	if (mvpLocation != -1) {
		glm::mat4 model = glm::translate(glm::mat4(1.0f), _transform.getPosition())
			* glm::toMat4(_transform.getRotation())
			* glm::scale(glm::mat4(1.0f), _transform.getScale());

		//uses camera pos, target pos, and up direction
		glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f));

		glm::mat4 projection = glm::perspective(glm::radians(45.0f), 640.0f / 480.0f, 0.1f, 100.0f);
		glm::mat4 mvp = projection * view * model;

		glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(mvp));
	}

	//draw 3 verts
	glDrawArrays(GL_TRIANGLES, 0, 3);

	//unbind to prevent accidental modification
	glBindVertexArray(0);
}

void PE::Model::cleanUp()
{
	glDeleteBuffers(1, &_vbo);
	glDeleteVertexArrays(1, &_vao);
	_shader.free();
}
