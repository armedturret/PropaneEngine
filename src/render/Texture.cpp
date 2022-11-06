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
		tex.free();
	}
}

void PE::Texture::loadFromFile(std::string fileName,
	bool transparency,
	WRAP_MODE mode,
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

	//generate the textures
	glGenTextures(1, &_texture);

	if (data == NULL)
	{
		cerr << "Failled to load texture" << endl;
		return;
	}

	//bind the texture to active to modify it
	glBindTexture(GL_TEXTURE_2D, _texture);
	glTexImage2D(GL_TEXTURE_2D, 0, transparency ? GL_RGBA : GL_RGB, width, height, 0, nrChannels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);

	//generate mipmaps if needed
	if (usingMipmaps)
		glGenerateMipmap(GL_TEXTURE_2D);

	//remove the data
	stbi_image_free(data);
}

unsigned int PE::Texture::getTexture() const
{
	return _texture;
}

void PE::Texture::free()
{

}