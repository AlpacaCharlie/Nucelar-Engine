#include "Graphics.h"
#include <iostream>
#include "Graphics/Color/Color.h"

int main()
{
	GLFWwindow* window = Graphics::InitializeWindow(1920, 1050);
		Color plastidecor = Color{ 0xff8000ff };
		Color carioca = Color{ 0xffffff00 };

		//render/por ahora pone naranja toda la pantalla cada frame (los dos buffers)
		glClearColor(plastidecor.v[0] , plastidecor.g, plastidecor.b, plastidecor.a);//naranja
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glClearColor(carioca.r, carioca.g, carioca.b, carioca.a);//naranja
		glClear(GL_COLOR_BUFFER_BIT);

	while (!glfwWindowShouldClose(window))
	{
		//input
		//...
		

		

		// check and call events and swap the buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	}


	glfwTerminate();
	return 0;
}