#pragma once

#include "Buffer.h"

#include <vector>

namespace Swan {

	class VertexArray
	{
	public:
		VertexArray();
		virtual ~VertexArray();

		virtual void Bind() const;
		virtual void Unbind() const;

		virtual void AddVertexBuffer(VertexBuffer* vertexBuffer);
		virtual void SetIndexBuffer(IndexBuffer* indexBuffer);

		virtual const std::vector<VertexBuffer*>& GetVertexBuffers() const { return m_VertexBuffers; }
		virtual const IndexBuffer* GetIndexBuffer() const { return m_IndexBuffer; }
	private:
		uint32_t m_RendererID;
		uint32_t m_VertexBufferIndex = 0;
		std::vector<VertexBuffer*> m_VertexBuffers;
		IndexBuffer* m_IndexBuffer;
	};

}