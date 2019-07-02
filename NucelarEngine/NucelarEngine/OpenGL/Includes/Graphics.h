#include <glad/glad.h>
#include <GLFW/glfw3.h>
namespace Graphics {
	GLFWwindow* InitializeWindow(int width, int height);

	void DrawRectangle(float x, float y, float width, float height);
}