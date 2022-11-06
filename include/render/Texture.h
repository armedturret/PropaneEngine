#pragma once

#include <vector>
#include <string>

namespace PE {
	class Texture {
	public:
		static void freeTextures();

		enum class WRAP_MODE { REPEAT, MIRROR_REPEAT, CLAMP_EDGE };

		enum class FILTERING { NEAREST, LINEAR, LINEAR_MIPMAP_LINEAR, LINEAR_MIPMAP_NEAREST, NEAREST_MIPMAP_LINEAR, NEAREST_MIPMAP_NEAREST };

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
		static std::vector<Texture*> _textures;
	};
}