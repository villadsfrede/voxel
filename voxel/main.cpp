#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "EBO.h"
#include "VAO.h"
#include "VBO.h"

#include "shader.h"

#include "camera.h"

const unsigned int width = 1000;
const unsigned int height = 1000;

GLfloat vertices[] =
{//     COORDINATES
	// BOTTOM
	-1.0f, -1.0f, -1.0f, //0
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	// TOP
	-1.0f, -1.0f, 1.0f, //4
	1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
};

GLuint indices[] =
{
	0, 5, 4,
	0, 5, 1,

	4, 6, 7,
	4, 6, 5,

	7, 2, 3,
	7, 2, 6,

	0, 2, 3,
	0, 2, 1,

	3, 4, 7,
	3, 4, 0,

	2, 5, 1,
	2, 5, 6,
};

int main()
{
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "voxel", NULL, NULL);

	if (!window) {
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to load opengl function pointers" << std::endl;
		glfwTerminate();
		return -1;
	}

	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO;
	VAO.Bind();

	VBO VBO(vertices, sizeof(vertices));
	EBO EBO(indices, sizeof(indices));

	VAO.Link(VBO, 0);

	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();

	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 0.0f));

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram();

		camera.Input(window);

		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "cameramatrix");

		VAO.Bind();

		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	shaderProgram.Delete();

	VAO.Delete();
	VBO.Delete();
	EBO.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
