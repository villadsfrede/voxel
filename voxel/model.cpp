#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "model.h"
#include "chunk.h"

#include "TriangleTable.h"
#include "EdgeTable.h"

void Model::setup() {
	// SETUP VAO and VBO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(2, vbo);
	glGenBuffers(1, &ibo);

	// POSITION BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(GLfloat), &positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// NORMAL BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), &normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	// INDEX BUFFER
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
}

void Model::cleanup() {
	glDisableVertexAttribArray(0);
	glDeleteBuffers(2, vbo);
	glDeleteVertexArrays(1, &vao);
}

void Model::renderChunk() {
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

void Model::renderPoint() {
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glDrawElements(GL_POINTS, indices.size(), GL_UNSIGNED_INT, 0);
}

static const glm::vec3 offset[8] = {
	glm::vec3(0,0,0),
	glm::vec3(1,0,0),
	glm::vec3(0,1,0),
	glm::vec3(1,1,0),
	glm::vec3(0,0,1),
	glm::vec3(1,0,1),
	glm::vec3(0,1,1),
	glm::vec3(1,1,1),
};

void Model::march(Chunk chunk) {
	positions.clear();
	indices.clear();

	float iso = 0.5;

	for (int x = 0; x < 15; x++) {
		for (int y = 0; y < 15; y++) {
			for (int z = 0; z < 15; z++) {
				int index = 0;

				if (chunk.data[((x + 0) * 16 * 16) + ((y + 0) * 16) + (z + 0)] > iso) index |= (1 << 0);
				if (chunk.data[((x + 1) * 16 * 16) + ((y + 0) * 16) + (z + 0)] > iso) index |= (1 << 1);
				if (chunk.data[((x + 0) * 16 * 16) + ((y + 1) * 16) + (z + 0)] > iso) index |= (1 << 2);
				if (chunk.data[((x + 1) * 16 * 16) + ((y + 1) * 16) + (z + 0)] > iso) index |= (1 << 3);
				if (chunk.data[((x + 0) * 16 * 16) + ((y + 1) * 16) + (z + 1)] > iso) index |= (1 << 4);
				if (chunk.data[((x + 1) * 16 * 16) + ((y + 0) * 16) + (z + 1)] > iso) index |= (1 << 5);
				if (chunk.data[((x + 0) * 16 * 16) + ((y + 1) * 16) + (z + 1)] > iso) index |= (1 << 6);
				if (chunk.data[((x + 1) * 16 * 16) + ((y + 1) * 16) + (z + 1)] > iso) index |= (1 << 7);

				for (int i = 0; TriangleTable[index][i] != -1; i++) {
					glm::vec3 O1 = offset[EdgeTable[TriangleTable[index][i]][0]];
					glm::vec3 O2 = offset[EdgeTable[TriangleTable[index][i]][0]];

					glm::vec3 position = ((O1 + O2) * 0.5f) + chunk.position;

					positions.push_back(position.x);
					positions.push_back(position.y);
					positions.push_back(position.z);

					indices.push_back(positions.size() - 0);
					indices.push_back(positions.size() - 1);
					indices.push_back(positions.size() - 2);
				}
			}
		}
	}
}

void Model::point(Chunk chunk) {

}