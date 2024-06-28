/**
 * @Author: Xia Yunkai
 * @Date:   2024-04-26 23:25:39
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-29 20:08:46
 */
#include <iostream>

#include "window.h"
#include "basis/logger.h"
#include "basis/defines.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "event/application_event.h"
#include "event/key_event.h"
#include "event/mouse_event.h"
namespace window
{
    Window::~Window()
    {
        if (m_handle != nullptr)
        {
            DestroyWindow();
        }
    }
    bool Window::Init(uint32_t width, uint32_t height, const std::string &title)
    {

        m_width = width;
        m_height = height;
        m_title = title;
        CHECK_RETURN_RET(!glfwInit(), false);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifndef NDEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif
        // glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        m_handle = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);

        if (m_handle == nullptr)
        {
            LOG_ERROR("glfwCreateWindow() failed");
            glfwTerminate();
            return false;
        }
        glfwMakeContextCurrent(m_handle);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            LOG_ERROR("gladLoadGLLoader() failed");
            glfwDestroyWindow(m_handle);
            glfwTerminate();
            return false;
        }

		m_Data.Title = title;
		m_Data.Height = height;
		m_Data.Width = width;
		SetGLFWCallbacks();
        LOG_INFO("Window InitGlfw succeeded");
        return true;
    }

	void  Window::SetGLFWCallbacks()
	{
		glfwSetWindowUserPointer(m_handle, &m_Data);
		glfwSwapInterval(1);
		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_handle, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(m_handle, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.EventCallback(event);
			});

		glfwSetKeyCallback(m_handle, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetCharCallback(m_handle, [](GLFWwindow* window, uint32_t keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(keycode);
				data.EventCallback(event);
			});

		glfwSetMouseButtonCallback(m_handle, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetScrollCallback(m_handle, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_handle, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});
	}

    void Window::PrewDraw()
    {
        auto size = GetSize();
        while (size.first == 0 || size.second == 0)
        {
            size = GetFramebufferSize();
        }
        SetSize(size.first, size.second);
        // 默认帧率
        WaitEventsTimeout(0.1f);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, m_width, m_height);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    void Window::PostDraw()
    {
		glfwPollEvents();
        glfwSwapBuffers(m_handle);

        
    }

    void Window::DestroyWindow()
    {
        glfwDestroyWindow(m_handle);
        glfwTerminate();
        m_handle = nullptr;
        LOG_INFO("Window Destroy");
    }

    void Window::SetDropCallback(void (*fp)(GLFWwindow *window, int count, const char **paths))
    {
        glfwSetDropCallback(m_handle, fp);
    }

    GLFWwindow *Window::GetHandle() const
    {
        return m_handle;
    }
    uint32_t Window::GetWidth() const
    {
        return m_width;
    }
    uint32_t Window::GetHeight() const
    {
        return m_height;
    }

    std::pair<uint32_t, uint32_t> Window::GetSize() const
    {
        return std::make_pair(m_width, m_height);
    }

    std::pair<int, int> Window::GetFramebufferSize() const
    {
        int width, height;
        glfwGetFramebufferSize(m_handle, &width, &height);
        return std::make_pair(width, height);
    }

    void Window::SetSize(uint32_t width, uint32_t height)
    {
        m_width = width;
        m_height = height;
    }

    bool Window::ShouldClose()
    {
        return glfwWindowShouldClose(m_handle);
    }

    void Window::Close()
    {
        glfwSetWindowShouldClose(m_handle, GLFW_TRUE);
    }

    void Window::ProcessEvents()
    {
        glfwPollEvents();
    }

    void Window::WaitEventsTimeout(float timeout)
    {
        glfwWaitEventsTimeout(timeout);
    }
	void Window::SetEventCallback(const EventCallbackFn& callback)
	{
		m_Data.EventCallback = callback;
	}
}