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
#include "Enemy.h"
#include "Item.h"
#include "FindPath.h"
#include "TextureManager.h"
#include "ItemManager.h"
#include "TileManager.h"
#include "World.h"
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

static std::mutex s_nodes;
// pushesh back row of nodes, only reason it's seperate function is to use prralelism
inline void AddNodeRow(std::vector<std::vector<sNode *>> &vNodeMap, int size = 512)
{

    std::vector<sNode *> v1;
    for (int i = 0; i < size; ++i)
    {
        v1.push_back(new sNode());
    }
    std::lock_guard<std::mutex> lock(s_nodes);
    std::cout << " Allocating node x: " << vNodeMap.size() << std::endl;
    vNodeMap.push_back(v1);
    std::cout << " Allocation of node x: " << vNodeMap.size() << "finished" << std::endl;
}

constexpr int TileSize = 16;
constexpr float PI = 3.14159;
float Distance(float x1, float y1, float x2, float y2)
{
    return sqrtf((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
class GameJam : public olc::PixelGameEngine
{

public:
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
    float fCameraX;
    float fCameraY;
    float fPlayerX = 64.5f;
    float fPlayerY = 64.5f;
    float fPlayerA = 0.0f;
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
    olc::Sprite *sEnemy = nullptr;
    olc::Sprite *sMT = nullptr;

    // ARRAYS/vectors
    std::vector<std::vector<std::vector<Tile *>>> vTileMap;

    // body is at the end of this file, this fun. goes through vector and chechs if one of the tile is colisive if yes returnes true other wise false
    bool isColisivTileInIt(std::vector<Tile *> vTiless);
    
    // managers
    sTextureManager TextureManager;
    sItemManager ItemManager;
    sTileManager TileManager;
    


    // when replacing vTiles array size replace in Enemy.h too.
    std::vector<Tile *> vTiles; // 0= Grass, 1 = Wood etc.
    std::vector<Tile *> vBuildableTiles;


    // std::vector<int> aResourses= {0,0,0};
    std::vector<Bullet *> vBullets;
    std::vector<Enemy *> vEnemies;
    // Node map for A* path finding
    // std::vector<std::vector<sNode*>> vNodeMap;
    // std::vector<olc::vf2d> Path;

    int FinishdEarly = 0;
    int ElapsedFrames = 0;

    float AStarCounterMax = 0.5f;
    float AStarCounter = AStarCounterMax;

public:
    GameJam()
    {
        // Name your application
        sAppName = "GameJamEntry";
    }

    void SpawnEnemy();

    inline void NewGame()
    {
        // Add "generating terrain" screen

        // seting player(and time) values to default
        fPlayerX = 64.5f;
        fPlayerY = 64.5f;
        fPlayerA = 0.0f;
        fDestruction = 1.0f;
        fConstruction = 0.0f;
        fMouseMapX = 0.0f;
        fMouseMapY = 0.0f;
        fReachDistance = 2;
        Health = 1;
        fSeconds = 0;

        GenerateMap(vTileMap, vTiles);
        ScreenMode = WhitchScreen::GAMEPLAY;
    }



public:
    bool OnUserCreate() override;

    bool OnUserUpdate(float fElapsedTime) override;

    bool OnUserDestroy() override
    {
        std::cout << "Frames: " << ElapsedFrames << " A start finished early: " << FinishdEarly << std::endl;
        return true;
    }
};
