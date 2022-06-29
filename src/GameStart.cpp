#include "Game.h"

void Game::GameStart()
{

        ComandLineDebugUtil.StartThread(this);
        ManagersManager.init(&ItemManager,&TileManager,&TextureManager,&EntityManager,&UIManager,&WorldManager,&TimeManager);

        TextureManager.LoadGraphics();
        ItemManager.LoadItems(TextureManager.TextureNameMap);
        TileManager.LoadStaticTiles(TextureManager.TextureNameMap,ItemManager.ItemNameMap);
        EntityManager.LoadEntites(TextureManager.TextureNameMap,TimeManager.GetPtrToWorldTime());
        // ComandLineThread = std::thread(ComandLineTest,0);
}

