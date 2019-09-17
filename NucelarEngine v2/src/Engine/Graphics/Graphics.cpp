#include "Graphics.h"
#include <iostream>

GLFWwindow* Graphics::InitializeWindow(int width, int height, bool fullscreen) {
	glfwInit();//initialize opengl

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//set GLFW_CONTEXT_VERSION_MAJOR to 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//set GLFW_CONTEXT_VERSION_MINOR to 3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_REFRESH_RATE, 60);//60 fps max

	auto monitor = glfwGetPrimaryMonitor();
	GLFWwindow* window;

	if(fullscreen)
		window = glfwCreateWindow(glfwGetVideoMode(monitor)->width, glfwGetVideoMode(monitor)->height, "NucelarEngine", monitor, nullptr);//pointer to window
	else
		window = glfwCreateWindow(glfwGetVideoMode(monitor)->width, glfwGetVideoMode(monitor)->height, "NucelarEngine", nullptr, nullptr);//pointer to window

	if (window == nullptr)
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




