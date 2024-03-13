#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "view.h"

#include "World.h"

#include "shader.h"

#include "camera.h"

int main()
{
	std::cout << "GENERATING WORLD" << std::endl;
	World world;
	world.blank();

	std::cout << "LOADING OPENGL" << std::endl;
	View view;
	view.init();
	view.loadChunkModels(world);

	Shader shaderProgram("default.vert", "default.frag");

	Camera camera(view.width, view.height, glm::vec3(0.0f, 0.0f, 0.0f));

	while (!glfwWindowShouldClose(view.window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram();

		camera.Input(view.window);

		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "cameramatrix");

		//glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);

		for (int i = 0; i < view.models.size(); i++) {
			view.models[i].renderPoint();
		}

		glfwSwapBuffers(view.window);

		glfwPollEvents();
	}

	shaderProgram.Delete();

	view.cleanup();

	return 0;
}
