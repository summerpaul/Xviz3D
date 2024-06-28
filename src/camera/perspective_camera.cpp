/**
 * @Author: Xia Yunkai
 * @Date:   2024-06-26 15:19:05
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-28 14:26:41
 */
#include <iostream>
#include "perspective_camera.h"
namespace camera
{
    PerspectiveCamera::PerspectiveCamera()
    {
    }

    void PerspectiveCamera::Recalculate()
    {
    }

    void PerspectiveCamera::SetAspectRatio(float ratio)
    {
        aspect_ratio_ = ratio;
    }

    void PerspectiveCamera::SetFOVY(float fovy)
    {
        fov_y_ = fovy;
    }

    void PerspectiveCamera::SetPosition(glm::vec3 posiiton)
    {
        position_ = posiiton;
    }

    void PerspectiveCamera::SetPositionOffset(glm::vec3 position_offset)
    {
        position_ += position_offset;
    }

    void PerspectiveCamera::SetPositionOffsetSpherical(glm::vec2 position_offset)
    {
    }

    void PerspectiveCamera::SetProjection(float fvo_y, float aspect_ratio, float z_near, float z_far)
    {
        fov_y_ = fvo_y;
        aspect_ratio_ = aspect_ratio;
        z_near_ = z_near;
        z_far_ = z_far;
        mat_projection_ = glm::perspective(fov_y_, aspect_ratio_, z_near_, z_far_);
    }
    void PerspectiveCamera::SetView(glm::vec3 camera_position, glm::vec3 look_at, glm::vec3 camera_up)
    {
        position_ = camera_position;
        front_ = glm::normalize(look_at - camera_position);
        up_ = camera_up;
        right_ = glm::normalize(glm::cross(front_, up_));
        mat_view_ = glm::lookAt(camera_position, look_at, up_);
        mat_projection_ = glm::perspective(fov_y_, aspect_ratio_, z_near_, z_far_);
        mat_view_projection_ = mat_projection_ * mat_view_;
    }

    void PerspectiveCamera::SetStare(glm::vec3 stare)
    {
        stare_ = stare;
    }

    void PerspectiveCamera::Update(glm::vec3 camPos, glm::vec3 camTar, float fov_y, float aspectRatio)
    {
        position_ = camPos;
        front_ = glm::normalize(camTar - camPos);
        fov_y_ = fov_y;
        aspect_ratio_ = aspectRatio;
        world_up_ = glm::vec3(0, 0, 1);
        right_ = glm::normalize(glm::cross(front_, world_up_));
        up_ = glm::normalize(glm::cross(right_, front_));
        mat_view_ = glm::lookAt(position_, camTar, up_);
        mat_projection_ = glm::perspective(fov_y_, aspect_ratio_, z_near_, z_far_);
        mat_view_projection_ = mat_projection_ * mat_view_;
    }
}