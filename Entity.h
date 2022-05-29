#pragma once
#include "olcPixelGameEngine.h"
#include <math.h>

static const int MapSize = 1024;

enum class EntityTypes {
    GenericEntity=0,
    Enemy,
    Player
};

class Entity{

    int TextureID =0;
    float x =0;
    float y = 0;
    float PreviousX=0;
    float PreviousY=0;
    float Angle =0;
public:
    EntityTypes EntityType = EntityTypes::GenericEntity;
    virtual void Move(float VecX,float VecY)
    {
        PreviousX = x;
        PreviousY = y;
        x+=VecX;
        y+=VecY;

    }
    virtual void MoveBack()
    {
        x = PreviousX; 
        y = PreviousY;


    }
public:
     Entity(int TextureID =0,float xx =0,float yy =0) 
    {
            x=xx;
            y=yy;

           
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
        x=X;
    }
    void SetY(float Y)
    {
        y=Y;
    }

    void SetAngle(float a)
    {
        Angle = a;
    }
    olc::vf2d GetPosition()
    {
        return olc::vf2d (x,y);

    }
};




class Enemy : public Entity
{
    float fDestruction =0.0f;
    float Speed = 0;
    int TextureID =0;
public:
    float& GetfDestruction()
    {
        return fDestruction;
    }
};

class cPlayer: public Entity
{
    float CameraX=0;
    float CameraY=0;
public:
    inline void SyncCameraWithPlayer(int ScreenWidth,int ScreenHeight,int TileSize =16)
    {
        CameraX = GetX() - (ScreenWidth / 2) / TileSize;
        CameraY = GetY() - (ScreenHeight / 2) / TileSize;
    }
    auto  GetCameraX()
    {
        return CameraX;
    }
    auto  GetCameraY()
    {
        return CameraY;
    }
    using Entity::SetAngle;
    void SetAngle(float MouseMapX, float MouseMapY)
    {
      SetAngle(atan2(MouseMapY-GetY(),MouseMapX-GetX()));
    }

    cPlayer ()
    {
        ;
    }
    //using Entity::Entity;
};