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
    EntityTypes EntityType = EntityTypes::GenericEntity;
    virtual void Move(float VecX,float VecY)
    {
        PreviousX = x;
        PreviousY = y;
        x+=VecX;
        y+=VecY;

    }
    virtual void Move()
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
    void SetX(float X)
    {
        x=x;
    }
    void SetY(float Y)
    {
        y=Y;
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
public:
    cPlayer ()
    {
        ;
    }
    //using Entity::Entity;
};