#include <iostream>
#include <cmath>
#include <glm/glm.hpp>

#include "noise.h"

#include "chunk.h"
#include "world.h"

void World::blank() {
	// Loop over all chunks
	for (int i = 0; i < dim.x; i++) {
		for (int j = 0; j < dim.y; j++) {
			for (int k = 0; k < dim.z; k++) {
				Chunk chunk;
				chunk.position = glm::vec3(16 * i, 0, 16 * k);

				for (int x = 0; x < 17; x++) {
					for (int z = 0; z < 17; z++) {
						int height = 50 + (int)(50 * perlin(x + (16 * i), z + (16 * k)));

						for (int y = 0; y < height; y++) {
							chunk.data[z + 17 * (y + 100 * x)] = 1;
						}
					}
				}
				chunks.push_back(chunk);
			}
		}
	}
}