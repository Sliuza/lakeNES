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

  //GETTERS
  uint16_t getPc_reg(); // program counter, 2 byte
  uint8_t getSp_reg();  // stack pointer
  uint8_t getX_reg(); // x register
  uint8_t getY_reg(); // y register
  Rom getRom();
  Memory getRam();
  
  //SETTERS
  void setPc_reg(uint16_t _pc_reg); // program counter, 2 byte
  void setSp_reg(uint8_t _sp_reg);  // stack pointer
  void setX_reg(uint8_t _x_reg); // x register
  void setY_reg(uint8_t _y_reg); // y register
  void setA_reg(uint8_t _a_reg);
};

#endif
