#pragma once

#include <string>

namespace PE {
	class Shader {
	public:
		//manually free up shader
		void free();

		//returns a non-zero error code if compilation failed for whatever reason
		int compile(std::string vertFile, std::string fragFile);

		//sets the shader to be the active one
		void useShader();

	private:
		//returns a non-zero error code if compilation failed for whatever reason
		int compileShader(std::string sourceFile, unsigned int* shaderId);

		unsigned int _vertShader, _fragShader, _shaderProgram;
	};
}