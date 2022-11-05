#include "render/Shader.h"

#include <gl/glew.h>

#include <fstream>
#include <iostream>
#include <streambuf>

using namespace std;

PE::Shader::Shader():
	_vertShader(0),
	_fragShader(0),
	_shaderProgram(0)
{

}

void PE::Shader::free()
{
	//delete all created objects
	glDeleteShader(_vertShader);
	glDeleteShader(_fragShader);
	glDeleteProgram(_shaderProgram);
}

int PE::Shader::compile(std::string vertFile, std::string fragFile)
{
	cout << "Compiling shaders from " << vertFile << " " << fragFile << endl;

	//compile the individual shaders
	_vertShader = glCreateShader(GL_VERTEX_SHADER);
	if (compileShader(vertFile, &_vertShader))
		return -1;

	_fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	if (compileShader(fragFile, &_fragShader))
		return -1;

	//generate and link the program
	_shaderProgram = glCreateProgram();
	glAttachShader(_shaderProgram, _vertShader);
	glAttachShader(_shaderProgram, _fragShader);
	glLinkProgram(_shaderProgram);

	//get shader link problems
	int success; // GL_TRUE if success
	char infoLog[512];
	glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(_shaderProgram, 512, NULL, infoLog);
		cerr << "Failed to link shaders: "  << infoLog << endl;
		return -1;
	}

	cout << "Compiled/linked succesfully!" << endl;

	//everything is ok
	return 0;
}

void PE::Shader::useShader()
{
	glUseProgram(_shaderProgram);
}

int PE::Shader::getAttribLocation(std::string name) 
{
	return glGetAttribLocation(_shaderProgram, name.c_str());
}

int PE::Shader::getUniformLocation(std::string name) 
{
	return glGetUniformLocation(_shaderProgram, name.c_str());
}

int PE::Shader::compileShader(std::string sourceFile, unsigned int* shaderId)
{
	//load all the data into a string
	ifstream shaderSource(sourceFile);
	if (shaderSource.fail()) {
		cerr << "Failed to find shader source file: " << sourceFile << endl;
		return -1;
	}

	//read all data into a string
	std::string src((std::istreambuf_iterator<char>(shaderSource)),
		std::istreambuf_iterator<char>());

	//set the source then compile the shader
	const char* cSrc = src.c_str();
	glShaderSource(*shaderId, 1, &cSrc, NULL); //1 represents there is one source file being passed, uses NULL since null terminated
	glCompileShader(*shaderId);

	//get any errors
	int success; // GL_TRUE if success
	char infoLog[512];
	glGetShaderiv(*shaderId, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(*shaderId, 512, NULL, infoLog);
		cerr << "Failed to compile shader from " << sourceFile << ": " << infoLog << endl;
		return -1;
	}

	//everything completed without incident, yipee
	return 0;
}
