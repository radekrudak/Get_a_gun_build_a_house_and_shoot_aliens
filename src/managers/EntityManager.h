#pragma once
#include <cstddef>
#include <memory>
#include "../Entity.h"


struct sEntityManager
{
    
    std::vector<std::unique_ptr<Entity>> vEntities;
    std::vector<std::unique_ptr<Entity>> vEntitiTemplates;
    std::unique_ptr<Entity> NullEntity;
    //std::unique_ptr<cPlayer>
    cPlayer  Player;
    auto &operator[](size_t index)
    {
        if (index >=0 && index<vEntities.size())
            return vEntities[index];
        else 
            return NullEntity;
            
    }
    void LoadEntites(std::map<std::string, int> TextureNameMap)
    {
        vEntitiTemplates.push_back(std::make_unique<Entity> (TextureNameMap["Enemy"],0,0));
    }
    sEntityManager()
    {
       ;// Player = std::unique_ptr<cPlayer> (new cPlayer);
    }
    //Spawns Entity from template and returns ID of spawned Entity
    int SpawnEntity(int TemplateID, float PosX, float PosY)
    {
        vEntities.push_back(std::make_unique<Entity>( *vEntitiTemplates[TemplateID],PosX,PosY ) );
        return vEntities.size()-1;
    }
    void SpawnDamageGiver(float x, float y,float Damage = 2,Entity* Owner = nullptr)
    {
        vEntities.push_back(std::make_unique<DamageGiver>(0,x,y,Damage,Owner));
    }
    auto begin()
    {
        return vEntities.begin();
    }
    auto end()
    {
        return vEntities.end();
    }
    void UpdateEntites()
    {

        for (auto &i:vEntities)
        {
            i->Update();
            if(i->GetEntityType() == EntityTypes::DamageGiver)
            {
                
                ((DamageGiver*)i.get())->GiveDamage(&Player);
                for (auto &Victim:vEntities)
                {
                    ((DamageGiver*)i.get())->GiveDamage(Victim.get());
                }
            }
        }
    }
};
