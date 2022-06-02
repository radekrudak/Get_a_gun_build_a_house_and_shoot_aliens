#include "FlagManager.h"
enum class InputFlags{
    start =-1,
    LeftMouseButton,
    end


};


class cInputManager: public cFlagManager<InputFlags>
{

    using cFlagManager::cFlagManager;

};