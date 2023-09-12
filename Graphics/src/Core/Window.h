#pragma once

#include <functional>

#include "Core/Base.h"
#include "Events/Event.h"

struct WindowProps {
	std::string Title;
	uint32_t Width;
	uint32_t Height;
	WindowProps(const std::string& title = "GraphicsCore", uint32_t width = 1600, uint32_t height = 900)
		: Title(title), Width(width), Height(height)
	{

	}
};

class Window {
public:
	using EventCallbackFn = std::function<void(Event&)>;

	virtual ~Window() {}

	//TODO: using timestep as a parameter.
	virtual void OnUpdate() = 0;

	virtual uint32_t GetWidth() const = 0;
	virtual uint32_t GetHeight() const = 0;

	virtual void SetEventCallback(EventCallbackFn callback) = 0;;
	virtual void SetVSync(bool enabled) = 0;
	virtual bool IsVSync() const = 0;

	virtual void* GetNativeWindow() = 0;
	//ֻ��Application���ȥ����window�����Բ���Ҫʹ�õ�����ȫ�־�̬ʵ��
	static Window* Create(const WindowProps& props);
};