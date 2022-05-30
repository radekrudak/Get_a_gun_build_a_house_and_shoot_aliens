#include "Game.h"
void GameJam::GetUserInput(float fElapsedTime)

{
    float MovingSpeed = 4.5f;

    if (GetMouseWheel() > 0)
    {
        fTest += 1 * fElapsedTime;
    }
    if (GetMouseWheel() < 0)
    {
        fTest -= 1 * fElapsedTime;
    }

    if (GetKey(olc::Key::F1).bPressed)
    {
        isStatsDis = !isStatsDis;
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




    static olc::vf2d  WorldMouse =  ScreenPosToWorldPos (GetMouseX(),GetMouseY());

    olc::vf2d PreviousWorldMouse = WorldMouse;
    WorldMouse =  ScreenPosToWorldPos (GetMouseX(),GetMouseY());

    auto Floorvf2d = [](olc::vf2d Input)
    { 
        return olc::vf2d(floor(Input.x),floor(Input.y) );
    };

    bool IsMouseStillPointingAtTheSameTile = (Floorvf2d(PreviousWorldMouse) == Floorvf2d(WorldMouse));

    

}