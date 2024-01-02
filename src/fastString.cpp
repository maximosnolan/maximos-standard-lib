#include "fastString.h"
#include <cstring>
#include <utility>


fastString::fastString(const char * str)
{
  data.intRep.size = strlen(str);
  data.intRep.__data = reinterpret_cast<const int *>(std::move(str));
}

[[nodiscard]] bool fastString::operator==(const fastString& other) const noexcept
{
  if (data.intRep.size != other.data.intRep.size)
  {
    return false; 
  }

  for (unsigned int i = 0; i < data.intRep.size; ++i)
  {
    if (data.intRep.__data[i] != other.data.intRep.__data[i]) 
    {
      return false;
    }
  }
  return true; 

}
