#pragma once

#ifndef Cpu_hpp
#define Cpu_hpp

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
  uint8_t ram[0x800];

public:
  Cpu();
  int getNumberOfPrgBlocks();
  void loadROM(string path);
  void printROM();
  void startCpu();
  enum Interrupt_type { BRK = 0, IRQ, NMI, reset };
  uint8_t read_mem(uint16_t addr);
  void write_mem(uint8_t val, uint16_t addr);
  void push(uint8_t val);
  uint8_t pull();
  void interrupt(Interrupt_type interruption);
  void run();
  //GETTERS
  uint16_t getPc_reg(); // program counter, 2 byte
  uint8_t getSp_reg();  // stack pointer
  uint8_t getX_reg(); // x register
  uint8_t getY_reg(); // y register
  uint8_t getA_reg(); // a register
  Rom getRom();
  //SETTERS
  void setPc_reg(uint16_t _pc_reg); // program counter, 2 byte
  void setSp_reg(uint8_t _sp_reg);  // stack pointer
  void setX_reg(uint8_t _x_reg); // x register
  void setY_reg(uint8_t _y_reg); // y register
  void setA_reg(uint8_t _a_reg);
};

#endif
