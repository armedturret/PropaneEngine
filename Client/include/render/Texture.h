#pragma once

#include <unordered_map>
#include <string>

namespace PE {
	class Texture {
	public:
		Texture(): _texture(0) {}

		static void freeTextures();

		enum WRAP_MODE { REPEAT, MIRROR_REPEAT, CLAMP_EDGE };

		enum FILTERING { NEAREST, LINEAR, LINEAR_MIPMAP_LINEAR, LINEAR_MIPMAP_NEAREST, NEAREST_MIPMAP_LINEAR, NEAREST_MIPMAP_NEAREST };

		//loads a texture, adds it to the texture, do not use mipmaps for max filters
		void loadFromFile(std::string fileName,
			bool transparency = false,
			WRAP_MODE wrapMode = WRAP_MODE::CLAMP_EDGE,
			FILTERING min = FILTERING::LINEAR_MIPMAP_LINEAR,
			FILTERING max = FILTERING::LINEAR);

		//gets the texture's location
		unsigned int getTexture() const;
	private:
		void free();

		unsigned int _texture;

		//store list of textures for freeing later
		static std::unordered_map<std::string, Texture*> _textures;
	};
}