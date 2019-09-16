#include <iostream>
#include <fstream>
#include <sstream>


#include "Graphics.h"
#include "Graphics/Color/Color.h"

#include "Editor\ImGuiDemo.h"

#include "../Engine/BasicTypes/NObjectManager.h"

std::stringstream console;

int main()
{

   //Get the console string
	auto* coutbuf = std::cout.rdbuf();
	auto old_buf = std::cout.rdbuf(console.rdbuf());
	
	GLFWwindow* window = Graphics::InitializeWindow(800, 600);//width and height are useless, it is fullscreen and with the resolution of the display
	Color plastidecor = Color( 1.0f,0.5f,0.0f,1.0f );
	Color carioca = Color{ 255,48,0,255 };


		//const GLFWvidmode* mode = glfwGetVideoMode(window);
		//glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);

		//glfwSetWindowMonitor()
	while (!glfwWindowShouldClose(window))
	{
		//input
		//...
		

			//render/por ahora pone naranja toda la pantalla cada frame (los dos buffers)
		glClearColor(plastidecor.r, plastidecor.g, plastidecor.b, plastidecor.a);//naranja
		glClear(GL_COLOR_BUFFER_BIT);
		

		// check and call events and swap the buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	}


	glfwTerminate();
	
	
	std::cout.rdbuf(coutbuf);
	
	return 0;
}