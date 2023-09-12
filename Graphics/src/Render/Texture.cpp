#include "Texture.h"

#include "Platform/OpenGL/OpenGLTexture2D.h"

std::shared_ptr<Texture2D> Texture2D::Create(const std::string& img_path)
{
#ifdef GRAPHICS_API_OPENGL
	return std::make_shared<OpenGLTexture2D>(img_path);
#endif
}

std::shared_ptr<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
{
#ifdef GRAPHICS_API_OPENGL
	return std::make_shared<OpenGLTexture2D>(width, height);
#endif
}
