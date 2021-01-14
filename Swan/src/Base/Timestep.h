#pragma once


namespace Swan
{
    class Timestep{
    public:
        Timestep(float time)
            : m_Time(time)
        {
        }
        operator float() { return m_Time; }

        float GetTime() { return m_Time; }
        float GetTimeMiliseconds() { return m_Time / 1000; }
    private:
        float m_Time;
    };
}