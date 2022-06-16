#pragma once
#include <map>
#include <string>
#include <iostream>
#include <vector>
class Item
{

protected:
    std::string m_Type = "GenericItem";
    std::string m_UserVisibleName = "NULL";
    std::string m_IdentifyingName = "NULL";
    
    int m_ID = 0;
    int m_TextureID = 0;
    std::string m_TextureName;
public:
    Item()
    {
        ;
    }
    
    Item(const std::map<std::string, int> &TextureNameMap, std::string tn = "black", std::string uvn = "NULL", std::string im ="NULL" )
    {
        m_TextureName = tn;
        m_TextureID = TextureNameMap.at(m_TextureName);
        m_UserVisibleName = uvn;
        m_IdentifyingName = im;
    }

    virtual int GetDamage()
    {
        return 0;
    }
    int GetTextureID()
    {
        return m_TextureID;
    }

    auto GetType()
    {
        return m_Type;
    }
    auto GetUserVisibleName()
    {
        return m_UserVisibleName;
    }

    auto GetIdentifyingName()
    {

        return m_IdentifyingName;
    }
    virtual bool IsFood()
    {
        return false;
    }
    virtual int GetHealthGainedAfterConsuption()
    {
        return 0;
    }
};

class Food : public Item
{
    using Item::Item;    
    
    int m_HealthGained =0;
    int m_HungerEreased =0;

    public:

    void SetFoodSpecyficStats(int Health, int Hunger )
    {
        m_HealthGained = Health;
        m_HungerEreased = Hunger;
    }

    virtual int GetHealthGainedAfterConsuption() override
    {
        return m_HealthGained;
    }

    virtual bool IsFood() override
    {
        return true;
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
    size_t size()
    {
        return vItemsInInventory.size(); 
    }
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
