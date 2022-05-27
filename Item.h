#pragma once
#include "Tile.h"
#include <map>
#include <string>
#include <iostream>
#include <vector>
class Item
{

protected:
    std::string Type = "GenericTile";
    std::string UserVisibleName = "NULL";
    std::string IdentifyingName = "NULL";
    
    int ID = 0;
    int TextureID = 0;
    std::string TextureName;
public:
    Item(const std::map<std::string, int> &TextureNameMap, std::string tn = "black", std::string uvn = "NULL", std::string im ="NULL" )
    {
        TextureName = tn;
        TextureID = TextureNameMap.at(TextureName);
        UserVisibleName = uvn;
        IdentifyingName = im;
    }

    virtual int GetDamage()
    {
        return 0;
    }
    int GetTextureID()
    {
        return TextureID;
    }

    auto GetType()
    {
        return Type;
    }
    auto GetUserVisibleName()
    {
        return UserVisibleName;
    }

    auto GetIdentifyingName()
    {

        return IdentifyingName;
    }

};




class Gun : public Item
{
    std::string Type = "GUN";
    int Damage = 10;
    //   virtual Tile* GetBuildTile() override{};
public:
    virtual int GetDamage() override
    {
        return Damage;
    }
};

class BuildBlock : public Item
{
    std::string Type = "BUILD_BLOCK";
    using Item::Item;

};

struct ItemSlot
{

    int Quantity = 0;
    Item *ItemPtr = nullptr;

    ItemSlot(Item *IPtr = nullptr, int qt = 1)
    {
        Quantity = qt;
        if (IPtr != nullptr)
        {
            ItemPtr = IPtr;
        }
    }
};
