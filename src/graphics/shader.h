/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-03 11:17:32
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-03 11:22:47
 */
#include <stdint.h>

#ifndef __SHADER_H__
#define __SHADER_H__

#include <glm/glm.hpp>
#include <string>

namespace graphics
{
    class Shader
    {
    public:
        Shader() = default;
        virtual ~Shader() = default;
        virtual void Use() = 0;
        virtual const unsigned int GetId() const = 0;
        virtual void SetBool(const std::string &name, bool value) const = 0;
        virtual void SetInt(const std::string &name, int value) const = 0;
        virtual void SetUint(const std::string &name, int value) const = 0;
        virtual void SetFloat(const std::string &name, float value) const = 0;
        virtual void SetVec2(const std::string &name, const glm::vec2 &value) const = 0;
        virtual void SetVec2(const std::string &name, float x, float y) const = 0;
        virtual void SetVec3(const std::string &name, const glm::vec3 &value) const = 0;
        virtual void SetVec3(const std::string &name, float x, float y, float z) const = 0;
        virtual void SetVec3(const std::string &name, float xyz) const = 0;
        virtual void SetVec4(const std::string &name, const glm::vec4 &value) const = 0;
        virtual void SetVec4(const std::string &name, float x, float y, float z, float w) = 0;
        virtual void SetMat2(const std::string &name, const glm::mat2 &mat) const = 0;
        virtual void SetMat3(const std::string &name, const glm::mat3 &mat) const = 0;
        virtual void SetMat4(const std::string &name, const glm::mat4 &mat) const = 0;
    };

} // namespace name

#endif /* __SHADER_H__ */
