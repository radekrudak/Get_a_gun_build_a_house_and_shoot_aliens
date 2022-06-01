#define OLC_PGE_APPLICATION
#include "Game.h"

int main()
{
   
#if defined ( __clang__)
    std::cout << "Compiled with Clang C++ compiler (clang++)" ;
#elif defined ( __GNUC__)
    std::cout << "Compiled with GNU C++ compiler (g++)";
#endif
    std::cout<<std::endl<< "on "<<__DATE__<<" at "<<__TIME__<<std::endl;
    std::cout << "Creating olcPixelGameEngine instance " << std::endl;
    GameJam game;
    if (game.Construct(480, 270, 4, 4))
        game.Start();
    return 0;
}
