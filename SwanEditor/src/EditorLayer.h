#pragma once
#include "Swan.h"
#include "nuklear.h"
#include "stdlib.h"

#include <glad/glad.h>
#include <glm.hpp>
#include <gtx/transform.hpp>

#include "Panels/SceneHierarhy.h"


namespace Swan
{

  class EditorLayer : public Layer
  {
  public:
    glm::vec4 c = glm::vec4(1.f, 0.f, 0.f, 0.1f);
    glm::mat4 t = glm::mat4(1.f);
    std::string fps;
    float lasttime = 0;
    Mesh mesh;
    Mesh sphere;
    Scene scene;

    SceneHierarhy m_SceneHierarhy;

    Framebuffer m_SceneFramebuffer;

    void OnAttach()
    {
      Renderer::Init();
      scene.OnLoad();
      m_SceneHierarhy.SetScene(&scene);
    }


    float time = 0.f;

    void OnUpdate(Timestep ts)
    {
      Camera cam(90.f, 640 / 480, 0.1f, 100000.f);


      m_SceneFramebuffer.Bind();
      RendererCommand::Clear();           
      scene.OnUpdate(ts, cam);
      m_SceneFramebuffer.Unbind();

      time += ts;
      fps = std::to_string(1 / ts);
    }

    void OnImGuiRender()
    {
      bool show_demo_window = true;
      if (show_demo_window)
          ImGui::ShowDemoWindow(&show_demo_window);

      static bool p_open = true;

			static bool opt_fullscreen = true;
      static bool opt_padding = false;
      static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

      // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
      // because it would be confusing to have two docking targets within each others.
      ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
      if (opt_fullscreen)
      {
          ImGuiViewport* viewport = ImGui::GetMainViewport();
          ImGui::SetNextWindowPos(viewport->GetWorkPos());
          ImGui::SetNextWindowSize(viewport->GetWorkSize());
          ImGui::SetNextWindowViewport(viewport->ID);
          ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
          ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
          window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
          window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
      }
      else
      {
          dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
      }

      // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
      // and handle the pass-thru hole, so we ask Begin() to not render a background.
      if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
          window_flags |= ImGuiWindowFlags_NoBackground;

      // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
      // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
      // all active windows docked into it will lose their parent and become undocked.
      // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
      // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
      if (!opt_padding)
          ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
      ImGui::Begin("DockSpace Demo", &p_open, window_flags);
      if (!opt_padding)
          ImGui::PopStyleVar();

      if (opt_fullscreen)
          ImGui::PopStyleVar(2);

      // DockSpace
      ImGuiIO& io = ImGui::GetIO();
      if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
      {
          ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
          ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
      }
      else
      {
      }

      if (ImGui::BeginMenuBar())
      {
          if (ImGui::BeginMenu("Options"))
          {
              // Disabling fullscreen would allow the window to be moved to the front of other windows,
              // which we can't undo at the moment without finer window depth/z control.
              ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
              ImGui::MenuItem("Padding", NULL, &opt_padding);
              ImGui::Separator();

              if (ImGui::MenuItem("Flag: NoSplit",                "", (dockspace_flags & ImGuiDockNodeFlags_NoSplit) != 0))                 { dockspace_flags ^= ImGuiDockNodeFlags_NoSplit; }
              if (ImGui::MenuItem("Flag: NoResize",               "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0))                { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
              if (ImGui::MenuItem("Flag: NoDockingInCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingInCentralNode) != 0))  { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode; }
              if (ImGui::MenuItem("Flag: AutoHideTabBar",         "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0))          { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
              if (ImGui::MenuItem("Flag: PassthruCentralNode",    "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
              ImGui::Separator();

              if (ImGui::MenuItem("Close", NULL, false, p_open != NULL))
                  p_open = false;
              ImGui::EndMenu();
          }

          ImGui::EndMenuBar();
      }

    ImGui::End();

      if(ImGui::Begin("Debug"))
      {
        ImGui::Text("FPS: ");
        ImGui::SameLine();
        ImGui::Text(fps.c_str());

        ImGui::End();
      }

      if(ImGui::Begin("Viewport"))
      {
        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        ImVec2  m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
        ImTextureID my_tex_id = (void*)m_SceneFramebuffer.GetTexture();
        ImGui::Image(my_tex_id, m_ViewportSize, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

        ImGui::End();
      }

      
      m_SceneHierarhy.ShowHierarhyPanel(true);
      m_SceneHierarhy.ShowPropertiesPanel(true);
    } 
  };
} // namespace Swan
