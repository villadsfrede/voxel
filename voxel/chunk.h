#ifndef CHUNK_H
#define CHUNK_H

#include <glm/glm.hpp>

#include "voxel.h"

class Chunk {
public:
	glm::vec3 position;
	int size;

	float data[8 * 8 * 8] = { 0 };
};

#endif
