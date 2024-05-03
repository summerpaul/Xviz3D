/**
 * @Author: Xia Yunkai
 * @Date:   2024-04-26 23:25:53
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-03 00:31:14
 */

#include "app.h"
#include "basis/logger.h"
#include "basis/defines.h"
#include "window/window.h"
#include "ui/main_layer.h"
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
        m_window = std::make_unique<window::Window>();
        CHECK_RETURN_RET(!m_window->Init(width, height, title), false);
        m_mainUI = std::make_unique<ui::MainLayer>("MainLayer");
        CHECK_RETURN_RET(!m_mainUI->Init(), false);
        CHECK_RETURN_RET(!m_mainUI->InitHandle(m_window->GetHandle()), false);
        LOG_INFO("APP init succeeded");
        return true;
    }

    void App::Run()
    {
        // 设置窗口回调函数
        m_window->SetDropCallback(ui::MainLayer::DropCallback);
        while (!m_window->ShouldClose())
        {
            m_window->PrewDraw();
            m_mainUI->BeginDraw();
            m_mainUI->Draw();
            m_mainUI->EndDraw();
            m_window->PostDraw();
        }
    }

    void App::SetDropFiles(int count, const char **paths)
    {
        m_mainUI->FilesDropCallback(count, paths);
    }

    void App::Shutdown()
    {
        m_mainUI->Shutdown();
        m_window->DestroyWindow();
        LOG_INFO("Shutting down");
        m_isShutDown = true;
    }

}
