#pragma once
#include "FindPath.h"
#include "olcPixelGameEngine.h"
#include <math.h>
static const int MapSize = 1024;

enum class EntityTypes {
    GenericEntity=0,
    Enemy,
    Player
};

class Entity{
    int TextureID;
public:
    float x;
    float y;
    EntityTypes EntityType = EntityTypes::GenericEntity;

public:
     Entity(std::map<std::string,int> TextureNameMap, std::string TextureName = "MissingTexture",float xx =0,float yy =0) 
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
    public:
    float fDestruction =0.0f;
    int TextureID =0;

    float Distance(float x1, float y1,float x2,float y2)
    {
        return sqrtf((x1 -x2)*(x1 -x2)+(y1 -y2)*(y1 -y2));
    }

    olc::vf2d Move(float fPX,float fPY,float fElapsedTime)
    {   
        return olc::vf2d(x,y);
    }

    olc::vf2d CheckNextPosytionStraight(float px, float py ,float fElapsedTime)
    {

        return olc::vf2d (x+(px-x) / Distance (px,py,x,y)*fElapsedTime, y+(py-y) / Distance (px,py,x,y)*fElapsedTime);

    }


    olc::vf2d Move_Straight(float px, float py ,float fElapsedTime)
    {

        return olc::vf2d (x+=(px-x) / Distance (px,py,x,y)*fElapsedTime, y+=(py-y) / Distance (px,py,x,y)*fElapsedTime);

    }

    float& GetfDestruction()
    {
        return fDestruction;
    }
};
