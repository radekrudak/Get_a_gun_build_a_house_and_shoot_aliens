#pragma once
#include <vector>
#include <filesystem>
struct sTextureManager
{

    std::vector<olc::Sprite *> vSprites;
    std::vector<olc::Decal *> vDecals;
    std::map<std::string, int> TextureNameMap;

    auto &operator[](const std::string &i)
    {
        return vDecals[TextureNameMap[i]];
    }
    auto &operator[](const int &i)
    {
        return vDecals[i];
    }

    auto &GetSprite(const std::string &i)
    {
        return vSprites[TextureNameMap[i]];
    }
    auto &GetSprite(const int &i)
    {
        return vSprites[i];
    }
    std::map<std::string, int> LoadGraphics(std::string TexturePackPath = "assets/")
    {
        vSprites.clear();
        vDecals.clear();
        TextureNameMap.clear();
        std::string path = TexturePackPath + "tiles";

        for (const auto &entry : std::filesystem::directory_iterator(path))
        {

            std::string EntryPath = entry.path().string();
            std::string extension = EntryPath.substr(EntryPath.size() - 3);

            if (extension == "png")
            {

                std::cout << "Loading: " << EntryPath;
                vSprites.push_back(new olc::Sprite(EntryPath));
                vDecals.push_back(new olc::Decal(vSprites.back()));

                std::string FileName = EntryPath;
                while (FileName.find("/") != FileName.npos)
                {
                    FileName.erase(0, FileName.find("/") + 1);
                }

                FileName = FileName.substr(0, FileName.find("."));
                TextureNameMap[FileName] = vSprites.size() - 1;
                std::cout << "as: " << FileName << " " << (vSprites.size() - 1) << std::endl;
            }
        }

        path = TexturePackPath + "characters";

        for (const auto &entry : std::filesystem::directory_iterator(path))
        {

            std::string EntryPath = entry.path().string();
            std::string extension = EntryPath.substr(EntryPath.size() - 3);

            if (extension == "png")
            {

                std::cout << "Loading: " << EntryPath;
                vSprites.push_back(new olc::Sprite(EntryPath));
                vDecals.push_back(new olc::Decal(vSprites.back()));

                std::string FileName = EntryPath;
                while (FileName.find("/") != FileName.npos)
                {
                    FileName.erase(0, FileName.find("/") + 1);
                }

                FileName = FileName.substr(0, FileName.find("."));
                TextureNameMap[FileName] = vSprites.size() - 1;
                std::cout << " as: \"" << FileName << "\" Texture's ID: " << (vSprites.size() - 1) << std::endl;
            }
        }

        return TextureNameMap;
    }
};