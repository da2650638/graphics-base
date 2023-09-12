#pragma once

#include "Render/Texture.h"

#include <glad/glad.h>

class OpenGLTexture2D : public Texture2D {
public:
	OpenGLTexture2D() = default;
	OpenGLTexture2D(uint32_t width, uint32_t height);
	OpenGLTexture2D(const std::string& img_path);
	virtual ~OpenGLTexture2D();

	virtual uint32_t GetWidth() const override;
	virtual uint32_t GetHeight() const override;
	virtual void Bind(uint32_t slot = 0) const override;
	virtual void UnBind(uint32_t slot = 0) const override;
	virtual void SetData(void* data, uint32_t size) const override;

	uint32_t GetRendererID() const { return m_RendererID; }
private:
	std::string m_Path;
	uint32_t m_RendererID = -1;
	uint32_t m_Width = 0, m_Height = 0;
	GLenum m_InternalFormat, m_DataFormat;
};