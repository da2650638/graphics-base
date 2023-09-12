#pragma once

#include <memory>

#include "LayerStack.h"
#include "ImGui/ImGuiLayer.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"

class Application
{
public:
	//start up
	Application();
	//clean up
	virtual ~Application();
	//main loop
	void Run();

	//在Window类及其子类当中通过SetEventCallback被设置到成员变量当中当作回调函数。
	void OnEvent(Event& e);

	void PushLayer(Layer* layer);
	void PopLayer(Layer* layer);
	void PushOverlay(Layer* overlay);
	void PopOverlay(Layer* overlay);

	inline Window& GetWindow() { return *m_Window; }
	static inline Application& Get() { return *s_Instance; }

	void Close();
private:
	bool OnWindowClose(WindowCloseEvent& e);
	bool OnWindowResize(WindowResizeEvent& e);
private:
	//成员变量的销毁顺序与声明顺序相反，如果需要特定的销毁顺序请注意安排声明顺序
	std::unique_ptr<Window> m_Window;
	
	ImGuiLayer* m_UILayer;
	LayerStack m_LayerStack;

	bool m_Running;
	bool m_Minimized = false;
private:
	static Application* s_Instance;
};

static Application* CreateApplication();