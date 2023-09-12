#include "Window.h"

#include "Platform/Windows/WindowsWindow.h"

Window* Window::Create(const WindowProps& props)
{
	return  new WindowsWindow(props);
}