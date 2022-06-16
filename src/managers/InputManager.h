#include "FlagManager.h"
#include <cstdint>
enum class InputFlags
{
    start = -1,
    LeftMouseButton,
    RightMouseButton,
    end

};
enum class GUIInput{
    start=-1,
    NoInput = start,
    NewGame,
    Eat=NewGame,
    LoadGame,
    end
};
class cInputManager : public cFlagManager<InputFlags>
{
private: 
    float m_MouseWorldPosytionX;
    float m_MouseWorldPosytionY;
    float m_PreviousMouseWorldPosytionX;
    float m_PreviousMouseWorldPosytionY;
    GUIInput m_GUIInput =GUIInput::NoInput;
    int m_GUIInputArgument;
public:

    void SetGUIInput(GUIInput val)
    {
        m_GUIInput = val;
    }

    void SetGUIInput(int val)
    {
        m_GUIInput = static_cast<GUIInput>(val);
    }

    auto GetGUIInput()
    {
        return m_GUIInput;
    }
    auto GetGUIInputInt()
    {
        return static_cast<int>(m_GUIInput);
    }
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
    auto GetGUIInputArgumet()
    {
        return m_GUIInputArgument;
    }
    void SetGUIInputArgument(int val)
    {
        m_GUIInputArgument = val;
    }
};
