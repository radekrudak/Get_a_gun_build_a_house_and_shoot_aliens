#pragma once
#include <cstddef>
#include <cstdint>
#include <functional>
#include <string>
#include <vector>
#include <utility>
#include <array>
#include <unordered_map>
#include <csignal>
#include <random>
#include "Math.h"

constexpr int CHUNK_SIZE =256;
using Chunk = std::array<std::array<std::vector<int>, CHUNK_SIZE>,CHUNK_SIZE>;
class Hasher
{
    public:
        size_t operator()(const VecInt2d &vec) const
        {

            size_t hash = (static_cast<size_t>(vec.x)& (int)(std::pow(2,32)-1)) | (static_cast<size_t>(vec.y) <<(8*4));

            return hash; 
        }
};

class cWorld{
    std::unordered_map<  VecInt2d, Chunk,Hasher,std::equal_to<VecInt2d>> m_Chunks;
    uint64_t m_Seed;
     std::map<std::string,int> m_TileNameMap;

    public:
    void operator()( std::map<std::string,int> TileNameMap,int Seed = 1) 
    {
        m_TileNameMap = TileNameMap;
        m_Seed = Seed;

    }
    cWorld& operator =(const cWorld& NewChunk)
    {
        m_Seed = NewChunk.m_Seed;
        m_TileNameMap =  NewChunk.m_TileNameMap;
        m_Chunks.clear();
        return *this;

    }
    cWorld(std::map<std::string,int> TileNameMap = std::map<std::string,int>(),int Seed = 1) : m_Seed(Seed),m_TileNameMap(TileNameMap)
    {}
    inline void LoadChunk(int x,int y)
    {
        std::array<std::array<std::vector<int>, CHUNK_SIZE>, CHUNK_SIZE> a;
        for (auto & x:a)
        {
            for (auto &y:x)
            {
                y.push_back(m_TileNameMap["GRASS"]);
            }
        }
        std::minstd_rand RandEngine(m_Seed ^ x+(y<<(int)(pow(2,32)-1)));
        std::uniform_int_distribution<int> TreeDistribution(1,254);
        
        auto CustomRand = std::bind(TreeDistribution,RandEngine);

        int Iterations = int(256*64) ;

        for (int i = 0; i<Iterations; i++) 
        {
            auto TreeX = CustomRand();
            auto TreeY = CustomRand();
            auto Tree = m_TileNameMap["TREE"];
            if ( a[TreeX-1][TreeY-1].back() != Tree && a[TreeX][TreeY-1].back() != Tree && a[TreeX+1][TreeY-1].back() != Tree &&
                 a[TreeX-1][TreeY].back() != Tree                                     && a[TreeX+1][TreeY].back() != Tree &&
                 a[TreeX-1][TreeY+1].back() != Tree && a[TreeX][TreeY+1].back() != Tree && a[TreeX+1][TreeY+1].back() != Tree
                    )
            {
                a[TreeX][TreeY].push_back(m_TileNameMap["TREE"]);
            }
        }
          //  a.fill({{std::vector<int>(1,m_TileNameMap["GRASS"])}});
            m_Chunks[{x,y}] = a ;
            
            
    }
    inline Chunk &GetChunk(int x, int y)
    {
         if (m_Chunks.find({x,y}) == m_Chunks.end())
            LoadChunk(x,y);     
        return m_Chunks[{x,y}];
 
    }

    inline std::vector<int> &GetTileStackAt(int x, int y)
    {
        int ChunkX = x/CHUNK_SIZE;
        int ChunkY = y/CHUNK_SIZE;
        int TileStackX = x%CHUNK_SIZE;
        int TileStackY = y%CHUNK_SIZE;
      
        return GetChunk(ChunkX,ChunkY)[TileStackX][TileStackY];
    }
};

//
// class cWorld
// {
//     
//     // std::unordered_map<std::pair<int,itn>
//     cChunkPool m_Chunks;
//     std::vector<int> DefaultTileStack;
//     int TileSize = 16;
//     int LenghtOfSide = 1024;
//
// public:
//     // cManagersManager *ManagersManager;
//
//     std::vector<int> &GetTileStackAt(int x, int y)
//     {
//        if (0 <= x && x < LenghtOfSide && 0 <= y && y < LenghtOfSide)
//             
//             return  m_Chunks.GetTileStackAt(x,y);
//        else
//             return DefaultTileStack;
//     }
//
//     void GenerateNewWorld(std::map<std::string, int> &TileNameMap, int LenghtOfSideOfTerrain = 1024, int Seed = 1)
//     {
//         m_Chunks = cChunkPool(TileNameMap,Seed);
//         LenghtOfSide = LenghtOfSideOfTerrain;
//         
//         DefaultTileStack.resize(1, TileNameMap["GRASS"]);
//     }
//
//     auto GetTileSize()
//     {
//         return TileSize;
//     }
//
//     void SetTileSize(int TS)
//     {
//         TileSize = TS;
//     }
//
//
//     // bool isTileStackColisiveAt(int x, int y)
//     // {
//     //     if (0 < x && x < LenghtOfSide && 0 < y && y < LenghtOfSide)
//     //         return ManagersManager->isTileStackColisive(GetTileStackAt(x, y));
//     //     else
//     //         return true;
//     // }
//     // bool isPlayerAbleToDeconstructTopTileAt(int x, int y)
//     // {
//     //     return ManagersManager->IsPlayerAbleToDeconstructTile(GetTileStackAt(x, y).back());
//     // }
//     // void DeconstructTopTileAt(int x, int y)
//     // {
//     //     int DeconstructedTile = GetTileStackAt(x, y).back();
//     //     ManagersManager->PlayerDeconstructedTile(DeconstructedTile);
//     //     if( DeconstructedTile <0 )
//     //         ManagersManager->GetTileManager()->DeleteDynamicTile(DeconstructedTile);
//     //     GetTileStackAt(x, y).pop_back();
//     // }
//     // void ConstructTileAtTopOf(int x, int y, int TileID)
//     // {
//     //     if( ManagersManager->GetTileManager()->IsTileDynamic(TileID))
//     //     {
//     //         GetTileStackAt(x, y).push_back(ManagersManager->GetTileManager()->GetNewDynamicTile(TileID));
//     //     }
//     //     else
//     //         GetTileStackAt(x, y).push_back(TileID);
//     // }
// };
