#ifndef Serializer_HPP
#define Serializer_HPP
#include <iostream>
#include <stdint.h>
typedef struct Data 
{
 std::string _name;
  int _age;
}Data;

class Serializer {
private:
  Serializer();
  Serializer(const Serializer &cpy);
  Serializer &operator=(const Serializer &other);
  ~Serializer();

  public:
  static uintptr_t serialize(Data *ptr);
  static Data *deserialize(uintptr_t raw);
};
#endif
