#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "view.h"

#include "EBO.h"
#include "VAO.h"
#include "VBO.h"

#include "World.h"

#include "shader.h"

#include "camera.h"

int main()
{
	View view;
	view.init();

	Shader shaderProgram("default.vert", "default.frag");

	//World world;
	//world.Mesh();

	/*
	VAO VAO;
	VAO.Bind();

	VBO VBO(&world.vertices);
	EBO EBO(&world.indices);

	VAO.Link(VBO, 0);

	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();
	*/

	Camera camera(view.width, view.height, glm::vec3(0.0f, 0.0f, 0.0f));

	while (!glfwWindowShouldClose(view.window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram();

		camera.Input(view.window);

		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "cameramatrix");

		//VAO.Bind();

		//glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(view.window);

		glfwPollEvents();
	}

	shaderProgram.Delete();

	/*
	VAO.Delete();
	VBO.Delete();
	EBO.Delete();
	*/

	return 0;
}
