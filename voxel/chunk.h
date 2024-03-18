#ifndef CHUNK_H
#define CHUNK_H

#include <glm/glm.hpp>

#include "voxel.h"

class Chunk {
public:
	glm::vec3 position;
	int size;

	float data[17 * 100 * 17] = { 0 };
};

#endif
