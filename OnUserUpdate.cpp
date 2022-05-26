 #include "Game.h"
 
 bool GameJam::OnUserUpdate(float fElapsedTime)
{
        #include "DebugControls.h"

        switch (ScreenMode)
        {
            case WhitchScreen::GAMEPLAY:
            {
                PreviousSecond = floor(fSeconds);
                float fMousePlayerDistance = sqrt( pow(fMouseMapY-fPlayerY,2)+pow(fMouseMapX-fPlayerX,2)  );
                Clear(olc::BLANK);
                // it copy all the code in Controls.h and paste it here (in Controls.h i store input handeling code)
                #include "Controls.h"
                fCameraX = fPlayerX-(ScreenWidth()/2)/TileSize;
                fCameraY = fPlayerY-(ScreenHeight()/2)/TileSize;

                if (fSeconds>fSecondsInDay )
                {   
                    vEnemies.push_back(new Enemy(fCameraX+1,fCameraY+1,sEnemy));
                    //FindPath(olc::vf2d(fCameraX+1,fCameraY+1), olc::vf2d(fPlayerX,fPlayerY),vNodeMap,vEnemies[vEnemies.size()-1]->Path,vTileMap,FinishdEarly);

                    for(auto i:vEnemies.front()->Path)
                    {
                        std::cout<<"Px: "<<i.x<<"Py: "<<i.y<<std::endl;
                        

                    }
                    
                    fSeconds=0.0;
                    isNight = !isNight;
                }

                fSeconds +=fElapsedTime;


                SetDrawTarget(lGround);
                Clear(olc::CYAN);


                ///Tile Drawing
                //y and x are cordinates of decals of tiles (-player cor offset) on screen, xx and yy are coordinates of position on tile map.
                for (int y = 0,yy= 0; y < ScreenHeight()+TileSize; y+=TileSize)
                {
                    for (int x = 0,xx= 0; x < ScreenWidth()+TileSize; x+=TileSize)
                    {
                        if(xx+(int)fCameraX>0 && yy+(int)fCameraY >0)
                        for (auto &i:vTileMap[ xx+(int)fCameraX  ][ yy+(int)fCameraY ] )
                        {

                                DrawDecal(olc::vf2d ((double)x-fmod((double)fPlayerX,1)*TileSize, (double)y-fmod((double)fPlayerY,1)*TileSize), i->GetDecal());

                        }

                        ++xx;
                    }
                    ++yy;
                }



                //draws player
                SetDrawTarget(lPlayer);
                Clear(olc::BLANK);


                fMouseMapX =(float)GetMouseX()/TileSize+fCameraX;
                fMouseMapY=(float)GetMouseY()/TileSize+fCameraY;

                fPlayerA = atan2((fMouseMapY-fPlayerY),(fMouseMapX-fPlayerX));
                //Draw Player
                DrawRotatedDecal(olc::vf2d((fPlayerX-fCameraX)*TileSize*fTileScale,(fPlayerY-fCameraY)*TileSize*fTileScale),vDecals[FileMap["mc"]], fPlayerA+PI/2, {float(sMC->width)/2.0f,float(sMC->height)/2.0f});

                {

                std::vector<std::thread *> vThreads; 
                int ii=0;
                ///Draws Enemy
                for(auto &i: vEnemies)
                {
                   // vThreads.push_back( new std::thread( FindPath, olc::vf2d(i->x,i->y), olc::vf2d(fPlayerX,fPlayerY),vNodeMap,
                     //               std::ref(vEnemies[vEnemies.size()-1]->Path),std::ref(vTileMap),std::ref(FinishdEarly )) );
                    olc::vf2d NextPos =  i->CheckNextPosytionStraight(fPlayerX,fPlayerY,fElapsedTime);
                    if  ( ! vTileMap[ NextPos.x ][ NextPos.y ].back()->isColisive() )
                    {
                         i->GetfDestruction() = 0.0f;
                        i->Move_Straight(fPlayerX,fPlayerY,fElapsedTime);
                    }
                    else
                    {
                        i->GetfDestruction() +=0.1f*fElapsedTime;
                        if(i->GetfDestruction() >=1)
                        {
                             i->GetfDestruction() = 0.0f;
                            vTileMap[ i->GetPosition().x ][ i->GetPosition().y ].pop_back();
                           
                        }
                    }
                    DrawDecal(olc::vf2d((i->x-fCameraX)*TileSize-TileSize/2,(i->y-fCameraY)*TileSize-TileSize/2),i->Decal);
                    
                    FillRect((i->x-fCameraX)*TileSize-TileSize/2,
                            (i->y-fCameraY)*TileSize-TileSize/2 -(i->Sprite->height/2),
                                i->GetfDestruction()*i->Sprite->width,10  ,olc::RED);
                                
                    if(Distance(fPlayerX,fPlayerY,i->x,i->y)<1.5f)
                    {
                        Health-=fElapsedTime/10.0f;
                    }

                    int jj =0;

                ++ii;
                }
                for(auto &i: vThreads)
                {
                    i->join();
                }
                vThreads.clear();
                }
                // enabling layers
                EnableLayer(lPlayer,true);
                EnableLayer(lGround,true);

                // HUD DRAWING


                DrawString(GetMouseX()-MouseText.size()*8/2,GetMouseY()-20, MouseText);
                float ClockScale = 4.0f;

                DrawRotatedDecal(olc::vf2d(ScreenWidth()-sMoonAndSun->width/2+5,sMoonAndSun->height*ClockScale),
                                dMoonAndSun,isNight ? fSeconds/fSecondsInDay*PI:fSeconds/fSecondsInDay*PI+PI,
                                olc::vf2d(sMoonAndSun->width/2.0f,sMoonAndSun->height/2.0f),olc::vf2d(ClockScale,ClockScale));


                if(fModeTextFading>0.0f)
                {
                    if (ModeTextLap >0) --ModeTextLap;
                    else if (ModeTextLap <0);
                    else fModeTextFading-= fElapsedTime;

                }

                std::string strMode;
                if (isFightMode) strMode = "Fight Mode";
                if (!isFightMode) strMode = "Build/Gathering Mode";

                DrawStringDecal({(float)ScreenWidth()-strMode.size()*9,10},strMode,olc::PixelF (1.0f,1.0f,1.0f,fModeTextFading));
                SetDrawTarget(lNight);
                Clear(olc::BLANK);
                if(isNight)
                    DrawDecal(olc::vf2d(0,0),dNight,olc::vf2d(1.0f,1.0f),olc::PixelF(1.0f,1.0f,1.0f,0.25f));

                EnableLayer(lNight,true);
                SetDrawTarget(nullptr);
                if (Health<0.0f)
                {
                    DrawString(ScreenWidth()/2-50,ScreenHeight()/2," Game over \n refresh page to start again");
                }
                if (isStatsDis)
                {
                    DrawString(0,0,"PlayerX: "+ std::to_string(fPlayerX));
                    DrawString(0,10,"PlayerY: "+ std::to_string(fPlayerY)+std::to_string(fPlayerA));

                    DrawString(0,20,"CameraX: "+ std::to_string(fCameraX));
                    DrawString(0,30,"CameraY: "+ std::to_string(fCameraY));
                    DrawString(0,40,"MouseX: "+ std::to_string(fMouseMapX));
                    DrawString(0,50,"MouseY: "+ std::to_string(fMouseMapY));
                    DrawString(0,60,"Destruction: "+ std::to_string(fDestruction));
                    DrawString(0,70,"Construction: "+ std::to_string(fConstruction));
                    if(!vInventory.empty())
                    {
                        DrawString(0,80,"R1: "+ std::to_string(vInventory[0]->Quantity));

                    }
                    else
                        DrawString(0,80,"R1: Empty");

                    if(vInventory.size()>=2)
                    {
                        DrawString(0,90,"R2: "+ std::to_string(vInventory[1]->Quantity));

                    }
                    else
                        DrawString(0,90,"R2: Empty");
                    

                    DrawString(0,110,"Distance: "+ std::to_string(Distance(fPlayerX,fPlayerY,GetMouseX()/TileSize+fCameraX,GetMouseY()/TileSize+fCameraY)));
                    DrawString(0,120,"DebugMode: "+ std::to_string(isDebugMode));
                    DrawString(0,130,"Screen: "+ std::to_string( static_cast<int> ( ScreenMode ) ) );
                    if(!vEnemies.empty())  DrawString(0,120,"x: "+ std::to_string(vEnemies.front()->x));
                    if(!vEnemies.empty())  DrawString(0,130,"y: "+ std::to_string(vEnemies.front()->y));
                }
                
                ++ElapsedFrames;
            }
        break;
            case WhitchScreen::MAIN_MENU:
                // why is it done this strange way ? Because evry "normal" one failed
                int chosed_option =0;
                MainMenu(this,lGround,lPlayer,lNight,chosed_option);
                switch (chosed_option)
                {
                    case 1:
                        NewGame();
                }


        break;
        }
        return true;

    }