#include <iostream>
#include <cmath>
#include <glm/glm.hpp>

#include "chunk.h"
#include "world.h"

void World::blank() {
	// Loop over all chunks
	for (int i = 0; i < dim.x; i++) {
		for (int j = 0; j < dim.y; j++) {
			for (int k = 0; k < dim.z; k++) {
				Chunk chunk;
				chunk.position = glm::vec3(i, j, k);
				chunks.push_back(chunk);
			}
		}
	}
}