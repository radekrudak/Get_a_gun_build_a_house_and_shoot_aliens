
#include "../olcPixelGameEngineBackend.h"

void olcPixelGameEngineBackend::GetUserInput(float fElapsedTime)
{
    InputManager.ClearAllFlags();

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
    InputManager.SetMouseWorldPosytion(WorldMouse.x, WorldMouse.y);

    auto Floorvf2d = [](olc::vf2d Input)
    {
        return olc::vf2d(floor(Input.x), floor(Input.y));
    };

    // constructionHandeling
    if (GetMouse(1).bHeld)
    {
        
        InputManager.Set(InputFlags::RightMouseButton, true);
    }

    if (GetMouse(0).bHeld)
        InputManager.Set(InputFlags::LeftMouseButton, true);
}