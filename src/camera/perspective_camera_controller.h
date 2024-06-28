/**
 * @Author: Xia Yunkai
 * @Date:   2024-06-26 16:54:28
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-28 15:03:12
 */
#include <stdint.h>

#ifndef __PERSPECTIVE_CAMERA_CONTROLLER_H__
#define __PERSPECTIVE_CAMERA_CONTROLLER_H__

#include "basis/timestep.h"
#include "perspective_camera.h"
#include "event/application_event.h"
#include "event/mouse_event.h"
#include "basis/input.h"
#include "event/key_event.h"

using namespace basis;
using namespace event;
namespace camera
{
    class PerspectiveCameraController
    {
    public:
        PerspectiveCameraController();

        void OnUpdate(Timestep ts);
        void OnEvent(Event &e);

        void SetRatio(float ratio);

        PerspectiveCamera &GetCamera() { return m_PerespectiveCamera; }
        const PerspectiveCamera &GetCamera() const { return m_PerespectiveCamera; }

    private:
        bool OnMouseScrolled(MouseScrolledEvent &e); // zoom in/out
        bool OnMousePressed(MouseButtonPressedEvent &e);
        bool OnMouseReleased(MouseButtonReleasedEvent &e);
        bool OnMouseMoved(MouseMovedEvent &e); // move camera position

        bool OnKeyBoardPressed(KeyEvent &e);

    private:
        PerspectiveCamera m_PerespectiveCamera;

        float m_CameraLongtitudeAngleRad = 0;
        float m_CameraLatitudeAngleRad = NUMBERS_PI / 4.0f;
        float m_FovyDeg = 30 * NUMBERS_ONEDEG;
        float m_RatioXtoY = 1.0f;

        // Pressed Events
        bool m_LeftButtonPressed = false;
        bool m_LeftButtonClicking = false;
        glm::vec2 m_LastClickedPos;

    public:
    };
}

#endif /* __PERSPECTIVE_CAMERA_CONTROLLER_H__ */
