#include "OpenGLContext.h"

#include <iostream>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
	: m_WindowHandle(windowHandle)
{
	Init();
}

void OpenGLContext::Init()
{
	glfwMakeContextCurrent(m_WindowHandle);
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	if (!status)
	{
		std::cout << "gladLoadGLLoader error." << std::endl;
		char* p = 0;
		*p = 1;
	}
	std::cout << "OpenGL Info:" << std::endl;
	std::string vendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
	std::string renderer = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
	std::string version = reinterpret_cast<const char*>(glGetString(GL_VERSION));
	std::cout << " Vendor:   {0}" <<  vendor;
	std::cout << " Renderer: {0}" <<  renderer;
	std::cout << " Version:  {0}" <<  version;
	int versionMajor;
	int versionMinor;
	glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
	glGetIntegerv(GL_MINOR_VERSION, &versionMinor);
	bool result = (versionMajor >= 4 && versionMinor >= 5);
	if (!result)
	{
		std::cout << "Ether requires at least OpenGL version 4.5!" << std::endl;
		char* p = 0;
		*p = 1;
	}
}

void OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(m_WindowHandle);
}