
if(GetKey(olc::Key::U).bPressed)
{
    isDebugMode = !isDebugMode;
}
if (isDebugMode)
{
    if (GetKey(olc::Key::O).bPressed)
    {
            
        std::cout<<"Debug Mode \n";
        if (ScreenMode == WhitchScreen::MAIN_MENU)
        {
            
        NewGame();
        }
        else if(ScreenMode == WhitchScreen::GAMEPLAY) 
            ScreenMode = WhitchScreen::MAIN_MENU;
    }




}