#include "pch.h"
#include "Texture.h"
#include "Utils/stb_image.h"
#include <glad/glad.h>

namespace Swan
{

  Texture::Texture(const std::string& filepath)
  {
    int width, height, channels;
    TextureDesc desc = {0};
    desc.Data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
    if(!desc.Data)
    {
      assert(false && "Failed to load texture");
      return;
    }

    desc.Width = width;
    desc.Height = height;

    switch(channels)
    {
      case 3: desc.DataModel = GL_RGB; break;
      case 4: desc.DataModel = GL_RGBA; break;
      default: desc.DataModel = GL_RGB; break;
    } 
    printf("Channels: %d\n", channels);
    desc.DataType = GL_UNSIGNED_BYTE;
    desc.TextureType = GL_TEXTURE_2D;
    Create(desc);
  }

  Texture::Texture(const TextureDesc& desc)
  {
    puts("desc");
    Create(desc);
  }

  Texture::~Texture()
  {
    glDeleteTextures(1, &m_TextureID);
  }

  void Texture::Bind()
  {
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
  }

  void Texture::Unbind()
  {
    glBindTexture(GL_TEXTURE_2D, 0);
  }

  void Texture::Create(const TextureDesc& desc)
  {
    glGenTextures(1, &m_TextureID); 
    glBindTexture(desc.TextureType, m_TextureID);
    glTexParameteri(desc.TextureType, GL_TEXTURE_WRAP_S, GL_REPEAT); 

    glTexParameteri(desc.TextureType, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(desc.TextureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(desc.TextureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(desc.TextureType, 0, desc.DataModel, desc.Width, desc.Height, 0, desc.DataModel, desc.DataType, desc.Data);
    glGenerateMipmap(desc.TextureType);
    glBindTexture(desc.TextureType, 0);
  }

} // namespace Swan
