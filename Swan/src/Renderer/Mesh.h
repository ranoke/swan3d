#pragma once
#include "Renderer.h"
#include <string>
#include <cstring>

namespace Swan
{
  class Mesh
  {
  public:
    Mesh() {}
    Mesh(const std::string& filepath);
    Mesh(const Mesh&) = default;

    void Load(const std::string& filepath);
    void Unload();

    operator BufferObject() const { return m_BufferObject; }

  private:
    //RenderObject m_RenderObject;
    BufferObject m_BufferObject {0};
  };

}
