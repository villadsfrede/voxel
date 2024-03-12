#include <iostream>
#include <glm/glm.hpp>

#include "chunk.h"
#include "world.h"

void World::blank() {
	// Loop over all chunks
	for (int i = 0; i < dim.x; i++) {
		for (int j = 0; j < dim.y; j++) {
			for (int k = 0; k < dim.z; k++) {
				//std::cout << "x: " << i << std::endl;
				//std::cout << "y: " << j << std::endl;
				//std::cout << "z: " << k << std::endl;
				Chunk chunk;
				chunk.position = glm::vec3(i, j, k);
				chunk.size = chunkSize;
				chunk.data[i * j * k] = int(std::rand());
				chunks.push_back(chunk);
			}
		}
	}
}