#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <glm/glm.hpp>
#include "chunk.h"



class World {
public:
	std::vector<Chunk> chunks;

	glm::vec3 dim = glm::vec3(20, 1, 20);

	void blank();
	void generate();
};

#endif
