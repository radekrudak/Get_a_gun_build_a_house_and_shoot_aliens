#pragma once

#include "olcPixelGameEngine.h"
#include <mutex>
#include <vector>

#include "whitch_screen_enum.h"
//#include <functional> // std::ref
#include "RRButton.h"
#include "MainMenu.h"
#include "MapGen.h"
#include "Tile.h"
#include "Bullet.h"
#include "Entity.h"
#include "Item.h"
#include "World.h"
#include "ManagersManager.h"
// later in code included Controls.h & GameStart.h

// to do:
// Enemies
// shooting
// health
// Hud:
// HP
// Resourses
// ammo ?
// items
// cleaning up code
// crafting
// inventory
// and freaking more
// tile selected to build

using TZpos = PositionOnTileStack;

constexpr int TileSize = 16;
constexpr float PI = 3.14159;

class GameJam : public olc::PixelGameEngine
{

public:
    float Distance(float x1, float y1, float x2, float y2)
    {
        return sqrtf((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    }

    WhitchScreen ScreenMode = WhitchScreen::MAIN_MENU;

    int NodeMapSize = 128;

    double fTileScale = 1.0f;
    float fTest;
    friend Enemy;
    /// BOOLS
    bool isEnd = false;
    bool isStatsDis = false;
    bool isFightMode = false;
    bool isNight = false;
    bool isNightStartSequence = false;
    bool isDebugMode = false;
    /// player's Stuff
    float fDestruction = 1.0f;
    float fConstruction = 0.0f;
    float fMouseMapX = 0.0f;
    float fMouseMapY = 0.0f;
    float fReachDistance = 2;
    double Health = 1;
    int ChosenBuildTile = 2;
    std::string MouseText;
    Inventory PlayerInventory;

    // Game Clocks stuff;
    double fSeconds = 0;
    int PreviousSecond = 0;
    double fSecondsInDay = 20.;

    ///////////////////////////////////////////// /VIASUAL EVECTS
    float fModeTextFading = 1.0f; // used in left top  mode displaying text fading effect
    int ModeTextLap = 50;         // used in left top  mode displaying text fading effect
                                  /////////////////////

    ////////////////////// layers
    int lGround;
    int lPlayer;
    int lNight;
    //////////////////////////// Sprites
    olc::Sprite *sNight = nullptr;
    olc::Sprite *sMoonAndSun = nullptr;
    olc::Decal *dNight = nullptr;
    olc::Decal *dMoonAndSun = nullptr;
    olc::Sprite *sMT = nullptr;

    // ARRAYS/vectors
    // std::vector<std::vector<std::vector<Tile *>>> vTileMap;

    // body is at the end of this file, this fun. goes through vector and chechs if one of the tile is colisive if yes returnes true other wise false
    // bool isColisivTileInIt(std::vector<Tile *> vTiless);

    // managers
    sTextureManager TextureManager;
    sItemManager ItemManager;
    sTileManager TileManager;
    sEntityManager EntityManager;
    cManagersManager ManagersManager;
    cWorld World;

    // std::vector<int> aResourses= {0,0,0};
    std::vector<Bullet *> vBullets;
    std::vector<Enemy *> vEnemies;

    int ElapsedFrames = 0;

    float AStarCounterMax = 0.5f;
    float AStarCounter = AStarCounterMax;

public:
    GameJam()
    {
        // Name your application
        sAppName = "GameJamEntry";
    }
    
    auto WorldPosToScreenPos(int x, int y)
    {
        return olc::vf2d(
            (static_cast<float>(x) - EntityManager.Player.GetCameraX()) * TileSize,
            (static_cast<float>(y) - EntityManager.Player.GetCameraY()) * TileSize);
    }
    auto WorldPosToScreenPos(float x, float y)
    {
        return olc::vf2d(
            (x - EntityManager.Player.GetCameraX()) * TileSize,
            (y - EntityManager.Player.GetCameraY()) * TileSize);
    }
    
    auto ScreenPosToWorldPos(float x, float y)
    {
        return olc::vf2d(
            (x/ static_cast<float>(TileSize))+EntityManager.Player.GetCameraX(),
            (y/static_cast<float>(TileSize))+EntityManager.Player.GetCameraY()
        );
    }


    inline void NewGame()
    {
        // Add "generating terrain" screen

        // seting player(and time) values to default
        EntityManager.Player.SetX(64.5f);
        EntityManager.Player.SetY(64.5f);
        EntityManager.Player.SetAngle(64.5f);
        fDestruction = 1.0f;
        fConstruction = 0.0f;
        fMouseMapX = 0.0f;
        fMouseMapY = 0.0f;
        fReachDistance = 2;
        Health = 1;
        fSeconds = 0;

        World.GenerateTerrain(TileManager.TileNameMap);
        ScreenMode = WhitchScreen::GAMEPLAY;
    }

public:
    bool OnUserCreate() override;

    bool OnUserUpdate(float fElapsedTime) override;

    bool OnUserDestroy() override
    {
        std::cout << "Frames: " << ElapsedFrames << " A start finished early: " << std::endl;
        return true;
    }
};
