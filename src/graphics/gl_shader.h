/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-03 11:24:35
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-03 11:43:42
 */
#include <stdint.h>

#ifndef __GL_SHADER_H__
#define __GL_SHADER_H__
#include "shader.h"
#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
namespace graphics
{
    class GLShader : public Shader
    {
        GLShader() = delete;
        GLShader(const char *vertex_path, const char *fragment_path, const char *geometry_path = nullptr);
        ~GLShader();
        virtual void Use();
        virtual const unsigned int GetId() const;
        virtual void SetBool(const std::string &name, bool value) const;
        virtual void SetInt(const std::string &name, int value) const;
        virtual void SetUint(const std::string &name, int value) const;
        virtual void SetFloat(const std::string &name, float value) const;
        virtual void SetVec2(const std::string &name, const glm::vec2 &value) const;
        virtual void SetVec2(const std::string &name, float x, float y) const;
        virtual void SetVec3(const std::string &name, const glm::vec3 &value) const;
        virtual void SetVec3(const std::string &name, float x, float y, float z) const;
        virtual void SetVec3(const std::string &name, float xyz) const;
        virtual void SetVec4(const std::string &name, const glm::vec4 &value) const;
        virtual void SetVec4(const std::string &name, float x, float y, float z, float w);
        virtual void SetMat2(const std::string &name, const glm::mat2 &mat) const;
        virtual void SetMat3(const std::string &name, const glm::mat3 &mat) const;
        virtual void SetMat4(const std::string &name, const glm::mat4 &mat) const;

    private:
        unsigned int m_id;
        void CheckCompileErrors(GLuint shader, std::string type);
    };
} // namespace name

#endif /* __GL_SHADER_H__ */
