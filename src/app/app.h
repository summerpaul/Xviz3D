/**
 * @Author: Xia Yunkai
 * @Date:   2024-04-26 23:25:46
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-28 14:37:23
 */

#ifndef __APP_H__
#define __APP_H__
#include <memory>
#include <string>

#include "event/event.h"
using namespace event;

namespace window
{
    class Window;
}

namespace layer
{
    class Layer;
    class ImGuiLayer;
    class LayerStack;
} // namespace name

using namespace layer;
using namespace event;
namespace app
{

    class App
    {
    public:
        App(const App &) = delete;
        App &operator=(const App &) = delete;
        static App *GetInstance();
        bool Init(const std::string &title = "App", uint32_t width = 1400, uint32_t height = 800);
        void Run();
        void Shutdown();
        void *GetNativeWindow() const;

        void PushLayer(Layer *layer);
        void PushOverlay(Layer *layer);

    private:
        App() = default;
        ~App();
        void OnEvent(Event &e);

    private:
        std::unique_ptr<window::Window> m_pWindow;
        std::unique_ptr<LayerStack> m_pLayerStack;
        ImGuiLayer *m_pImGuiLayer;
        bool m_isShutDown = false;
        float m_LastFrameTime = 0.0f;
    };

} // namespace app

#endif /* __APP_H__ */
