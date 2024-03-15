#ifndef VIEW_H
#define VIEW_H

#include "model.h"
#include "world.h"

class View {
public:
	const unsigned int width = 1000;
	const unsigned int height = 1000;

	GLFWwindow* window;

	std::vector<Model> models;

	// init GLFW, GLAD, OPENGL
	bool init();

	// load chunks
	void loadChunkModels(World& world);
	void cleanup();
	void render(World &world);
};

#endif
