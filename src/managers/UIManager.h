#pragma once
#include <vector>
enum class UIFlags{

    start = -1,
    isStatsDis,
    end

};



class cUIManager
{
    std::vector<char> vFlags;
public:
    cUIManager()
    {
        int size = static_cast<int>(UIFlags::end);
        vFlags.resize(size,false);
    }

    bool &operator[](int Offset)
    {
        return *((bool*)(&vFlags[Offset]));
    }
    bool &operator[](UIFlags Flag)
    {
        return *((bool*)(&vFlags[static_cast<int>(Flag)]));

    }


    bool Get(int Offset)
    {
        return vFlags[Offset];
    }
    bool Get(UIFlags Flag)
    {
        return vFlags[static_cast<int>(Flag)];
    }

    void Set(int Offset,bool value)
    {
        vFlags[Offset] = value;
    }
    void Set(UIFlags Flag,bool value)
    {
        vFlags[static_cast<int>(Flag)] = value ;
    }
    void Flip(int Offset)
    {
        vFlags[Offset] = !vFlags[Offset];
    }
    void Flip(UIFlags Flag)
    {
        vFlags[static_cast<int>(Flag)] = !vFlags[static_cast<int>(Flag)] ;
    }
};