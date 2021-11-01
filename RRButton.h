#pragma once
class RRButton{

public:
    float x=0;
    float y=0;
    float width=0;
    float height=0;
    float colorr =0.25f;
    float colorg =0.25f;
    float colorb =0.25f;
    std::string Label;

    RRButton(float xx, float yy,float ww,float hh,std::string l, float cr=0.25f, float cg=0.25f, float cb=0.25f ) :
    x(xx), y(yy), width(ww),height(hh),colorr(cr),colorb(cb),colorg(cg), Label(l)
    {
        ;
    }

   //#ifdef OLC_PGE_APPLICATION
    bool  IsClicked(olc::PixelGameEngine *PGE)
    {
       
        
        if(PGE->GetMouseX() >=x && PGE->GetMouseX() <= x+width && PGE->GetMouseY()>=y && PGE->GetMouseY()<= y+height )
        {
             //std::cout<<"Menu check"<<std::endl;
             PGE->FillRect(x,y,PGE->ScreenWidth()/4*2,25,olc::PixelF(colorr+0.10f,colorg+0.10f,colorb+0.10f));
             if(PGE->GetMouse(0).bPressed)
             {
                  
                 return true;
             }
        }
        else{
             PGE->FillRect(x,y,PGE->ScreenWidth()/4*2,25,olc::PixelF(colorr,colorg,colorb));
        }
        PGE->DrawString(x,y+height/2-4,Label);

        return false;
    }
   // #endif

};