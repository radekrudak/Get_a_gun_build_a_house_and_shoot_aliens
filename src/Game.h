#pragma once

#include <atomic>
#include <cctype>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
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
    

    double fTileScale = 1.0f;
    /// BOOLS
    bool isDebugMode = false;
        
    std::thread ComandLineThread;

    // managers
    sTextureManager TextureManager;
    sItemManager ItemManager;
    sTileManager TileManager;
    sEntityManager EntityManager;
    cManagersManager ManagersManager;
    cInputManager InputManager;
    cUIManager UIManager;

    cWorldManager WorldManager;

    struct sComandLineDebugUtil
    {
        Game *m_GameInstance;
        std::atomic<bool> ContinueReadingInput = {true};
        std::thread m_ComandLineDebugThread;
        // ~sComandLineDebugUtil()
        // {
        //     std::cout<<"Closing ComandLineDebugUtil thread"<<std::endl;
        //     std::cout<<"Thread Joined"<<std::endl;
        // }
        void StartThread(Game *GameInstance)
        {
            m_GameInstance = GameInstance;
            ContinueReadingInput = true;
            m_ComandLineDebugThread = std::thread(&sComandLineDebugUtil::ReadInput,this);

        }
        void JoinThread()
        {
            ContinueReadingInput = false;
            m_ComandLineDebugThread.join();
        }

        void ReadInput()
        {
            while(ContinueReadingInput)
            {
                std::string line;
                std::getline(std::cin,line);
                InterpretLine(line);
            }
        }
        void InterpretLine(std::string line)
        {
            while(line.front() == ' ')
            {
                line.erase(0,1);
            }
            
            transform(line.begin(), line.end(), line.begin(), ::tolower);
            std::vector<std::string> args;
            
            
        
            while(/* args.back() != */ line.find(' ') != std::string::npos )
            {
                args.push_back(line.substr(0,line.find(' ')));
                line.erase(0,line.find(' ')+1);

            } 

            args.push_back(line.substr(0,line.find(' ')));
            line.erase(0,line.find(' ')+1);

            
            auto comand = args.front();
            args.erase(args.begin());

            std::cout<<comand<<std::endl;

            for(auto &i: args)
            {
                std::cout<<i<<std::endl;
            }

            if(comand == "tp")
            {
                if(args[0] == "p")
                {
                    m_GameInstance->EntityManager.Player.SetX(stof(args[1]));
                    
                    m_GameInstance->EntityManager.Player.SetY(stof(args[2]));
                }
                else if (std::isdigit(args[0][0]))
                {
                    auto &EntityPtr = m_GameInstance->EntityManager[stoi(args[0])];
                    if (EntityPtr != nullptr)
                    {
                        EntityPtr->SetX(stof( args[1]));
                        EntityPtr->SetY(stof(args[2]));
                    }
                }
            }
            else if (comand == "spawn")
            {
                m_GameInstance->EntityManager.SpawnEntity( stoi(args[0]) , stof(args[1]) , stof(args[2]));
            }
            else
            {
                std::cout<<"Unknown Comand"<<std::endl;
            }
        
        }
    } ComandLineDebugUtil;

    friend sComandLineDebugUtil;
    int ElapsedFrames = 0;


public:
    void GameStart(); 
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
    

        WorldManager.GenerateNewWorld(TileManager.TileNameMap,MapSize,time(NULL));
        UIManager.OpenWindow(WhichWindowIsOpen::NONE);
        UIManager.SetUIMode(WhichScreen::GAMEPLAY);
    }

    void MovePlayerWithColysionCheck(float fElapsedTime = 1.0f,float VecX =0.0f,float VecY = 0.0f)
    {   
        EntityManager.Player.Move(
            EntityManager.Player.GetSpeed()*fElapsedTime*VecX,
            EntityManager.Player.GetSpeed()*fElapsedTime*VecY
            ); 
        if (ManagersManager.isTileStackColisive(EntityManager.Player.GetX()    ,EntityManager.Player.GetY()   ))
        {
           EntityManager.Player.MoveBack();
        }
    }


    

};


    // void ComandLineTest(int a);

// void ComandLineTest(int a)
// {
//     while (true) 
//     {
//     
//     
//     std::string a;
//     std::getline(std::cin,a);
//     std::cout<<a<<std::endl;
//
//     }
// }
