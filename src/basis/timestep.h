/**
 * @Author: Xia Yunkai
 * @Date:   2024-06-26 15:42:57
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-26 15:43:15
 */
#include <stdint.h>

#ifndef __TIMESTEP_H__
#define __TIMESTEP_H__

namespace basis
{
    class Timestep
    {
    public:
        Timestep(float time = 0.0f)
            : m_Time(time)
        {
        }

        operator float() const { return m_Time; }

        float GetSeconds() const { return m_Time; }
        float GetMilliseconds() const { return m_Time * 1000.0f; }

    private:
        float m_Time;
    };
} // namespace basis

#endif /* __TIMESTEP_H__ */
