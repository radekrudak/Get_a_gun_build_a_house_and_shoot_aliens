#pragma once
#include "olcPixelGameEngine.h"
#include "Item.h"
#include <math.h>

static const int MapSize = 1024;

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
    float PreviousX = 0;
    float PreviousY = 0;
    float Angle = 0;

public:
    EntityTypes EntityType = EntityTypes::GenericEntity;
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
    auto GetX()
    {
        return x;
    }
    auto GetY()
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
    virtual float GetfDestruction()
    {
        return 0;
    }
    virtual float GetHealth()
    {
        return 0;
    }
    virtual float GetSpeed()
    {
        return 0.0f;
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
    float Destruction = 0.0f;
    float Speed = 0;
    float Health = 0.0f;

    cInventory Inventory;
    
public:
    cInventory &GetInventory()
    {
        return Inventory;
    }
    virtual float GetDestruction()
    {
        return Destruction;
    }
    virtual float GetHealth()
    {
        return Destruction;
    }

    virtual float GetSpeed()
    {
        return Speed;
    }
    virtual void SetSpeed(float s = 0.0f)
    {
        Speed = s;
    }
};

class Enemy : public Character
{

public:
};

class cPlayer : public Character
{
    float CameraX = 0;
    float CameraY = 0;
    int IDofTileSelectedToBuild = 1;

    float VelocityX = 0.0f;
    float VelocityY = 0.0f;

public:
    using Character::GetInventory;
    using Entity::SetAngle;

    inline void SyncCameraWithPlayer(int ScreenWidth, int ScreenHeight, int TileSize = 16)
    {
        CameraX = GetX() - (ScreenWidth / 2) / TileSize;
        CameraY = GetY() - (ScreenHeight / 2) / TileSize;
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
        SetX(GetX() + VelocityX*fElapsedTime);
        SetY(GetY() + VelocityY*fElapsedTime);
    }
    void MoveBack()
    {
        VelocityX = 0;
        VelocityY = 0;
        Entity::MoveBack();
    }
};