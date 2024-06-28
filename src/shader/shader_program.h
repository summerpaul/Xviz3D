/**
 * @Author: Xia Yunkai
 * @Date:   2024-06-28 17:50:12
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-28 18:05:54
 */
#include <stdint.h>

#ifndef __SHADER_PROGRAM_H__
#define __SHADER_PROGRAM_H__
#include <glad/glad.h>
namespace shader
{
    class ShaderProgram
    {
    public:
        void compose();

    private:
        GLuint m_vertShader;
        GLuint m_fragShader;
        GLuint m_tescShader;
        GLuint m_teseShader;
        GLuint m_geomShader;
    };
}
#endif /* __SHADER_PROGRAM_H__ */
