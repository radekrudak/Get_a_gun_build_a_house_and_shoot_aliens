#include <vector>

class cWorld
{
    std::vector<std::vector<std::vector<int>>> vTerrain;
public:
    std::vector<int> &GetTilesAt(int x, int y)
    {
        return vTerrain[x][y];
    }

    void GenerateTerrain(std::map<std::string, int> &TileNameMap,int LenghtOfSide = 1024)
    {
        vTerrain.resize(LenghtOfSide,
                        std::vector<std::vector<int>>(LenghtOfSide, 
                                std::vector<int>(1, TileNameMap["GRASS"])));
        for (size_t x = 0; x < LenghtOfSide; x++)
        {

            for (size_t y = 0; y < LenghtOfSide; y++)
            {
               if (rand()%100 <10) 
                  vTerrain[x][y].push_back(  TileNameMap["TREE"]  ) ;
            }
        }
    } 
    
};