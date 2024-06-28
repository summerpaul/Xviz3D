/**
 * @Author: Xia Yunkai
 * @Date:   2024-06-26 17:08:47
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-28 14:37:04
 */
#include <stdint.h>

#ifndef __BASE_LAYER_H__
#define __BASE_LAYER_H__
#include "basis/timestep.h"
#include "event/event.h"
#include <string>

using namespace basis;
using namespace event;
namespace layer
{
    class Layer
    {
    public:
        Layer(const std::string &name = "Layer") : m_name(name) {}
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(Timestep ts) {}
        virtual void OnImGuiRender() {}
        virtual void OnEvent(Event &event) {}

        inline const std::string &GetName() const { return m_name; }

    protected:
        std::string m_name;
    };

}

#endif /* __BASE_LAYER_H__ */
