#include "Core/Input.h"
#include "Core/Application.h"

#include <GLFW/glfw3.h>

#ifdef GRAPHICS_PLATFORM_WINDOWS
bool Input::IsKeyPressed(int keycode)
{
	auto window = (GLFWwindow*)Application::Get().GetWindow().GetNativeWindow();
	auto state = glfwGetKey(window, keycode);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Input::IsMouseButtonPressed(int button)
{
	auto window = (GLFWwindow*)Application::Get().GetWindow().GetNativeWindow();
	auto state = glfwGetMouseButton(window, button);
	return state == GLFW_PRESS;
}

std::pair<float, float> Input::GetMousePosition()
{
	auto window = (GLFWwindow*)Application::Get().GetWindow().GetNativeWindow();
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	return { (float)x ,(float)y };
}

float Input::GetMouseX()
{
	auto [x, y] = GetMousePosition();
	return x;
}

float Input::GetMouseY()
{
	auto [x, y] = GetMousePosition();
	return y;
}
#endif