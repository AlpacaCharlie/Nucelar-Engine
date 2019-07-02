#include "Graphics.h"
#include <iostream>


int main()
{

	GLFWwindow* window = Graphics::InitializeWindow(800, 600);


	while (!glfwWindowShouldClose(window))
	{
		glClearColor(255.0f/255.0f, 164.0f/255.0f, 32.0f/255.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);




		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}