#include "Graphics.h"
#include <iostream>


int main()
{

	GLFWwindow* window = Graphics::InitializeWindow(800, 600);


	while (!glfwWindowShouldClose(window))
	{
		//input
		//...


		//render/por ahora pone naranja toda la pantalla cada frame (los dos buffers)
		glClearColor(255.0f/255.0f, 164/255.0f, 32/255.0f, 1.0f);//naranja
		glClear(GL_COLOR_BUFFER_BIT);



		// check and call events and swap the buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	}


	glfwTerminate();
	return 0;
}