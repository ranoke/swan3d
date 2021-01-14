#pragma once
#include "Base/Timestep.h"

#include "Components.h"
#include "Renderer/Framebuffer.h"

#include <entt/entt.hpp>

namespace Swan
{
    class Entity;

    class Scene
    {
    public:

      Entity CreateEntity(const std::string& name = std::string());
      void DestroyEntity(Entity entity);

      void OnLoad();
      void OnUpdate(Timestep ts, Camera& camera);



    private:
      entt::registry m_Registry;
      friend class Entity;
      friend class SceneHierarhy;
    };

} // namespace Swan
