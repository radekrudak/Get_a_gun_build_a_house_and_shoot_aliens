#pragma once
// #include "ManagersManager.h"
// #include "Game.h"
#include "olcPixelGameEngine.h"
#include "Item.h"
#include <math.h>


enum class EntityTypes
{
    GenericEntity = 0,
    Enemy,
    Player
};

class Entity
{
protected:
    int TextureID = 0;
    float x = 0;
    float y = 0;
    float VelocityX =0;
    float VelocityY =0;
    float PreviousX = 0;
    float PreviousY = 0;
    float Angle = 0;

public:
    EntityTypes EntityType = EntityTypes::GenericEntity;
    // virtual void Update(const cManagersManager &ManagersManager)
    // {
    //     ;
    // }
    virtual void Move(float fElapsedTime)
    {
        Move(VelocityX*fElapsedTime,VelocityY*fElapsedTime);
    }
    virtual void Move(float VecX, float VecY)
    {
        PreviousX = x;
        PreviousY = y;
        x += VecX;
        y += VecY;
    }
    virtual void MoveBack()
    {
        x = PreviousX;
        y = PreviousY;
    }

    Entity(int TextureID = 0, float xx = 0, float yy = 0)
    {
        x = xx;
        y = yy;
    }
    auto GetX() const
    {
        return x;
    }
    auto GetY() const
    {
        return y;
    }
    auto GetAngle()
    {
        return Angle;
    }

    void SetX(float X)
    {
        x = X;
    }
    void SetY(float Y)
    {
        y = Y;
    }

    void SetAngle(float a)
    {
        Angle = a;
    }
    olc::vf2d GetPosition()
    {
        return olc::vf2d(x, y);
    }
    virtual float GetfDeconstruction()
    {
        return 0;
    }
    virtual int GetHealth()
    {
        return 0;
    }
    virtual int GetMaxHealth ()
    {
        return 0;
    }
    virtual float GetSpeed()
    {
        return 0.0f;
    }
    virtual void SetHealth(int health)
    {
        ;
    }
    virtual void GetSpeed(float s = 0.0f)
    {
        ;
    }
    virtual olc::vf2d GetVelocity()
    {
        return {0, 0};
    }

    virtual void SetVelocity(olc::vf2d InVec)
    {
        ;
    }
    virtual void AddVelocity(olc::vf2d AddVec)
    {
        ;
    }
};
class Character : public Entity
{

    float m_Speed = 0;
    int m_MaxHealth =10;
    int m_Health = m_MaxHealth;
    float m_ConstructionProgress = 0.0f;
    float m_DeconstructionProgress = 0.0f;
    float m_ReachDistance =4.0f;


    float m_LevelofConstructionProgression = 1.0f; // how much second construction will take
    float m_LevelofDeconstructionProgression = 1.0f;  // how much second deconstruction will take
    cInventory m_Inventory;

public:

    Character()
    {
        cInventory TempInventory;
        GetInventory() = TempInventory;
    }
    
    void AddHealth(int health)
    {
       if (m_Health+health >= m_MaxHealth)
       {
           m_Health = m_MaxHealth;
       }
       else 
            m_Health+=health;
    }
    void ClearInventory()
    {
        m_Inventory.clear();
    }

    cInventory &GetInventory()
    {
        return m_Inventory;
    }
    float GetConstructionProgress()
    {
        return m_ConstructionProgress;
    }
    float GetDeconstructionProgress()
    {
        return m_DeconstructionProgress;
    }
    bool ProgressConstruction(float fElapsedTime)
    {
        m_ConstructionProgress += m_LevelofConstructionProgression * fElapsedTime;
        if (m_ConstructionProgress >= 1.0f)
        {
            ResetConstructionProgress();
            return true;
        }
        else
            return false;
    }

    bool ProgressDeconstruction(float fElapsedTime)
    {
        m_DeconstructionProgress += m_LevelofDeconstructionProgression * fElapsedTime;
        if (m_DeconstructionProgress >= 1.0f)
        {
            ResetDeconstructionProgress();
            return true;
        }
        else
            return false;
    }

    void ResetConstructionProgress()
    {
        m_ConstructionProgress = 0.0f;
    }
    void ResetDeconstructionProgress()
    {
        m_DeconstructionProgress = 0.0f;
    }

    virtual int GetHealth() override
    {
        return m_Health;
    }

    virtual void SetHealth(int val) override
    {
       m_Health = val; 
    }

    virtual int GetMaxHealth() override
    {
        return m_MaxHealth;
    }

    virtual float GetSpeed() override
    {
        return m_Speed;
    }
    
    virtual void SetSpeed(float s = 0.0f)
    {
        m_Speed = s;
    }
    auto GetReachDistance()
    {
        return m_ReachDistance;
    }
    void GetReachDistance(float val)
    {
         m_ReachDistance = val;
    }
    

};

class Enemy : public Character
{

public:
   // virtual void Update(const Game *GameInstance) override
   // {
   //      auto PlayerX = GameInstance->EntityManager.Player.GetX();
   //      auto PlayerY = GameInstance->EntityManager.Player.GetY();
   //      
   // }
};

class cPlayer : public Character
{
    // float DeconstructionProgress = 0.0f;
    float GatheringProgress = 0.0f;
    float CameraX = 0;
    float CameraY = 0;
    int IDofTileSelectedToBuild = 3;

    float VelocityX = 0.0f;
    float VelocityY = 0.0f;

public:
    using Entity::SetAngle;

    inline void SyncCameraWithPlayer(int ScreenWidth, int ScreenHeight, int TileSize = 16)
    {
        CameraX = GetX() - (static_cast<float>(ScreenWidth) / 2) / TileSize;
        CameraY = GetY() - (static_cast<float>(ScreenHeight)/ 2) / TileSize;
    }
    auto GetCameraX()
    {
        return CameraX;
    }
    auto GetCameraY()
    {
        return CameraY;
    }
    void SetAngle(float MouseMapX, float MouseMapY)
    {
        SetAngle(atan2(MouseMapY - GetY(), MouseMapX - GetX()));
    }

    auto GetIDofTileToBuild()
    {
        return IDofTileSelectedToBuild;
    }

    void SetIDofTileToBuild(int ID)
    {
        IDofTileSelectedToBuild = ID;
    }
    using Character::Character;
    cPlayer()
    {
        
        SetSpeed(4.0f);

    }
    virtual olc::vf2d GetVelocity()
    {
        return {VelocityX, VelocityY};
    }

    virtual void SetVelocity(olc::vf2d InVec)
    {
        VelocityX = InVec.x;
        VelocityY = InVec.y;
    }
    virtual void AddVelocity(olc::vf2d AddVec)
    {
        VelocityX += AddVec.x;
        VelocityY += AddVec.y;
    }
    using Entity::Move;
    void Move(float fElapsedTime)
    {
        // Entity::PreviousX;
        // Entity::PreviousY;
        Entity::PreviousX = GetX();
        Entity::PreviousY = GetY();
        SetX(GetX() + VelocityX * fElapsedTime);
        SetY(GetY() + VelocityY * fElapsedTime);
    }
    void MoveBack()
    {
        VelocityX = 0;
        VelocityY = 0;
        Entity::MoveBack();
    }
};
