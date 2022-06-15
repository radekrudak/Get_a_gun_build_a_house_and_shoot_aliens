#pragma once

#include <mutex>
#include <vector>

#include "Tile.h"
#include "Entity.h"
#include "Item.h"
#include "World.h"
#include "ManagersManager.h"


//TODO:
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

class Game //: public olc::PixelGameEngine
{

public:
    float Distance(float x1, float y1, float x2, float y2)
    {
        return sqrtf((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
    }

    

    int NodeMapSize = 128;

    double fTileScale = 1.0f;
    float fTest;
    friend Enemy;
    /// BOOLS
    bool isEnd = false;
    bool isNight = false;
    bool isNightStartSequence = false;
    bool isDebugMode = false;
        
    /// player's Stuff



    //std::string MouseText;
  

    // Game Clocks stuff;
    double fSeconds = 0;
    int PreviousSecond = 0;
    double fSecondsInDay = 20.;


    ////////////////////// layers
    int lGround;
    int lPlayer;
    int lNight;


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
    cInputManager InputManager;
    cUIManager UIManager;

    cWorld World;


    int ElapsedFrames = 0;


public:
    void GameUpdate(float fElapsedTime);

    void MainMenu(GUIInput ChosenOption)
    {
        switch (ChosenOption)
        {
        case GUIInput::NewGame:
            NewGame();
            break;
        
        default:
            break;
        }
    }


    inline void NewGame()
    {
        // Add "generating terrain" screen

        // seting player(and time) values to default
         int MapSize = 1024;
        //std::string temp_input;
        //std::cin >> MapSize;
        //MapSize = stoi(temp_input);
        EntityManager.Player.SetX((float)MapSize/2+0.5f);
        EntityManager.Player.SetY((float)MapSize/2+0.5f);
        EntityManager.Player.SetAngle(64.5f);
        EntityManager.Player.ClearInventory();
        fSeconds = 0;

        World.GenerateTerrain(TileManager.TileNameMap,MapSize);
        UIManager.SetUIMode(WhichScreen::GAMEPLAY);
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



    

};
