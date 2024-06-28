/**
 * @Author: Xia Yunkai
 * @Date:   2024-06-26 16:34:39
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-26 16:49:20
 */
#include <iostream>

#include "window_input.h"
#include "app/app.h"
#include <GLFW/glfw3.h>

Input *Input::s_Instance = new window::WindowInput();
namespace window
{

    bool WindowInput::IsKeyPressedImpl(int keycode)
    {
        auto window = static_cast<GLFWwindow *>(app::App::GetInstance()->GetNativeWindow());
        auto state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool WindowInput::IsMouseButtonPressedImpl(int button)
    {
        auto window = static_cast<GLFWwindow *>(app::App::GetInstance()->GetNativeWindow());
        auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    std::pair<float, float> WindowInput::GetMousePositionImpl()
    {
        auto window = static_cast<GLFWwindow *>(app::App::GetInstance()->GetNativeWindow());
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        return {(float)xpos, (float)ypos};
    }

    float WindowInput::GetMouseXImpl()
    {
        auto [x, y] = GetMousePositionImpl();
        return x;
    }

    float WindowInput::GetMouseYImpl()
    {
        auto [x, y] = GetMousePositionImpl();

        return y;
    }
}