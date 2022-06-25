#include "Game.h"

void Game::GameStart()
{

        ComandLineDebugUtil.StartThread(this);
        ManagersManager.init(&ItemManager,&TileManager,&TextureManager,&EntityManager,&UIManager,&WorldManager);

        TextureManager.LoadGraphics();
        ItemManager.LoadItems(TextureManager.TextureNameMap);
        TileManager.LoadStaticTiles(TextureManager.TextureNameMap,ItemManager.ItemNameMap);
        EntityManager.LoadEntites(TextureManager.TextureNameMap);
        // ComandLineThread = std::thread(ComandLineTest,0);
}

