#pragma once
#include "Item.h"
#include <string>
#include <map>
enum class PositionOnTileStack{

    dirt=0,
    floor = 1,
    wall=2,
    roof=3



};

//class Item;
using TZpos = PositionOnTileStack;
class Tile
{
protected:
    std::vector <ItemSlot> vItemsRequiredToBuild;
    std::vector <ItemSlot> vItemsDroped;

    int ID;
    PositionOnTileStack ZLevel; // 0 = dirt 1 = Floor 2= Wall 3= Roof
    std::string Name = "NULL";
    bool isColide =false;
    int TextureID =0;
    std::string TextureName;


public:
    Tile(const std::map<std::string,int> &TextureNameMap,int id =0,std::string TextureName =  "TextureMissing", bool colisive=false, PositionOnTileStack Zlvl = PositionOnTileStack::wall)
    {
        ID = id;
        isColide =colisive;
        ZLevel = Zlvl;
        TextureID = TextureNameMap.at(TextureName);

    }
    void AddItemsRequiredToBuild(int ItemID,int Quantity )
    {
        vItemsRequiredToBuild.push_back(ItemSlot(ItemID,Quantity));
    }
    void AddItemsRequiredToBuild(ItemSlot ItemToAdd )
    {
        vItemsRequiredToBuild.push_back(ItemToAdd);
    }

    void AddItemsDroped(int ItemID,int Quantity )
    {
        vItemsDroped.push_back(ItemSlot(ItemID,Quantity));
    }
    void AddItemsDroped(ItemSlot ItemToAdd )
    {
        vItemsDroped.push_back(ItemToAdd);
    }



    int GetTextureID()
    {
        return TextureID;
    }
    bool isColisive()
    {
        return isColide;
    }
    const auto &GetItemsRequiredToBuild()
    {
        return vItemsRequiredToBuild;
    }
    const auto &GetItemsDroped()
    {
        return vItemsDroped;
    }
    bool isColisivTileInIt( std::vector<Tile *> vTiless)
    {
        for(auto &i: vTiless)
        {
            if (i->isColisive())
                return true;
            else
                continue;
        }
        return false;
    }
    PositionOnTileStack GetZLevel()
    {
        return ZLevel;
    }
};
