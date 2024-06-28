/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-28 19:08:47
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-28 14:37:34
 */
#include "app.h"
#include "basis/logger.h"
#include "window/window.h"
#include "basis/defines.h"
#include "layer/imgui_layer.h"
#include "layer/layer_stack.h"
#include <GLFW/glfw3.h>

namespace app
{
    App::~App()
    {
        CHECK_RETURN(m_isShutDown);
        Shutdown();
        LOG_INFO("APP shutdown succeeded");
    }
    App *App::GetInstance()
    {
        static App app;
        return &app;
    }

    bool App::Init(const std::string &title, uint32_t width, uint32_t height)
    {
        m_pWindow = std::make_unique<window::Window>();

        CHECK_RETURN_RET(!m_pWindow->Init(width, height, title), false);
        m_isShutDown = false;
        m_pImGuiLayer = new ImGuiLayer();
        m_pLayerStack = std::make_unique<layer::LayerStack>();
        PushOverlay(m_pImGuiLayer);

        LOG_INFO("APP init succeeded");
        return true;
    }

    void App::Run()
    {
        while (!m_pWindow->ShouldClose())
        {
            float time = (float)glfwGetTime();
            Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;
            for (auto layer : *m_pLayerStack)
            {
                layer->OnUpdate(timestep);
            }

            m_pWindow->PrewDraw();
            m_pImGuiLayer->Begin();
            for (auto layer : *m_pLayerStack)
            {
                layer->OnImGuiRender();
            }
            m_pImGuiLayer->End();

            m_pWindow->PostDraw();
        }
    }

    void App::Shutdown()
    {
        m_pWindow->DestroyWindow();
        LOG_INFO("Shutting down");
        m_isShutDown = true;
    }
    void *App::GetNativeWindow() const
    {
        return m_pWindow->GetNativeWindow();
    }

    void App::PushLayer(Layer *layer)
    {
        m_pLayerStack->PushLayer(layer);
    }
    void App::PushOverlay(Layer *layer)
    {
        m_pLayerStack->PushOverlay(layer);
    }

    void App::OnEvent(Event &e)
    {
    }

}