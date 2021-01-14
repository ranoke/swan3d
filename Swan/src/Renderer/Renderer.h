#pragma once

#include <glm.hpp>
#include "Camera.h"
#include "Buffer.h"
#include "Texture.h"


namespace Swan{

    struct Vertex{
      glm::vec3 pos;
      glm::vec3 normal;
      glm::vec2 uv;
    };

    struct RenderObject{
      uint32_t offset;
      uint32_t count;
    };

    struct BufferObject
    {
      VertexBuffer* vbo;
      IndexBuffer* ibo; 
      uint32_t offset;
      uint32_t count;
    };


    class Renderer{
    public:
      static void Init();
      static void Shutdown();

      static void BeginScene(Camera& cam);
      static void BeginScene(Camera& cam, glm::mat4& view);
      static void EndScene();

      static BufferObject LoadBuffer(void* vertices, size_t vertices_size, uint32_t* indices, size_t indices_size);
      static void FreeBuffer(BufferObject obj);
      static RenderObject Load(void* vertices, size_t vertices_size, uint32_t* indices, size_t indices_size);
      static void RenderLoaded(RenderObject obj, glm::mat4& transform);
      static void RenderBuffer(BufferObject obj, glm::mat4& transform, glm::vec3 color, Texture* texture);
    };

} // namespace Swan
