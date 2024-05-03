/**
 * @Author: Xia Yunkai
 * @Date:   2024-04-27 10:29:36
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-03 01:07:23
 */
#include <iostream>
#include "basis/logger.h"
#include "main_layer.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <app/app.h>
#include "basis/defines.h"
#include <ImGuizmo.h>

namespace ui
{

    MainLayer::MainLayer(const std::string &name) : BaseLayer(name)
    {
    }
    bool MainLayer::Init()
    {

        LOG_INFO("Main Layer Init");
        return true;
    }

    bool MainLayer::InitHandle(GLFWwindow *window)
    {
        CHECK_RETURN_RET(window == nullptr, false);
        const char *glsl_version = "#version 330";
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        CHECK_RETURN_RET(!ImGui_ImplGlfw_InitForOpenGL(window, true), false);
        CHECK_RETURN_RET(!ImGui_ImplOpenGL3_Init(glsl_version), false);
        LOG_INFO("Init Handle");
        return true;
    }

    void MainLayer::FilesDropCallback(int count, const char **paths)
    {
        for (auto &layer : m_layers)
        {
            layer->FilesDropCallback(count, paths);
        }
    }

    void MainLayer::DropCallback(GLFWwindow *window, int count, const char **paths)
    {
        app::App::GetInstance()->SetDropFiles(count, paths);
    }

    void MainLayer::BeginDraw()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        // dockspace and menu bar
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        const ImGuiViewport *viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", NULL, window_flags);
        ImGui::PopStyleVar(3);
        ImGuiIO &io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }
        ImGui::End();
    }

    void MainLayer::EndDraw()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        ImGuiIO &io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow *backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }

    void MainLayer::Draw()
    {
        ImGui::Begin("ImGuizmo Demo");

        // 设置相机视图矩阵和投影矩阵
        float windowWidth = ImGui::GetWindowWidth();
        float windowHeight = ImGui::GetWindowHeight();
        ImGuizmo::SetOrthographic(false);
        ImGuizmo::SetRect(0, 0, windowWidth, windowHeight);

        // 创建一个模拟的物体变换矩阵
        static float matrix[16] = {1.0f};

        // 绘制gizmo
        // ImGuizmo::DrawCube(matrix);
        // ImGuizmo::DrawCubes()
        // 或者使用ImGuizmo::DrawGrid(...)来绘制一个网格

        ImGui::End();
    }
    void MainLayer::Shutdown() {}
}
