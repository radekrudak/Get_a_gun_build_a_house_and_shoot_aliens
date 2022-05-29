#pragma once
#include "ItemManager.h"
#include "TileManager.h"
#include "TextureManager.h"
#include "EntityManager.h"
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
};