/**
 * @Author: Xia Yunkai
 * @Date:   2024-04-26 23:25:31
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-27 14:59:54
 */

#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <string>
#include <functional>
#include "event/event.h"
using namespace event;
struct GLFWwindow;
namespace window
{
    class Window
    {

    public:
        using EventCallbackFn = std::function<void(Event &)>;
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
        inline void *GetNativeWindow() const { return m_handle; }

		void SetEventCallback(const EventCallbackFn& callback);
		void SetGLFWCallbacks();

    private:
        GLFWwindow *m_handle = nullptr;
        uint32_t m_width = 500;
        uint32_t m_height = 500;
        std::string m_title = "XvizApp";
        
        struct WindowData
        {
            std::string Title;
            uint32_t Width, Height;
            bool VSync;

            EventCallbackFn EventCallback;
        };
        WindowData m_Data;
    };

}

#endif /* __WINDOW_H__ */
