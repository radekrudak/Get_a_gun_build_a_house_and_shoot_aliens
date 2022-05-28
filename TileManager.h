#pragma once
#include <vector>
#include <memory>
#include <map>
#include <fstream>
#include <typeinfo>

#include "Tile.h"
#include "nlohmann/json.hpp"
using json = nlohmann::json;

struct sTileManager
{
    std::vector< std::unique_ptr<Tile> > vStaticTiles;
    std::vector< std::unique_ptr<Tile> > vDynamicTiles;
    std::map<std::string,int> TileNameMap;

    const auto &operator[](const int &i)
    {
        if (i >=0)
            return vStaticTiles[i];
        else 
            return vStaticTiles[i];
    }

    const auto &operator[](const std::string &i)
    {
        if (TileNameMap[i] >= 0)
            return vStaticTiles[TileNameMap[i]];
        else 
            return vDynamicTiles[TileNameMap[i]];
    }


    void LoadStaticTiles(std::map<std::string,int> TextureNameMap,std::string PathToTileFile = "assets/tiles.json")
    { 
        std::string JsonText;
        std::string line;
        std::ifstream JsonFile(PathToTileFile);

        while (std::getline(JsonFile, line))
        {
            JsonText.append(line);
            JsonText.append("\r\n");
        }

        // parse and serialize JSON
        json ParsedJson = json::parse(JsonText);

        for (auto i : ParsedJson.items())
        {
            // TODO: SOME ERROR CHECKING
            TileNameMap[i.key()] = vStaticTiles.size();
            
            vStaticTiles.push_back(std::unique_ptr<Tile>( 
                    new Tile(TextureNameMap,
                            vStaticTiles.size(),
                            static_cast<std::string> (i.value().value("TextureName","TextureMissing")),
                            static_cast <bool> (i.value().value("isColisive",false)),
                            static_cast <PositionOnTileStack>(i.value().value("PositionOnTileStack",1))                        
                               )));
            
        }
        /*
        for(const auto &i: vItems)
        {
            std::cout<< i->GetType()<<" "<<i->GetIdentifyingName()<<" "<<i->GetUserVisibleName()<<" "<<i->GetTextureID()<<" "<<std::endl;

        }*/

    }

    void ClearStaticTiles()
    {
        vStaticTiles.clear();
    }
    void ClearDynamicTiles()
    {
        vStaticTiles.clear();
    }


};