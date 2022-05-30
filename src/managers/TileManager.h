#pragma once
#include <vector>
#include <memory>
#include <map>
#include <fstream>
#include <typeinfo>

#include "../Tile.h"
#include "../nlohmann/json.hpp"
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


    void LoadStaticTiles(std::map<std::string,int> TextureNameMap,std::map<std::string,int>ItemNameMap,std::string PathToTileFile = "configs/tiles.json")
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

        for (const auto &item : ParsedJson.items())
        {
            // TODO: SOME ERROR CHECKING
            TileNameMap[item.key()] = vStaticTiles.size();
            
            vStaticTiles.push_back(std::unique_ptr<Tile>( 
                    new Tile(TextureNameMap,
                            vStaticTiles.size(),
                            static_cast<std::string> (item.value().value("TextureName","TextureMissing")),
                            static_cast <bool> (item.value().value("isColisive",false)),
                            static_cast <PositionOnTileStack>(item.value().value("PositionOnTileStack",1))                        
                               )));
            
            if (item.value().contains("ItemsDroped"))
                for (const auto &ItemsDrioped: item.value()["ItemsDroped"].items())
                    vStaticTiles.back()->AddItemsDroped( ItemNameMap[ItemsDrioped.key()]  ,ItemsDrioped.value());
            
            if (item.value().contains("ItemsRequiredToBuild"))
                for (const auto &ItemsRequired: item.value()["ItemsRequiredToBuild"].items())
                    vStaticTiles.back()->AddItemsRequiredToBuild( ItemNameMap[ItemsRequired.key()]  ,ItemsRequired.value());
        }
        

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