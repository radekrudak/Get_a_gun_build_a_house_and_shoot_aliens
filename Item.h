#pragma once
#include "Tile.h"
#include <map>
#include <string>

class Item
{

protected:
    std::string Type = "NULL";
    std::string Name = "NULL";
    int ID = 0;
    int Quantity;
    int TextureID =0;
public:
    Item(const std::map<std::string,int> &TextureNameMap,std::string TextureName =0)
    {
        TextureID = TextureNameMap.at(TextureName);
    }

    virtual int GetDamage()
    {
        return 0;
    }
    int GetTextureID()
    {
        return TextureID;
    }
};

class Gun: public Item
{
    int Damage =10;
//   virtual Tile* GetBuildTile() override{};
public:
    virtual int GetDamage() override
    {
        return Damage;
    }

};

class BuildBlock: public Item
{

    using Item::Item;

//    Item(olc::Sprite *spr, olc::Decal *Dec): Sprite(spr), Decal(Dec)
//    {
//    ;
//    }
//    virtual Tile* GetBuildTile() override
//    {
//        return BuildTile;
//    }

};

struct ItemSlot
{


    int Quantity=0;
    Item *ItemPtr=nullptr;

    ItemSlot(Item *IPtr=nullptr,int qt=1)
    {
        Quantity = qt;
        if (IPtr!= nullptr)
        {
            ItemPtr = IPtr;
        }
    }


};
