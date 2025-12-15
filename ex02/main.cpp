
#include "Base.hpp"
#include <iostream>

int main(void) {
  Base *p = Base::generate();

  std::cout << "Identify pointer:   ";
  p->identify(p);

  std::cout << "Identify reference: ";
  p->identify(*p);

  delete p;

  return 0;
}
