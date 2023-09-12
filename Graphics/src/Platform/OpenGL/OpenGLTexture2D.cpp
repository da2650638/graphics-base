#include "OpenGLTexture2D.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
{
	m_Width = width, m_Height = height;
	m_InternalFormat = GL_RGBA8;
	m_DataFormat = GL_RGBA;

	glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
	glTextureStorage2D(m_RendererID, 1, m_InternalFormat, width, height);

	glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

OpenGLTexture2D::OpenGLTexture2D(const std::string& img_path)
{
	int width, height, channels;
	stbi_set_flip_vertically_on_load(1);
	stbi_uc* data = stbi_load(img_path.c_str(), &width, &height, &channels, 0);
	if (!data)
	{
		//TODO:
		std::cout << "Load File:" << img_path << " error." << std::endl;
		char* p = 0;
		*p = 1;
	}
	if (channels == 4)
	{
		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;
	}
	else if (channels == 3)
	{
		m_InternalFormat = GL_RGB8;
		m_DataFormat = GL_RGB;
	}
	else
	{
		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;
	}
	m_Width = width, m_Height = height;
	glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
	glTextureStorage2D(m_RendererID, 1, m_InternalFormat, width, height);
	glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	stbi_image_free(data);
}

OpenGLTexture2D::~OpenGLTexture2D()
{
	glDeleteTextures(1, &m_RendererID);
}

uint32_t OpenGLTexture2D::GetWidth() const
{
	return m_Width;
}

uint32_t OpenGLTexture2D::GetHeight() const
{
	return m_Height;
}

void OpenGLTexture2D::Bind(uint32_t slot) const
{
	glBindTextureUnit(slot, m_RendererID);
}

void OpenGLTexture2D::UnBind(uint32_t slot) const
{
	glBindTextureUnit(slot, 0);
}

void OpenGLTexture2D::SetData(void* data, uint32_t size) const
{
	uint32_t bytes_per_pixel = m_DataFormat == GL_RGBA ? 4 : 3;
	glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
}
