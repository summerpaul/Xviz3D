/**
 * @Author: Xia Yunkai
 * @Date:   2024-06-26 15:25:33
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-26 15:27:33
 */

#include "opengl_framebuffer.h"
#include <iostream>
namespace opengl
{
    OpenGLFramebuffer::OpenGLFramebuffer(int width, int height)
    {
        m_width = width;
        m_height = height;

        CreateFBO();
    }

    OpenGLFramebuffer::~OpenGLFramebuffer()
    {
    }

    void OpenGLFramebuffer::ReSize(int width, int height)
    {
        bool needReCreate = false;
        needReCreate |= (width != m_width);
        needReCreate |= (height != m_height);

        if (needReCreate)
        {
            m_width = width;
            m_height = height;
            glDeleteFramebuffers(1, &m_fbo);
            glDeleteTextures(1, &m_textureBind);
            CreateFBO();
        }
    }

    void OpenGLFramebuffer::Use()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
    }

    void OpenGLFramebuffer::UnUse()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    GLuint OpenGLFramebuffer::GetBoundTextureId()
    {
        return m_textureBind;
    }

    void OpenGLFramebuffer::CreateFBO()
    {

        glGenFramebuffers(1, &m_fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
        // create a color attachment texture
        glGenTextures(1, &m_textureBind);
        glBindTexture(GL_TEXTURE_2D, m_textureBind);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureBind, 0);
        // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
        unsigned int rbo;
        glGenRenderbuffers(1, &rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height);               // use a single renderbuffer object for both a depth AND stencil buffer.
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
        // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    int OpenGLFramebuffer::GetWidth()
    {
        return m_width;
    }

    int OpenGLFramebuffer::GetHeight()
    {
        return m_height;
    }
}