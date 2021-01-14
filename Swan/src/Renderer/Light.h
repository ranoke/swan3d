#pragma once

#include <glm.hpp>

namespace Swan
{
    class Light
    {
    public:
        Light()
            : m_Position(glm::vec3(0.f)), m_Color(glm::vec4(1.f)) 
        {
        }
        Light(glm::vec3& position, glm::vec4& color)
            : m_Position(position), m_Color(color)
        {
        }
        const glm::vec3& GetPosition() { return m_Position; }
        const glm::vec4& GetColor() { return m_Color; }
    private:
        glm::vec3 m_Position;
        glm::vec4 m_Color;

    };
}