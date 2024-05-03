/**
 * @Author: Xia Yunkai
 * @Date:   2024-04-26 23:41:09
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-03 00:22:58
 */
#include <stdint.h>

#ifndef __BASE_LAYER_H__
#define __BASE_LAYER_H__

#include <memory>
namespace ui
{

    class BaseLayer
    {
    public:
        typedef std::shared_ptr<BaseLayer> Ptr;
        BaseLayer(const std::string &name = "") : m_name(name) {}
        virtual ~BaseLayer() {}
        const std::string &GetName() const { return m_name; }
        virtual void Draw(){};
        virtual bool Init() { return false; }
        virtual void FilesDropCallback(int count, const char **paths) {}
        virtual void Shutdown(){};
        bool IsInitialized() const { return m_initialized; }

    protected:
        std::string m_name;
        bool m_initialized = false;
    };

} // namespace ui

#endif /* __BASE_LAYER_H__ */
