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
				chunk.position = glm::vec3(16 * i, 16 * j, 16 * k);

				//for (int v = 0; v < (8 * 8 * 8); v++) {
				//	chunk.data[v] = (float)rand() / RAND_MAX - 0.4f;
				//}

				
				for (int x = 0; x < 16; x++) {
					for (int y = 0; y < 16; y++) {
						for (int z = 0; z < 16; z++) {
							if (z == 2 || y == 4) chunk.data[z + 16 * (y + 16 * x)] = 1;
							else chunk.data[z + 16 * (y + 16 * x)] = 0;
							//chunk.data[z + 8 * (y + 8 * x)] = (float)rand() / RAND_MAX;
						}
					}
				}
				
				chunks.push_back(chunk);
			}
		}
	}
}