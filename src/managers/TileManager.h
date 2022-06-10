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
    std::vector<std::unique_ptr<Tile>> vTiles;
    std::vector<std::unique_ptr<Tile>> vDynamicTiles;
    std::vector<int> vBuildableTiles;
    std::map<std::string, int> TileNameMap;

    sTileManager()
    {
        vDynamicTiles.resize(1);
    }
    const auto &operator[](const int &i)
    {
        if (i >= 0)
            return vTiles[i];
        else
            return vDynamicTiles[i*-1];
    }

    const auto &operator[](const std::string &i)
    {
        if (TileNameMap[i] >= 0)
            return vTiles[TileNameMap[i]];
        else
            return vDynamicTiles[TileNameMap[i]];
    }

    void LoadStaticTiles(std::map<std::string, int> TextureNameMap, std::map<std::string, int> ItemNameMap, std::string PathToTileFile = "configs/tiles.json")
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
            TileNameMap[item.key()] = vTiles.size();
            if( !(item.value().contains("isDynamic")) || item.value()["isDynamic"] == false)
                vTiles.push_back(std::unique_ptr<Tile>(
                    new Tile(TextureNameMap,
                            vTiles.size(),
                            static_cast<std::string>(item.value().value("TextureName", "TextureMissing")),
                            static_cast<bool>(item.value().value("isColisive", false)),
                            static_cast<PositionOnTileStack>(item.value().value("PositionOnTileStack", 1)),
                            item.key())));
            else 
                vTiles.push_back(
                    std::unique_ptr<DynamicTile>(
                    new DynamicTile(TextureNameMap,
                            vTiles.size(),
                            static_cast<std::string>(item.value().value("TextureName", "TextureMissing")),
                            static_cast<bool>(item.value().value("isColisive", false)),
                            static_cast<PositionOnTileStack>(item.value().value("PositionOnTileStack", 1)),
                            item.key())) );
            std::cout<<item.key()<<std::endl;
            if (item.value().contains("ItemsDroped"))
                for (const auto &ItemsDrioped : item.value()["ItemsDroped"].items())
                    vTiles.back()->AddItemsDroped(ItemNameMap[ItemsDrioped.key()], ItemsDrioped.value());

            if (item.value().contains("ItemsRequiredToConstruct"))
                for (const auto &ItemsRequired : item.value()["ItemsRequiredToConstruct"].items())
                    vTiles.back()->AddItemsRequiredToConstruct(ItemNameMap[ItemsRequired.key()], ItemsRequired.value());

            if (item.value().contains("ItemsRequiredToDeconstruct"))
                for (const auto &ItemsRequired : item.value()["ItemsRequiredToDeconstruct"].items())
                    vTiles.back()->AddItemsRequiredToDeconstruct(ItemNameMap[ItemsRequired.key()], ItemsRequired.value());
        }
        std::cout << "BuildableTiles:" << std::endl;
        for (int i = 0; i < vTiles.size(); i++)
        {
            if (vTiles[i]->GetItemsRequiredToConstruct().size() > 0)
            {
                vBuildableTiles.push_back(i);
                std::cout << i << " " << vTiles[i]->GetTileName() << std::endl;
            }
        }
    }

    void ClearStaticTiles()
    {
        vTiles.clear();
    }
    void ClearDynamicTiles()
    {
        vTiles.clear();
    }

    const auto &GetBuildableTiles()
    {
        return vBuildableTiles;
    }
    bool IsTileDynamic(int TileID)
    {
        return vTiles[TileID]->isDynamic();
    }
    auto GetNewDynamicTile(int TileTemplateID)
    {
        vDynamicTiles.push_back(std::unique_ptr<Tile>( new DynamicTile(*((DynamicTile*)vTiles[TileTemplateID].get()))));
        return (vDynamicTiles.size()-1)*-1;
    }
    void DeleteDynamicTile(int TileID)
    {   
        vDynamicTiles[TileID*-1].reset(nullptr);
    }
};