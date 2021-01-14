#pragma once
#include <entt/entt.hpp>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/quaternion.hpp>

#include "Renderer/Camera.h"
#include "Renderer/Mesh.h"

namespace Swan
{
  struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) {}

    operator bool() { return Tag.size(); }
	};

	struct TransformComponent
	{
		glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3& translation)
			: Translation(translation) {}

		glm::mat4 GetTransform() const
		{
			glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

			return glm::translate(glm::mat4(1.0f), Translation)
				* rotation
				* glm::scale(glm::mat4(1.0f), Scale);
		}
	};

  // TODO add freeing memory after deleting it
	struct MeshComponent
  {
    Mesh mesh;
    std::string filepath;
    MeshComponent() = default;
    MeshComponent(const std::string& filepath)
      : filepath(filepath) 
    {
      mesh.Load(filepath);
    }
  
  };

	

} //namespace Swan
