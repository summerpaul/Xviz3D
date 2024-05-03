/**
 * @Author: Xia Yunkai
 * @Date:   2024-04-26 23:25:31
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-02 00:39:03
 */

#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <string>

struct GLFWwindow;
namespace window
{
    class Window
    {

    public:
        Window() = default;
        virtual ~Window();
        bool Init(uint32_t width, uint32_t height, const std::string &title);
        void PrewDraw();
        void PostDraw();
        GLFWwindow *GetHandle() const;
        uint32_t GetWidth() const;
        uint32_t GetHeight() const;
        std::pair<uint32_t, uint32_t> GetSize() const;
        std::pair<int, int> GetFramebufferSize() const;
        void SetSize(uint32_t width, uint32_t height);
        bool ShouldClose();
        void Close();
        void ProcessEvents();
        void WaitEventsTimeout(float timeout);
        void DestroyWindow();
        void SetDropCallback(void (*fp)(GLFWwindow *window, int count, const char **paths));

    private:
        GLFWwindow *m_handle = nullptr;  // 窗口句柄
        uint32_t m_width = 500;          // 窗口宽
        uint32_t m_height = 500;         // 窗口高
        std::string m_title = "XvizApp"; // 窗口标题
        float m_factor = 1.0f;           // frame_width / window_width
    };

}

#endif /* __WINDOW_H__ */
