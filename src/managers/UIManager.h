#pragma once
#include <vector>
#include <string>
#include "FlagManager.h"
enum class UIFlags{

    start = -1,
    isStatsDis,
    //isPlayerInventoryDisplayed,
    //isPlayerTileToBuildSelectionDisplayed,
    end

};
enum class WhichWindowIsOpen{
    NONE,
    INVENTORY,
    BUILDABLE_TILES_SELECT,
    MAIN_MENU
};


enum class WhichScreen{
    MAIN_MENU =0,
    GAMEPLAY =1
};



class cUIManager : public cFlagManager<UIFlags>
{
    // std::vector<unsigned char> vFlags;
    float ProgressBarProgress =0.0f;
    std::string m_MouseText;
    WhichWindowIsOpen m_WhichWindowIsOpen = WhichWindowIsOpen::NONE ;
    WhichScreen m_ScreenMode = WhichScreen::MAIN_MENU;
public:


    using cFlagManager<UIFlags>::cFlagManager;
    cUIManager()
    {
        int size = static_cast<int>(UIFlags::end);
       
    }

    auto GetWhichWindowIsOpen()
    {
        return m_WhichWindowIsOpen;
    }

    void OpenWindow(WhichWindowIsOpen window)
    {
        m_WhichWindowIsOpen = window;
    }
    void OpenWindow(int windowID)
    {
        m_WhichWindowIsOpen = static_cast<WhichWindowIsOpen>(windowID);
    }
    void CloseWindow()
    {
        m_WhichWindowIsOpen = WhichWindowIsOpen::NONE;
    }
    void SetUIMode(WhichScreen ScreenMode)
    {
        m_ScreenMode = ScreenMode;
    }
    auto GetUIMode()
    {
        return m_ScreenMode;
    }
    const auto &GetMouseText()
    {
        return m_MouseText;
    }
    void SetMouseText(std::string val)
    {
        m_MouseText=val;
    }
    void SetProgressBar(float val)
    {
        ProgressBarProgress = val;
    }

    const auto &GetPRogressBar()
    {
        return ProgressBarProgress;
    }

    
};
