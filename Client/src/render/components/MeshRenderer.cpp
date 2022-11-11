#include "render/components/MeshRenderer.h"

#include <iostream>

#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>

#include <GLFW/glfw3.h>

#include <imgui.h>

#include "render/Shader.h"
#include "render/LightingData.h"

using namespace std;

PE::MeshRenderer::MeshRenderer():
	_vao(0),
	_vbo(0),
	_ebo(0),
	_buffersCreated(false),
	_material(nullptr)
{

}

void PE::MeshRenderer::setMesh(Mesh mesh)
{
	_mesh = mesh;

	reloadData();
}

void PE::MeshRenderer::setMaterial(std::shared_ptr<Material> material)
{
	_material = material;

	reloadData();
}

void PE::MeshRenderer::onStart()
{
	
}

void PE::MeshRenderer::render(RenderContext* context)
{
	if (!_buffersCreated)
		return;

	//use the material
	_material->useMaterial();

	//enable the vao
	glBindVertexArray(_vao);

	Shader shader = _material->getShader();

	//find the mvp and calculate the camera
	int modelLocation = shader.getUniformLocation("model");
	glm::mat4 model = getTransform()->getTransformMatrix();
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

	int viewLocation = shader.getUniformLocation("view");
	glm::mat4 view = context->camera->getLookMatrix();
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

	int projLocation = shader.getUniformLocation("projection");
	glm::mat4 proj = context->camera->getProjectionMatrix();
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(proj));

	//set ambient light
	int ambientLocation = shader.getUniformLocation("ambient");
	glUniform3fv(ambientLocation, 1, glm::value_ptr(context->lightingData->ambient.normalized()));

	//set camera position
	int viewPos = shader.getUniformLocation("viewPos");
	glUniform3fv(viewPos, 1, glm::value_ptr(context->camera->getTransform()->getPosition()));

	//add lights
	int lightsToRender = (int)std::min(context->lightingData->lights.size(), LightingData::MAX_LIGHTS);
	int lightNumLocation = shader.getUniformLocation("numLights");
	glUniform1iv(lightNumLocation, 1, &lightsToRender);
	
	//attempt to set the number of lights
	for (size_t i = 0; i < lightsToRender; i++)
	{
		Light* light = context->lightingData->lights[i];
		int posLoc = shader.getUniformLocation("pointLights[" + to_string(i) + "].pos");
		int colorLoc = shader.getUniformLocation("pointLights[" + to_string(i) + "].color");
		glUniform3fv(posLoc, 1, glm::value_ptr(light->getTransform()->getPosition()));
		glUniform3fv(colorLoc, 1, glm::value_ptr(light->getColor().normalized()));
	}

	//draw all the bound indices
	glDrawElements(GL_TRIANGLES, (GLsizei)_mesh.indices.size(), GL_UNSIGNED_INT, 0);

	//unbind to prevent accidental modification
	glBindVertexArray(0);
}

void PE::MeshRenderer::update()
{

}

void PE::MeshRenderer::onDestroy()
{
	if (!_buffersCreated)
		return;

	glDeleteBuffers(1, &_vbo);
	glDeleteBuffers(1, &_ebo);
	glDeleteVertexArrays(1, &_vao);
}

void PE::MeshRenderer::reloadData()
{
	//quit if no vertices or material
	if (_mesh.vertices.size() == 0  || _mesh.indices.size() == 0)
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
	glBufferData(GL_ARRAY_BUFFER, _mesh.vertices.size() * sizeof(Vertex), &_mesh.vertices[0], GL_STATIC_DRAW);

	//bind EBO to reduce amount of data needed and set its indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _mesh.indices.size() * sizeof(unsigned int), &_mesh.indices[0], GL_STATIC_DRAW);

	//determine if position data needs to be written
	int vertPos = _material->getShader().getAttribLocation("vertPos");
	if (vertPos != -1)
	{
		//3 values of type float, not normalized with a gap of one Vertex object with an offset of the position location
		glVertexAttribPointer(vertPos, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		glEnableVertexAttribArray(vertPos);
	}

	//determine if normal data needs to be written
	int normPos = _material->getShader().getAttribLocation("norm");
	if (normPos != -1)
	{
		//3 values of type float, not normalized with a gap of one Vertex object with an offset of the position location
		glVertexAttribPointer(normPos, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
		glEnableVertexAttribArray(normPos);
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