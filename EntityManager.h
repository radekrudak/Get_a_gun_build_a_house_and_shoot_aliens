#pragma once
#include <memory>
#include "Entity.h"


struct sEntityManager
{
    
    std::vector<std::unique_ptr<Entity>> vEntities;
    //std::unique_ptr<cPlayer>
    cPlayer  Player;
    sEntityManager()
    {
       ;// Player = std::unique_ptr<cPlayer> (new cPlayer);
    }

};