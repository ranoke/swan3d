#pragma once

#include <matrix.hpp>

namespace Swan
{
    class Camera{
    public:
        Camera(float fovy, float aspect, float near, float far);
        // TODO add ortho cam constructor
        Camera(float left, float rigth, float bottom, float top, float near, float far);
        Camera();

        void SetProjection(const glm::mat4& proj) { m_Projection = proj; }
        glm::mat4& GetProjection() { return m_Projection; }
    private:
        glm::mat4 m_Projection;
    };
}