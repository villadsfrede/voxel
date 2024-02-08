#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "chunk.h"

class World {
public:
	std::vector<GLfloat> vertices;
	std::vector<GLint> indices;

	std::map<glm::vec3, Chunk> chunks;

	World();

	void Mesh();
};

World::World() {
	for (int x = 0; x < 5; x++) {
		for (int y = 0; y < 5; y++) {
			for (int z = 0; z < 5; z++) {
				glm::vec3 position = glm::vec3(x * 16, y * 16, z * 16);
				chunks[position] = Chunk(position);
			}
		}
	}
}

void World::Mesh() {
	for (const auto& [key, value] : chunks) {
		for (int x = 0; x < 16; x++) {
			for (int y = 0; y < 16; y++) {
				for (int z = 0; z < 16; z++) {
					
				}
			}
		}
	}
}

#endif
