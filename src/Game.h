#pragma once

#include <mutex>
#include <vector>
#include <ctime>
#include <climits>
#include "Tile.h"
#include "Entity.h"
#include "Item.h"
#include "World.h"
#include "ManagersManager.h"


//TODO:
// Enemies
//      Path finding 
//      Damage
// shooting
// health
// Hud:
// HP
// ammo ?
// items
// cleaning up code
// crafting

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
    

    double fTileScale = 1.0f;
    /// BOOLS
    bool isDebugMode = false;
        

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

    void MainMenu()
    {
        
        switch (InputManager.GetGUIInput())
        {
        case GUIInput::NewGame:
            InputManager.SetGUIInput(GUIInput::start);
            InputManager.SetGUIInputArgument(0);
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
         int MapSize = int(pow(2,20));
        //std::string temp_input;
        //std::cin >> MapSize;
        //MapSize = stoi(temp_input);
        EntityManager.Player.SetX((float)MapSize/2+0.5f);
        EntityManager.Player.SetY((float)MapSize/2+0.5f);
        EntityManager.Player.SetAngle(64.5f);
        EntityManager.Player.ClearInventory();
    

        World.GenerateNewWorld(TileManager.TileNameMap,MapSize,time(NULL));
        UIManager.OpenWindow(WhichWindowIsOpen::NONE);
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
        //    EntityManager.Player.MoveBack();
        }
    }



    

};
