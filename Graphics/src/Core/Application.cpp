#include "Application.h"

#include <iostream>

#include <glad/glad.h>

Application* Application::s_Instance = nullptr;

Application::Application()
	: m_Running(true),
	  m_LayerStack()
{
	s_Instance = this;
	//start up
	std::cout << "Start up" << std::endl;


	WindowProps props{ "Graphics", 1600, 900 };
	//Window Init(Start Up)
	m_Window.reset(Window::Create(props));	//不用特意调用window的shutdown了，会随着Application的析构函数一起调用
	m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
	m_Window->SetVSync(false);

	//TODO: 封装起来
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, 1600, 900);

	//不用特意清理，LayerStack自动清理
	//一定要在Window::Create之后再将m_UILayer进行PushOverlay，由初始化顺序决定的
	m_UILayer = new ImGuiLayer("UILayer");
	PushOverlay(m_UILayer);
}

Application::~Application()
{
	//clean up
	std::cout << "Clean up" << std::endl;
}

void Application::Run()
{
	//开启渲染大循环
	std::cout << "Welcome to the Ehter engine." << std::endl;
	std::cout << "Welcome to App." << std::endl;

	
	while (m_Running)
	{
		for (auto layer : m_LayerStack)
		{
			layer->OnUpdate();
		}

		m_UILayer->Begin();
		for (auto layer : m_LayerStack)
		{
			layer->OnUIRender();
		}
		m_UILayer->End();

		//Window main loop
		m_Window->OnUpdate();
	}
}

void Application::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>( std::bind(&Application::OnWindowClose, this, std::placeholders::_1) );
	dispatcher.Dispatch<WindowResizeEvent>(std::bind(&Application::OnWindowResize, this, std::placeholders::_1));

	//iterate the layer stack
	//TODO: OnEvent为什么从后往前呢？
	for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
	{
		if (e.Handled)
			break;
		(*it)->OnEvent(e);
	}
}

void Application::PushLayer(Layer* layer)
{
	m_LayerStack.PushLayer(layer);
}

void Application::PopLayer(Layer* layer)
{
	m_LayerStack.PopLayer(layer);
}

void Application::PushOverlay(Layer* overlay)
{
	m_LayerStack.PushOverlay(overlay);
}

void Application::PopOverlay(Layer* overlay)
{
	m_LayerStack.PopOverlay(overlay);
}

void Application::Close()
{
	m_Running = false;
}

bool Application::OnWindowClose(WindowCloseEvent& e)
{
	std::cout << "Closing Application..." << std::endl;
	m_Running = false;
	return true;
}

bool Application::OnWindowResize(WindowResizeEvent& e)
{
	std::cout << "New Width：" << e.GetWidth() << ", New Height:" << e.GetHeight() << std::endl;
	if (e.GetWidth() == 0 || e.GetHeight() == 0)
	{
		m_Minimized = true;
		return false;
	}
	m_Minimized = false;
	//Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
	//TODO: 封装起来
	glViewport(0, 0, e.GetWidth(), e.GetHeight());
	return false;
}
