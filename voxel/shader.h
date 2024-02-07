#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <glad/glad.h>

std::string get_file_contents(const char* filename) {
	std::ifstream in(filename, std::ios::binary);

	if (in) {
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	throw(errno);
}

class Shader {
public:
	GLuint ID;

	Shader(const char* vertexFile, const char* fragmentFile);

	void operator () () const {
		glUseProgram(ID);
	}

	void Delete();
};

Shader::Shader(const char* vertexFile, const char* fragmentFile) {
	std::string vertexData = get_file_contents(vertexFile);
	std::string fragmentData = get_file_contents(fragmentFile);

	const char* vertexSource = vertexData.c_str();
	const char* fragmentSource = fragmentData.c_str();

	// VERTEXT SHADER
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);


	// FRAGMENT SHADER
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	// SHADER PROGRAM
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	glLinkProgram(ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::Delete() {
	glDeleteShader(ID);
}

#endif
