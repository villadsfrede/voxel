#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <glm/glm.hpp>
#include "chunk.h"

class World {
public:
	std::vector<Chunk> chunks;

	int chunkSize = 16;

	glm::vec3 dim = glm::vec3(3, 3, 3);

	void blank();
	void generate();
};

#endif
