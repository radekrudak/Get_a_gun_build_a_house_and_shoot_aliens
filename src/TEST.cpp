#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Game.h"
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class Test : public olc::PixelGameEngine
{
public:
	Test()
	{
		sAppName = "Test";
	}
    sTextureManager TestTextureManager;
    sTileManager TestTileManager;
public:
    

	
    bool OnUserCreate() override
	{

    int a =0;

    TestTextureManager.LoadGraphics();
    std::cout<<sizeof(Tile)<<" "<<sizeof(std::unique_ptr<Tile>)<<std::endl;
    std::cin >> a;
    for (int i=0;i<a;i++)
        TestTileManager.LoadStaticTiles(TestTextureManager.TextureNameMap);

    std::cin >> a;
    TestTileManager.ClearStaticTiles();
		// Called once at the start, so create things here
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// called once per frame
		for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
				Draw(x, y, olc::Pixel(rand() % 255, rand() % 255, rand()% 255));	
		return true;
	}
};


int main()
{
	Test demo;
	if (demo.Construct(256, 240, 4, 4))
		demo.Start();

}