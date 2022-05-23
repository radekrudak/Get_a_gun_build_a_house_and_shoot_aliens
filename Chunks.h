#pragma once
#include <map>
#include <vector>
#include <iostream>
template<typename T>
class Chunks
{

    int CenterChunkX;
    int CenterChunkY;

    int PreviousCenterChunkX;
    int PreviousCenterChunkY;

    int ChunkingDistance;
    int ChunkSize;

    bool first_time = true;
    std::map<std::pair< int, int>, std::vector<std::vector< T >>  > mChunkMap;

    std::vector<std::vector< T >> LoadChunk(int XX, int YY)
    {
        std::vector<std::vector< T >>  ret;

        ret.resize(ChunkSize);
        for(int x=0; x<ChunkSize; x++)
        {
            ret[x].resize(ChunkSize);
        }

        for(int x=0; x<ChunkSize; x++)
        {
            for(int y=0; y<ChunkSize; y++)
            {


                ret[x][y].push_back(Tile(0));
                if(rand() %100 < 25  )
                {
                    ret[x][y].push_back(1);
                }


            }
        }

        return ret;
    }

public:
    Chunks(int x,int y,int CS, int CD)
    {


        ChunkingDistance = CD;
        ChunkSize = CS;

        CenterChunkX =x/ChunkSize;
        CenterChunkY =y/ChunkSize;

        for(int x= CenterChunkX-ChunkingDistance; x<CenterChunkX+ChunkingDistance+1; x++)
        {
            for(int y=CenterChunkY-ChunkingDistance ; y<CenterChunkY+ChunkingDistance+1; y++)
            {
                mChunkMap[std::make_pair(x,y)] = LoadChunk(x,y);

            }
        }



    }
    T& GetElement( int x, int y)
    {

        int ChunkAddrsX = x/ChunkSize;
        int ChunkAddrsY = y/ChunkSize;


        constexpr int test = 5;

        if(mChunkMap.find(std::make_pair(ChunkAddrsX,ChunkAddrsY)) != mChunkMap.end() )
        {
            //std::cout<< x<<" "<< y<<" " <<ChunkAddrsX<<" "<<ChunkAddrsY<<" "<< x-ChunkAddrsX<< " "<<y-ChunkAddrsY<<" "<<abs(x-ChunkAddrsX) << " "<< abs(y-ChunkAddrsY)<<std::endl;
            return mChunkMap[std::make_pair(ChunkAddrsX,ChunkAddrsY)][abs(x-(ChunkAddrsX*ChunkSize))][abs(y-(ChunkAddrsY*ChunkSize))];
        }


    }

    void ReLoadChunks(int x, int y)
    {
        PreviousCenterChunkX = CenterChunkX;
        PreviousCenterChunkY = CenterChunkY;

        CenterChunkX = x/ChunkSize;
        CenterChunkY = y/ChunkSize;
        if(CenterChunkX != PreviousCenterChunkX || CenterChunkY != PreviousCenterChunkY)
        {
            mChunkMap.clear();
            for(int x= CenterChunkX-ChunkingDistance; x<CenterChunkX+ChunkingDistance+1; x++)
            {
                for(int y=CenterChunkY-ChunkingDistance ; y<CenterChunkY+ChunkingDistance+1; y++)
                {
                    mChunkMap[std::make_pair(x,y)] = LoadChunk(x,y);
                }
            }
        }
    }

};
