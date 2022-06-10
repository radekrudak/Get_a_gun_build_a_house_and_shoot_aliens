#include "Game.h"

void Game::GameUpdate(float fElapsedTime)
{
    if (UIManager.GetWhichWindowIsOpen() == WhichWindowIsOpen::BUILDABLE_TILES_SELECT && InputManager.GetGUIInputInt() >= 0)
    {
        EntityManager.Player.SetIDofTileToBuild(
            TileManager.GetBuildableTiles()[InputManager.GetGUIInputInt()]);
            std::cout<<"Selected tile to build: "<<(TileManager.GetBuildableTiles()[InputManager.GetGUIInputInt()])<<std::endl;;
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
                ManagersManager.CanTileFitOnTileStack(World.GetTileStackAt(InputManager.GetMouseWorldPosytionX(), InputManager.GetMouseWorldPosytionY()), EntityManager.Player.GetIDofTileToBuild()))
            {

                UIManager.SetMouseText("Construction");
                UIManager.SetProgressBar(EntityManager.Player.GetConstructionProgress());

                bool didConstructionFinished = EntityManager.Player.ProgressConstruction(fElapsedTime);
                if (didConstructionFinished)
                {
                    World.ConstructTileAtTopOf(InputManager.GetMouseWorldPosytionX(), InputManager.GetMouseWorldPosytionY(),
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
                World.isPlayerAbleToDeconstructTopTileAt(InputManager.GetMouseWorldPosytionX(), InputManager.GetMouseWorldPosytionY()))
            {
                UIManager.SetMouseText("Deconstructon");
                UIManager.SetProgressBar(EntityManager.Player.GetDeconstructionProgress());
                bool didDeconstructionFinished = EntityManager.Player.ProgressDeconstruction(fElapsedTime);
                if (didDeconstructionFinished)
                {
                    World.DeconstructTopTileAt(InputManager.GetMouseWorldPosytionX(), InputManager.GetMouseWorldPosytionY());
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