#pragma once
#include "Tile.h"
#include <map>
#include <string>
#include <iostream>
#include <vector>
class Item
{

protected:
    std::string Type = "GenericItem";
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
    ItemSlot (int ID,int Q):ItemID(ID),Quantity(Q) {}
    int ItemID =0;
    int Quantity = 0;

};

class  cInventory{
    ItemSlot NullItem = {0,0};
    std::vector<ItemSlot> vItemsInInventory;
    ItemSlot ItemEquiped = NullItem;
public:
    auto begin()
    {
        return vItemsInInventory.begin();
    }
    auto end()
    {
        return vItemsInInventory.end();
    }
    cInventory()
    {
        vItemsInInventory.push_back(NullItem);
    }
    void clear()
    {
        NullItem = {0,0};
        vItemsInInventory =std::vector<ItemSlot> (1,NullItem);
        ItemEquiped = NullItem;
    }
    ItemSlot &operator[](const int &i)
    {
        return vItemsInInventory[i];
    }
    bool IsEnoughItems(ItemSlot SearchedItem)
    {

        for (auto &i : vItemsInInventory)
        {
            if (i.ItemID == SearchedItem.ItemID && SearchedItem.Quantity <= i.Quantity)
            {
                return true;
            }
        }
        return false;
    }
    ItemSlot &FindItemInInventory(int SearchedItemID)
    {

        for (auto &i : vItemsInInventory)
        {
            if (i.ItemID == SearchedItemID)
            {
                return i;
            }
        }
        return NullItem;
    }

    void PickUpItem(ItemSlot AddedItem)
    {

        if(&FindItemInInventory(AddedItem.ItemID) == &NullItem)
        {
            vItemsInInventory.push_back(AddedItem);
        }
        else
        {
            FindItemInInventory(AddedItem.ItemID).Quantity+=AddedItem.Quantity;
        }
    }

    bool isEmpty()
    {
        return !(vItemsInInventory.size()-1);
    }

    void DecreaseItemQuantity(ItemSlot DecreasedItem)
    {
        FindItemInInventory(DecreasedItem.ItemID).Quantity -= DecreasedItem.Quantity;

        for (int i=1;i< vItemsInInventory.size();i++)
        {
            if (vItemsInInventory[i].Quantity <= 0)
            {
                vItemsInInventory.erase(vItemsInInventory.begin()+i);
            }
        }
        
    }


};