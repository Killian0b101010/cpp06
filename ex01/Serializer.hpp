#ifndef Serializer_HPP
#define Serializer_HPP
#include <cstdint>
#include <iostream>

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
