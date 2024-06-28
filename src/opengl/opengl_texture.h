/**
 * @Author: Xia Yunkai
 * @Date:   2024-06-26 15:28:13
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-26 15:32:40
 */
#include <stdint.h>

#ifndef __OPENGL_TEXTURE_H__
#define __OPENGL_TEXTURE_H__
#include <string>

#include <glad/glad.h>

namespace opengl
{
    class OpenGLTexture
    {
    public:
        static OpenGLTexture *FromFile(const char *path);
        static OpenGLTexture *FromBytes(unsigned char *pixels, int width, int height, int channels);

        GLuint GetId();
        void Resize(int width, int height);

    private:
        OpenGLTexture() = default;

        void Create();
        void UploadImageDataFromFile(const char *path);
        void UploadImageData(unsigned char *pixels, int size);

        int m_width = 0;
        int m_height = 0;

        GLuint m_textureId = 0;
    };
} // namespace opengl

#endif /* __OPENGL_TEXTURE_H__ */
