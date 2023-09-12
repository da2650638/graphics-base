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
	m_Window.reset(Window::Create(props));	//�����������window��shutdown�ˣ�������Application����������һ�����
	m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
	m_Window->SetVSync(false);

	//TODO: ��װ����
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, 1600, 900);

	//������������LayerStack�Զ�����
	//һ��Ҫ��Window::Create֮���ٽ�m_UILayer����PushOverlay���ɳ�ʼ��˳�������
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
	//������Ⱦ��ѭ��
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
	//TODO: OnEventΪʲô�Ӻ���ǰ�أ�
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
	std::cout << "New Width��" << e.GetWidth() << ", New Height:" << e.GetHeight() << std::endl;
	if (e.GetWidth() == 0 || e.GetHeight() == 0)
	{
		m_Minimized = true;
		return false;
	}
	m_Minimized = false;
	//Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
	//TODO: ��װ����
	glViewport(0, 0, e.GetWidth(), e.GetHeight());
	return false;
}
