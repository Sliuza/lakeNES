#ifndef Memory_hpp
#define Memory_hpp

#include <iostream>
#include <list>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class Memory {
private:
  vector<uint8_t> _data;

public:
  Memory(uint size = 64 * 1024); /* 64KB*/
  vector<uint8_t> getData();
};

#endif
