#pragma once

#include <string>
#include <stdint.h>

namespace Swan
{
  
  struct TextureDesc
  {
    void* Data;
    uint32_t Width;
    uint32_t Height;
    uint32_t TextureType; // GL_TEXTURE_2D
    uint32_t DataModel; // GL_RGB
    uint32_t DataType; // GL_UINSIGNED_INT
  };

  class Texture
  {
  public:
    Texture() = default;
    Texture(const std::string& filepath);
    Texture(const TextureDesc& desc);
    Texture(Texture& other) = default;

    ~Texture();

    void Bind();
    void Unbind();
  private:
    void Create(const TextureDesc& desc);
  private:
    uint32_t m_TextureID;
  };

} // namespace Swan
