#pragma  once
#include "Base/Layer.h"

//#include <nuklear.h>
//#include <nuklear_glfw_gl3.h>




namespace Swan
{


    class NuklearLayer : public Layer
    {
	public:
        NuklearLayer();
		~NuklearLayer() override;

		void OnAttach() override;
		void OnDetach() override;
        void Begin() override;
        void End() override;

		void* GetCtx() { return m_Ctx; }
	private:
		void* m_Ctx;
		void* m_Glfw;
	};

	class ImGuiLayer : public Layer
	{
	public:
        ImGuiLayer();
		~ImGuiLayer() override;

		void OnAttach() override;
		void OnDetach() override;
        void Begin() override;
        void End() override;
	};

    
}