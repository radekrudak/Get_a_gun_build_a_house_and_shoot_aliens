#pragma once

#include "olcPixelGameEngine.h"
#include <mutex>
#include "whitch_screen_enum.h"
//#include <functional> // std::ref
#include "RRButton.h"
#include "MainMenu.h"
#include "MapGen.h"
#include "Tile.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Item.h"
#include "FindPath.h"
#include <vector>
// later in code included Controls.h & GameStart.h


// to do:
// Enemies
// shooting
// health
// Hud:
// HP
// Resourses
// ammo ?
// items
// cleaning up code
// crafting
// inventory
// and freaking more 
// tile selected to build

using TZpos = PositionOnTileStack;

static std::mutex s_nodes;
// pushesh back row of nodes, only reason it's seperate function is to use aprralelism
inline void AddNodeRow (std::vector<std::vector<sNode*>> &vNodeMap,int size=512 )
{   
    
   
    std::vector<sNode*>  v1;
    for(int i=0;i<size;++i)
    {
        v1.push_back(new sNode());

    }
    std::lock_guard<std::mutex> lock(s_nodes);
     std::cout<<" Allocating node x: "<<vNodeMap.size()<<std::endl;
    vNodeMap.push_back(v1);
    std::cout<<" Allocation of node x: "<<vNodeMap.size()<<"finished"<<std::endl;

}

constexpr int TileSize =16;
constexpr float PI = 3.14159;
float Distance(float x1, float y1,float x2,float y2)
{
    return sqrtf((x1 -x2)*(x1 -x2)+(y1 -y2)*(y1 -y2));
}
class GameJam : public olc::PixelGameEngine
{

    public:
    WhitchScreen ScreenMode = WhitchScreen::MAIN_MENU;
    int MapSize = 1024;
    int NodeMapSize = 128;
    
    double fTileScale =1.0f;
    float fTest;
    friend Enemy;
/// BOOLS
    bool isEnd = false;
    bool isStatsDis = false;
    bool isFightMode = false;
    bool isNight = false;
    bool isNightStartSequence = false;
    bool isDebugMode = false;
/// players Stuff
    float fCameraX;
    float fCameraY;
    float fPlayerX =64.5f;
    float fPlayerY =64.5f;
    float fPlayerA =0.0f;
    float fDestruction =1.0f;
    float fConstruction = 0.0f;
    float fMouseMapX =0.0f;
    float fMouseMapY = 0.0f;
    float fReachDistance =2;
    double Health =1 ;
    std::string MouseText;
// Game Clocks stuff;
    double fSeconds =0;
    int PreviousSecond=0;
    double fSecondsInDay=20.;

///////////////////////////////////////////// /VIASUAL EVECTS
    float fModeTextFading = 1.0f; // used in left top  mode displaying text fading effect
    int ModeTextLap = 50; // used in left top  mode displaying text fading effect
/////////////////////






////////////////////// layers
    int lGround;
    int lPlayer;
    int lNight;
//////////////////////////// Sprites
    olc::Sprite *sGrass =nullptr;
    olc::Sprite *sWood =nullptr;
    olc::Sprite *sMT =nullptr;
    olc::Sprite *sTest=nullptr;
    olc::Sprite *sMC=nullptr;
    olc::Sprite *sWoodWall=nullptr;
    olc::Sprite *sWoodFloor=nullptr;
    olc::Sprite *sEnemy=nullptr;
    olc::Sprite *sNight = nullptr;
    olc::Sprite *sMoonAndSun = nullptr;
    olc::Sprite *sPGELogo = nullptr;

    olc::Decal *dTest = nullptr;
    olc::Decal *dPGELogo = nullptr;
    olc::Decal  *dWood = nullptr;
    olc::Decal *dMoonAndSun = nullptr;
    olc::Decal *dNight = nullptr;
    olc::Decal *dMC=nullptr;
    Tile *Tilemapp;

// ARRAYS/vectors
    std::vector<std::vector< std::vector<Tile *> > > vTileMap;

// body is at the end of this file, this fun. goes through vector and chechs if one of the tile is colisive if yes returnes true other wise false
    bool isColisivTileInIt( std::vector<Tile *> vTiless);


// when replacing vTiles array size replace in Enemy.h too.
    std::vector<Tile*> vTiles ; // 0= Grass, 1 = Wood etc.
    std::vector<Tile*> vBuildableTiles;
    int ChosenBuildTile = 2;
    std::vector<Item*> vItems;
    std::vector<ItemSlot*> vInventory;

//std::vector<int> aResourses= {0,0,0};
    std::vector<Bullet*> vBullets;
    std::vector<Enemy*> vEnemies;
// Node map for A* path finding
    std::vector<std::vector<sNode*>> vNodeMap;
    std::vector<olc::vf2d> Path;

    int FinishdEarly =0;
    int ElapsedFrames =0;

    std::thread *threadAstar=nullptr;
    float AStarCounterMax=0.5f;
    float AStarCounter =AStarCounterMax;
public:
    GameJam()
    {
        // Name your application
        sAppName = "GameJamEntry";

    }


    void SpawnEnemy();

    inline void NewGame()
    {
        // Add "generating terrain" screen

        // seting player(and time) values to default
        fPlayerX =64.5f;
        fPlayerY =64.5f;
        fPlayerA =0.0f;
        fDestruction =1.0f;
        fConstruction = 0.0f;
        fMouseMapX =0.0f;
        fMouseMapY = 0.0f;
        fReachDistance =2;
        Health =1 ;
        fSeconds =0;

        GenerateMap(vTileMap,vTiles);
        ScreenMode = WhitchScreen::GAMEPLAY;
        
    }

    inline bool IsEnoughItems(Item* SearchedItem,int Quant)
    {

        for(auto &i: vInventory)
        {
            if(i->ItemPtr== SearchedItem&& Quant<= i->Quantity)
            {
                return true;
            }
        }
        return false;
    }
     ItemSlot* FindItemInInventory(Item* SearchedItem)
    {


        for (auto &i:vInventory)
        {
            if(i->ItemPtr==SearchedItem)
            {
                return i;
            }

        }
        return nullptr;
    }
public:
     bool OnUserCreate() override;




    inline bool OnUserUpdate(float fElapsedTime) override
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
                    FindPath(olc::vf2d(fCameraX+1,fCameraY+1), olc::vf2d(fPlayerX,fPlayerY),vNodeMap,vEnemies[vEnemies.size()-1]->Path,vTileMap,FinishdEarly);

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

                DrawRotatedDecal(olc::vf2d((fPlayerX-fCameraX)*TileSize*fTileScale,(fPlayerY-fCameraY)*TileSize*fTileScale),dMC, fPlayerA+PI/2, {float(sMC->width)/2.0f,float(sMC->height)/2.0f});

                {

                std::vector<std::thread *> vThreads; 
                int ii=0;
                ///Draws Enemy
                for(auto &i: vEnemies)
                {
                    vThreads.push_back( new std::thread( FindPath, olc::vf2d(i->x,i->y), olc::vf2d(fPlayerX,fPlayerY),vNodeMap,
                                    std::ref(vEnemies[vEnemies.size()-1]->Path),std::ref(vTileMap),std::ref(FinishdEarly )) );

                    
                    i->Move(fPlayerX,fPlayerY,fElapsedTime);

                    DrawDecal(olc::vf2d((i->x-fCameraX)*TileSize-TileSize/2,(i->y-fCameraY)*TileSize-TileSize/2),i->Decal);

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

                for(auto &i: Path)
                {
                    FillCircle((i.x-fCameraX)*TileSize+TileSize/2,(i.y-fCameraY)*TileSize+TileSize/2,10, vNodeMap[i.x][i.y]->isColisive ? olc::RED : olc::BLUE); // vTileMap[i.x][i.y].back()->isColisive()
                }

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


    bool OnUserDestroy() override
    {
        std::cout<<"Frames: " << ElapsedFrames<<" A start finished early: "<< FinishdEarly << std::endl;
        delete sGrass;
        return true;
    }
};



