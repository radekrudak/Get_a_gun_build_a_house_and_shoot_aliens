#pragma once
#include "managers/ItemManager.h"
#include "managers/TileManager.h"
#include "managers/TextureManager.h"
#include "managers/EntityManager.h"
#include "managers/UIManager.h"
#include "managers/InputManager.h"
#include "managers/WorldManager.h"
#include <vector>
class cManagersManager
{

    sItemManager *ItemManager;
    sTileManager *TileManager;
    sTextureManager *TextureManager;
    sEntityManager *EntityManager;
    cUIManager *UIManager;
    cWorldManager *WorldManager;

public:
    cManagersManager(sItemManager *IM = nullptr, sTileManager *TiM = nullptr, sTextureManager *TeM = nullptr) : ItemManager(IM), TileManager(TiM), TextureManager(TeM)
    {
        ;
    }
    void init(sItemManager *IM = nullptr, sTileManager *TiM = nullptr, sTextureManager *TeM = nullptr, sEntityManager *EnM = nullptr, cUIManager *UIM = nullptr, cWorldManager *WM = nullptr)
    {
        ItemManager = IM;
        TileManager = TiM;
        TextureManager = TeM;
        EntityManager = EnM;
        UIManager = UIM;
        WorldManager = WM;
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


};
