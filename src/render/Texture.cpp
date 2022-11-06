#include "render/Texture.h"

#include <iostream>
#include <gl/glew.h>

#define STB_IMAGE_IMPLEMENTATION
#include "render/stb_image.h"

using namespace std;

void PE::Texture::freeTextures()
{
	for (auto tex : _textures)
	{
		tex->free();
	}
	_textures.clear();
}

void PE::Texture::loadFromFile(std::string fileName,
	bool transparency,
	WRAP_MODE wrapMode,
	FILTERING min,
	FILTERING max)
{
	cout << "Loading texture " << fileName << endl;

	if (max != FILTERING::NEAREST && max != FILTERING::LINEAR)
	{
		throw "Cannot use mipmaps for upper level generation";
	}

	//determine if mip maps need to be generated
	bool usingMipmaps = min != FILTERING::NEAREST && min != FILTERING::LINEAR;

	//images are typically inverted on loading so flip it
	stbi_set_flip_vertically_on_load(true);

	//load the image into memory
	int width, height, nrChannels;
	unsigned char* data = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0);

	if (data == NULL)
	{
		cerr << "Failled to load texture" << endl;
		return;
	}

	//generate the textures
	glGenTextures(1, &_texture);


	//bind the texture to active to modify it
	glBindTexture(GL_TEXTURE_2D, _texture);
	
	//determine the wrap mode
	int wrapModeValue;
	switch (wrapMode)
	{
	case WRAP_MODE::REPEAT:
		wrapModeValue = GL_REPEAT;
		break;
	case WRAP_MODE::CLAMP_EDGE:
		wrapModeValue = GL_CLAMP_TO_EDGE;
		break;
	case WRAP_MODE::MIRROR_REPEAT:
		wrapModeValue = GL_MIRRORED_REPEAT;
		break;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapModeValue);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapModeValue);

	//determine filtering mode
	int minFiltering, maxFiltering;
	switch (min)
	{
	case FILTERING::NEAREST:
		minFiltering = GL_NEAREST;
		break;
	case FILTERING::LINEAR:
		minFiltering = GL_LINEAR;
		break;
	case FILTERING::LINEAR_MIPMAP_LINEAR:
		minFiltering = GL_LINEAR_MIPMAP_LINEAR;
		break;
	case FILTERING::LINEAR_MIPMAP_NEAREST:
		minFiltering = GL_LINEAR_MIPMAP_NEAREST;
		break;
	case FILTERING::NEAREST_MIPMAP_LINEAR:
		minFiltering = GL_NEAREST_MIPMAP_LINEAR;
		break;
	case FILTERING::NEAREST_MIPMAP_NEAREST:
		minFiltering = GL_NEAREST_MIPMAP_NEAREST;
		break;
	}

	switch (max)
	{
	case FILTERING::NEAREST:
		maxFiltering = GL_NEAREST;
		break;
	case FILTERING::LINEAR:
		maxFiltering = GL_LINEAR;
		break;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFiltering);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, maxFiltering);

	//bind texture data
	glTexImage2D(GL_TEXTURE_2D, 0, transparency ? GL_RGBA : GL_RGB, width, height, 0, nrChannels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);

	//generate mipmaps if needed
	if (usingMipmaps)
		glGenerateMipmap(GL_TEXTURE_2D);

	//remove the data
	stbi_image_free(data);

	_textures.push_back(this);
}

unsigned int PE::Texture::getTexture() const
{
	return _texture;
}

void PE::Texture::free()
{
	glDeleteTextures(1, &_texture);
}