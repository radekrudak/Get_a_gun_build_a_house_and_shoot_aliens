#pragma once
#include "Game.h"
#include <vector>
#include <filesystem>


std::map<std::string,int> LoadGraphics(    std::vector<olc::Sprite*> &vSprites, std::vector<olc::Decal*> &vDecals,std::string TexturePackPath = "assets/")
{
    vSprites.clear();
    vDecals.clear();

    std::string path = TexturePackPath+"tiles";
    std::map<std::string,int> FileMap;

    for (const auto & entry : std::filesystem::directory_iterator(path))
    {    
        
        std::string EntryPath =entry.path().string();
        std::string extension = EntryPath.substr(EntryPath.size()-3);
       
        if(extension == "png")
        {

            std::cout<<"Loading: " << EntryPath;
            vSprites.push_back(new olc::Sprite(EntryPath));
            vDecals.push_back(new olc::Decal(vSprites.back()));
            
            std::string FileName =EntryPath;
            while (FileName.find("/") != FileName.npos )
            {
                FileName.erase(0,FileName.find("/")+1);
            }
            
            FileName = FileName.substr(0,FileName.find("."));
            FileMap[FileName] = vSprites.size()-1;
            std::cout<<"as: " << FileName <<" "<<(vSprites.size()-1)<< std::endl;

        }


    }

    path = TexturePackPath+"characters";

    for (const auto & entry : std::filesystem::directory_iterator(path))
    {    
        
        std::string EntryPath =entry.path().string();
        std::string extension = EntryPath.substr(EntryPath.size()-3);
       
        if(extension == "png")
        {

            std::cout<<"Loading: " << EntryPath;
            vSprites.push_back(new olc::Sprite(EntryPath));
            vDecals.push_back(new olc::Decal(vSprites.back()));
            
            std::string FileName =EntryPath;
            while (FileName.find("/") != FileName.npos )
            {
                FileName.erase(0,FileName.find("/")+1);
            }
            
            FileName = FileName.substr(0,FileName.find("."));
            FileMap[FileName] = vSprites.size()-1;
            std::cout<<" as: " << FileName <<" "<<(vSprites.size()-1)<< std::endl;

        }


    }


    return FileMap;
}