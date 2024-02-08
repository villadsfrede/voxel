#ifndef CHUNK_H
#define CHUNK_H

#include <glm/glm.hpp>

#include "voxel.h"

class Chunk {
public:
	glm::vec3 position;

	Voxel voxels[16][16][16];

	Chunk(glm::vec3 position);
};

Chunk::Chunk(glm::vec3 position) {
	Chunk::position = position;

	for (int x = 0; x < 16; x++) {
		for (int y = 0; y < 16; y++) {
			for (int z = 0; z < 16; z++) {
				voxels[x][y][z] = Voxel(Chunk::position + glm::vec3(x, y, z));
			}
		}
	}
}

#endif
