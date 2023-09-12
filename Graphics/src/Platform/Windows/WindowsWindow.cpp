#include "WindowsWindow.h"
#include <iostream>

#include "Platform/OpenGL/OpenGLContext.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

static uint8_t s_GLFWWindowCount = 0;

WindowsWindow::WindowsWindow(const WindowProps& props)
{
	Init(props);
}

WindowsWindow::~WindowsWindow()
{
	ShutDown();
}

void WindowsWindow::OnUpdate()
{
	glfwPollEvents();
	m_Context->SwapBuffers();
}

void WindowsWindow::SetVSync(bool enabled)
{
	m_Data.VSync = enabled;
	if (enabled)
	{
		glfwSwapInterval(1);
		return;
	}

	glfwSwapInterval(0);
}

bool WindowsWindow::IsVSync() const
{
	return m_Data.VSync;
}

void WindowsWindow::Init(const WindowProps& props)
{
	m_Data.Title = props.Title;
	m_Data.Width = props.Width;
	m_Data.Height = props.Height;

	if (s_GLFWWindowCount == 0)
	{
		int success = glfwInit();

		if (!success)
		{
			std::cout << "Could not intialize GLFW!" << std::endl;
			char* p = 0;
			*p = 1;
		}

		s_GLFWWindowCount++;
	}

	m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
	if (!m_Window)
	{
		std::cout << "GLFW Failed to create window." << std::endl;
		char* p = 0;
		*p = 1;
	}

	m_Context = new OpenGLContext(m_Window);

	glfwSetWindowUserPointer(m_Window, &m_Data);
	SetVSync(true);

	glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
		WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

		WindowCloseEvent e;
		data->Callback(e);
		});

	glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
		WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

		WindowResizeEvent e(width, height);
		data->Callback(e);
		});

	glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) {
		WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

		MouseScrolledEvent e((float)xoffset, (float)yoffset);
		data->Callback(e);
		});

	glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

		switch (action) {
		case GLFW_RELEASE:
		{
			KeyReleasedEvent e(key);
			data->Callback(e);
			break;
		}
		case GLFW_PRESS:
		{
			KeyPressedEvent e(key, 0);
			data->Callback(e);
			break;
		}
		case GLFW_REPEAT:
		{
			KeyPressedEvent e(key, true);
			data->Callback(e);
			break;
		}
		}
		});
}

void WindowsWindow::ShutDown()
{
	glfwDestroyWindow(m_Window);
	--s_GLFWWindowCount;
	if (s_GLFWWindowCount == 0)
	{
		glfwTerminate();
	}
}