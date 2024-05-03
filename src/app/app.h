/**
 * @Author: Xia Yunkai
 * @Date:   2024-04-26 23:25:46
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-03 00:31:10
 */

#ifndef __APP_H__
#define __APP_H__
#include <memory>
#include <string>

namespace window
{
    class Window;
}

namespace ui
{
    class MainLayer;
    class BaseLayer;
}

namespace scene
{
    class SceneManager;
}

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

        void SetDropFiles(int count, const char **paths);

    private:
        App() = default;
        ~App();

    private:
        std::unique_ptr<ui::MainLayer> m_mainUI;
        std::unique_ptr<window::Window> m_window;
        std::shared_ptr<scene::SceneManager> m_sceneManager;
        bool m_isShutDown = false;
    };

} // namespace app

#endif /* __APP_H__ */
