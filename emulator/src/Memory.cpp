
#include "../include/Memory.hpp"
#include <iostream>
#include <list>
#include <stdio.h>
#include <string>

/* Representation of a 64KB memory.*/
Memory::Memory(uint size) {
  _data.reserve(size);
  cout << "Alocating Memory\n";
}
