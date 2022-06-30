#pragma once
#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include "../Entity.h"


struct sEntityManager
{
    
    std::vector<std::unique_ptr<Entity>> vEntities;
    std::vector<std::unique_ptr<Entity>> vEntitiTemplates;
    std::unique_ptr<Entity> NullEntity;
    std::map<std::string,int> m_EntityTemplatesNameMap;
    //std::unique_ptr<cPlayer>
    cPlayer  Player;
    auto &operator[](size_t index)
    {
        if (index >=0 && index<vEntities.size())
            return vEntities[index];
        else 
            return NullEntity;
            
    }
    void LoadEntites(std::map<std::string, int> TextureNameMap,const uint64_t* WorldTime)
    {
        vEntitiTemplates.push_back(std::make_unique<Entity> (TextureNameMap["Enemy"],0,0));
        // vEntitiTemplates.push_back(std::make_unique<SpearEntity>(TextureNameMap["Enemy"],1,WorldTime));
        // m_EntityTemplatesNameMap["Spear"] = vEntitiTemplates.size()-1;
    }
    void AddEntity(Entity* NewEntity)
    {
        for(auto &i: vEntities)
        {
            if(i == nullptr)
            {
                i = std::unique_ptr<Entity>(NewEntity);
                return;
            }
        }
        vEntities.push_back(std::unique_ptr<Entity>(NewEntity));
    }
    //Spawns Entity from template and returns ID of spawned Entity
    int SpawnEntity(int TemplateID, float PosX, float PosY)
    {
        AddEntity( new Entity ( *vEntitiTemplates[TemplateID],PosX,PosY ) );
        return vEntities.size()-1;
    }

    void SpawnDamageGiver(float x, float y,float Damage = 2,Entity* Owner = nullptr, const uint64_t *Time = nullptr)
    {
        // AddEntity( new DamageGiver (0,Damage,Time));
    }
    void SpawnDamageGiver(std::string TypeOfDamageGiver,int TextureID,float Damage = 1.0f,float Range = 1.0,Entity* Owner = nullptr,const uint64_t* Time= nullptr)
    {
        if (TypeOfDamageGiver == "SPEAR")
        {
            AddEntity(new SpearEntity(TextureID,Damage,Range,Time,Owner));     
        }
        // AddEntity(new SpearEntity ((DamageGiver*)vEntitiTemplates[m_EntityTemplatesNameMap["Spear"]].get(),Owner));
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
            if(i != nullptr)
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
                if (i->isDead())
                {
                     i.reset();
                }
            }
        }
    }
    auto GetSizeOfvEntitesVector()
    {
        return vEntities.size();
    }
};
