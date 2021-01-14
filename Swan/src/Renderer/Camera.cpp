#include "pch.h"
#include "Camera.h"

#include <gtc/matrix_transform.hpp>

namespace Swan
{
    Camera::Camera()
    {
        m_Projection = glm::mat4(0); 
    }
    Camera::Camera(float fov_degrees, float aspect, float near, float far)
    {
        m_Projection = glm::mat4(0);
        m_Projection = glm::perspective(glm::radians(fov_degrees), aspect, near, far);
    }
    Camera::Camera(float left, float rigth, float bottom, float top, float near, float far)
    {
        m_Projection = glm::mat4(0);
        m_Projection = glm::ortho(left, rigth, bottom, top, near, far);
    }
}