#pragma once
#include "Game.h"

void Game::GameStart()
{
  
        ManagersManager.init(&ItemManager,&TileManager,&TextureManager,&EntityManager,&UIManager,&WorldManager);

        TextureManager.LoadGraphics();
        ItemManager.LoadItems(TextureManager.TextureNameMap);
        TileManager.LoadStaticTiles(TextureManager.TextureNameMap,ItemManager.ItemNameMap);

        // ComandLineThread = std::thread(ComandLineTest,0);
}

