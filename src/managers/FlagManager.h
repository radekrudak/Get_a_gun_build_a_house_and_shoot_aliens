
#include <vector>
template <typename T>
class cFlagManager
{

    std::vector<unsigned char> vFlags;

public:
    cFlagManager()
    {
        int size = static_cast<int>(T::end);
        vFlags.resize(size, false);
    }

    bool &operator[](int Offset)
    {
        return (bool &)(vFlags[Offset]);
    }
    bool &operator[](T Flag)
    {
        return (bool &)(vFlags[static_cast<int>(Flag)]);
    }

    bool Get(int Offset)
    {
        return vFlags[Offset];
    }
    bool Get(T Flag)
    {
        return vFlags[static_cast<int>(Flag)];
    }

    void Set(int Offset, bool value)
    {
        vFlags[Offset] = value;
    }
    void Set(T Flag, bool value)
    {
        vFlags[static_cast<int>(Flag)] = value;
    }
    void Flip(int Offset)
    {
        vFlags[Offset] = !vFlags[Offset];
    }
    void Flip(T Flag)
    {
        vFlags[static_cast<int>(Flag)] = !vFlags[static_cast<int>(Flag)];
    }
};