
#include <vector>
#include <map>
#include <string>
#include <fstream>

#include "Item.h"
#include "nlohmann/json.hpp"
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

    void LoadItems(const std::map<std::string,int> &TextureNameMap,std::string path_to_item_file = "assets/items.json")
    {
        std::string json_text;
        std::string line;
        std::ifstream json_file(path_to_item_file);

        while (std::getline(json_file, line))
        {
            json_text.append(line);
            json_text.append("\r\n");
        }

        // parse and serialize JSON
        json j_complete = json::parse(json_text);

        for (auto i : j_complete.items())
        {
            // TODO: SOME ERROR CHECKING
            std::cout << i.key() << " " << i.value() << std::endl;
            ItemNameMap[i.key()] = vItems.size();
            vItems.push_back(std::unique_ptr<Item>( 
                    new Item(TextureNameMap,
                             i.value()["TextureName"],
                             i.value()["UserVisibleName"],
                             i.key()


            )));
            
        }
        for(const auto &i: vItems)
        {
            std::cout<< i->GetType()<<" "<<i->GetIdentifyingName()<<" "<<i->GetUserVisibleName()<<" "<<i->GetTextureID()<<" "<<std::endl;

        }
        // std::cout << typeid(static_cast<float>(j_complete["100"]["id"])).name() << "  "<<(static_cast<float>(j_complete["100"]["id"])*2.0)<<std::endl;
    }
};