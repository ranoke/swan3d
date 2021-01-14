#include "pch.h"
#include "Application.h"

#include "Timestep.h"

#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"
#include "Renderer/RendererCommand.h"
#include "Renderer/Camera.h"
#include "Renderer/Light.h"

#include <nuklear.h>

#include <glad/glad.h>

#include <glm.hpp>

#include <GLFW/glfw3.h>



namespace Swan
{
    #define SW_BIND_EVENT_FN(fn)  std::bind(&fn, this, std::placeholders::_1)

    Application* Application::m_App = nullptr;

    Application::Application()
    {
        m_App = this;
        m_Window = new Window("Swan3d", 640, 480);
        // m_GuiLayer = new NuklearLayer();
		// PushOverlay(m_GuiLayer);

        m_GuiLayer = new ImGuiLayer();
        PushOverlay(m_GuiLayer);
		
    }

    Application::~Application()
    {

    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }
    void Application::PushOverlay(Layer* layer)
    {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    // void Application::OnEvent(Event& e)
    // {
    //     EventDispatcher dispatcher(e);
    //     dispatcher.Dispatch<WindowCloseEvent>(SW_BIND_EVENT_FN(Application::OnApplicationClose));

    //     for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
	// 	{
	// 		(*--it)->OnEvent(e);
	// 		if (e.Handled)
	// 			break;
	// 	}
    // }

    void Application::Init()
    {
        

    }

    void Application::Run()
    {

        RendererCommand::SetClearColor({0.1, 0.1, 0.1, 1});



        while(m_Running)
        {
            glCullFace(GL_BACK);
            glEnable(GL_DEPTH_TEST);
            glDepthMask(GL_TRUE);

            float time = (float)glfwGetTime();
            Timestep ts = time - m_Time;
            m_Time = time;

           
            

            for(Layer* i : m_LayerStack)
                i->OnUpdate(ts);

            m_GuiLayer->Begin();
            for(Layer* i : m_LayerStack)
            {
               i->OnNuklearRender(m_GuiLayer->GetCtx());
               i->OnImGuiRender();
            }
            m_GuiLayer->End();

            m_Window->Update();
        }
    }

    bool Application::OnApplicationClose()
    {
        m_Running = false;
        return false;
    }
 
}
