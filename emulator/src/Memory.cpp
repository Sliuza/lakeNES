
#include "../include/Memory.hpp"
#include <iostream>
#include <list>
#include <stdio.h>
#include <string>

/* Representation of a 64KB memory.*/
Memory::Memory(uint size) {
  this->_data.reserve(size);
  cout << "Alocating Memory\n"; // TODO: This Constructor is been called to many
                                // times. Fix it!
}
