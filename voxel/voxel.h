#ifndef VOXEL_H
#define VOXEL_H

#include <glm/glm.hpp>

class Voxel {
public:
	glm::vec3 position;

	Voxel(glm::vec3 position);
};

Voxel::Voxel(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f)) {
	Voxel::position = position;
}

#endif
