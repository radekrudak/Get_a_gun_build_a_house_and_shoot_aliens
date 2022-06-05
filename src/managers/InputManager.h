#include "FlagManager.h"
enum class InputFlags
{
    start = -1,
    LeftMouseButton,
    RightMouseButton,
    end

};

class cInputManager : public cFlagManager<InputFlags>
{
private:
    float m_MouseWorldPosytionX;
    float m_MouseWorldPosytionY;
    float m_PreviousMouseWorldPosytionX;
    float m_PreviousMouseWorldPosytionY;

public:

    using cFlagManager::cFlagManager;
    auto GetMouseWorldPosytionX()
    {
        return m_MouseWorldPosytionX;
    }
    auto GetMouseWorldPosytionY()
    {
        return m_MouseWorldPosytionY;
    }
    auto GetPreviousMouseWorldPosytionX()
    {
        return m_PreviousMouseWorldPosytionX;
    }
    auto GetPreviousMouseWorldPosytionY()
    {
        return m_PreviousMouseWorldPosytionY;
    }
    void SetMouseWorldPosytion(float X, float Y)
    {
        m_PreviousMouseWorldPosytionX =  m_MouseWorldPosytionX;
        m_PreviousMouseWorldPosytionY =  m_MouseWorldPosytionY;

        m_MouseWorldPosytionX = X;
        m_MouseWorldPosytionY = Y;
    }
};