License Information: Everything in this reposytory writen by me is under GPL 3 license, files not made by me have it's own licenses specyfied on top of file itself.
Files not made by me:
 src/ThirdPartyFiles/nlohmann/json.hpp : Json single heather file library 
 src/ThirdPartyFiles/olcPixelGameEngine/olcPixelGameEngine.h : single file, cross platform graphics and userinput framework
 src/ThirdPartyFiles/olcPixelGameEngine/olcPGEX_PopUpMenu.h : (Modyfied by me by adding Delete and DeleteAllChildren functions) extension to the olcPixelGameEngine (provides popup menu system)

Coding project that started as CodeJam enterence (original enterence should still be present on my github)

General Idea of arhitecture:
Code is segmented into Managers each responsible for it own thing, ManagersManager is "One to rule them all" when some fucntion needs to acces more than one manager should be put here.

Game.h shouldn't have any framework specyfic drawing rutines or framework specyfic IO, all the framework/library specyfic should be in the backends. Backend should gather all the inputs, set flags in InputManager, Them execute GameUpdate() and do drawing.

That's general idea for now, but since it wasn't from the start some of the ideas requre implementation (rewrite).
