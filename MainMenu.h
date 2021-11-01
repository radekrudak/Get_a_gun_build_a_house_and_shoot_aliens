#include "RRButton.h"


inline void MainMenu(olc::PixelGameEngine* PGE, int &lG, int &lP, int &lN,int &output )
{
    PGE->SetDrawTarget(lG);
    PGE->Clear(olc::BLANK);
    
    PGE->SetDrawTarget(lP);
    PGE->Clear(olc::BLANK);

    PGE->SetDrawTarget(lN);
    PGE->Clear(olc::BLANK);

    PGE->SetDrawTarget(nullptr);
    PGE->Clear(olc::BLANK);

    const float LabelPosytionY =100;

    RRButton NewGameButton(PGE->ScreenWidth()/4,LabelPosytionY,PGE->ScreenWidth()/4*2,25,"Create New World" );
   
    if(NewGameButton.IsClicked(PGE))
    {
        
        output = 1;
        //PGE->NewGame(); i wanted to use this function but for some reason it told PGE dson't have it
        // (even trough it actually have) so i had to improvise

    }

}