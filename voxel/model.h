#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "chunk.h"

class Model {
public:
	std::vector<GLfloat> positions;
	//std::vector<GLfloat> normals;
	std::vector<GLuint> indices;

	GLuint vbo[2], vao, ibo;
	
	void setup();
	void march(Chunk chunk);
	void point(Chunk chunk);
	void cleanup();
	void renderChunk();
	void renderPoint();
};

#endif