#include "Graphics.h"
#include <iostream>

GLFWwindow* Graphics::InitializeWindow(int width, int height) {
	glfwInit();//initialize opengl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);//set GLFW_CONTEXT_VERSION_MAJOR to 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);//set GLFW_CONTEXT_VERSION_MINOR to 3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "NucelarEngine", NULL, NULL);//pointer to window
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(1);
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		exit(1);
	}

	glViewport(0, 0, width, height);//0,0 in lower left corner

	return window;
}




