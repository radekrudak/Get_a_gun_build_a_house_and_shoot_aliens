float MovingSpeed = 4.5f;

if(GetMouseWheel()>0)
{
    fTest+= 1*fElapsedTime;
}
if(GetMouseWheel()<0)
{
    fTest-= 1*fElapsedTime;
}

if (GetKey(olc::Key::F1).bPressed)
{
    isStatsDis = !isStatsDis;

}

if (GetKey(olc::Key::D).bHeld)
{
    fPlayerX+= MovingSpeed*fElapsedTime;
    
    if (ManagersManager.isTileStackColisive(World.GetTileStackAt(fPlayerX+ MovingSpeed*fElapsedTime,fPlayerY)))
    {
        fPlayerX-= MovingSpeed*fElapsedTime;
    }
    
}
if (GetKey(olc::Key::A).bHeld)
{
    fPlayerX-= MovingSpeed*fElapsedTime;
    
    if (ManagersManager.isTileStackColisive(World.GetTileStackAt(fPlayerX- MovingSpeed*fElapsedTime,fPlayerY)))
    {
        fPlayerX+= MovingSpeed*fElapsedTime;
    }
    
}
if (GetKey(olc::Key::S).bHeld)
{
    fPlayerY+= MovingSpeed*fElapsedTime;

    // if (vTileMap[fPlayerX][fPlayerY+ MovingSpeed*fElapsedTime].front()->isColisivTileInIt(vTileMap[fPlayerX][fPlayerY+ MovingSpeed*fElapsedTime]))
    if (ManagersManager.isTileStackColisive(World.GetTileStackAt(fPlayerX,fPlayerY+ MovingSpeed*fElapsedTime)))
    {
        fPlayerY-= MovingSpeed*fElapsedTime;
    }
}
if (GetKey(olc::Key::W).bHeld)
{
    fPlayerY-= MovingSpeed*fElapsedTime;
    if (ManagersManager.isTileStackColisive(World.GetTileStackAt(fPlayerX,fPlayerY- MovingSpeed*fElapsedTime)))
    {
        fPlayerY+= MovingSpeed*fElapsedTime;
    }
}

if (GetKey(olc::Key::CTRL).bPressed)
{
    isFightMode = !isFightMode;
    fModeTextFading =1.0f;
    ModeTextLap = 50;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
if (!isFightMode)
{
    // Build  /resoursce mode




    if (GetKey(olc::Key::K1).bHeld)
    {
        ChosenBuildTile = 2;
    }
    if (GetKey(olc::Key::K2).bHeld)
    {
        ChosenBuildTile = 3;
    }
    // GATHERING RESOURSERS

    if ((int)((float)GetMouseX()/TileSize+fCameraX) ==(int)fMouseMapX &&   // those two lines make sure gathering will
            //not reset when you move a mouse while being still on same block... i guess ?
            (int)((float)GetMouseY()/TileSize+fCameraY)==(int)fMouseMapY &&//  idk at this point but i will keep them to be safe

            GetMouse(0).bHeld &&
            TileManager[World.GetTileStackAt(fMouseMapX,fMouseMapY).back()]->vItemsGatheredID.empty()   // checks if there is anything to gather on this vTile posytion


       )
    {
        // draws "Progess bar"

        MouseText = "Gathering Resourses";
        if(fMousePlayerDistance > fReachDistance)
            MouseText = "Target Out of reach";

        else
        {
            FillRect(GetMouseX()-MouseText.size()*8/2, GetMouseY()-10, MouseText.size()*8*fDestruction,10,olc::RED );
            DrawRect(GetMouseX()-MouseText.size()*8/2, GetMouseY()-10, MouseText.size()*8,10, olc::WHITE );

            fDestruction += 0.6f*fElapsedTime;
            if (fDestruction >1)
            {
                fDestruction =0.0f;
                 //ads item to inventory
                // PlayerInventory.PickUpItem({
                //     vTileMap[fMouseMapX][fMouseMapY].back()->vItemsGatheredID.back(),
                //     vTileMap[fMouseMapX][fMouseMapY].back()->vItemsGatheredQuantity.back()
                // });
                // vTileMap[fMouseMapX][fMouseMapY].pop_back();


            }
        }

    }

    // BUILDING
    else if ((int)((float)GetMouseX()/TileSize+fCameraX) ==(int)fMouseMapX &&

             (int)((float)GetMouseY()/TileSize+fCameraY)==(int)fMouseMapY &&

             GetMouse(1).bHeld &&

             !TileManager[ChosenBuildTile]->vItemsRequiredID.empty() && // later put this check elswhere to give feedbck to player what he is doing wrong

              World.GetTileStackAt(fMouseMapX,fMouseMapY).size()-1 <  static_cast<int> (TileManager[ChosenBuildTile]->GetZLevel())  // Checks if you want to let's say put a wall in place where there is
             // alrady a wall or floor on vTile where there is a floor



            )
    {
        MouseText = "Constructing";
        if (fMousePlayerDistance > fReachDistance)
            MouseText = "Target out of reach";
        else if (  PlayerInventory.IsEnoughItems( {TileManager[ChosenBuildTile]->vItemsRequiredID.front(),TileManager[ChosenBuildTile]->vItemsRequiredQuantity.front() }))
        {
            //std::string Building = "Constructing";
            //DrawString(GetMouseX()-Building.size()*8/2,GetMouseY()-20, Building);
            // width
            FillRect(GetMouseX()-MouseText.size()*8/2, GetMouseY()-10, MouseText.size()*8*fConstruction,10,olc::RED );
            DrawRect(GetMouseX()-MouseText.size()*8/2, GetMouseY()-10, MouseText.size()*8,10, olc::WHITE );


            fConstruction += 0.6f*fElapsedTime;
            if (fConstruction >1)
            {
                fConstruction =0.0f;


                World.GetTileStackAt(fMouseMapX,fMouseMapY).push_back(ChosenBuildTile);
                PlayerInventory.DecreaseItemQuantity({TileManager[ChosenBuildTile]->vItemsRequiredID.front(),TileManager[ChosenBuildTile]->vItemsRequiredQuantity.front()});
                

                //PlayerInventory.FindItemInInventory(TileManager[ChosenBuildTile]->vItemsRequiredID.front())->Quantity -=TileManager[ChosenBuildTile]->vItemsRequiredQuantity.front();
                /*int ii=0;
                for (auto &i: vInventory)
                {
                    if (i->Quantity <=0)
                    {
                        delete i;
                        vInventory.erase(vInventory.begin()+ii);
                    }
                    ++ii;
                }
*/
            }
            else ;
        }
        else
            MouseText = "Not enough Resources !";

    }
    else
    {
        fConstruction =0.0f;

        fDestruction =0.0f;
        MouseText = "";

    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
else if(Health>0)
{
    //std::string strAmmo = "Ammo: "
    std::string strHealth= "Health";
    DrawString(ScreenWidth()/2-strHealth.size()*8/2,ScreenHeight()-20,strHealth);
    FillRect(ScreenWidth()/2-strHealth.size()*8/2,ScreenHeight()-10,strHealth.size()*8*Health,5, olc::RED);
     DrawRect(ScreenWidth()/2-strHealth.size()*8/2,ScreenHeight()-10,strHealth.size()*8,5, olc::WHITE);
    if (GetMouse(0).bPressed)
    {
        vBullets.push_back(new Bullet(fPlayerX,fPlayerY,fPlayerA));
    }



}


