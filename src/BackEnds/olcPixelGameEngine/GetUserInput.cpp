
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
    if (GetKey(olc::Key::Q).bPressed)
    {
        UIManager.Flip(UIFlags::isPlayerTileToBuildSelectionDisplayed);
    }
    if (GetMouseWheel() > 0)
    {
        fTest += 1 * fElapsedTime;
    }
    if (GetMouseWheel() < 0)
    {
        fTest -= 1 * fElapsedTime;
    }

    olc::popup::Menu *command = nullptr;

    olc::vf2d PlayerMoveVector = {0, 0};
    if (UIManager.Get(UIFlags::isPlayerInventoryDisplayed) == false &&
        UIManager.Get(UIFlags::isPlayerTileToBuildSelectionDisplayed) == false)
    {
        if (GetKey(olc::Key::D).bHeld)
            PlayerMoveVector.x = 1;
        if (GetKey(olc::Key::A).bHeld)
            PlayerMoveVector.x = -1;
        if (GetKey(olc::Key::S).bHeld)
            PlayerMoveVector.y = 1;
        if (GetKey(olc::Key::W).bHeld)
            PlayerMoveVector.y = -1;
    }
    else
    {
        if (GetKey(olc::Key::UP).bPressed || GetKey(olc::Key::W).bPressed)
            olcPopUpManager.OnUp();
        if (GetKey(olc::Key::DOWN).bPressed || GetKey(olc::Key::S).bPressed)
            olcPopUpManager.OnDown();
        if (GetKey(olc::Key::LEFT).bPressed)
            olcPopUpManager.OnLeft();
        if (GetKey(olc::Key::RIGHT).bPressed)
            olcPopUpManager.OnRight();
        if (GetKey(olc::Key::SPACE).bPressed || GetKey(olc::Key::ENTER).bPressed)
        {
            command = olcPopUpManager.OnConfirm();
        }
        if (GetKey(olc::Key::Z).bPressed || GetKey(olc::Key::ESCAPE).bPressed)
        {
            olcPopUpManager.OnBack();
        }
        if (command != nullptr)
        {
            std::cout << "Item chosen: " << command->GetName() << " with id: " << command->GetID() << " In menu: ";
            std::cout<<OlcPopUpMenu->GetSelectedItem()->GetName()<<" "<<OlcPopUpMenu->GetSelectedItem()->GetID()<<std::endl;
        }
    }
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