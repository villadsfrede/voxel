#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>
#include "VBO.h"

class VAO {
public:
	GLuint ID;

	VAO();

	void Link(VBO& VBO, GLuint layout);
	void Bind();
	void Unbind();
	void Delete();
};

VAO::VAO() {
	glGenVertexArrays(1, &ID);
}

void VAO::Link(VBO& VBO, GLuint layout) {
	VBO.Bind();
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

void VAO::Bind() {
	glBindVertexArray(ID);
}

void VAO::Unbind() {
	glBindVertexArray(0);
}

void VAO::Delete() {
	glDeleteVertexArrays(1, &ID);
}

#endif
