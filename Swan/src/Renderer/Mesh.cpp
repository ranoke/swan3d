#include "pch.h"
#include "Mesh.h"

#include <tiny_obj_loader.h>

namespace Swan
{

  Mesh::Mesh(const std::string& filepath)
  {
    Load(filepath);
  }



  void Mesh::Load(const std::string& filepath)
  {
    puts("Load");
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn;
    std::string err;
    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filepath.c_str(),
                                "./", true);
   
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    for (const auto& shape : shapes) {
      for (const auto& index : shape.mesh.indices) {
          Vertex vertex{};
          vertex.pos = {
            attrib.vertices[3 * index.vertex_index + 0],
            attrib.vertices[3 * index.vertex_index + 1],
            attrib.vertices[3 * index.vertex_index + 2]
        };
        vertex.normal = {
          attrib.normals[3 * index.vertex_index + 0],
          attrib.normals[3 * index.vertex_index + 1],
          attrib.normals[3 * index.vertex_index + 2]
        };
        vertex.uv = {
            attrib.texcoords[2 * index.vertex_index + 0],
            attrib.texcoords[2 * index.vertex_index + 1],
        };
        
        vertices.push_back(vertex);
        indices.push_back(indices.size());
      }
    }

    m_BufferObject = Renderer::LoadBuffer(&vertices[0], vertices.size()*sizeof(Vertex), &indices[0], indices.size()*sizeof(uint32_t));
  }


  void Mesh::Unload()
  {
    // dont know is it actually fine but i think
    // its better then messing around with moving semantics

    delete m_BufferObject.vbo;
    delete m_BufferObject.ibo;
  }

}
