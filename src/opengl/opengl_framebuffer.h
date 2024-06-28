/**
 * @Author: Xia Yunkai
 * @Date:   2024-06-26 15:25:26
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-26 15:25:57
 */
#include <stdint.h>

#ifndef __OPENGL_FRAMEBUFFER_H__
#define __OPENGL_FRAMEBUFFER_H__
#include <string>

#include <glad/glad.h>
namespace opengl
{
    class OpenGLFramebuffer
    {
    public:
        OpenGLFramebuffer(int width, int height);
        ~OpenGLFramebuffer();

        void ReSize(int width, int height);
        void Use();
        void UnUse();
        int GetWidth();
        int GetHeight();

        GLuint GetBoundTextureId();

    private:
        void CreateFBO();

        int m_width = 0;
        int m_height = 0;

        GLuint m_textureBind = 0;
        GLuint m_fbo;
    };
}

#endif /* __OPENGL_FRAMEBUFFER_H__ */
