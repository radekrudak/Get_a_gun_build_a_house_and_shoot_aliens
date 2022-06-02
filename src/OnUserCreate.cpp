
#include "Game.h"
#include <functional>
#include <iostream>
#include <map>
#include <vector>

bool GameJam::OnUserCreate()
{

        Clear(olc::BLACK);
        //vTileMap.reserve(MapSize);
        ManagersManager.init(&ItemManager,&TileManager,&TextureManager,&EntityManager,&UIManager);

        TextureManager.LoadGraphics();
        ItemManager.LoadItems(TextureManager.TextureNameMap);
        TileManager.LoadStaticTiles(TextureManager.TextureNameMap,ItemManager.ItemNameMap);
        World.ManagersManager = &ManagersManager;
        // Tilemapp = new Tile[1024]();
        //Enemy test(vTileMap,vTiles);
        lNight = CreateLayer();
        lPlayer = CreateLayer();
        lGround = CreateLayer();
        //sprite loading
        sMT = new olc::Sprite("./assets/tiles/TextureMissing.png");
        Tile *defaultTile = new Tile(TextureManager.TextureNameMap);
        /*for(auto &i:vTiles)
        {
            i = defaultTile;
        }
        */


        sNight =      new olc::Sprite ("./assets/tiles/black.png");
        sMoonAndSun = new olc::Sprite("./assets/tiles/MoonandSun.png");


        dMoonAndSun = new olc::Decal(sMoonAndSun);
        dNight =      new olc::Decal (sNight);


        
        return true;


}