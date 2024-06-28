/**
 * @Author: Xia Yunkai
 * @Date:   2024-06-26 17:19:02
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-28 14:36:24
 */
#include <stdint.h>

#ifndef __LAYER_STACK_H__
#define __LAYER_STACK_H__
#include <vector>
#include "layer.h"
namespace layer
{
    class LayerStack
    {
    public:
        LayerStack();
        ~LayerStack();

        void PushLayer(Layer *layer);
        void PushOverlay(Layer *overlay);
        void PopLayer(Layer *layer);
        void PopOverlay(Layer *overlay);

        std::vector<Layer *>::iterator begin() { return m_Layers.begin(); }
        std::vector<Layer *>::iterator end() { return m_Layers.end(); }

    private:
        std::vector<Layer *> m_Layers;
        uint32_t m_LayerInsertIndex = 0;
    };
} // namespace layer

#endif /* __LAYER_STACK_H__ */
