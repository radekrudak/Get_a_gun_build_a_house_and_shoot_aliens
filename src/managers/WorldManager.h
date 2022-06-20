#pragma once
#include "../World.h"
// std::unordered_map<std::pair<int,itn>
class cWorldManager
{
    cWorld World;
    std::vector<int> DefaultTileStack;
    int TileSize = 16;
    int LenghtOfSide = 1024;

public:

    inline    std::vector<int> &GetTileStack(int x, int y)
    {
       if (0 <= x && x < LenghtOfSide && 0 <= y && y < LenghtOfSide)
            
            return  World.GetTileStackAt(x,y);
       else
            return DefaultTileStack;
    }

    void GenerateNewWorld(std::map<std::string, int> &TileNameMap, int LenghtOfSideOfTerrain = 1024, int Seed = 1)
    {
        World = cWorld(TileNameMap,Seed);
        LenghtOfSide = LenghtOfSideOfTerrain;
        
        DefaultTileStack.resize(1, TileNameMap["GRASS"]);
    }

    auto GetTileSize()
    {
        return TileSize;
    }

    void SetTileSize(int TS)
    {
        TileSize = TS;
    }

    
};
