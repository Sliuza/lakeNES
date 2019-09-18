#pragma once

#ifndef Rom_hpp
#define Rom_hpp

#include <iostream>
#include <list>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class Rom {
private:
  unsigned int memory_start_location = 0x8000;
  int memory_end_location = 0xFFFF;
  int header_size = 0x10;
  int num_prg_blocks;
  bool hasROM = false;
  vector<uint8_t> rom_bytes;

public:
  // Rom(vector<uint8_t> rom_bytes);
  Rom();
  void setBytes(vector<uint8_t> rom_bytes);
  vector<uint8_t> getRom();
};

#endif
