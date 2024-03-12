#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "chunk.h"



class Model {
public:
	std::vector<GLfloat> positions;
	std::vector<GLuint> indices;

	GLuint vbo, vao, ibo;
	
	void setup();
	void march(Chunk chunk);
	void cleanup();
	void render();
};

#endif