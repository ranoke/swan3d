#pragma once

#include <glad/glad.h>
#include <vec4.hpp>


namespace Swan
{
    class RendererCommand
    {
    public:
        static void SetClearColor(const glm::vec4& color)
        {
            glClearColor(color[0], color[1], color[2], color[3]);
        }
        static void Clear()
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }

    };
}
