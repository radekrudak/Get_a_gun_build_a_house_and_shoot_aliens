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

    WhichScreen ScreenMode = WhichScreen::MAIN_MENU;

    int NodeMapSize = 128;

    double fTileScale = 1.0f;
    float fTest;
    friend Enemy;
    /// BOOLS
    bool isEnd = false;
    bool isStatsDis = false;
    bool isNight = false;
    bool isNightStartSequence = false;
    bool isDebugMode = false;
    /// player's Stuff



    std::string MouseText;
  

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


    int ElapsedFrames = 0;


public:
    GameJam()
    {
        // Name your application
        sAppName = "GameJamEntry";
    }
    
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


    inline void NewGame()
    {
        // Add "generating terrain" screen

        // seting player(and time) values to default
        EntityManager.Player.SetX(1000.5f);
        EntityManager.Player.SetY(1000.5f);
        EntityManager.Player.SetAngle(64.5f);
        EntityManager.Player.ClearInventory();
        fSeconds = 0;

        World.GenerateTerrain(TileManager.TileNameMap);
        ScreenMode = WhichScreen::GAMEPLAY;
    }

    void MovePlayerWithColysionCheck(float fElapsedTime = 1.0f,float VecX =0.0f,float VecY = 0.0f)
    {   
        EntityManager.Player.Move(
            EntityManager.Player.GetSpeed()*fElapsedTime*VecX,
            EntityManager.Player.GetSpeed()*fElapsedTime*VecY
            ); 
        if (World.isTileStackColisiveAt(EntityManager.Player.GetX()    ,EntityManager.Player.GetY()   ))
        {
            EntityManager.Player.MoveBack();
        }
    }


public:

    bool OnUserCreate() override;

    bool OnUserUpdate(float fElapsedTime) override;
    void GetUserInput(float fElapsedTime);
    bool OnUserDestroy() override
    {
        std::cout << "Frames: " << ElapsedFrames << " A start finished early: " << std::endl;
        return true;
    }
};
