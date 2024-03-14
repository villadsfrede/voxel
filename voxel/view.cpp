#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "view.h"

bool View::init() {
	if (!glfwInit())
		return false;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, "voxel", NULL, NULL);

	if (!window) {
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to load opengl function pointers" << std::endl;
		glfwTerminate();
		return false;
	}

	//glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
	//glEnable(GL_PROGRAM_POINT_SIZE);
	glPointSize(10);

	glEnable(GL_DEPTH_TEST);

	return true;
}

void View::cleanup() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

void View::loadChunkModels(World &world) {
	//std::cout << world.chunks.size() << std::endl;
	for (unsigned int i = 0; i < world.chunks.size(); i++) {
		Model model;
		//model.point(world.chunks[i]);
		model.march(world.chunks[i]);
		model.setup();
		models.push_back(model);
	}

	Model model;
	model.point(world.chunks[0]);
	model.setup();
	models.push_back(model);
}

void View::render(World &world) {
}