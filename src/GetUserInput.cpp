#include "Game.h"
void GameJam::GetUserInput(float fElapsedTime)

{
    float MovingSpeed = 4.5f;
    if (GetKey(olc::Key::F1).bPressed)
    {
        UIManager.Flip(UIFlags::isStatsDis);
    }

    if (GetKey(olc::Key::E).bPressed)
    {
        UIManager.Flip(UIFlags::isPlayerInventoryDisplayed);
    }


    if (GetMouseWheel() > 0)
    {
        fTest += 1 * fElapsedTime;
    }
    if (GetMouseWheel() < 0)
    {
        fTest -= 1 * fElapsedTime;
    }



    olc::vf2d PlayerMoveVector = {0, 0};
    if (GetKey(olc::Key::D).bHeld)
        PlayerMoveVector.x = 1;
    if (GetKey(olc::Key::A).bHeld)
        PlayerMoveVector.x = -1;
    if (GetKey(olc::Key::S).bHeld)
        PlayerMoveVector.y = 1;
    if (GetKey(olc::Key::W).bHeld)
        PlayerMoveVector.y = -1;
    MovePlayerWithColysionCheck(fElapsedTime, PlayerMoveVector.x, PlayerMoveVector.y);

    static olc::vf2d WorldMouse = ScreenPosToWorldPos(GetMouseX(), GetMouseY());

    olc::vf2d PreviousWorldMouse = WorldMouse;
    WorldMouse = ScreenPosToWorldPos(GetMouseX(), GetMouseY());

    auto Floorvf2d = [](olc::vf2d Input)
    {
        return olc::vf2d(floor(Input.x), floor(Input.y));
    };

    bool isMouseInReachDistance = (Distance(WorldMouse.x, WorldMouse.y, EntityManager.Player.GetX(), EntityManager.Player.GetY()) < EntityManager.Player.GetReachDistance());
    bool IsMouseStillPointingAtTheSameTile = (Floorvf2d(PreviousWorldMouse) == Floorvf2d(WorldMouse));
    // constructionHandeling
    if (GetMouse(1).bHeld)
    {
        if (isMouseInReachDistance)
        {
            if (IsMouseStillPointingAtTheSameTile && isMouseInReachDistance &&
                ManagersManager.IsPlayerAbleToConstructTile() &&
                ManagersManager.CanTileFitOnTileStack(World.GetTileStackAt(WorldMouse.x, WorldMouse.y), EntityManager.Player.GetIDofTileToBuild()))
            {
                UIManager.SetMouseText("Construction");
                UIManager.SetProgressBar(EntityManager.Player.GetConstructionProgress());

                bool didConstructionFinished = EntityManager.Player.ProgressConstruction(fElapsedTime);
                if (didConstructionFinished)
                {
                    World.ConstructTileAtTopOf(WorldMouse.x, WorldMouse.y,
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
    else if (GetMouse(0).bHeld)
    {
        if (isMouseInReachDistance)
        {
            if (IsMouseStillPointingAtTheSameTile && isMouseInReachDistance &&
                World.isPlayerAbleToDeconstructTopTileAt(WorldMouse.x, WorldMouse.y))
            {
                UIManager.SetMouseText("Deconstructon");
                UIManager.SetProgressBar(EntityManager.Player.GetDeconstructionProgress());
                bool didDeconstructionFinished = EntityManager.Player.ProgressDeconstruction(fElapsedTime);
                if (didDeconstructionFinished)
                {
                    World.DeconstructTopTileAt(WorldMouse.x, WorldMouse.y);
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
}