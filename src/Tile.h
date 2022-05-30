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
    std::vector <ItemSlot> vItemsRequiredToConstruct;
    std::vector <ItemSlot> vItemsDroped;
    std::vector <ItemSlot> vItemsRequiredToDeconstruct;
    int ID;
    PositionOnTileStack ZLevel; // 0 = dirt 1 = Floor 2= Wall 3= Roof
    std::string Name = "NULL";
    bool isColide =false;
    int TextureID =0;
    std::string TextureName;


public:
    Tile(const std::map<std::string,int> &TextureNameMap,int id =0,std::string TextureName =  "TextureMissing", bool colisive=false, PositionOnTileStack Zlvl = PositionOnTileStack::wall,std::string TileName = "NULL")
    {
        ID = id;
        isColide =colisive;
        ZLevel = Zlvl;
        TextureID = TextureNameMap.at(TextureName);
        Name =TileName;

    }
    void AddItemsRequiredToConstruct(int ItemID,int Quantity )
    {
        vItemsRequiredToConstruct.push_back(ItemSlot(ItemID,Quantity));
    }
    void AddItemsRequiredToConstruct(ItemSlot ItemToAdd )
    {
        vItemsRequiredToConstruct.push_back(ItemToAdd);
    }

    void AddItemsRequiredToDeconstruct(int ItemID,int Quantity )
    {
        vItemsRequiredToDeconstruct.push_back(ItemSlot(ItemID,Quantity));
    }
    void AddItemsRequiredToDeconstruct(ItemSlot ItemToAdd )
    {
        vItemsRequiredToConstruct.push_back(ItemToAdd);
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
    const auto &GetItemsRequiredToConstruct()
    {
        return vItemsRequiredToConstruct;
    }
    const auto &GetItemsRequiredToDeconstruct()
    {
        return vItemsRequiredToDeconstruct;
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
