#pragma once
#include "Scene.h"

#include <entt/entt.hpp>

namespace Swan
{

	class Entity
	{
    public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene)
			: m_EntityHandle(handle), m_Scene(scene)
		{
		}
		Entity(Entity& other) = default;

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			T& component = m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
			//m_Scene->OnComponentAdded<T>(*this, component);
			return component;
		}

		template<typename T>
		T& GetComponent()
		{
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

    operator uint32_t() { return (uint32_t)m_EntityHandle; }
		operator entt::entity() { return m_EntityHandle; }
    operator bool() { if(!m_Scene) return false; return m_Scene->m_Registry.valid(m_EntityHandle); }

    bool operator==(const Entity& other) const
    {
      return m_EntityHandle == other.m_EntityHandle && m_Scene == other.m_Scene;
    }

	private:
		entt::entity m_EntityHandle{0};
		Scene* m_Scene = nullptr;
		friend class Scene;
	};

}
