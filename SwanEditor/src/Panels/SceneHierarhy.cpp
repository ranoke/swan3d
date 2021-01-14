#include "pch.h"
#include "SceneHierarhy.h"

namespace Swan
{

  SceneHierarhy::SceneHierarhy(Scene *ctx)
      : m_Context(ctx)
  {
  }

  void SceneHierarhy::SetScene(Scene *ctx)
  {
    m_Context = ctx;
  }

  void SceneHierarhy::ShowHierarhyPanel(bool show)
  {
    if (!show)
      return;
    if (ImGui::Begin("Hierarhy Panel"))
    {

      // get objects and display them here
      m_Context->m_Registry.each([&](auto entityID) {
        Entity entity(entityID, m_Context);
        DrawEntityNode(entity);
      });

      if (ImGui::BeginPopupContextWindow(0, 1, false))
      {

        if (ImGui::Button("New object"))
        {
          m_Context->CreateEntity("EmptyEntity");
        }
        if (ImGui::Button("Cube"))
        {
          auto new_entity = m_Context->CreateEntity("CubeEntity");
          new_entity.AddComponent<MeshComponent>("Swan/res/cube.obj");
        }
        if (ImGui::Button("Sphere"))
        {
          auto new_entity = m_Context->CreateEntity("SphereEntity");
          new_entity.AddComponent<MeshComponent>("Swan/res/sphere.obj");
        }
        ImGui::EndPopup();
      }

    }
    ImGui::End();
  }

  void SceneHierarhy::ShowPropertiesPanel(bool show)
  {
    if(!show) return;


    if(ImGui::Begin("Properties"))
    {
      if(m_SelectionContext)
      {
        auto& tag = m_SelectionContext.GetComponent<TagComponent>().Tag;
        auto& transform = m_SelectionContext.GetComponent<TransformComponent>();
        glm::vec3 rotationDegrees = {
          glm::degrees(transform.Rotation.x),
          glm::degrees(transform.Rotation.y),
          glm::degrees(transform.Rotation.z)
        };


        ImGui::Text("Entity: ");
        ImGui::SameLine();
        ImGui::Text(tag.c_str());
        ImGui::Spacing();
        
        ImGui::Text("Transform");
        ImGui::DragFloat3("Translation", glm::value_ptr(transform.Translation));
        

        ImGui::DragFloat3("Rotation", glm::value_ptr(rotationDegrees));

        ImGui::DragFloat3("Scale", glm::value_ptr(transform.Scale));

        transform.Rotation = (glm::vec3){
          glm::radians(rotationDegrees.x),
          glm::radians(rotationDegrees.y),
          glm::radians(rotationDegrees.z),
        };
      }
      
    }
    ImGui::End();

  }

  void SceneHierarhy::DrawEntityNode(Entity e)
  {
    auto &tag = e.GetComponent<TagComponent>().Tag;
    ImGuiTreeNodeFlags flags = ((m_SelectionContext == e) ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
    flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
    bool opened = ImGui::TreeNodeEx((void *)(uint64_t)(uint32_t)e, flags, tag.c_str());
    if (opened)
    {
      m_SelectionContext = e;
    }

    if(ImGui::IsItemClicked())
      m_SelectionContext = e;

    if (ImGui::BeginPopupContextItem())
    {
      if (ImGui::MenuItem("Delete Entity"))
      {
        m_Context->DestroyEntity(e);
        if (m_SelectionContext == e)
          m_SelectionContext = {};
      } 
      if(ImGui::MenuItem("Select"))
      {
        m_SelectionContext = e;
      }
      ImGui::EndPopup();
    }

    if (opened)
    {
      ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;
      bool opened = ImGui::TreeNodeEx((void *)9817239, flags, tag.c_str());
      if (opened)
        ImGui::TreePop();
      ImGui::TreePop();
    }

  }

} // namespace Swan
