#include "../src/fastString.h"
#include <cassert>

int main()
{
  fastString s1 = "hello world";
  fastString s2 = "hello world";

  assert(s1 == s2);
}
