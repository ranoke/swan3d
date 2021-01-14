#include "pch.h"
#include "Buffer.h"

#include <glad/glad.h>

namespace Swan
{
    VertexBuffer::VertexBuffer(uint32_t size)
    {

      glGenBuffers(1, &m_RendererID);
      glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
      glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }

    VertexBuffer::VertexBuffer(float *vertices, uint32_t size)
    {

      glGenBuffers(1, &m_RendererID);
      glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
      glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    VertexBuffer::~VertexBuffer()
    {

      glDeleteBuffers(1, &m_RendererID);
    }

    void VertexBuffer::Bind() const
    {

      glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    }

    void VertexBuffer::Unbind() const
    {
      glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VertexBuffer::SetData(const void* data, size_t size, uint32_t offset)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
	}

    // void VertexBuffer::SetData(const void *data, uint32_t size)
    // {
    //     glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    //     glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    // }

    /////////////////////////////////////////////////////////////////////////////
    // IndexBuffer //////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////
    IndexBuffer::IndexBuffer(uint32_t size)
        : m_Count(size/sizeof(uint32_t))
    {
      glGenBuffers(1, &m_RendererID);
      glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
      glBufferData(GL_ARRAY_BUFFER, size, 0, GL_DYNAMIC_DRAW);
    }

    IndexBuffer::IndexBuffer(uint32_t *indices, uint32_t count)
      : m_Count(count)
    {

      glGenBuffers(1, &m_RendererID);

      // GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
      // Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state.
      glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
      glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    IndexBuffer::~IndexBuffer()
    {

      glDeleteBuffers(1, &m_RendererID);
    }

    void IndexBuffer::SetData(const void* data, size_t size, uint32_t offset)
    {
      glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
      glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
    }

    void IndexBuffer::Bind() const
    {

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    }

    void IndexBuffer::Unbind() const
    {

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
} // namespace Swan
