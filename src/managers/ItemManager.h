
#include <vector>
#include <map>
#include <string>
#include <fstream>

#include "../Item.h"
#include "../nlohmann/json.hpp"
using json = nlohmann::json;

struct sItemManager
{
    std::vector<std::unique_ptr<Item>> vItems;
    std::map<std::string, int> ItemNameMap;
    auto &operator[](const std::string &i)
    {
        return vItems[ItemNameMap[i]];
    }
    auto &operator[](const int &i)
    {
        return vItems[i];
    }

    void LoadItems(const std::map<std::string,int> &TextureNameMap,std::string PathToItemFile = "configs/items.json")
    {
        std::string JsonText;
        std::string line;
        std::ifstream JsonFile(PathToItemFile);

        while (std::getline(JsonFile, line))
        {
            JsonText.append(line);
            JsonText.append("\r\n");
        }
                // parse and serialize JSON
        json ParsedJson = json::parse(JsonText);


        //push back null item as element with index 0
       if (vItems.size() == 0)
       {
        ItemNameMap["NULL_ITEM"]=0;
        vItems.push_back( 
                std::unique_ptr<Item>( 
                    new Item(TextureNameMap,
                             "TextureMissing",
                             "You shouldn't see that !",
                             "NULL_ITEM"


            )));
        }

        for (auto i : ParsedJson.items())
        {
            // TODO: SOME ERROR CHECKING
            std::cout << i.key() << " " << i.value() << std::endl;
            
            ItemNameMap[i.key()] = vItems.size();
            auto item = i.value();
            if (item.contains("Eat"))
            {
                std::unique_ptr<Food> food (new Food( TextureNameMap,
                             i.value().value("TextureName","TextureMissing"),
                             i.value().value("UserVisibleName","You shouldn't see that !"),
                             i.key()
                             ));
                food->SetFoodSpecyficStats(item["Eat"].value("Health",0), item["Eat"].value("Hunger",0) );
                vItems.push_back(std::unique_ptr<Food>(food.release() )); 
            }
            else
                vItems.push_back(std::unique_ptr<Item>( 
                        
                    new Item(TextureNameMap,
                             i.value().value("TextureName","TextureMissing"),
                             i.value().value("UserVisibleName","You shouldn't see that !"),
                             i.key()


                )));
            
        }
        for(const auto &i: vItems)
        {
            std::cout<< i->GetType()<<" "<<i->GetIdentifyingName()<<" "<<i->GetUserVisibleName()<<" "<<i->GetTextureID()<<" "<<ItemNameMap[i->GetIdentifyingName()]<<" "<<std::endl;

        }
        // std::cout << typeid(static_cast<float>(j_complete["100"]["id"])).name() << "  "<<(static_cast<float>(j_complete["100"]["id"])*2.0)<<std::endl;
    }
};
