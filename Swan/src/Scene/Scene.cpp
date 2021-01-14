#include "pch.h"
#include "Scene.h"
#include "Renderer/Renderer.h"

#include "Entity.h"

namespace Swan
{

  Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;
		return entity;
	}

	void Scene::DestroyEntity(Entity entity)
	{
		m_Registry.destroy(entity);
	}

    void Scene::OnLoad()
    {
    }
    
    void Scene::OnUpdate(Timestep ts, Camera& camera)
    {
      glm::mat4 view = glm::mat4(1.0f);
      view = glm::translate(view, glm::vec3(0.f, 3.f, 5.0f));
      Renderer::BeginScene(camera, view);

      auto group = m_Registry.group<TransformComponent>(entt::get<MeshComponent>);
      for (auto entity : group)
      {
        const auto [transform, mesh] = group.get<TransformComponent, MeshComponent>(entity);


        auto t = transform.GetTransform();
        Renderer::RenderBuffer(mesh.mesh, t, glm::vec3(255), nullptr);
      }

      Renderer::EndScene();
    }


}// namespace Swan
