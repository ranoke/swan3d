#pragma once
#include "Swan.h"

namespace Swan
{


  class SceneHierarhy
  {
  public:
    SceneHierarhy(){}
    SceneHierarhy(Scene* ctx);

    void SetScene(Scene* ctx);
    void ShowHierarhyPanel(bool show);
    void ShowPropertiesPanel(bool show);
    void DrawEntityNode(Entity e);

  private:
    Scene* m_Context;
    Entity m_SelectionContext;

  };

} // namespace Swan

