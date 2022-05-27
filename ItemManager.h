
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include "Item.h"
#include "nlohmann/json.hpp"
using json = nlohmann::json;

struct sItemManager
{
    std::vector<Item *> vItems;
    std::map<std::string, int> ItemNameMap;
    auto &operator[](const std::string &i)
    {
        return vItems[ItemNameMap[i]];
    }
    auto &operator[](const int &i)
    {
        return vItems[i];
    }

    void LoadItems(std::string path_to_item_file = "assets/items.json")
    {
        std::string json_text;
        std::string line;
        std::ifstream json_file (path_to_item_file);

        while (std::getline(json_file,line))
        {
            json_text.append(line);
            json_text.append("\r\n");
        }
        

        // parse and serialize JSON
        json j_complete = json::parse(json_text);

        for(auto i:j_complete.items())
        {
            std::cout<<i.key()<<" "<<i.value()<<std::endl;
            for(auto j:i.value().items())
                std::cout<<"    "<<j.key()<<" "<<j.value()<<std::endl;

        }


        //std::cout << typeid(static_cast<float>(j_complete["100"]["id"])).name() << "  "<<(static_cast<float>(j_complete["100"]["id"])*2.0)<<std::endl;
        

    }
};