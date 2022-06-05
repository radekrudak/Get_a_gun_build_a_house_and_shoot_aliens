#include "../olcPixelGameEngineBackend.h"
#include <functional>
#include <iostream>
#include <map>
#include <vector>

bool olcPixelGameEngineBackend::OnUserCreate()
{

        Clear(olc::GREY);
        //vTileMap.reserve(MapSize);
        ManagersManager.init(&ItemManager,&TileManager,&TextureManager,&EntityManager,&UIManager);

        TextureManager.LoadGraphics();
        ItemManager.LoadItems(TextureManager.TextureNameMap);
        TileManager.LoadStaticTiles(TextureManager.TextureNameMap,ItemManager.ItemNameMap);
        World.ManagersManager = &ManagersManager;

        lNight = CreateLayer();
        lPlayer = CreateLayer();
        lGround = CreateLayer();
        
        //sprite loading
        sMT = new olc::Sprite("./assets/tiles/TextureMissing.png");
        Tile *defaultTile = new Tile(TextureManager.TextureNameMap);
        sNight =      new olc::Sprite ("./assets/tiles/black.png");
        sMoonAndSun = new olc::Sprite("./assets/tiles/MoonandSun.png");
        dMoonAndSun = new olc::Decal(sMoonAndSun);
        dNight =      new olc::Decal (sNight);
        OlcPopUpMenu = std::make_unique<olc::popup::Menu>();
        (*OlcPopUpMenu)["MainMenu"].SetTable(1,2);
        (*OlcPopUpMenu)["MainMenu"]["New Game"].SetID(1);
        // (*OlcPopUpMenu)["MainMenu"]["Load Game"].SetTable(1,2);
        // (*OlcPopUpMenu)["MainMenu"]["Load Game"]["Map1"].SetID(2);
        // (*OlcPopUpMenu)["MainMenu"]["Load Game"]["Map2"].SetID(3);
        (*OlcPopUpMenu).Build();
        olcPopUpManager.Open( &((*OlcPopUpMenu)["MainMenu"]) );
        return true;


}