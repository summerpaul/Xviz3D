/**
 * @Author: Xia Yunkai
 * @Date:   2024-06-26 16:33:34
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-28 14:41:01
 */
#include <stdint.h>

#ifndef __WINDOW_INPUT_H__
#define __WINDOW_INPUT_H__
#include "input.h"
#include "basis/key_codes.h"
namespace window
{
    class WindowInput : public basis::Input
    {
    protected:
        virtual bool IsKeyPressedImpl(int keycode) override;

        virtual bool IsMouseButtonPressedImpl(int button) override;
        virtual std::pair<float, float> GetMousePositionImpl() override;
        virtual float GetMouseXImpl() override;
        virtual float GetMouseYImpl() override;
    };
} // namespace window

#endif /* __WINDOW_INPUT_H__ */
