
if(GetKey(olc::Key::U).bPressed)
{
    isDebugMode = !isDebugMode;
}
if (isDebugMode)
{
    if (GetKey(olc::Key::O).bPressed)
    {
            
        std::cout<<"Debug Mode \n";
        if (ScreenMode == WhichScreen::MAIN_MENU)
        {
            
        NewGame();
        }
        else if(ScreenMode == WhichScreen::GAMEPLAY) 
            ScreenMode = WhichScreen::MAIN_MENU;
    }




}