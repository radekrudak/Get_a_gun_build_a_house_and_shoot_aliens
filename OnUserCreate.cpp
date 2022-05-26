
#include "Game.h"
#include "LoadGraphics.h"
#include <functional>
#include <iostream>
#include <map>
#include <vector>

bool GameJam::OnUserCreate()
{

        Clear(olc::BLACK);
        vTileMap.reserve(MapSize);
        FileMap = LoadGraphics(vSprites,vDecals);
        // Tilemapp = new Tile[1024]();
        //Enemy test(vTileMap,vTiles);
        lNight = CreateLayer();
        lPlayer = CreateLayer();
        lGround = CreateLayer();
        //sprite loading
        sMT = new olc::Sprite("./assets/tiles/TextureMissing.png");
        Tile *defaultTile = new Tile(FileMap);
        for(auto &i:vTiles)
        {
            i = defaultTile;
        }
        sPGELogo =    new olc::Sprite("./assets/PGELogo.png");
        sGrass =      new olc::Sprite("./assets/tiles/Grass.png");
        sTest =       new olc::Sprite ("./assets/tiles/TestTile.png");
        sMC =         new olc::Sprite ("./assets/characters/mc.png");
        sWood =       new olc::Sprite ("./assets/tiles/WoodAlpha.png");
        sWoodWall =   new olc::Sprite ("./assets/tiles/WoodWall.png");
        sWoodFloor =  new olc::Sprite ("./assets/tiles/WoodFloor.png");
        sEnemy =      new olc::Sprite ("./assets/characters/Enemy.png");
        sNight =      new olc::Sprite ("./assets/tiles/black.png");
        sMoonAndSun = new olc::Sprite("./assets/tiles/MoonandSun.png");

        dPGELogo =     new olc::Decal(sPGELogo);
        dWood =       new olc::Decal (sWood);
        dMoonAndSun = new olc::Decal(sMoonAndSun);
        dNight =      new olc::Decal (sNight);
        dMC =         new olc::Decal(sMC);

        vItems.push_back(new Item(sWood,dWood));
        vItems.push_back(new Item(sWood,dWood));

        vTiles.push_back( new Tile(FileMap,0,"Grass",false,TZpos::floor)); // grass

        vTiles.push_back(new Tile(FileMap,1,"WoodAlpha",true)); // Wood
        vTiles[1]->vItemsGathered.push_back(vItems[1]);
        std::cout<<vTiles[1]->vItemsGathered.back()<<std::endl;
        std::cout<<vTiles[1]->vItemsGathered.front()<<std::endl;
        vTiles[1]->vItemsGatheredQuantity.push_back(5);

        vTiles.push_back(new Tile(FileMap,2,"WoodWall",true)); // Wood wall
        vTiles[2]->vItemsRequiredQuantity.push_back(10);
        vTiles[2]->vItemsRequired.push_back(vItems[1]);
        vBuildableTiles.push_back(vTiles[2]);


        vTiles.push_back(new Tile(FileMap,3,"WoodFloor",false,TZpos::floor)); // WoodFloor

        vTiles.push_back(new Tile(FileMap,4,"black",false,TZpos::dirt)); // cley
       
        
        return true;


}