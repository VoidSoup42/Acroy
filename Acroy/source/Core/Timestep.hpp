#pragma once

namespace Acroy
{
    class Timestep
    {
    private:
        float m_time;

    public:
        Timestep(float time) : m_time(time) {}

        operator float() const { return m_time; }

        float GetSeconds() const { return m_time; }
        float GetMilliseconds() const { return m_time * 1000; }
    };
}
