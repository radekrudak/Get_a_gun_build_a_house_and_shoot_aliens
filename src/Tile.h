#pragma once
#include "Item.h"
#include <string>
#include <map>
#include <vector>
enum class PositionOnTileStack
{
    dirt = 0,
    floor = 1,
    wall = 2,
    roof = 3
};

// class Item;
using TZpos = PositionOnTileStack;
class Tile
{
protected:
    std::vector<ItemSlot> vItemsRequiredToConstruct;
    std::vector<ItemSlot> vItemsDroped;
    std::vector<ItemSlot> vItemsRequiredToDeconstruct;
    int ID;
    PositionOnTileStack ZLevel; // 0 = dirt 1 = Floor 2= Wall 3= Roof
    std::string Name = "NULL";
    std::string m_Type = "STATIC_TILE";
    bool isColide = false;
    int TextureID = 0;
    std::string TextureName;

public:
    Tile()
    {
        ;
    }
    Tile(const std::map<std::string, int> &TextureNameMap, int id = 0, std::string TextureName = "TextureMissing", bool colisive = false, PositionOnTileStack Zlvl = PositionOnTileStack::wall, std::string TileName = "NULL")
    {
        ID = id;
        isColide = colisive;
        ZLevel = Zlvl;
        TextureID = TextureNameMap.at(TextureName);
        Name = TileName;
    }
    auto GetType()
    {
        return m_Type;
    }
    virtual void Update()
    {
        ;
    }
    const auto GetTileName() const
    {
        return Name;
    }
    void AddItemsRequiredToConstruct(int ItemID, int Quantity)
    {
        vItemsRequiredToConstruct.push_back(ItemSlot(ItemID, Quantity));
    }
    void AddItemsRequiredToConstruct(ItemSlot ItemToAdd)
    {
        vItemsRequiredToConstruct.push_back(ItemToAdd);
    }

    void AddItemsRequiredToDeconstruct(int ItemID, int Quantity)
    {
        vItemsRequiredToDeconstruct.push_back(ItemSlot(ItemID, Quantity));
    }
    void AddItemsRequiredToDeconstruct(ItemSlot ItemToAdd)
    {
        vItemsRequiredToConstruct.push_back(ItemToAdd);
    }

    void AddItemsDroped(int ItemID, int Quantity)
    {
        vItemsDroped.push_back(ItemSlot(ItemID, Quantity));
    }
    void AddItemsDroped(ItemSlot ItemToAdd)
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
    bool isColisivTileInIt(std::vector<Tile *> vTiless)
    {
        for (auto &i : vTiless)
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
    virtual bool isDynamic()
    {
        return false;
    }
};
class DynamicTile : public Tile
{
    using Tile::Tile;

protected:
    std::vector<uint64_t> m_vTimers;
    std::vector<uint64_t> m_vImerResetValues;
    std::vector<int> m_TextureIDs;

public:
    DynamicTile(const std::map<std::string, int> &TextureNameMap,
                int id, const std::vector<std::string> &TextureNames,
                bool colisive = false, PositionOnTileStack Zlvl = PositionOnTileStack::wall, std::string TileName = "NULL")
    {
        m_Type = "DYNAMIC_TILE";
        ID = id;
        isColide = colisive;
        ZLevel = Zlvl;
        TextureID = TextureNameMap.at(TextureName);
        Name = TileName;

        ID = id;
        isColide = colisive;
        ZLevel = Zlvl;
        Name = TileName;
        for (auto &i : TextureNames)
        {
            if (TextureNameMap.find(i) != TextureNameMap.end())
                m_TextureIDs.push_back(TextureNameMap.at(i));
            else
                m_TextureIDs.push_back(TextureNameMap.at("TextureMissing"));
        }
        TextureID = m_TextureIDs.front();
    }
    DynamicTile(DynamicTile &TileTemplate)
    {
        m_Type = "DYNAMIC_TILE";
        ID = TileTemplate.ID;
        isColide = TileTemplate.isColide;
        ZLevel = TileTemplate.ZLevel;
        TextureID = TileTemplate.TextureID;
        Name = TileTemplate.Name;
        vItemsDroped = TileTemplate.vItemsDroped;
        vItemsRequiredToConstruct = TileTemplate.vItemsRequiredToConstruct;
        vItemsRequiredToDeconstruct = TileTemplate.vItemsRequiredToDeconstruct;
    }
    virtual bool isDynamic()
    {
        return true;
    }
};

class PlantTile : public DynamicTile
{

    uint64_t m_PlantGrowthTimer = 0;
    uint64_t m_PlantGrowthTime = 0;
    std::vector<ItemSlot> m_vItemsHarvested;
    bool isPlantReadyToHarvest = false;

public:
    using DynamicTile::DynamicTile;
    PlantTile(const std::map<std::string, int> &TextureNameMap,
              int id, const std::vector<std::string> &TextureNames,
              bool colisive = false, PositionOnTileStack Zlvl = PositionOnTileStack::wall,
              std::string TileName = "NULL", uint64_t PlantGrowthTime = 100)
    {
        m_Type = "PLANT_TILE";
        ID = id;
        isColide = colisive;
        ZLevel = Zlvl;
        Name = TileName;
        for (auto &i : TextureNames)
        {
            if (TextureNameMap.find(i) != TextureNameMap.end())
                m_TextureIDs.push_back(TextureNameMap.at(i));
            else
                m_TextureIDs.push_back(TextureNameMap.at("TextureMissing"));
        }
        TextureID = m_TextureIDs.front();
        m_PlantGrowthTime = PlantGrowthTime;
        m_PlantGrowthTimer = 0;
        isPlantReadyToHarvest = false;
    }

    PlantTile(PlantTile &TileTemplate)
    {
        m_Type = "PLANT_TILE";
        ID = TileTemplate.ID;
        isColide = TileTemplate.isColide;
        ZLevel = TileTemplate.ZLevel;
        m_TextureIDs = TileTemplate.m_TextureIDs;
        TextureID = TileTemplate.TextureID;
        Name = TileTemplate.Name;
        m_vItemsHarvested = TileTemplate.vItemsDroped;
        vItemsDroped.clear();
        m_PlantGrowthTime = TileTemplate.m_PlantGrowthTime;
        vItemsRequiredToConstruct = TileTemplate.vItemsRequiredToConstruct;
        vItemsRequiredToDeconstruct = TileTemplate.vItemsRequiredToDeconstruct;
    }
    void Update() override
    {
        if (isPlantReadyToHarvest == false)
        {
            m_PlantGrowthTimer++;

            if (m_PlantGrowthTimer >= m_PlantGrowthTime)
            {

                isPlantReadyToHarvest = true;
                vItemsDroped = m_vItemsHarvested;
            }
            else
            {
                float PlantGrowthStage = static_cast<float>(m_PlantGrowthTimer) / static_cast<float>(m_PlantGrowthTime) * static_cast<float>(m_TextureIDs.size());

                TextureID = m_TextureIDs[static_cast<int>(PlantGrowthStage + 0.5f)];
            }
        }
    }
};
