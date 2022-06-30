#pragma once
#include "Entity.h"
#include "managers/ItemManager.h"
#include "managers/TileManager.h"
#include "managers/TextureManager.h"
#include "managers/EntityManager.h"
#include "managers/UIManager.h"
#include "managers/InputManager.h"
#include "managers/WorldManager.h"
#include "managers/TimeManager.h"
#include <cstdint>
#include <vector>
class cManagersManager
{
    sItemManager *ItemManager;
    sTileManager *TileManager;
    sTextureManager *TextureManager;
    sEntityManager *EntityManager;
    cUIManager *UIManager;
    cWorldManager *WorldManager;
    cTimeManager *TimeManager;

public:
    void init(sItemManager *IM = nullptr, sTileManager *TiM = nullptr, 
                sTextureManager *TeM = nullptr, sEntityManager *EnM = nullptr,
                cUIManager *UIM = nullptr, cWorldManager *WM = nullptr,
                cTimeManager *TimeMan = nullptr
                )
    {
        ItemManager = IM;
        TileManager = TiM;
        TextureManager = TeM;
        EntityManager = EnM;
        UIManager = UIM;
        WorldManager = WM;
        TimeManager= TimeMan;
    }

    auto GetItemDecal(int ItemID)
    {
        return (*TextureManager)[(*ItemManager)[ItemID]->GetTextureID()];
    }

    auto GetTileDecal(int TileID)
    {
        return (*TextureManager)[(*TileManager)[TileID]->GetTextureID()];
    }
    auto isTileColisive(int TileId)
    {
        return (*TileManager)[TileId]->isColisive();
    }
    auto isTileStackColisive(int x, int y )
    {
        auto TileStack = WorldManager->GetTileStack(x, y);
        for (const auto &i : TileStack)
            if ((*TileManager)[i]->isColisive())
                return true;

        return false;
    }

    auto isTileStackColisive(std::vector<int> TileStack )
    {
        for (const auto &i : TileStack)
            if ((*TileManager)[i]->isColisive())
                return true;

        return false;
    }
    bool IsPlayerAbleToDeconstructTile(int TileID)
    {
        auto vItems = (*TileManager)[TileID].get()->GetItemsRequiredToDeconstruct();
        if (vItems.empty())
            return false;
        
        for (auto const Items : vItems)
            if (EntityManager->Player.GetInventory().IsEnoughItems(Items) == false)
                return false;
        
        return true;
    }

    void PlayerDeconstructedTile(int TileID)
    {
        auto vItemsDroped = (*TileManager)[TileID]->GetItemsDroped();
        for(auto DropedItem:vItemsDroped)
            EntityManager->Player.GetInventory().PickUpItem(DropedItem );
    }
    bool IsPlayerAbleToConstructTile()
    {
        int TileID = EntityManager->Player.GetIDofTileToBuild(); 
        auto vItems = (*TileManager)[TileID].get()->GetItemsRequiredToConstruct();
        if (vItems.empty())
            return false;
        
        for (auto const Items : vItems)
            if (EntityManager->Player.GetInventory().IsEnoughItems(Items) == false)
                return false;
        
        return true;
    }
    void PlayerConstructedTile()
    {
        int TileID = EntityManager->Player.GetIDofTileToBuild(); 

        auto vItems = (*TileManager)[TileID].get()->GetItemsRequiredToConstruct();
        for (auto const Items : vItems)
            EntityManager->Player.GetInventory().DecreaseItemQuantity(Items);
    }

    bool CanTileFitOnTileStack(std::vector<int> TileStack, int TileID)
    {
        int TileZLevel = static_cast<int>((*TileManager)[TileID]->GetZLevel());
        int ZLevelofTileAtTheTopOFStack = static_cast<int>((*TileManager)[TileStack.back()]->GetZLevel());
        if (TileZLevel > ZLevelofTileAtTheTopOFStack )
        {
            return true;
        }

        return false;
    }
    std::string GetItemUserVisibleName(int ItemID)
    {
        return (*ItemManager)[ItemID]->GetUserVisibleName();
    }
    auto GetTileManager()
    {
        return TileManager;
    }

    bool isPlayerAbleToDeconstructTopTileAt(int x, int y)
    {
        return IsPlayerAbleToDeconstructTile(WorldManager->GetTileStack(x, y).back());
    }

    void PlayerUseEquipedItem()
    {
        EntityUseItem(&EntityManager->Player);
        // auto ItemEquipedByPlayer = (*ItemManager)[EntityManager->Player.GetInventory().GetEquipedItemSlot().ItemID].get();
        // if( ItemEquipedByPlayer->isWapon() )
        // {
        //     if( ((Weapon*)ItemEquipedByPlayer)->GetAttackType() == AttackType::Spear)
        //     {
        //         EntityManager->SpawnDamageGiver("SPEAR",ItemEquipedByPlayer->GetDamage(),1.0,&(EntityManager->Player),TimeManager->GetPtrToWorldTime());
        //     }
        // }
    }

    void EntityUseItem(Character* a_Entity)
    {
        auto ItemEquipedByPlayer = (*ItemManager)[a_Entity->GetInventory().GetEquipedItemSlot().ItemID].get();
        if( ItemEquipedByPlayer->isWapon() && a_Entity->GetCanAttack())
        {
            a_Entity->SetCanAttack(false);
            if( ((Weapon*)ItemEquipedByPlayer)->GetAttackType() == AttackType::Spear)
            {
                EntityManager->SpawnDamageGiver("SPEAR",ItemEquipedByPlayer->GetTextureID(),ItemEquipedByPlayer->GetDamage(),((Weapon*)ItemEquipedByPlayer)->GetRange(),(Entity*)a_Entity,TimeManager->GetPtrToWorldTime());
            }
        }
    }
    void DeconstructTopTileAt(int x, int y)
    {
        int DeconstructedTile = WorldManager->GetTileStack(x, y).back();
        PlayerDeconstructedTile(DeconstructedTile);
        if( DeconstructedTile <0 )
            GetTileManager()->DeleteDynamicTile(DeconstructedTile);
        WorldManager->GetTileStack(x, y).pop_back();
    }
    void ConstructTileAtTopOf(int x, int y, int TileID)
    {
        if( TileManager->IsTileDynamic(TileID))
        {
            WorldManager->GetTileStack(x, y).push_back(TileManager->GetNewDynamicTile(TileID));
        }
        else
            WorldManager->GetTileStack(x, y).push_back(TileID);
    }
    
    bool MoveEntity(Entity Ent,float fElapsedTime)
    {
        
    // void MovePlayerWithColysionCheck(float fElapsedTime = 1.0f,float VecX =0.0f,float VecY = 0.0f)
       
        Ent.Move(
            fElapsedTime
            );
        bool DidColysionHappen = (isTileStackColisive(Ent.GetX(),Ent.GetY()));
        if (DidColysionHappen)
        {
           Ent.MoveBack();
        }
        return DidColysionHappen;
    }
    
};
