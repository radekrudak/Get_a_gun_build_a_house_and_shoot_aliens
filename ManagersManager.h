#pragma once
#include "ItemManager.h"
#include "TileManager.h"
#include "TextureManager.h"


class cManagersManager
{
    sItemManager *ItemManager;
    sTileManager *TileManager;
    sTextureManager *TextureManager;
    public:
    cManagersManager(sItemManager *IM = nullptr,sTileManager* TiM = nullptr,sTextureManager* TeM =  nullptr) : ItemManager(IM), TileManager(TiM),TextureManager(TeM)
    {
        ;
    }
    void init(sItemManager *IM = nullptr,sTileManager* TiM = nullptr,sTextureManager* TeM =  nullptr)
    {
    ItemManager =IM;
    TileManager = TiM;
    TextureManager = TeM;

    }
};