#pragma once
#include "Core/Graphics.h"

class GraphicsAppLayer : public Layer {
public:
	GraphicsAppLayer(const std::string& name)
		: Layer(name) {}
	virtual ~GraphicsAppLayer()
	{

	}

	virtual void OnAttach() override 
	{
		//初始化
        uint32_t width = 1280, height = 720;
        m_ImageData = new uint32_t[width * height];
        for (uint32_t y = 0; y < height; y++)
        {
            for (uint32_t x = 0; x < width; x++)
            {
                //整个纹理设置成红色
                m_ImageData[y * width + x] = 0xff0000ff;
            }
        }
        m_Image1 = Texture2D::Create(width, height);
        m_Image1->SetData((void*)m_ImageData, sizeof(uint32_t) * width * height);
        m_Image2 = Texture2D::Create("assets/textures/Checkerboard.png");
	}
	//TODO: virtual void OnUpdate(Timestep ts);
	virtual void OnUpdate() override 
	{
		//TODO: 封装起来
		glClearColor(0.2f, 0.2f, 0.2f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	virtual void OnUIRender() override 
	{
        // READ THIS !!!
        // TL;DR; this demo is more complicated than what most users you would normally use.
        // If we remove all options we are showcasing, this demo would become:
        //     void ShowExampleAppDockSpace()
        //     {
        //         ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
        //     }
        // In most cases you should be able to just call DockSpaceOverViewport() and ignore all the code below!
        // In this specific demo, we are not using DockSpaceOverViewport() because:
        // - (1) we allow the host window to be floating/moveable instead of filling the viewport (when opt_fullscreen == false)
        // - (2) we allow the host window to have padding (when opt_padding == true)
        // - (3) we expose many flags and need a way to have them visible.
        // - (4) we have a local menu bar in the host window (vs. you could use BeginMainMenuBar() + DockSpaceOverViewport()
        //      in your code, but we don't here because we allow the window to be floating)

        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        bool open = true;
        bool* p_open = &open;
        ImGui::Begin("DockSpace Demo", p_open, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }
        else
        {
            
        }

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Options"))
            {
                // Disabling fullscreen would allow the window to be moved to the front of other windows,
                // which we can't undo at the moment without finer window depth/z control.

                if (ImGui::MenuItem("Close", NULL, false, p_open != NULL))
                    Application::Get().Close();
                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        //Code Your UI.
        ImGui::Begin("Viewport");
        auto viewport_width = ImGui::GetContentRegionAvail().x;
        auto viewport_height = ImGui::GetContentRegionAvail().y;
        if (viewport_width != m_ViewportWidth || viewport_height != m_ViewportHeight)
        {
            OnViewportSizeChange((uint32_t)viewport_width, (uint32_t)viewport_height);
        }
        if (m_Image2)
        {
            auto rendererId = m_Image2->GetRendererID();
            ImGui::Image((void*)rendererId, { viewport_width,viewport_height }, ImVec2{0, 1}, ImVec2{1,0});
        }            
        ImGui::End();   //Viewport

        ImGui::Begin("Settings And Status");
        ImGui::End();   //Settings And Status

        ImGui::End();   //DockSpace Demo
	}
	virtual void OnDetach() override 
	{
		//销毁资源
	}
	virtual void OnEvent(Event& e) override 
	{
	}
private:
    void OnViewportSizeChange(uint32_t width, uint32_t height)
    {
        m_ViewportWidth = width, m_ViewportHeight = height;
        if (!m_ImageData)
            delete[] m_ImageData;
        m_ImageData = new uint32_t[width * height];
        memset(m_ImageData, 0, m_ViewportWidth * m_ViewportHeight * sizeof(uint32_t));
        for (uint32_t y = 0; y < height; y++)
        {
            for (uint32_t x = 0; x < width; x++)
            {
                //整个纹理设置成红色
                m_ImageData[y * width + x] = 0xff0000ff;
            }
        }
        m_Image1 = Texture2D::Create(width, height);
        m_Image1->SetData((void*)m_ImageData, sizeof(uint32_t) * width * height);
    }
private:
    std::shared_ptr<Texture2D> m_Image1;
    std::shared_ptr<Texture2D> m_Image2;
    uint32_t* m_ImageData = nullptr;
    float m_ViewportWidth = 0.f, m_ViewportHeight = 0.f;
};

class GraphicsApp : public Application {
public:
	GraphicsApp()
	{
		PushLayer(new GraphicsAppLayer("GraphicsAppLayer"));
	}
	virtual ~GraphicsApp()
	{

	}
private:

};

Application* CreateApplication()
{
	return new GraphicsApp();
}