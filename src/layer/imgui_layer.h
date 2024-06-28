/**
 * @Author: Xia Yunkai
 * @Date:   2024-06-26 17:11:54
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-28 10:24:38
 */
#include <stdint.h>

#ifndef __IMGUI_LAYER_H__
#define __IMGUI_LAYER_H__
#include "layer.h"
namespace layer
{
    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer() = default;

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        void Begin();
        void End();
        void DrawDock();

        virtual void OnEvent(Event &event);

        int win_width_;
        int win_height_;

    private:
        float m_Time = 0.0f;

        void ConfigFontsAndIcon();
        void ConfigStyles();
    };
} // namespace layer

#endif /* __IMGUI_LAYER_H__ */
