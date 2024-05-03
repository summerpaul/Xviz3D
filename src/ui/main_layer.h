/**
 * @Author: Xia Yunkai
 * @Date:   2024-04-27 10:29:24
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-03 00:31:00
 */
#include <stdint.h>

#ifndef __MAIN_LAYER_H__
#define __MAIN_LAYER_H__

#include "base_layer.h"
#include <vector>
struct GLFWwindow;

namespace ui
{

    class MainLayer : public BaseLayer
    {
    public:
        MainLayer(const std::string &name);
        virtual bool Init() override;
        virtual void Draw() override;
        virtual void Shutdown() override;
        virtual void FilesDropCallback(int count, const char **paths) override;
        bool InitHandle(GLFWwindow *window);
        void BeginDraw();
        void EndDraw();
        static void DropCallback(GLFWwindow *window, int count, const char **paths);


    protected:
        std::vector<BaseLayer::Ptr> m_layers;
    };
}

#endif /* __MAIN_LAYER_H__ */
