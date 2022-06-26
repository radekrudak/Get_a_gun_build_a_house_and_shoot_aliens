#pragma once
#include <cstdint>
class cTimeManager{
  private:
    //time in miliseconds 
  uint64_t m_WorldTime =0;

  public:
  const auto*GetPtrToWorldTime()
  {
    return &m_WorldTime;
  }
  const auto &GetWorldTime()
  {
    return m_WorldTime;
  }
  void SetWorldTime(int_fast32_t NewTime)
  {
    m_WorldTime = NewTime;
  }
  void AddTime(int_fast32_t TimeAdded)
  {
    m_WorldTime+=TimeAdded;
  }
  
};
