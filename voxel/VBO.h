#ifndef VBO_H
#define VBO_H

#include <vector>

#include <glad/glad.h>

class VBO {
public:
	GLuint ID;

	VBO(std::vector<GLint>* vertices);

	void Bind();
	void Unbind();
	void Delete();
};

VBO::VBO(std::vector<GLint>* vertices) {
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, vertices->size() * sizeof(GLint), &vertices->front(), GL_STATIC_DRAW);
}

void VBO::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::Delete() {
	glDeleteBuffers(1, &ID);
}

#endif
