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
	//glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	//glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), &normals[0], GL_STATIC_DRAW);
	//glEnableVertexAttribArray(1);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// COLOR BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(GLfloat), &colors[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	
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

int offset[8][3] = {
	{0, 0, 0},
	{1, 0, 0},
	{0, 1, 0},
	{1, 1, 0},
	{0, 0, 1},
	{1, 0, 1},
	{0, 1, 1},
	{1, 1, 1},
};

void Model::march(Chunk chunk) {
	positions.clear();
	colors.clear();
	indices.clear();

	float iso = 0.5;

	for (int x = 0; x < 15; x++) {
		for (int y = 0; y < 15; y++) {
			for (int z = 0; z < 15; z++) {
				int index = 0;

				if (chunk.data[(z + 0) + 16 * ((y + 0) + 16 * (x + 0))] < iso) index |= (1 << 0);
				if (chunk.data[(z + 0) + 16 * ((y + 0) + 16 * (x + 1))] < iso) index |= (1 << 1);
				if (chunk.data[(z + 0) + 16 * ((y + 1) + 16 * (x + 0))] < iso) index |= (1 << 2);
				if (chunk.data[(z + 0) + 16 * ((y + 1) + 16 * (x + 1))] < iso) index |= (1 << 3);
				if (chunk.data[(z + 1) + 16 * ((y + 0) + 16 * (x + 0))] < iso) index |= (1 << 4);
				if (chunk.data[(z + 1) + 16 * ((y + 0) + 16 * (x + 1))] < iso) index |= (1 << 5);
				if (chunk.data[(z + 1) + 16 * ((y + 1) + 16 * (x + 0))] < iso) index |= (1 << 6);
				if (chunk.data[(z + 1) + 16 * ((y + 1) + 16 * (x + 1))] < iso) index |= (1 << 7);

				for (int edge : TriangleTable[index]) {
					if (edge == -1) break;

					int v0 = EdgeTable[edge][0];
					int v1 = EdgeTable[edge][1];

					float posx = (float)(offset[v0][0] + offset[v1][0]) / 2;
					float posy = (float)(offset[v0][1] + offset[v1][1]) / 2;
					float posz = (float)(offset[v0][2] + offset[v1][2]) / 2;

					positions.push_back(x + posx + chunk.position.x);
					positions.push_back(y + posy + chunk.position.y);
					positions.push_back(z + posz + chunk.position.z);

					colors.push_back(0.8f);
					colors.push_back(0.4f);
					colors.push_back(0.4f);
					colors.push_back(1.0f);

					indices.push_back(positions.size() - 1);
					indices.push_back(positions.size() - 2);
					indices.push_back(positions.size() - 3);
				}
			}
		}
	}
	std::cout << "POSITIONS: " << positions.size() << std::endl;
	std::cout << "COLOS: " << colors.size() << std::endl;
	std::cout << "INDICES: " << indices.size() << std::endl;
}

void Model::point(Chunk chunk) {
	positions.clear();
	colors.clear();
	indices.clear();

	for (int x = 0; x < 16; x++) {
		for (int y = 0; y < 16; y++) {
			for (int z = 0; z < 16; z++) {
				positions.push_back(x + chunk.position.x);
				positions.push_back(y + chunk.position.y);
				positions.push_back(z + chunk.position.z);

				float value = chunk.data[z + 16 * (y + 16 * x)];

				colors.push_back(1.0f * value);
				colors.push_back(1.0f * value);
				colors.push_back(1.0f * value);
				colors.push_back(1.0f);
				
				indices.push_back(positions.size() - 1);
				indices.push_back(positions.size() - 2);
				indices.push_back(positions.size() - 3);
			}
		}
	}
	std::cout << "POSITIONS: " << positions.size() << std::endl;
	std::cout << "COLOS: " << colors.size() << std::endl;
	std::cout << "INDICES: " << indices.size() << std::endl;
}