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
	cUIManager TestUIManager;
public:
    

	
    bool OnUserCreate() override
	{


		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// called once per frame
		Clear(olc::BACK);
			for (int y = 0; y < 5; y++)
				DrawString(0, y*16,std::to_string(TestUIManager.Get(y)),olc::WHITE);	
		if(GetKey(olc::A).bPressed)
			for (int y = 0; y < 5; y++)
				TestUIManager[y] = !TestUIManager[y] ;
		return true;
	}
};


int main()
{

	Test demo;
	if (demo.Construct(256, 240, 4, 4))
		demo.Start();

}