#ifndef VIEW_H
#define VIEW_H

#include "world.h"

class View {
public:
	const unsigned int width = 1000;
	const unsigned int height = 1000;

	GLFWwindow* window;

	bool init();
	void cleanup();
	void render(World &world);
};

#endif
