#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "model.h"
#include "chunk.h"

void Model::setup() {
	// SETUP VAO and VBO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);

	// POSITION BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(GLfloat), &positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	// INDEX BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
}

void Model::cleanup() {
	glDisableVertexAttribArray(0);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}

void Model::render() {
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}


void Model::march(Chunk chunk) {
	positions.clear();
	indices.clear();

	for (int x = 0; x < chunk.size; x++) {
		for (int y = 0; y < chunk.size; y++) {
			for (int z = 0; z < chunk.size; z++) {
				positions.push_back(x);
				positions.push_back(y);
				positions.push_back(z);

				indices.push_back(positions.size() + 0);
				indices.push_back(positions.size() + 1);
				indices.push_back(positions.size() + 2);
			}
		}
	}
	std::cout << "POSITIONS " << positions.size() << std::endl;
	std::cout << "INDICES " << indices.size() << std::endl;
}