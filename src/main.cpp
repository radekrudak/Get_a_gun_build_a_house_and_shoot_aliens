#define OLC_PGE_APPLICATION
#include "Game.h"

int main()
{
    std::cout<<"Creating olcPixelGameEngine instance "<<std::endl;
    GameJam game;
    if (game.Construct(480,270 , 4, 4))
        game.Start();
    return 0;
}
