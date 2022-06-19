#pragma once
#include <cstddef>
#include <functional>
#include <vector>
#include <utility>
#include <array>
#include <unordered_map>
#include "ManagersManager.h"
#include "Math.h"

constexpr int CHUNK_SIZE =256;
class Hasher
{
    public:
        size_t operator()(const VecInt2d &vec) const
        {
            size_t hash = static_cast<size_t>(vec.x) | (static_cast<size_t>(vec.y) <<(8*4));
            
            return hash; 
        }
};

class cChunkPool{
    std::unordered_map<  VecInt2d, 
        // 2d array of std::vector of size CHUNK_SIZE
            std::array< std::array< std::vector<int>, CHUNK_SIZE >, CHUNK_SIZE>,Hasher,std::equal_to<VecInt2d>> m_Chunks;
    std::vector<int> GetTileStackAt(int x, int y)
    {
        int ChunkX = x/CHUNK_SIZE;
        int ChunkY = y/CHUNK_SIZE;
        int TileStackX = x%CHUNK_SIZE;
        int TileStackY = y&CHUNK_SIZE;
        return m_Chunks[{ChunkX,ChunkY}][TileStackX][TileStackY];
    }
};


class cWorld
{
    
    // std::unordered_map<std::pair<int,itn>
    std::vector<std::vector<std::vector<int>>> vTerrain;
    std::vector<int> DefaultTileStack;
    int TileSize = 16;
    int LenghtOfSide = 1024;

public:
    cManagersManager *ManagersManager;

    std::vector<int> &GetTileStackAt(int x, int y)
    {
        if (0 <= x && x < LenghtOfSide && 0 <= y && y < LenghtOfSide)
            return vTerrain[x][y];
        else
            return DefaultTileStack;
    }

    void GenerateTerrain(std::map<std::string, int> &TileNameMap, int LenghtOfSideOfTerrain = 1024)
    {
        LenghtOfSide = LenghtOfSideOfTerrain;
        vTerrain.resize(LenghtOfSide,
                        std::vector<std::vector<int>>(LenghtOfSide,
                                                      std::vector<int>(1, TileNameMap["GRASS"])));
        DefaultTileStack.resize(1, 0);
        for (size_t x = 1; x < LenghtOfSide-1; x++)
        {

            for (size_t y = 1; y < LenghtOfSide-1; y++)
            {
                if (rand() % 100 < 10)
                { 
                    if(vTerrain[x-1][y-1].back() != TileNameMap["TREE"] &&vTerrain[x][y-1].back() != TileNameMap["TREE"] && vTerrain[x+1][y-1].back() != TileNameMap["TREE"] &&
                    vTerrain[x-1][y].back() != TileNameMap["TREE"]                            && vTerrain[x+1][y].back() != TileNameMap["TREE"] &&
                    vTerrain[x-1][y+1].back() != TileNameMap["TREE"] &&vTerrain[x][y+1].back() != TileNameMap["TREE"] && vTerrain[x+1][y+1].back() != TileNameMap["TREE"]
                    )
                       vTerrain[x][y].push_back(TileNameMap["TREE"]);
                }
            }
        }
    }
    bool isTileStackColisiveAt(int x, int y)
    {
        if (0 < x && x < LenghtOfSide && 0 < y && y < LenghtOfSide)
            return ManagersManager->isTileStackColisive(GetTileStackAt(x, y));
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
        return ManagersManager->IsPlayerAbleToDeconstructTile(GetTileStackAt(x, y).back());
    }
    void DeconstructTopTileAt(int x, int y)
    {
        int DeconstructedTile = GetTileStackAt(x, y).back();
        ManagersManager->PlayerDeconstructedTile(DeconstructedTile);
        if( DeconstructedTile <0 )
            ManagersManager->GetTileManager()->DeleteDynamicTile(DeconstructedTile);
        GetTileStackAt(x, y).pop_back();
    }
    void ConstructTileAtTopOf(int x, int y, int TileID)
    {
        if( ManagersManager->GetTileManager()->IsTileDynamic(TileID))
        {
            GetTileStackAt(x, y).push_back(ManagersManager->GetTileManager()->GetNewDynamicTile(TileID));
        }
        else
            GetTileStackAt(x, y).push_back(TileID);
    }
};
