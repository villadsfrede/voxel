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
				chunk.position = glm::vec3(i + 1, j + 1, k + 1);

				//for (int v = 0; v < (8 * 8 * 8); v++) {
				//	chunk.data[v] = (float)rand() / RAND_MAX - 0.4f;
				//}

				
				for (int x = 0; x < 8; x++) {
					for (int y = 0; y < 8; y++) {
						for (int z = 0; z < 8; z++) {
							if (z == 2 || y == 4) chunk.data[z + 8 * (y + 8 * x)] = 1;
							else chunk.data[z + 8 * (y + 8 * x)] = 0;
							//chunk.data[z + 8 * (y + 8 * x)] = (float)rand() / RAND_MAX;
						}
					}
				}
				
				chunks.push_back(chunk);
			}
		}
	}
}