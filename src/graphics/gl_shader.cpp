/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-03 11:28:57
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-03 11:43:02
 */
#include <iostream>

#include "gl_shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
namespace graphics
{

    GLShader::GLShader(const char *vertex_path, const char *fragment_path, const char *geometry_path)
    {
        std::string vertex_code;
        std::string fragment_code;
        std::string geometry_code;
        std::ifstream vert_shader_file;
        std::ifstream frag_shader_file;
        std::ifstream geo_shader_file;
        vert_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        frag_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        geo_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            // open files
            vert_shader_file.open(vertex_path);
            frag_shader_file.open(fragment_path);
            std::stringstream vert_shader_stream, frag_shader_stream;
            // read file's buffer contents into streams
            vert_shader_stream << vert_shader_file.rdbuf();
            frag_shader_stream << frag_shader_file.rdbuf();
            // close file handlers
            vert_shader_file.close();
            frag_shader_file.close();
            // convert stream into string
            vertex_code = vert_shader_stream.str();
            fragment_code = frag_shader_stream.str();
            // if geometry shader path is present, also load a geometry shader
            if (geometry_path != nullptr)
            {
                geo_shader_file.open(geometry_path);
                std::stringstream geo_shader_stream;
                geo_shader_stream << geo_shader_file.rdbuf();
                geo_shader_file.close();
                geometry_code = geo_shader_stream.str();
            }
        }
        catch (std::ifstream::failure &e)
        {
            // anim::LOG("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");
        }
        const char *vert_shader_code = vertex_code.c_str();
        const char *frag_shader_code = fragment_code.c_str();

        // 2. compile shaders
        unsigned int vertex_shader, fragment_shader;
        // vertex shader
        vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, &vert_shader_code, NULL);
        glCompileShader(vertex_shader);
        CheckCompileErrors(vertex_shader, "VERTEX");
        // fragment Shader
        fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, 1, &frag_shader_code, NULL);
        glCompileShader(fragment_shader);
        CheckCompileErrors(fragment_shader, "FRAGMENT");
    }
    GLShader::~GLShader()
    {
        glDeleteProgram(m_id);
    }
    void GLShader::Use()
    {
        glUseProgram(m_id);
    }
    const unsigned int GLShader::GetId() const
    {
        return m_id;
    }
    void GLShader::SetBool(const std::string &name, bool value) const
    {
        glUniform1i(glGetUniformLocation(m_id, name.c_str()), (int)value);
    }
    void GLShader::SetInt(const std::string &name, int value) const
    {
        glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
    }
    void GLShader::SetUint(const std::string &name, int value) const
    {
        glUniform1ui(glGetUniformLocation(m_id, name.c_str()), value);
    }
    void GLShader::SetFloat(const std::string &name, float value) const
    {
        glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
    }
    void GLShader::SetVec2(const std::string &name, const glm::vec2 &value) const
    {
        glUniform2fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
    }
    void GLShader::SetVec2(const std::string &name, float x, float y) const
    {
        glUniform2f(glGetUniformLocation(m_id, name.c_str()), x, y);
    }
    void GLShader::SetVec3(const std::string &name, const glm::vec3 &value) const
    {
        glUniform3fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
    }
    void GLShader::SetVec3(const std::string &name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(m_id, name.c_str()), x, y, z);
    }
    void GLShader::SetVec3(const std::string &name, float xyz) const
    {
        glUniform3f(glGetUniformLocation(m_id, name.c_str()), xyz, xyz, xyz);
    }
    void GLShader::SetVec4(const std::string &name, const glm::vec4 &value) const
    {
        glUniform4fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
    }
    void GLShader::SetVec4(const std::string &name, float x, float y, float z, float w)
    {
        glUniform4f(glGetUniformLocation(m_id, name.c_str()), x, y, z, w);
    }
    void GLShader::SetMat2(const std::string &name, const glm::mat2 &mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    void GLShader::SetMat3(const std::string &name, const glm::mat3 &mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    void GLShader::SetMat4(const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void GLShader::CheckCompileErrors(GLuint shader, std::string type)
    {
        GLint success;
        GLchar info_log[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, info_log);
                // anim::LOG("ERROR::SHADER_COMPILATION_ERROR of type: " + type + "\n-- log:" + info_log);
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, info_log);
                // anim::LOG("ERROR::PROGRAM_LINKING_ERROR of type: " + type + "\n-- log:" + info_log);
            }
        }
    }
}