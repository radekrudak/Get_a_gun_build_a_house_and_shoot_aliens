#pragma once

#include "Entity.h"
#include "Item.h"
#include "ManagersManager.h"
#include "Tile.h"
#include "World.h"
#include "managers/TimeManager.h"
#include <atomic>
#include <cctype>
#include <climits>
#include <ctime>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

// TODO:
//  Enemies
//       Path finding
//       Damage
//  shooting
//  health
//  Hud:
//  HP
//  ammo ?
//  items
//  cleaning up code
//  crafting

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
  cTimeManager TimeManager;
  sTextureManager TextureManager;
  sItemManager ItemManager;
  sTileManager TileManager;
  sEntityManager EntityManager;
  cManagersManager ManagersManager;
  cInputManager InputManager;
  cUIManager UIManager;

  cWorldManager WorldManager;

  struct sComandLineDebugUtil {
    Game *m_GameInstance;
    std::atomic<bool> ContinueReadingInput = {true};
    std::thread m_ComandLineDebugThread;
    // ~sComandLineDebugUtil()
    // {
    //     std::cout<<"Closing ComandLineDebugUtil thread"<<std::endl;
    //     std::cout<<"Thread Joined"<<std::endl;
    // }
    void StartThread(Game *GameInstance) {
      m_GameInstance = GameInstance;
      ContinueReadingInput = true;
      m_ComandLineDebugThread =
          std::thread(&sComandLineDebugUtil::ReadInput, this);
    }
    void JoinThread() {
      ContinueReadingInput = false;
      m_ComandLineDebugThread.join();
    }

    void ReadInput() {
      while (ContinueReadingInput) {
        std::string line;
        std::getline(std::cin, line);
        InterpretLine(line);
      }
    }
    void InterpretLine(std::string line) {
      while (line.front() == ' ') {
        line.erase(0, 1);
      }

      transform(line.begin(), line.end(), line.begin(), ::tolower);
      std::vector<std::string> args;

      while (/* args.back() != */ line.find(' ') != std::string::npos) {
        args.push_back(line.substr(0, line.find(' ')));
        line.erase(0, line.find(' ') + 1);
      }

      args.push_back(line.substr(0, line.find(' ')));
      line.erase(0, line.find(' ') + 1);

      auto comand = args.front();
      args.erase(args.begin());

      std::cout << comand << std::endl;

      for (auto &i : args) {
        std::cout << i << std::endl;
      }

      if (comand == "tp") {
        if (args[0] == "p") {
          m_GameInstance->EntityManager.Player.SetX(stof(args[1]));

          m_GameInstance->EntityManager.Player.SetY(stof(args[2]));
        } else if (std::isdigit(args[0][0])) {
          auto &EntityPtr = m_GameInstance->EntityManager[stoi(args[0])];
          if (EntityPtr != nullptr) {
            EntityPtr->SetX(stof(args[1]));
            EntityPtr->SetY(stof(args[2]));
          }
        }
      } else if (comand == "spawn") {
        if (args[0] == "damagegiver") {
          m_GameInstance->EntityManager.SpawnDamageGiver(
              stof(args[1]), stof(args[2]), 1,
              &(m_GameInstance->EntityManager.Player),
              m_GameInstance->TimeManager.GetPtrToWorldTime());
        } else if (args[0] == "spear_entity") {
          // m_GameInstance->EntityManager.SpawnDamageGiver("SPEAR",&m_GameInstance->EntityManager.Player,m_GameInstance->TimeManager.GetPtrToWorldTime());
        } else if (args[0] == "character") {
          m_GameInstance->EntityManager.SpawnCharacter(stof(args[1]),
                                                       stof(args[2]));
        }else if(args[0] == "Enemy")
        {
          // m_GameInstance->EntityManager.SpawnEnemy(0,stof(args[1]),stof(args[2]),
          //     &(m_GameInstance->ManagersManager.EntityUseItem));
        }

        else
          m_GameInstance->EntityManager.SpawnEntity(
              stoi(args[0]), stof(args[1]), stof(args[2]));

      } else if (comand == "hurt") {
        if (args[0] == "p") {
          m_GameInstance->EntityManager.Player.SubtractHealth(stoi(args[1]));
        } else if (std::isdigit(args[0][0])) {
          m_GameInstance->EntityManager[stoi(args[0])]->SubtractHealth(
              stoi(args[1]));
        }
      } else if (comand == "heal") {
        if (args[0] == "p") {
          m_GameInstance->EntityManager.Player.AddHealth(stoi(args[1]));
        } else if (std::isdigit(args[0][0])) {
          m_GameInstance->EntityManager[stoi(args[0])]->AddHealth(
              stoi(args[1]));
        }
      } else {
        std::cout << "Unknown Comand" << std::endl;
      }
    }
  } ComandLineDebugUtil;

  friend sComandLineDebugUtil;
  int ElapsedFrames = 0;

public:
  void GameStart();
  void GameUpdate(float fElapsedTime);

  void MainMenu() {

    switch (InputManager.GetGUIInput()) {
    case GUIInput::NewGame:
      InputManager.SetGUIInput(GUIInput::start);
      InputManager.SetGUIInputArgument(0);
      NewGame();
      break;

    default:
      break;
    }
  }
  // Starts New Game
  // TODO: EtityManager Reset
  // TODO: TileManager Reset

  inline void NewGame() {

    int MapSize = int(pow(2, 20));
    EntityManager.Player.SetX((float)MapSize / 2 + 0.5f);
    EntityManager.Player.SetY((float)MapSize / 2 + 0.5f);
    EntityManager.Player.SetAngle(64.5f);
    EntityManager.Player.ClearInventory();
    EntityManager.Player.GetInventory().EquipItem(
        ItemSlot(ItemManager.GetItemID("DEFAULT_SPEAR"), 1));
    std::cout << ItemManager["DEFAULT_SPEAR"]->GetTextureID() << std::endl;
    TimeManager.SetWorldTime(0);
    WorldManager.GenerateNewWorld(TileManager.TileNameMap, MapSize, time(NULL));
    UIManager.OpenWindow(WhichWindowIsOpen::NONE);
    UIManager.SetUIMode(WhichScreen::GAMEPLAY);
  }

  void MovePlayerWithColysionCheck(float fElapsedTime = 1.0f, float VecX = 0.0f,
                                   float VecY = 0.0f) {
    EntityManager.Player.Move(
        EntityManager.Player.GetSpeed() * fElapsedTime * VecX,
        EntityManager.Player.GetSpeed() * fElapsedTime * VecY);
    if (ManagersManager.isTileStackColisive(EntityManager.Player.GetX(),
                                            EntityManager.Player.GetY())) {
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
