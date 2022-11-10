#include "render/components/Mesh.h"

#include <iostream>

#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>

#include <GLFW/glfw3.h>

#include <imgui.h>

#include "render/Shader.h"

using namespace std;

PE::Mesh::Mesh():
	_vao(0),
	_vbo(0),
	_ebo(0),
	_buffersCreated(false),
	_material(nullptr)
{

}

void PE::Mesh::setVertices(std::vector<Vertex> vertices, std::vector<unsigned int> indices) 
{
	_vertices = vertices;
	_indices = indices;

	reloadData();
}

void PE::Mesh::useMaterial(std::shared_ptr<Material> material)
{
	_material = material;

	reloadData();
}

void PE::Mesh::onStart()
{
	
}

void PE::Mesh::render(Camera* camera)
{
	//use the material
	_material->useMaterial();

	//enable the vao
	glBindVertexArray(_vao);

	//find the mvp and calculate the camera
	int mvpLocation = _material->getShader().getUniformLocation("mvp");
	if (mvpLocation != -1)
	{
		glm::mat4 model = getTransform()->getTransformMatrix();

		glm::mat4 mvp = camera->getProjectionMatrix() * camera->getLookMatrix() * model;

		glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(mvp));
	}

	//draw all the bound indices
	glDrawElements(GL_TRIANGLES, (GLsizei)_indices.size(), GL_UNSIGNED_INT, 0);

	//unbind to prevent accidental modification
	glBindVertexArray(0);
}

void PE::Mesh::update()
{

}

void PE::Mesh::onDestroy()
{
	if (!_buffersCreated)
		return;

	glDeleteBuffers(1, &_vbo);
	glDeleteBuffers(1, &_ebo);
	glDeleteVertexArrays(1, &_vao);
}

void PE::Mesh::reloadData()
{
	//quit if no vertices or material
	if (_vertices.size() == 0  || _indices.size() == 0)
		return;
	if (_material == nullptr)
		return;

	if (!_buffersCreated)
	{
		//generate vaos for storing pointer properties once (and only once)
		glGenVertexArrays(1, &_vao);
		//generate vbo
		glGenBuffers(1, &_vbo);
		//create an ebo to reduce data allocated
		glGenBuffers(1, &_ebo);
		_buffersCreated = true;
	}

	//bind vao for storage of subsequent data
	glBindVertexArray(_vao);

	//bind vbo to the array buffer and then set up its data
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_STATIC_DRAW);

	//bind EBO to reduce amount of data needed and set its indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW);

	//determine if position data needs to be written
	int vertPos = _material->getShader().getAttribLocation("vertPos");
	if (vertPos != -1)
	{
		//3 values of type float, not normalized with a gap of one Vertex object with an offset of the position location
		glVertexAttribPointer(vertPos, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		glEnableVertexAttribArray(vertPos);
	}

	//determine if uv data needs to be writen
	int uvPos = _material->getShader().getAttribLocation("texCoord");
	if (uvPos != -1)
	{
		//2 values of type float, not noramlized with a gap of one Vertex object with an offset of the uv location
		glVertexAttribPointer(uvPos, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
		glEnableVertexAttribArray(uvPos);
	}
	
	//unuse the vao to prevent accidental modification
	glBindVertexArray(0);
}