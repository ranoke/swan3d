#include "pch.h"
#include "Shader.h"

#include <glad/glad.h>


namespace Swan
{
    static std::tuple<std::string, std::string> __read_file(const std::string& filepath)
    {
        auto f = std::ifstream(filepath, std::ifstream::in | std::ifstream::app);

        std::string line;
        std::stringstream vertex, fragment;
        std::stringstream* ss;
        while(std::getline(f, line))
        {
            if(line == "#type vertex") ss = &vertex;
            else if(line == "#type fragment") ss = &fragment;
            else *ss << line << "\n";
        }

        return {move(vertex.str()), move(fragment.str())};
    }

    static uint32_t __shader_compile(const char* shader, uint32_t type)
    {
        uint32_t vertex_id = glCreateShader(type);
        glShaderSource(vertex_id, 1, &shader, NULL);
        glCompileShader(vertex_id);
        return vertex_id;
    }

    static int __check_errors(uint32_t id, uint32_t type)
    {
        int success;
        char infoLog[512];
        // print compile errors if any
        if(type == GL_COMPILE_STATUS) glGetShaderiv(id, type, &success);
        else glGetProgramiv(id, type, &success);
        if(!success)
        {
            glGetShaderInfoLog(id, 512, NULL, infoLog);
            const char* t = type==GL_VERTEX_SHADER?"VERTEX":"FRAGMENT";
            std::cout << "Error: " << infoLog << "\n"; 
            assert(false && "Failed compile shader!" && t);
        }
        return success;
    }


    Shader::Shader(const std::string& filepath)
    {
       auto [v,f] = __read_file(filepath);
        

        auto vertex = v.c_str();
        auto fragment = f.c_str();

        
        unsigned int vertex_id, fragment_id;
        int success;

        
        // compile Shader
        vertex_id = __shader_compile(v.c_str(), GL_VERTEX_SHADER);
        __check_errors(vertex_id, GL_COMPILE_STATUS);

        fragment_id = __shader_compile(f.c_str(), GL_FRAGMENT_SHADER);
        __check_errors(fragment_id, GL_COMPILE_STATUS);       
       
        // shader Program
        m_Program = glCreateProgram();
        glAttachShader(m_Program, vertex_id);
        glAttachShader(m_Program, fragment_id);
        glLinkProgram(m_Program);
        __check_errors(m_Program, GL_LINK_STATUS);
        
        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex_id);
        glDeleteShader(fragment_id); 
    }

    Shader::Shader(std::string& name, std::string& filepath)
        : m_Name(name)
    {
        auto [v,f] = __read_file(filepath);
        

        auto vertex = v.c_str();
        auto fragment = f.c_str();

        
        unsigned int vertex_id, fragment_id;
        int success;

        
        // compile Shader
        vertex_id = __shader_compile(v.c_str(), GL_VERTEX_SHADER);
        __check_errors(vertex_id, GL_COMPILE_STATUS);

        fragment_id = __shader_compile(f.c_str(), GL_FRAGMENT_SHADER);
        __check_errors(fragment_id, GL_COMPILE_STATUS);       
       
        // shader Program
        m_Program = glCreateProgram();
        glAttachShader(m_Program, vertex_id);
        glAttachShader(m_Program, fragment_id);
        glLinkProgram(m_Program);
        __check_errors(m_Program, GL_LINK_STATUS);
        
        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertex_id);
        glDeleteShader(fragment_id);
    }
    Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
    {

    }

    Shader::~Shader()
    {
        glUseProgram(0);
        glDeleteProgram(m_Program);
    }

    void Shader::Bind()
    {
        glUseProgram(m_Program);
    }

    void Shader::UnBind()
    {
        glUseProgram(0);
    }

    void Shader::SetMat4(const char* name, const glm::mat4& val)
    {
        int loc = glGetUniformLocation(m_Program, name);
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(val));
    }

    void Shader::SetFloat(const char* name, const float& val)
    {
        int loc = glGetUniformLocation(m_Program, name);
        glUniform1f(loc, val);
    }

    void Shader::SetFloat3(const char* name, const glm::vec3& val)
    {
        int loc = glGetUniformLocation(m_Program, name);
        glUniform3fv(loc, 1, glm::value_ptr(val));
    }

    ShaderLibrary::~ShaderLibrary()
    {
        for(auto& s : m_Shaders)
            delete &s;
    }

    void ShaderLibrary::Add(Shader* shader)
    {
        auto search = m_Shaders.find(shader->GetName());
        if(search != m_Shaders.end()) 
        {
            std::cout << search->first << " " << search->second->GetName() << "\n"; 
            assert(false && "Shader already exists in the library");
        }
        m_Shaders.insert({shader->GetName(), shader});
    }

    Shader* ShaderLibrary::Get(const std::string& name)
    {
        return m_Shaders.at(name);
    }
}