#pragma once
#include "managers/ItemManager.h"
#include "managers/TileManager.h"
#include "managers/TextureManager.h"
#include "managers/EntityManager.h"
#include "managers/UIManager.h"
class cManagersManager
{

    sItemManager *ItemManager;
    sTileManager *TileManager;
    sTextureManager *TextureManager;
    sEntityManager *EntityManager;
    cUIManager *UIManager;

public:
    cManagersManager(sItemManager *IM = nullptr, sTileManager *TiM = nullptr, sTextureManager *TeM = nullptr) : ItemManager(IM), TileManager(TiM), TextureManager(TeM)
    {
        ;
    }
    void init(sItemManager *IM = nullptr, sTileManager *TiM = nullptr, sTextureManager *TeM = nullptr, sEntityManager *EnM = nullptr, cUIManager *UIM = nullptr)
    {
        ItemManager = IM;
        TileManager = TiM;
        TextureManager = TeM;
        EntityManager = EnM;
        UIManager = UIM;
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
    auto isTileStackColisive(std::vector<int> TileStack)
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
};