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
public:
    std::vector <int> vItemsRequiredID;
    std::vector <int> vItemsRequiredQuantity;
    std::vector <int> vItemsGatheredID;
    std::vector <int> vItemsGatheredQuantity ;

protected:
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

    int GetTextureID()
    {
        return TextureID;
    }
    bool isColisive()
    {
        return isColide;
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

//#pragma once
//class TileTwo: public  Tile
//{
//
//    public:
//    TileTwo(int id =0, olc::Sprite *spr = nullptr, bool colisive=false)
//    {
//        ID = id;
//        isColide =colisive;
//
//        if (spr)
//        {
//            Sprite = spr;
//            Decal = new olc::Decal(Sprite);
//        }
//
//    }
//
//};
