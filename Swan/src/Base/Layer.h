#pragma once
#include "Timestep.h"

#include <vector>


namespace Swan
{
    class Layer
	{
	public:
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnNuklearRender(void* ctx) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(/*Event& e*/) {}
		virtual void Begin() {}
		virtual void End() {}

		//for nuklear - no idea do i need this
		virtual void* GetCtx() { /*assert(false);*/ return nullptr; }
	};
	
}