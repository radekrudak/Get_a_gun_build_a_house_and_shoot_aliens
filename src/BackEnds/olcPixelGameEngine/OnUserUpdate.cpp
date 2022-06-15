#include "../olcPixelGameEngineBackend.h"

bool olcPixelGameEngineBackend::OnUserUpdate(float fElapsedTime)
{

    switch (UIManager.GetUIMode())
    {
    case WhichScreen::GAMEPLAY:
    {
        // enabling layers
        EnableLayer(lPlayer, true);
        EnableLayer(lGround, true);
        EnableLayer(lNight, true);

        PreviousSecond = floor(fSeconds);
        Clear(olc::BLANK);
        // it copy all the code in Controls.h and paste it here (in Controls.h i store input handeling code)
        //#include "Controls.h"
        GetUserInput(fElapsedTime);
        GameUpdate(fElapsedTime);
        EntityManager.Player.SyncCameraWithPlayer(ScreenWidth(), ScreenHeight(), TileSize);


        SetDrawTarget(lGround);
        Clear(olc::CYAN);

        /// Tile Drawing
        // y and x are cordinates of decals of tiles (-player cor offset) on screen, xx and yy are coordinates of position on tile map.
        int intCameraX = static_cast<int>(EntityManager.Player.GetCameraX());
        int intCameraY = static_cast<int>(EntityManager.Player.GetCameraY());
        for (int y = intCameraY; y < intCameraY + ScreenHeight() / TileSize + TileSize; y++)
            for (int x = intCameraX; x < intCameraX + ScreenWidth() / TileSize + TileSize; x++)
                for (auto &i : World.GetTileStackAt(x, y))
                {

                    DrawDecal(WorldPosToScreenPos(x, y), TextureManager[TileManager[i]->GetTextureID()]);
                }
        // draws player
        SetDrawTarget(lPlayer);
        Clear(olc::BLANK);

        float fMouseMapX = ScreenPosToWorldPos(GetMouseX(), GetMouseY()).x;
        float fMouseMapY = ScreenPosToWorldPos(GetMouseX(), GetMouseY()).y;

        EntityManager.Player.SetAngle(fMouseMapX, fMouseMapY);
        // Draw Player
        DrawRotatedDecal(WorldPosToScreenPos(EntityManager.Player.GetX(), EntityManager.Player.GetY()), TextureManager["mc"], EntityManager.Player.GetAngle(), {float(TextureManager.GetSprite("mc")->width) / 2.0f, float(TextureManager.GetSprite("mc")->height) / 2.0f});

        // UI Drawing
        SetDrawTarget(nullptr);
        Clear(olc::BLANK);

        constexpr int PROGRESS_BARR_W = 5;
        constexpr int PROGRESS_BARR_OFFSET = -30;
        constexpr int CHAR_SIZE_ON_SCREEN = 8;
        DrawString(GetMouseX() - UIManager.GetMouseText().size() * CHAR_SIZE_ON_SCREEN / 2, GetMouseY() - 20, UIManager.GetMouseText());
        if (UIManager.GetPRogressBar() > 0.0f)
        {

            FillRect({GetMouseX() - (int)UIManager.GetMouseText().size() * CHAR_SIZE_ON_SCREEN / 2, GetMouseY() + PROGRESS_BARR_OFFSET}, {static_cast<int>(UIManager.GetPRogressBar() * UIManager.GetMouseText().size() * CHAR_SIZE_ON_SCREEN), PROGRESS_BARR_W}, olc::RED);
            DrawRect({GetMouseX() - (int)UIManager.GetMouseText().size() * CHAR_SIZE_ON_SCREEN / 2, GetMouseY() + PROGRESS_BARR_OFFSET}, {static_cast<int>(UIManager.GetMouseText().size() * CHAR_SIZE_ON_SCREEN), PROGRESS_BARR_W}, olc::BLACK);
        }

        static bool BuildManuAlreadyBuild = false;

        bool isFirstPass = true;
        switch (UIManager.GetWhichWindowIsOpen())
        {
        case WhichWindowIsOpen::INVENTORY:
            OlcPopUpMenu["Inventory"].DeleteAllChildren();
            if (EntityManager.Player.GetInventory().isEmpty() == false)
            {

                OlcPopUpMenu["Inventory"].SetTable(1, EntityManager.Player.GetInventory().size() - 1);
                int PlaceInInventory = 1;
                for (const auto &i : EntityManager.Player.GetInventory())
                {
                    if (isFirstPass)
                    {
                        isFirstPass = false;
                        continue;
                    }
                    OlcPopUpMenu["Inventory"][ManagersManager.GetItemUserVisibleName(i.ItemID) + " x" + std::to_string(i.Quantity)].SetTable(1,1).SetID(PlaceInInventory<<4);
                    PlaceInInventory++;
                }
                OlcPopUpMenu.Build();
                olcPopUpManager.Open(&(OlcPopUpMenu["Inventory"]));
                olcPopUpManager.Draw(Game::TextureManager.GetSprite("PopUpMenu").get(), {30, 30});
            }
            else
            {

                OlcPopUpMenu["Inventory"].SetTable(1, 1)["No Items in inventory"].SetID(0);
                OlcPopUpMenu.Build();
                olcPopUpManager.Open(&(OlcPopUpMenu["Inventory"]));
                olcPopUpManager.Draw(Game::TextureManager.GetSprite("PopUpMenu").get(), {30, 30});
            }
            break;

        case WhichWindowIsOpen::BUILDABLE_TILES_SELECT:

            if (BuildManuAlreadyBuild == false)
            {

                OlcPopUpMenu["BuildableTileSelection"].DeleteAllChildren();
                int BuildableTileIndex = 0;
                for (auto const &i : TileManager.GetBuildableTiles())
                {
                    OlcPopUpMenu["BuildableTileSelection"][TileManager[i]->GetTileName()].SetID(BuildableTileIndex);
                    BuildableTileIndex++;
                }
                OlcPopUpMenu.Build();
                olcPopUpManager.Open(&(OlcPopUpMenu["BuildableTileSelection"]));
                BuildManuAlreadyBuild = true;
            }
            olcPopUpManager.Draw(Game::TextureManager.GetSprite("PopUpMenu").get(), {30, 30});
            break;

        default:
        case WhichWindowIsOpen::NONE:
            BuildManuAlreadyBuild = false;
            break;
        }

        SetDrawTarget(lNight);

        Clear(olc::BLANK);
        if (isNight)
            DrawDecal(olc::vf2d(0, 0), dNight, olc::vf2d(1.0f, 1.0f), olc::PixelF(1.0f, 1.0f, 1.0f, 0.25f));

        SetDrawTarget(nullptr);
        if (EntityManager.Player.GetHealth() < 0.0f)
        {
            DrawString(ScreenWidth() / 2 - 50, ScreenHeight() / 2, " Game over \n refresh page to start again");
        }
        if (UIManager.Get(UIFlags::isStatsDis))
        {
            DrawString(0, 0, "PlayerX: " + std::to_string(EntityManager.Player.GetX()));
            DrawString(0, 10, "PlayerY: " + std::to_string(EntityManager.Player.GetY()) + std::to_string(EntityManager.Player.GetAngle()));

            DrawString(0, 20, "CameraX: " + std::to_string(EntityManager.Player.GetCameraX()));
            DrawString(0, 30, "CameraY: " + std::to_string(EntityManager.Player.GetCameraY()));
            DrawString(0, 40, "MouseX: " + std::to_string(InputManager.GetMouseWorldPosytionX()));
            DrawString(0, 50, "MouseY: " + std::to_string(InputManager.GetMouseWorldPosytionY()));
            DrawString(0, 60, "Construction: " + std::to_string(EntityManager.Player.GetConstructionProgress()));
            DrawString(0, 70, "Deconstruction: " + std::to_string(EntityManager.Player.GetDeconstructionProgress()));
            if (EntityManager.Player.GetInventory().isEmpty() == false)
            {
                DrawString(0, 80, "R1: " + std::to_string(EntityManager.Player.GetInventory()[0].Quantity));
                DrawDecal({0, 80}, TextureManager[ItemManager[EntityManager.Player.GetInventory()[0].ItemID]->GetTextureID()]);
            }
            else
                DrawString(0, 80, "R1: Empty");

            if (EntityManager.Player.GetInventory().isEmpty() == false)
            {
                DrawString(5, 90, "R2: " + std::to_string(EntityManager.Player.GetInventory()[1].Quantity));
                DrawDecal({5, 90}, TextureManager[ItemManager[EntityManager.Player.GetInventory()[1].ItemID]->GetTextureID()]);
            }
            else
                DrawString(0, 90, "R2: Empty");

            DrawString(0, 110, "Distance: " + std::to_string(Distance(EntityManager.Player.GetX(), EntityManager.Player.GetY(), GetMouseX() / TileSize + EntityManager.Player.GetX(), GetMouseY() / TileSize + EntityManager.Player.GetY())));
            DrawString(0, 120, "DebugMode: " + std::to_string(isDebugMode));
            DrawString(0, 130, "Screen: " + std::to_string(static_cast<int>(UIManager.GetUIMode())));
        }

        ++ElapsedFrames;
    }
    break;
    case WhichScreen::MAIN_MENU:

        // why is it done this strange way ? Because evry "normal" one failed
        int ChosenOption = -1;
        olc::popup::Menu *command = nullptr;
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
            olcPopUpManager.Open(&(OlcPopUpMenu["MainMenu"]));
            // olcPopUpManager.OnBack();
        }

        Clear(olc::GREY);

        olcPopUpManager.Draw(Game::TextureManager.GetSprite("PopUpMenu").get(), {30, 30});
        if (command != nullptr)
        {
            ChosenOption = command->GetID();
            if (ChosenOption == static_cast<int>(GUIInput::LoadGame))
            {
                olcPopUpManager.Open(&(OlcPopUpMenu["Load Game"]));
            }
        }

        Game::MainMenu(static_cast<GUIInput>(ChosenOption));
    }
    return true;
}
