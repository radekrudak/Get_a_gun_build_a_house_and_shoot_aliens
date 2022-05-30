#pragma once
#include <vector>
#include "ManagersManager.h"
class cWorld
{
    std::vector<std::vector<std::vector<int>>> vTerrain;
    std::vector<int> DefaultTileStack;
    int TileSize =16;
    int LenghtOfSide = 1024;

public:

    cManagersManager *ManagersManager;

    std::vector<int> &GetTileStackAt(int x, int y)
    {
        if (0 <= x && x<LenghtOfSide && 0 <= y && y < LenghtOfSide )
            return vTerrain[x][y];
        else 
            return DefaultTileStack;
    }

    void GenerateTerrain(std::map<std::string, int> &TileNameMap,int LenghtOfSideOfTerrain = 1024)
    {
        LenghtOfSide = LenghtOfSideOfTerrain;
        vTerrain.resize(LenghtOfSide,
                        std::vector<std::vector<int>>(LenghtOfSide, 
                                std::vector<int>(1, TileNameMap["GRASS"])));
        DefaultTileStack.resize(1,0);
        for (size_t x = 0; x < LenghtOfSide; x++)
        {

            for (size_t y = 0; y < LenghtOfSide; y++)
            {
               if (rand()%100 <10) 
                  vTerrain[x][y].push_back(  TileNameMap["TREE"]  ) ;
            }
        }
    } 
    bool isTileStackColisiveAt(int x, int y )
    {
        if (0 < x && x<LenghtOfSide && 0 < y && y < LenghtOfSide )
            return ManagersManager->isTileStackColisive(GetTileStackAt(x,y));
        else 
            return true;
    }
    auto GetTileSize()
    {
        return TileSize;
    }
    
    void SetTileSize(int TS)
    {
        TileSize = TS;
    }
    bool isPlayerAbleToDeconstructTopTileAt(int x, int y)
    {
       return  ManagersManager->IsPlayerAbleToDeconstructTile(GetTileStackAt(x,y).back());
    }
    void DeconstructTopTileAt(int x,int y )
    {
        int DeconstructedTile = GetTileStackAt(x,y).back();
        ManagersManager->PlayerDeconstructedTile(DeconstructedTile);
        GetTileStackAt(x,y).pop_back();
    }
};