/**
 * @Author: Xia Yunkai
 * @Date:   2024-06-26 16:54:36
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-28 14:40:25
 */
#include <iostream>

#include "perspective_camera_controller.h"
#include <functional>
#include "basis/key_codes.h"
namespace camera
{
    PerspectiveCameraController::PerspectiveCameraController()
    {
    }

    void PerspectiveCameraController::OnUpdate(Timestep ts)
    {
        float wanderSphereRadius = 10.0f;
        glm::vec3 camPos;

        camPos.x = wanderSphereRadius * cos(m_CameraLatitudeAngleRad) * cos(m_CameraLongtitudeAngleRad);
        camPos.y = wanderSphereRadius * cos(m_CameraLatitudeAngleRad) * sin(m_CameraLongtitudeAngleRad);
        camPos.z = wanderSphereRadius * sin(m_CameraLatitudeAngleRad);

        glm::vec3 camTar = glm::vec3(0);

        m_PerespectiveCamera.Update(camPos, camTar, m_FovyDeg, m_RatioXtoY);
    }

    void PerspectiveCameraController::OnEvent(Event &e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<MouseButtonPressedEvent>(GLCORE_BIND_EVENT_FN(PerspectiveCameraController::OnMousePressed));
        dispatcher.Dispatch<MouseButtonReleasedEvent>(GLCORE_BIND_EVENT_FN(PerspectiveCameraController::OnMouseReleased));
        dispatcher.Dispatch<MouseMovedEvent>(GLCORE_BIND_EVENT_FN(PerspectiveCameraController::OnMouseMoved));
        dispatcher.Dispatch<MouseScrolledEvent>(GLCORE_BIND_EVENT_FN(PerspectiveCameraController::OnMouseScrolled));
        dispatcher.Dispatch<KeyPressedEvent>(GLCORE_BIND_EVENT_FN(PerspectiveCameraController::OnKeyBoardPressed));
    }

    void PerspectiveCameraController::SetRatio(float ratio)
    {
        m_RatioXtoY = ratio;
    }

    bool PerspectiveCameraController::OnMouseScrolled(MouseScrolledEvent &e)
    {
        // Change camera's FOV
        m_FovyDeg -= e.GetYOffset() * NUMBERS_ONEDEG * 1.5f;

        // FOV has limits
        m_FovyDeg = XVIZ_CLAMP(m_FovyDeg, float(0.001f), float(NUMBERS_PI / 2.f));

        return true;
    }

    bool PerspectiveCameraController::OnMousePressed(MouseButtonPressedEvent &e)
    {
        if (e.GetMouseButton() == 0)
        {
            m_LeftButtonPressed = true;
        }
        return false;
    }

    bool PerspectiveCameraController::OnMouseReleased(MouseButtonReleasedEvent &e)
    {
        if (e.GetMouseButton() == 0)
        {
            m_LeftButtonPressed = false;
            m_LeftButtonClicking = false;
        }
        return false;
    }

    bool PerspectiveCameraController::OnMouseMoved(MouseMovedEvent &e)
    {
        if (m_LeftButtonPressed)
        {

            // 计算拖拽矢量
            glm::vec2 vecDragged;
            glm::vec2 currMousePos = {e.GetX(), e.GetY()};

            // 点击的时刻不计算
            if (!m_LeftButtonClicking)
            {
                m_LeftButtonClicking = true;
                m_LastClickedPos = currMousePos;
                return false;
            }

            vecDragged = currMousePos - m_LastClickedPos;

            m_CameraLongtitudeAngleRad -= vecDragged.x * NUMBERS_ONEDEG * 0.28f;

            m_CameraLatitudeAngleRad += vecDragged.y * NUMBERS_ONEDEG * 0.28f;
            m_CameraLatitudeAngleRad = XVIZ_CLAMP(m_CameraLatitudeAngleRad, -89 * NUMBERS_ONEDEG, 89 * NUMBERS_ONEDEG);

            m_LastClickedPos = currMousePos;
        }

        return false;
    }

    bool PerspectiveCameraController::OnKeyBoardPressed(KeyEvent &e)
    {

        // 回归默认位置
        bool needBack = (e.GetKeyCode() == 341);
        if (needBack)
        {
            m_CameraLongtitudeAngleRad = 0;
            m_CameraLatitudeAngleRad = NUMBERS_PI / 4.0f;
            m_FovyDeg = 30 * NUMBERS_ONEDEG;
        }

        return true;
    }
}