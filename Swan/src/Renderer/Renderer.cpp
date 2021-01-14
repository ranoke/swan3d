#include "pch.h"
#include "Renderer.h"

#include "VertexArray.h"
#include "Buffer.h"
#include "Shader.h"
#include "Texture.h"

#include <glad/glad.h>

namespace Swan{

    BufferLayout defaultLayout = {
        {ShaderDataType::Float3, "aPos"},
        {ShaderDataType::Float3, "aNormal"},
        {ShaderDataType::Float2, "aUv"}  
    };

    struct RendererData{
        const uint32_t maxVertexCount = 1024*512;
        const uint32_t maxIndexCount = 1024*512;

        Shader* defaultShader;
        VertexArray* vertexArray;
        VertexBuffer* vertexBuffer;
        IndexBuffer* indexBuffer;
        Texture* whiteTexture;
        Texture* brick;

        uint32_t bufferOffset = 0; // not actually the offset, but rather a multiplayer for both vbo and ibo
    };

    static RendererData s_Data;

    void Renderer::Init()
    {
      TextureDesc desc = {0};
      desc.Data = new unsigned char[3]{255,255,255};
      desc.Width = 1;
      desc.Height = 1;
      desc.DataModel = GL_RGB;
      desc.DataType = GL_UNSIGNED_BYTE;
      desc.TextureType = GL_TEXTURE_2D;
    
      s_Data.defaultShader = new Shader("Swan/res/basic.glsl");
      s_Data.whiteTexture = new Texture(desc);
      s_Data.brick = new Texture("Swan/res/tex.jpg");
      s_Data.vertexArray = new VertexArray();
      s_Data.vertexBuffer = new VertexBuffer(s_Data.maxVertexCount*sizeof(Vertex));
      s_Data.indexBuffer = new IndexBuffer(s_Data.maxIndexCount*sizeof(uint32_t));

      s_Data.vertexBuffer->SetLayout(defaultLayout);
      auto& vao = s_Data.vertexArray;
      auto& vbo = s_Data.vertexBuffer;
      auto& ibo = s_Data.indexBuffer;
      //vao->AddVertexBuffer(vbo);
      vao->SetIndexBuffer(ibo);
    }

    void Renderer::Shutdown()
    {

    }

    void Renderer::BeginScene(Camera& cam)
    {

    }

    void Renderer::BeginScene(Camera& cam, glm::mat4& view)
    {
      auto viewprojection = cam.GetProjection() * glm::inverse(view);
      s_Data.defaultShader->Bind();
      s_Data.defaultShader->SetMat4("u_ProjView", viewprojection);
    }

    void Renderer::EndScene()
    {

    }

    BufferObject Renderer::LoadBuffer(void* vertices, size_t vertices_size, uint32_t* indices, size_t indices_size)
    {
        auto vbo = new VertexBuffer(vertices_size);
        auto ibo = new IndexBuffer(indices_size);
        vbo->SetLayout(defaultLayout);
        ibo->SetData(indices, indices_size, 0);
        auto buffer_obj = (BufferObject){vbo, ibo, 0, indices_size/sizeof(uint32_t)};
        //auto buffer_obj = (BufferObject){vbo, s_Data.bufferOffset*sizeof(uint32_t), indices_size/sizeof(uint32_t) };
        vbo->SetData(vertices, vertices_size, 0);
        //ibo->SetData(indices, indices_size, s_Data.bufferOffset*sizeof(uint32_t));
        //s_Data.bufferOffset += indices_size/sizeof(uint32_t);

        return buffer_obj;
    }

    RenderObject Renderer::Load(void* vertices, size_t vertices_size, uint32_t* indices, size_t indices_size)
    {
      uint32_t* indices_c = new uint32_t[indices_size/sizeof(uint32_t)];
      memcpy(indices_c, indices, indices_size);
      for(int i = 0; i < indices_size/sizeof(uint32_t); i++)
          indices_c[i] += s_Data.bufferOffset;

      auto& vbo = s_Data.vertexBuffer;
      auto& ibo = s_Data.indexBuffer;
      
      auto drawobject = (RenderObject){ s_Data.bufferOffset*sizeof(uint32_t), indices_size/sizeof(uint32_t) };
      vbo->SetData(vertices, vertices_size, s_Data.bufferOffset*sizeof(Vertex));
      ibo->SetData(indices_c, indices_size, s_Data.bufferOffset*sizeof(uint32_t));
      s_Data.bufferOffset += indices_size/sizeof(uint32_t);

      delete[] indices_c;
      return drawobject;
    }

    void Renderer::RenderLoaded(RenderObject obj, glm::mat4& transf)
    {
        s_Data.defaultShader->Bind();
        s_Data.defaultShader->SetMat4("u_Model", transf);

        auto& vao = s_Data.vertexArray;
        auto& vbo = s_Data.vertexBuffer;
        auto& ibo = s_Data.indexBuffer;

        vao->Bind();
        glDrawElements(GL_TRIANGLES, obj.count, GL_UNSIGNED_INT, (void*)(obj.offset));
        vao->Unbind();
    }

    void Renderer::RenderBuffer(BufferObject obj, glm::mat4& transform, glm::vec3 color, Texture* texture)
    {
      s_Data.defaultShader->Bind();
      s_Data.defaultShader->SetMat4("u_Model", transform);

      auto& vao = s_Data.vertexArray;
      auto& vbo = obj.vbo;
      //auto& ibo = s_Data.indexBuffer;
      auto& ibo = obj.ibo;
      vao->AddVertexBuffer(vbo);
      vao->SetIndexBuffer(ibo);

      s_Data.brick->Bind();

      vao->Bind();
      glDrawElements(GL_TRIANGLES, obj.count, GL_UNSIGNED_INT, (void*)(obj.offset));
      vao->Unbind();

      s_Data.brick->Unbind();
    }

}   // namespace Swan
