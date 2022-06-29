#include "Game.h"
#include <cstdint>

void Game::GameUpdate(float fElapsedTime)
{
    TimeManager.AddTime(static_cast<int64_t>(fElapsedTime*100));
    EntityManager.UpdateEntites();



    if (InputManager.GetGUIInput() == GUIInput::Eat)
    {
        int  EatenItemID = EntityManager.Player.GetInventory()[
            InputManager.GetGUIInputArgumet()
        ].ItemID;
        if(ItemManager[EatenItemID]->IsFood())
        {
            EntityManager.Player.GetInventory().DecreaseItemQuantity({EatenItemID,1});
            EntityManager.Player.AddHealth(ItemManager[EatenItemID]->GetHealthGainedAfterConsuption());
            std::cout<<"EatenItem"<<ItemManager[EatenItemID]->GetIdentifyingName()<<std::endl;

            UIManager.OpenWindow(WhichWindowIsOpen::NONE);
            InputManager.SetGUIInput(GUIInput::NoInput);
            InputManager.SetGUIInputArgument(0);
        }
         
    }

        if (UIManager.GetWhichWindowIsOpen() == WhichWindowIsOpen::BUILDABLE_TILES_SELECT && InputManager.GetGUIInputInt() >= 0)
    {
        EntityManager.Player.SetIDofTileToBuild(
            TileManager.GetBuildableTiles()[InputManager.GetGUIInputInt()]);
            std::cout<<"Selected tile to build: "<<(TileManager.GetBuildableTiles()[InputManager.GetGUIInputInt()])<<std::endl;

            UIManager.OpenWindow(WhichWindowIsOpen::NONE);
            InputManager.SetGUIInput(GUIInput::NoInput);
            InputManager.SetGUIInputArgument(0);
    }

    bool isMouseInReachDistance = (Distance(InputManager.GetMouseWorldPosytionX(), InputManager.GetMouseWorldPosytionY(),
                                            EntityManager.Player.GetX(), EntityManager.Player.GetY()) < EntityManager.Player.GetReachDistance());

    bool IsMouseStillPointingAtTheSameTile = ((floor(InputManager.GetMouseWorldPosytionX()) == floor(InputManager.GetPreviousMouseWorldPosytionX())) &&
                                              (floor(InputManager.GetMouseWorldPosytionY()) == floor(InputManager.GetPreviousMouseWorldPosytionY())));
    // construction handling
    if (InputManager[InputFlags::RightMouseButton])
    {
        if (isMouseInReachDistance)
        {
            if (IsMouseStillPointingAtTheSameTile && isMouseInReachDistance &&
                ManagersManager.IsPlayerAbleToConstructTile() &&
                ManagersManager.CanTileFitOnTileStack(WorldManager.GetTileStack(InputManager.GetMouseWorldPosytionX(), InputManager.GetMouseWorldPosytionY()), EntityManager.Player.GetIDofTileToBuild()))
            {

                UIManager.SetMouseText("Construction");
                UIManager.SetProgressBar(EntityManager.Player.GetConstructionProgress());

                bool didConstructionFinished = EntityManager.Player.ProgressConstruction(fElapsedTime);
                if (didConstructionFinished)
                {
                    ManagersManager.ConstructTileAtTopOf(InputManager.GetMouseWorldPosytionX(), InputManager.GetMouseWorldPosytionY(),
                                               EntityManager.Player.GetIDofTileToBuild());
                    ManagersManager.PlayerConstructedTile();
                    UIManager.SetMouseText("");
                    UIManager.SetProgressBar(0.0f);
                    EntityManager.Player.ResetConstructionProgress();
                }
            }
            else
            {
                UIManager.SetMouseText("");
                UIManager.SetProgressBar(0);
                EntityManager.Player.ResetConstructionProgress();
            }
        }
    }

    // DeconstructionHandeling Code
    else if (InputManager[InputFlags::LeftMouseButton])
    {
        if (isMouseInReachDistance)
        {
            if (IsMouseStillPointingAtTheSameTile && isMouseInReachDistance &&
                ManagersManager.isPlayerAbleToDeconstructTopTileAt(InputManager.GetMouseWorldPosytionX(), InputManager.GetMouseWorldPosytionY()))
            {
                UIManager.SetMouseText("Deconstructon");
                UIManager.SetProgressBar(EntityManager.Player.GetDeconstructionProgress());
                bool didDeconstructionFinished = EntityManager.Player.ProgressDeconstruction(fElapsedTime);
                if (didDeconstructionFinished)
                {
                    ManagersManager.DeconstructTopTileAt(InputManager.GetMouseWorldPosytionX(), InputManager.GetMouseWorldPosytionY());
                    UIManager.SetMouseText("");
                    UIManager.SetProgressBar(0.0f);
                    EntityManager.Player.ResetDeconstructionProgress();
                }
            }
            else
            {
                UIManager.SetMouseText("");
                UIManager.SetProgressBar(0);
                EntityManager.Player.ResetDeconstructionProgress();
            }
        }
    }

    else
    {
        EntityManager.Player.ResetDeconstructionProgress();
        EntityManager.Player.ResetConstructionProgress();

        UIManager.SetMouseText("");
        UIManager.SetProgressBar(0.0f);
    }
    // std::cout<<std::endl;
}
