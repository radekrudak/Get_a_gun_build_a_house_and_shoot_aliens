#include "Game.h"

bool GameJam::OnUserUpdate(float fElapsedTime)
{
#include "DebugControls.h"

    switch (ScreenMode)
    {
    case WhitchScreen::GAMEPLAY:
    {

        PreviousSecond = floor(fSeconds);
        //float fMousePlayerDistance = sqrt(pow(fMouseMapY - EntityManager.Player.GetY(), 2) + pow(fMouseMapX - EntityManager.Player.GetX(), 2));
        Clear(olc::BLANK);
        // it copy all the code in Controls.h and paste it here (in Controls.h i store input handeling code)
        //#include "Controls.h"
        GetUserInput(fElapsedTime);
        EntityManager.Player.SyncCameraWithPlayer(ScreenWidth(),ScreenHeight(),TileSize);

        if (fSeconds > fSecondsInDay)
        {
           
            // FindPath(olc::vf2d(fCameraX+1,fCameraY+1), olc::vf2d(fPlayerX,fPlayerY),vNodeMap,vEnemies[vEnemies.size()-1]->Path,vTileMap,FinishdEarly);


            fSeconds = 0.0;
            isNight = !isNight;
        }

        fSeconds += fElapsedTime;

        SetDrawTarget(lGround);
        Clear(olc::CYAN);

        /// Tile Drawing
        // y and x are cordinates of decals of tiles (-player cor offset) on screen, xx and yy are coordinates of position on tile map.
        int intCameraX = static_cast<int>(EntityManager.Player.GetCameraX());
        int intCameraY = static_cast<int>(EntityManager.Player.GetCameraY());
        for (int y =  intCameraY; y < intCameraY+ScreenHeight()/TileSize+TileSize  ;y++)
            for (int x =intCameraX; x <  intCameraX+ScreenWidth() / TileSize+TileSize; x++ )
                    for (auto &i : World.GetTileStackAt(x,y))
                    {

                        DrawDecal(WorldPosToScreenPos(x,y), TextureManager[ TileManager[i]->GetTextureID() ]);
                    }
        // draws player
        SetDrawTarget(lPlayer);
        Clear(olc::BLANK);

        fMouseMapX = ScreenPosToWorldPos(GetMouseX(),GetMouseY()).x;
        fMouseMapY = ScreenPosToWorldPos(GetMouseX(),GetMouseY()).y;

        EntityManager.Player.SetAngle(fMouseMapX,fMouseMapY);
        // Draw Player
        DrawRotatedDecal(WorldPosToScreenPos(EntityManager.Player.GetX(),EntityManager.Player.GetY()), TextureManager["mc"], EntityManager.Player.GetAngle(), {float(TextureManager.GetSprite("mc")->width) / 2.0f, float(TextureManager.GetSprite("mc")->height) / 2.0f});
       

        // enabling layers
        EnableLayer(lPlayer, true);
        EnableLayer(lGround, true);

        // HUD DRAWING

        DrawString(GetMouseX() - MouseText.size() * 8 / 2, GetMouseY() - 20, MouseText);
        float ClockScale = 4.0f;

        DrawRotatedDecal(olc::vf2d(ScreenWidth() - sMoonAndSun->width / 2 + 5, sMoonAndSun->height * ClockScale),
                         dMoonAndSun, isNight ? fSeconds / fSecondsInDay * PI : fSeconds / fSecondsInDay * PI + PI,
                         olc::vf2d(sMoonAndSun->width / 2.0f, sMoonAndSun->height / 2.0f), olc::vf2d(ClockScale, ClockScale));

        if (fModeTextFading > 0.0f)
        {
            if (ModeTextLap > 0)
                --ModeTextLap;
            else if (ModeTextLap < 0)
                ;
            else
                fModeTextFading -= fElapsedTime;
        }

        std::string strMode;
        if (isFightMode)
            strMode = "Fight Mode";
        if (!isFightMode)
            strMode = "Build/Gathering Mode";

        DrawStringDecal({(float)ScreenWidth() - strMode.size() * 9, 10}, strMode, olc::PixelF(1.0f, 1.0f, 1.0f, fModeTextFading));
        SetDrawTarget(lNight);
        Clear(olc::BLANK);
        if (isNight)
            DrawDecal(olc::vf2d(0, 0), dNight, olc::vf2d(1.0f, 1.0f), olc::PixelF(1.0f, 1.0f, 1.0f, 0.25f));

        EnableLayer(lNight, true);
        SetDrawTarget(nullptr);
        if (Health < 0.0f)
        {
            DrawString(ScreenWidth() / 2 - 50, ScreenHeight() / 2, " Game over \n refresh page to start again");
        }
        if (isStatsDis)
        {
            DrawString(0, 0, "PlayerX: " + std::to_string(EntityManager.Player.GetX()));
            DrawString(0, 10, "PlayerY: " + std::to_string(EntityManager.Player.GetY()) + std::to_string(EntityManager.Player.GetAngle()));

            DrawString(0, 20, "CameraX: " + std::to_string(EntityManager.Player.GetCameraX()));
            DrawString(0, 30, "CameraY: " + std::to_string(EntityManager.Player.GetCameraY()));
            DrawString(0, 40, "MouseX: " + std::to_string(fMouseMapX));
            DrawString(0, 50, "MouseY: " + std::to_string(fMouseMapY));
            DrawString(0, 60, "Destruction: " + std::to_string(fDestruction));
            DrawString(0, 70, "Construction: " + std::to_string(fConstruction));
            if (PlayerInventory.isEmpty() == false)
            {
                DrawString(0, 80, "R1: " + std::to_string(PlayerInventory[0].Quantity));
                DrawDecal({0, 80}, TextureManager[ItemManager[PlayerInventory[0].ItemID]->GetTextureID()]);
            }
            else
                DrawString(0, 80, "R1: Empty");

            if (PlayerInventory.isEmpty() == false)
            {
                DrawString(5, 90, "R2: " + std::to_string(PlayerInventory[1].Quantity));
                DrawDecal({5, 90}, TextureManager[ItemManager[PlayerInventory[1].ItemID]->GetTextureID()]);
            }
            else
                DrawString(0, 90, "R2: Empty");

            DrawString(0, 110, "Distance: " + std::to_string(Distance(EntityManager.Player.GetX(), EntityManager.Player.GetY(), GetMouseX() / TileSize + EntityManager.Player.GetX(), GetMouseY() / TileSize + EntityManager.Player.GetY())));
            DrawString(0, 120, "DebugMode: " + std::to_string(isDebugMode));
            DrawString(0, 130, "Screen: " + std::to_string(static_cast<int>(ScreenMode)));

        }

        ++ElapsedFrames;
    }
    break;
    case WhitchScreen::MAIN_MENU:
        // why is it done this strange way ? Because evry "normal" one failed
        int chosed_option = 0;
        MainMenu(this, lGround, lPlayer, lNight, chosed_option);
        switch (chosed_option)
        {
        case 1:
            NewGame();
        }

        break;
    }
    return true;
}