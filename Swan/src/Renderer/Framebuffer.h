#pragma once

#include <stdint.h>

namespace Swan
{

  class Framebuffer
  {
  public:
    Framebuffer();
    ~Framebuffer();

    void Bind();
    void Unbind();

    uint32_t GetTexture() { return m_TextureID; }

  private:
    uint32_t m_FramebufferID;
    uint32_t m_TextureID;
  };

} // namespace Swan
