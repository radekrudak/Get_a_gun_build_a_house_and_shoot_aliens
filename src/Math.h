#pragma once

#if BACKEND == OLC_PIXEL_GAME_ENGINE
  #include "./ThirdPartyFiles/olcPixelGameEngine/olcPixelGameEngine.h"
  using VecInt2d = olc::vi2d ;
#endif

inline float Distance(float x1, float y1, float x2, float y2)
{
  return sqrtf((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
