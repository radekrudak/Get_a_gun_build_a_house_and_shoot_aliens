
#pragma once
#include "../Game.h"
#include "olcPixelGameEngine/olcPixelGameEngine.h"
class olcPixelGameEngineBackend : public olc::PixelGameEngine,public GameJam
{

    //////////////////////////// Sprites

    olc::Sprite *sNight = nullptr;
    olc::Sprite *sMoonAndSun = nullptr;
    olc::Decal *dNight = nullptr;
    olc::Decal *dMoonAndSun = nullptr;
    olc::Sprite *sMT = nullptr;

    public:
    olcPixelGameEngineBackend()
    {
        sAppName = "GameJamEntry";
    }
    bool OnUserCreate() override;
    void GetUserInput(float fElapsedTime);
    bool OnUserUpdate(float fElapsedTime) override;

    inline auto WorldPosToScreenPos(int x, int y)
    {
        return olc::vf2d(
            (static_cast<float>(x) - EntityManager.Player.GetCameraX()) * TileSize,
            (static_cast<float>(y) - EntityManager.Player.GetCameraY()) * TileSize);
    }
    inline  auto WorldPosToScreenPos(float x, float y)
    {
        return olc::vf2d(
            (x - EntityManager.Player.GetCameraX()) * TileSize,
            (y - EntityManager.Player.GetCameraY()) * TileSize);
    }
    
    inline  auto ScreenPosToWorldPos(float x, float y)
    {
        return olc::vf2d(
            (x/ static_cast<float>(TileSize))+EntityManager.Player.GetCameraX(),
            (y/static_cast<float>(TileSize))+EntityManager.Player.GetCameraY()
        );
    }

    bool OnUserDestroy() override
    {
        std::cout << "Frames: " << ElapsedFrames << " A start finished early: " << std::endl;
        return true;
    }
};