#pragma once
#include "managers/ItemManager.h"
#include "managers/TileManager.h"
#include "managers/TextureManager.h"
#include "managers/EntityManager.h"
class cManagersManager
{

    sItemManager *ItemManager;
    sTileManager *TileManager;
    sTextureManager *TextureManager;
    sEntityManager *EntityManager;

public:
    cManagersManager(sItemManager *IM = nullptr, sTileManager *TiM = nullptr, sTextureManager *TeM = nullptr) : ItemManager(IM), TileManager(TiM), TextureManager(TeM)
    {
        ;
    }
    void init(sItemManager *IM = nullptr, sTileManager *TiM = nullptr, sTextureManager *TeM = nullptr, sEntityManager *EnM = nullptr)
    {
        ItemManager = IM;
        TileManager = TiM;
        TextureManager = TeM;
        EntityManager = EnM;
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
        
        for (auto const Items : (*TileManager)[TileID].get()->GetItemsRequiredToDeconstruct())
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
};