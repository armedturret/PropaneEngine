#include "render/Model.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>

#include "Application.h"
#include "render/components/MeshRenderer.h"

using namespace std;

void PE::Model::loadFromFile(std::string modelFile)
{
	cout << "Loading Model: " << modelFile << endl;

	//load the scene
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(modelFile, aiProcess_Triangulate);

	//check for errors
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cout << "Error loading model" << importer.GetErrorString() << endl;
		return;
	}

	//get required material count
	cout << "Model requires " << scene->mNumMaterials << " materials" << endl;
	_requiredMaterialCount = scene->mNumMaterials;

	//load all meshes
	_meshes.reserve((size_t)scene->mNumMeshes);
	for (unsigned int i = 0; i < scene->mNumMeshes; i++)
	{
		cout << "Loading mesh (" << i + 1 << "/" << scene->mNumMeshes << ")" << endl;
		aiMesh* mesh = scene->mMeshes[i];
		Mesh meshData{ {}, {},  mesh->mMaterialIndex};

		//add vertices
		for (unsigned int vert = 0; vert < mesh->mNumVertices; vert++)
		{
			Vertex vertex;
			glm::vec3 pos;
			pos.x = mesh->mVertices[vert].x;
			pos.y = mesh->mVertices[vert].y;
			pos.z = mesh->mVertices[vert].z;
			vertex.position = pos;

			glm::vec3 normal;
			normal.x = mesh->mNormals[vert].x;
			normal.y = mesh->mNormals[vert].y;
			normal.z = mesh->mNormals[vert].z;
			vertex.normal = normal;

			glm::vec2 texCoord(0.0f);
			//posibility of no tex coords in this model
			if (mesh->mTextureCoords[0])
			{
				//there can be up to 8 tex coords per vertex but idk what for so we're sticking to the first
				texCoord.x = mesh->mTextureCoords[0][vert].x;
				texCoord.y = mesh->mTextureCoords[0][vert].y;
			}
			vertex.texCoord = texCoord;

			meshData.vertices.push_back(vertex);
		}

		//add indices (faces each have indices)
		for (unsigned int face = 0; face < mesh->mNumFaces; face++)
		{
			for (unsigned int index = 0; index < mesh->mFaces[face].mNumIndices; index++)
			{
				meshData.indices.push_back(mesh->mFaces[face].mIndices[index]);
			}
		}

		_meshes.push_back(meshData);
	}

	//create child nodes
	_rootNode = convertNode(scene->mRootNode);

	cout << "Sucessfully loaded model" << endl;
}

void PE::Model::setMaterials(std::vector<std::shared_ptr<Material>> materials)
{
	_materials = materials;
}

int PE::Model::getRequiredMaterialCount()
{
	return _requiredMaterialCount;
}

PE::GameObject * PE::Model::createInstance()
{
	return createObjectFromNode(&_rootNode);
}

PE::Model::Node PE::Model::convertNode(aiNode* assimpNode)
{
	Node node;

	//add the target meshes
	for (unsigned int i = 0; i < assimpNode->mNumMeshes; i++)
	{
		node.targetMeshes.push_back(assimpNode->mMeshes[i]);
	}

	//add children
	for (unsigned int i = 0; i < assimpNode->mNumChildren; i++)
	{
		node.children.push_back(convertNode(assimpNode->mChildren[i]));
	}
	
	//store RELATIVE transform
	glm::mat4 transform;
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			transform[x][y] = assimpNode->mTransformation[x][y];
		}
	}
	node.transform = transform;

	//store the name
	node.name = assimpNode->mName.C_Str();

	return node;
}

PE::GameObject* PE::Model::createObjectFromNode(Node* node)
{
	GameObject* nodeObject = Application::getInstance().createGameObject();

	//create mesh renderers for each mesh
	for (unsigned int i = 0; i < node->targetMeshes.size(); i++)
	{
		Mesh meshData = _meshes[node->targetMeshes[i]];
		MeshRenderer* meshRenderer = nodeObject->addComponent<MeshRenderer>();
		meshRenderer->setMaterial(_materials[meshData.modelMaterialIndex]);
		meshRenderer->setMesh(meshData);
	}

	//set relative transform
	nodeObject->getTransform()->setRelativeTransformMatrix(node->transform);

	//set name
	nodeObject->setName(node->name);

	//process child nodes
	for (unsigned int i = 0; i < node->children.size(); i++)
	{
		GameObject* child = createObjectFromNode(&node->children[i]);
		child->getTransform()->setParent(nodeObject->getTransform());
	}
	
	return nodeObject;
}