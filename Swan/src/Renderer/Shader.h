#pragma once

#include <mat4x4.hpp>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

#include <unordered_map>

namespace Swan
{
    class Shader{
    public:

        Shader() {}
        Shader(const std::string& filepath);
        Shader(std::string& name, std::string& filepath);
        Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
        ~Shader();
        void Bind();
        void UnBind(); 

        void SetName(const std::string& name) { m_Name = name; }
        std::string& GetName() { return m_Name; }

        
        void SetMat4(const char* name, const glm::mat4& val);
        void SetFloat(const char* name, const float& val);
        void SetFloat3(const char* name, const glm::vec3& val);
    private:
        uint32_t m_Program;
        std::string m_Name;        
    };


    class ShaderLibrary
    {
    public:
        ShaderLibrary() {}
        ~ShaderLibrary();
        void Add(Shader* shader);
        Shader* Get(const std::string& name);

    private:
        std::unordered_map<std::string, Shader*> m_Shaders;
    };

}