#pragma once

#include "Window.h"
#include "Layer.h"
#include "GUI/GuiLayer.h"
#include "LayerStack.h"
// #include "Events.h"

namespace Swan
{
    class Application{
    public:
        Application();
        ~Application();

        void Init();
        void Run();

        void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

        //void OnEvent(Event& e);

        Window* GetWindow() { return m_Window; }
        static Application* GetApp() { return m_App; }
    private:
        bool OnApplicationClose();

    private:
        Window* m_Window;
        float m_Time = 0;
        Layer* m_GuiLayer;
        LayerStack m_LayerStack;
        static Application* m_App;

        bool m_Running = true;
    };   

    Application* CreateApplication();

} // namespace Swan

