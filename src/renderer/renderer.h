/**
 * @Author: Xia Yunkai
 * @Date:   2024-06-28 17:31:58
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-28 17:35:22
 */
#include <stdint.h>

#ifndef __RENDERER_H__
#define __RENDERER_H__
#include "opengl/opengl_texture.h"
#include "opengl/opengl_framebuffer.h"
namespace renderer
{
    class Renderer
    {
    public:
        GLuint Draw(PerspectiveCamera *cam, int width, int height);
    };
} // namespace renderer

#endif /* __RENDERER_H__ */
