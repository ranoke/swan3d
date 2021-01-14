#pragma once


#include <iostream>
#include <functional>


namespace Swan
{
    class Window
    {
        // using EventCallbackFn = std::function<void(Event&)>;
    public:
        Window(const char* name, uint32_t width, uint32_t height);
        ~Window();

        void Update();
        void SetVsync(bool vsync);
        bool IsVsync() { return m_Vsync; }
        // void SetEventCallback(const EventCallbackFn& callback) { EventCallback = callback; }

        uint32_t GetWidth() { return m_Width; }
        uint32_t GetHeight() { return m_Height; }

        void* GetNativeWindow() { return m_Window; };
    private:
        bool m_Vsync;
        uint32_t m_Width, m_Height;
        void* m_Window;
        // EventCallbackFn EventCallback;
    };
    
   
    
} // namespace Swan
