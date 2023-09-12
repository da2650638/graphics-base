#pragma once
#include "Render/GraphicsContext.h"
#include <GLFW/glfw3.h>

class OpenGLContext : public GraphicsContext
{
public:
	OpenGLContext(GLFWwindow* windowHandle);

	virtual void Init();
	virtual void SwapBuffers();
private:
	GLFWwindow* m_WindowHandle;
};