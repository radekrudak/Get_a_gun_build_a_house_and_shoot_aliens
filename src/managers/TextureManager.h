#pragma once
#include <vector>
#include <filesystem>
#include <memory>
#include "../olcPixelGameEngine.h"
struct sTextureManager
{

    std::vector<std::unique_ptr<olc::Sprite>> vSprites;
    std::vector<std::unique_ptr<olc::Decal>> vDecals;
    std::map<std::string, int> TextureNameMap;

    const auto operator[](const std::string &i)
    {
        return vDecals[TextureNameMap[i]].get();
    }
    const auto operator[](const int &i)
    {
        return vDecals[i].get();
    }

    auto &GetSprite(const std::string &i)
    {
        return vSprites[TextureNameMap[i]];
    }
    auto &GetSprite(const int &i)
    {
        return vSprites[i];
    }
    std::map<std::string, int> LoadGraphics(std::string TexturePackPath = "TexturePacks/Default/")
    {


        // Load files .png in given folder
        std::string path = TexturePackPath;
        std::cout << std::endl;
        for (const auto &entry : std::filesystem::directory_iterator(path))
        {

            std::string EntryPath = entry.path().string();
            std::string extension = EntryPath.substr(EntryPath.size() - 3);

            if (extension == "png")
            {

                std::cout << "Loading: " << EntryPath;
                vSprites.push_back(std::unique_ptr<olc::Sprite>(new olc::Sprite(EntryPath)));
                vDecals.push_back(std::unique_ptr<olc::Decal>(new olc::Decal(vSprites.back().get())));

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
        //recursevly get all subdirectories in directory, and call LoadGraphics with path to each directory as argument
        for (auto &p : std::filesystem::recursive_directory_iterator(path))
        {
            if (p.is_directory())
                LoadGraphics(p.path().string());
        }
        return TextureNameMap;
    }
};