#include "FlagManager.h"
enum class InputFlags{
    start =-1,
    LeftMouseButton,
    RightMouseButton,
    end


};


class cInputManager: public cFlagManager<InputFlags>
{

    using cFlagManager::cFlagManager;

};