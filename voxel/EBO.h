#ifndef EBO_H
#define EBO_H

#include <vector>

#include <glad/glad.h>

class EBO {
public:
	GLuint ID;

	EBO(std::vector<GLint>* indices);

	void Bind();
	void Unbind();
	void Delete();
};

EBO::EBO(std::vector<GLint>* indices) {
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->size() * sizeof(GLint), &indices->front(), GL_STATIC_DRAW);
}

void EBO::Bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete() {
	glDeleteBuffers(1, &ID);
}

#endif
