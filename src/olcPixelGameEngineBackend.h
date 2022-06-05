
#pragma once
#include "Game.h"
#include "olcPixelGameEngine.h"
class olcPixelGameEngineBackend : public olc::PixelGameEngine,public GameJam
{
    public:
    olcPixelGameEngineBackend()
    {
       
        sAppName = "GameJamEntry";
    }
    bool OnUserCreate() override;
    void GetUserInput(float fElapsedTime);
    bool OnUserUpdate(float fElapsedTime) override;

    bool OnUserDestroy() override
    {
        std::cout << "Frames: " << ElapsedFrames << " A start finished early: " << std::endl;
        return true;
    }
};