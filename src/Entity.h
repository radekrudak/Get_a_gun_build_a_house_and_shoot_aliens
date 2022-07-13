#pragma once
// #include "ManagersManager.h"
// #include "Game.h"
#include "Math.h"
#include "olcPixelGameEngine.h"
#include "Item.h"
#include <math.h>
#include <vector>


enum class EntityTypes
{
    GenericEntity = 0,
    Enemy,
    Player,
    DamageGiver,
    Character
};

class Entity
{
protected:
    int m_TextureID = 0;
    float m_x = 0;
    float m_y = 0;
    float VelocityX =0;
    float VelocityY =0;
    float PreviousX = 0;
    float PreviousY = 0;
    float Angle = 0;
    bool m_isDead = false;

public:
    EntityTypes m_EntityType = EntityTypes::GenericEntity;
    // virtual void Update(const cManagersManager &ManagersManager)
    // {
    //     ;
    // }
    
    Entity(int TextureID = 0, float xx = 0, float yy = 0,EntityTypes EntityType = EntityTypes::GenericEntity): 
            m_TextureID(TextureID),m_x(xx),m_y(yy),m_EntityType(EntityType)
    {
    }

    Entity(const Entity &TemplateEntity, float x, float y): m_TextureID(TemplateEntity.m_TextureID), m_x(x),m_y(y)
    {
    }
    auto GetEntityType()
    {
        return m_EntityType;
    }
    auto GetTextureID()
    {
        return m_TextureID;
    }
    virtual void Move(float fElapsedTime)
    {
        Move(VelocityX*fElapsedTime,VelocityY*fElapsedTime);
    }
    virtual void Move(float VecX, float VecY)
    {
        PreviousX = m_x;
        PreviousY = m_y;
        m_x += VecX;
        m_y += VecY;
    }
    virtual void MoveBack()
    {
        m_x = PreviousX;
        m_y = PreviousY;
    }


    auto GetX() const
    {
        return m_x;
    }
    auto GetY() const
    {
        return m_y;
    }
    auto GetAngle()
    {
        return Angle;
    }

    void SetX(float X)
    {
        m_x = X;
    }
    void SetY(float Y)
    {
        m_y = Y;
    }

    void SetAngle(float a)
    {
        Angle = a;
    }
    olc::vf2d GetPosition()
    {
        return olc::vf2d(m_x, m_y);
    }
    virtual float GetfDeconstruction()
    {
        return 0;
    }
    virtual float GetHealth()
    {
        return 0;
    }
    virtual float GetMaxHealth ()
    {
        return 0;
    }
    virtual bool SubtractHealth(float health)
    {
        return false;
    }
    virtual void AddHealth(float health)
    {

    }
    virtual float GetSpeed()
    {
        return 0.0f;
    }
    virtual void SetHealth(float health)
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
    virtual float GetDamage()
    {
        return 0;
    }
    virtual bool IsPointInsideEntity(float x, float y)
    {
        return false;
    }
    virtual void Update()
    {
        ;
    }
    auto isDead()
    {
        return m_isDead;
    }
};




class Character : public Entity
{
    
    float m_Speed = 0;
    float m_MaxHealth =10;
    float m_Health = m_MaxHealth;
    float m_ConstructionProgress = 0.0f;
    float m_DeconstructionProgress = 0.0f;
    float m_ReachDistance =4.0f;
    float m_SizeOfEntityInTiles = 1;

    float m_LevelofConstructionProgression = 1.0f; // how much second construction will take
    float m_LevelofDeconstructionProgression = 1.0f;  // how much second deconstruction will take
    cInventory m_Inventory;
    bool m_CanAttack = true;
public:
    // Entity::m_Type;
    Character(int TextureID = 0, float xx = 0, float yy = 0,EntityTypes EntityType = EntityTypes::GenericEntity): 
            Entity(TextureID,xx,yy,EntityTypes::Character)
    {
        m_Health=m_MaxHealth;
    }

    Character()
    {
        cInventory TempInventory;
        GetInventory() = TempInventory;
    }
    
    virtual void AddHealth(float health) override
    {
       if (m_Health+health >= m_MaxHealth)
       {
           m_Health = m_MaxHealth;
       }
       else 
            m_Health+=health;
    }
    virtual bool SubtractHealth(float health) override
    {
    
       if (m_Health-health <= 0 )
       {
           m_Health = 0;
           m_isDead = true;
            return true;
       }
       else 
            m_Health-=health;
       
       return false;
        
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

    virtual float GetHealth() override
    {
        return m_Health;
    }

    virtual void SetHealth( float val) override
    {
       m_Health = val; 
    }

    virtual float GetMaxHealth() override
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

    virtual bool IsPointInsideEntity(float x, float y) override
    {
        x-=m_x-m_SizeOfEntityInTiles/2;
        y-=m_y-m_SizeOfEntityInTiles/2;

        if (x<= m_SizeOfEntityInTiles && y<m_SizeOfEntityInTiles && x>=0 && y >=0 )
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    void SetCanAttack(bool a_CanAttack)
    {
        m_CanAttack = a_CanAttack;
    }
    auto GetCanAttack()
    {
        return m_CanAttack;
    }

};

class DamageGiver : public Entity
{
    protected:
    float m_Damage;
    float m_Range;
    Entity* m_Owner;
    const uint64_t *m_Time;
    uint64_t m_StartTime;

    std::vector<VecFloat2d> m_vOffsetList;

    std::vector<Entity*> m_vAlreadyDamagedEntites;
    public:
   //  DamageGiver(int TextureID,float Damage,const uint64_t *Time) :Entity(TextureID,0,0,EntityTypes::DamageGiver), m_Damage(Damage),m_Owner(nullptr),m_Time(Time)
   //  {
   //      m_StartTime = *Time;
   // //      m_vOffsetList.push_back({1,0});
   // // 
   // //      m_vOffsetList.push_back({0.9,0});
   // //
   // //      m_vOffsetList.push_back({0.8,0});
   //  }
   //  DamageGiver(DamageGiver* TemplateEntity,Entity* Owner) :Entity(TemplateEntity->m_TextureID,TemplateEntity->m_x,TemplateEntity->m_y,EntityTypes::DamageGiver), m_Damage(TemplateEntity->m_Damage),m_Owner(Owner),m_Time(TemplateEntity->m_Time)
   //  {
   //      m_StartTime = *m_Time;
   //  }
    DamageGiver(int TextureID,float Damage,float Range,const uint64_t * Time, Entity* Owner ):Entity(TextureID,0,0,EntityTypes::DamageGiver), m_Damage(Damage),m_Range(Range),m_Owner(Owner),m_Time(Time)
    {
        m_StartTime = *m_Time;
    }
    virtual float GetDamage() override
    {
        return m_Damage; 
    }
    void GiveDamage(Entity* Victim)
    {
        if (Victim != m_Owner && Victim != nullptr)
        {
            for(auto &i: m_vAlreadyDamagedEntites )
            {
                if(i == Victim)
                    return;


            }

            if(Victim->IsPointInsideEntity(m_x, m_y))
            {

                m_vAlreadyDamagedEntites.push_back(Victim);
                Victim->SubtractHealth(GetDamage());
            }
                // if(isDead)
            
             //ll yourself or something;
            
        }
    }
    virtual void Update() override
    {
    
        m_vOffsetList.push_back({1,0});
        int i = (*m_Time-m_StartTime)/10;
        if (i > m_vOffsetList.size()-1)
            i=m_vOffsetList.size()-1;
        Angle = m_Owner->GetAngle();
        m_x = m_Owner->GetX() +(m_vOffsetList[i].x*cos(m_Owner->GetAngle())-m_vOffsetList[i].y*sin(m_Owner->GetAngle()));
        m_y = m_Owner->GetY() +(m_vOffsetList[i].y*cos(m_Owner->GetAngle())+m_vOffsetList[i].x*sin(m_Owner->GetAngle()));
        m_vOffsetList.clear();
        ((Character*)m_Owner)->SetCanAttack(true);
        // float mtrix[] = {
        //     cos(Angle),-sin(Angle),
        //     sin(Angle),cos(Angle)};
    }

};
class SpearEntity : public DamageGiver
{
    using DamageGiver::DamageGiver;

    virtual void Update() override
    {
        float i = sin(static_cast<float>(*m_Time-m_StartTime)/100*8*3.14)+m_Range;
        // std::cout<<i<<" "<< *m_Time<<" "<<m_StartTime<<std::endl;
        Angle = m_Owner->GetAngle();
        m_x = m_Owner->GetX() +(i*cos(m_Owner->GetAngle())-0*sin(m_Owner->GetAngle()));
        m_y = m_Owner->GetY() +(0*cos(m_Owner->GetAngle())+i*sin(m_Owner->GetAngle()));
        if (*m_Time-m_StartTime > 1 && i <= m_Range)
        {
            // m_StartTime = *m_Time;AGPL
            ((Character *)m_Owner)->SetCanAttack(true);
            m_isDead = true;
        }
    }
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
    cPlayer() : Character(0,0,0)
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


class Enemy : public Character
{
    cPlayer* m_Player = nullptr;
    void (*m_Attack)(Character*);
public:
    Enemy():Character(0,0,0){

    }
    Enemy(int TextureID = 0, float xx = 0, float yy = 0,cPlayer *Player = nullptr,
            void (*Attack)(Character*) = nullptr): Character(TextureID,xx,yy,EntityTypes::Enemy) , m_Attack(Attack)
    {
        
    }

    virtual void Update() override
    {
        auto x1 = GetX();
        auto y1 = GetY();
        auto x2 = m_Player->GetX();
        auto y2 = m_Player->GetY();
        float DistanceToPlayerSquare = (x2-x1)*(x2-x1)+(y2-y1)*(y2-y1);
        if (DistanceToPlayerSquare < 4)
        {
            m_Attack(this);
        }
    }

    // virtual void Update(const Game *GameInstance) override
   // {
   //      auto PlayerX = GameInstance->EntityManager.Player.GetX();
   //      auto PlayerY = GameInstance->EntityManager.Player.GetY();
   //      
   // }
};
