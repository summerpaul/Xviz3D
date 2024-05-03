/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-03 11:45:05
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-03 12:23:20
 */
#include <stdint.h>

#ifndef __FRAMEBUFFER_H__
#define __FRAMEBUFFER_H__

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <initializer_list>

namespace graphics
{
    class Shader;

    enum class FramebufferTextureFormat
    {
        None = 0,
        // Color
        RGBA8,
        RGB,
        RED_INTEGER,

        // Depth/stencil
        DEPTH24STENCIL8,

        // Defaults
        Depth = DEPTH24STENCIL8
    };

    struct FramebufferTextureSpec
    {
        FramebufferTextureSpec() = delete;
        FramebufferTextureSpec(FramebufferTextureFormat format) : texture_format(format) {}
        FramebufferTextureFormat texture_format = FramebufferTextureFormat::None;
    };

    struct FramebufferSpec
    {
        FramebufferSpec() = delete;
        FramebufferSpec(uint32_t framebuffer_width, uint32_t framebuffer_height, uint32_t msaa_samples, std::initializer_list<FramebufferTextureSpec> color_attachments, FramebufferTextureSpec depth_attachment = FramebufferTextureFormat::None)
            : width(framebuffer_width), height(framebuffer_height), samples(msaa_samples), color_attachments_spec(color_attachments), depth_attachment_spec(depth_attachment) {}

        uint32_t width, height;
        std::vector<FramebufferTextureSpec> color_attachments_spec;
        FramebufferTextureSpec depth_attachment_spec = FramebufferTextureFormat::None;
        uint32_t samples = 1;
    };

    namespace util
    {
        inline GLenum GetTextureTarget(bool is_msaa);
        inline GLenum ConvertFormat(const FramebufferTextureFormat &format);
        inline GLenum GetDataType(const FramebufferTextureFormat &format);
        inline void AttachColorAttachment(uint32_t &id, int samples, uint32_t width, uint32_t height, const FramebufferTextureSpec &spec, int index);
        inline void AttachDepthRBO(uint32_t &id, int samples, uint32_t width, uint32_t height, const FramebufferTextureSpec &spec);
        inline bool GenFramebuffer(uint32_t &id, const FramebufferSpec &spec, std::vector<uint32_t> &color_id, uint32_t &depth_id);
    }

    class Framebuffer
    {
    public:
        /**
         * spec_.samples = 1 forced
         */
        Framebuffer() = delete;
        Framebuffer(const FramebufferSpec &spec);
        ~Framebuffer();
        uint32_t GetFbo() const;
        uint32_t get_color_attachment(uint32_t index = 0) const;
        uint32_t get_width() const;
        uint32_t get_height() const;
        GLenum get_color_format(uint32_t idx = 0) const;
        float get_aspect() const;
        void draw(Shader &shader);
        void bind_without_clear();
        void bind(const glm::vec4 &color = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
        void bind_with_depth(const glm::vec4 &color = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
        void bind_with_depth_and_stencil(const glm::vec4 &color = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
        void unbind();
        bool error();
        const int read_pixel(unsigned int x, unsigned int y, uint32_t color_attachment_idx)
        {
            if (spec_.samples > 1)
            {
                glBindFramebuffer(GL_READ_FRAMEBUFFER, m_intermediateRendererId);
            }
            else
            {
                glBindFramebuffer(GL_READ_FRAMEBUFFER, m_rendererId);
            }
            glReadBuffer(GL_COLOR_ATTACHMENT0 + 1);

            int data = 0;
            glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &data);

            glReadBuffer(GL_NONE);
            glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

            return data;
        }
        void attach_depth24_stencil8(Framebuffer *framebuffer = nullptr)
        {
            if (framebuffer)
            {
                glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, framebuffer->depth_id_);
            }
            else
            {
                glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depth_id_);
            }
        }

    private:
        void InitFramebuffer();
        void set_quad_VAO();
        void InitFramebufferWithMSAA();

    private:
        uint32_t m_rendererId;
        uint32_t m_intermediateRendererId;
        uint32_t tmp_texture_id_;
        FramebufferSpec spec_;

        std::vector<uint32_t> color_id_;
        uint32_t depth_id_;
        uint32_t intermediate_color_id_;
        uint32_t screen_texture_id_;

        // uint32_t msaa_texture_id_ = 0;
        // uint32_t screen_texture_id_ = 0;
        // uint32_t d24s8_RBO_ = 0;
        uint32_t quad_VAO_ = 0;
        uint32_t quad_VBO_ = 0;
        bool m_isError = false;

        inline static const float c_quadVertices[24] = {
            // positions   // texCoords
            -1.0f, 1.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 1.0f, 0.0f,

            -1.0f, 1.0f, 0.0f, 1.0f,
            1.0f, -1.0f, 1.0f, 0.0f,
            1.0f, 1.0f, 1.0f, 1.0f};
    };
}
#endif /* __FRAMEBUFFER_H__ */
