#pragma once
#include <vector>
#include "FlagManager.h"
enum class UIFlags{

    start = -1,
    isStatsDis,
    isPlayerInventoryDisplayed,
    end

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
    WhichScreen m_ScreenMode = WhichScreen::MAIN_MENU;
public:
    using cFlagManager::cFlagManager;
    cUIManager()
    {
        int size = static_cast<int>(UIFlags::end);
       // vFlags.resize(size,false);
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