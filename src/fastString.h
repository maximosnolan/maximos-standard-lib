#ifndef FAST_STRING_H
#define FAST_STRING_H

struct __intRep
{
  const int * __data; 
  unsigned int size; 
};

union __data
{
    const char * __sPtr = nullptr; 
    __intRep intRep;  
};


class fastString 
{
  public: 

  explicit fastString(const char * str);
    
  [[nodiscard]] bool operator==(const fastString& other) const noexcept;

  private: 

  __data data; 
};

#endif 
