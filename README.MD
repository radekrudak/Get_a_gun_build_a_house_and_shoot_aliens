License Information: Everything in this reposytory writen by me is under GPL 3 license, files not made by me have it's own licenses specyfied on top of file itself.<br>
Files not made by me:<br>
 src/nlohmann/json.hpp : Json single heather file library <br>
 src/BackEnds/olcPixelGameEngine/olcPGEX_PopUpMenu.h : single file, cross platform graphics and userinput framework<br>
 src/BackEnds/olcPixelGameEngine/olcPGEX_PopUpMenu.h extension to the olcPixelGameEngine (provides popup menu system)<br>

Coding project that started as CodeJam enterence (original enterence should still be present on my github)

General Idea of arhitecture:
Code is segmented into Managers each responsible for it own thing, ManagersManager is "One to rule them all" when some fucntion needs to acces more than one manager should be put here.

Game.h shouldn't have any framework specyfic drawing rutines or framework specyfic IO, all the framework/library specyfic should be in the backends. Backend should gather all the inputs, set flags in InputManager, Them execute GameUpdate() and do drawing.

That's general idea for now, but since it wasn't from the start some of the ideas requre implementation (rewrite).
