#pragma once

#ifndef Cpu_hpp
#define Cpu_hpp

#include "Memory.hpp"
#include "Rom.hpp"
#include <bitset>
#include <fstream>
#include <iostream>
#include <stdint.h>
#include <vector>

using namespace std;

class Cpu {
private:
  // counter registers: store a single byte
  uint16_t pc_reg = 0; // program counter, 2 byte
  uint8_t sp_reg = 0;  // stack pointer

  // data registers: store a single byte
  uint8_t x_reg = 0; // x register
  uint8_t y_reg = 0; // y register
  uint8_t a_reg = 0; // a register
  Rom rom;
  Memory ram;

public:
  Cpu();
  int getNumberOfPrgBlocks();
  void loadROM(string path);
  void printROM();
};

#endif
