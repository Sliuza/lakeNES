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
  // flags
  uint8_t f_carry = 0;
  uint8_t f_zero = 0;
  uint8_t f_interrupt = 0;
  uint8_t f_decimal = 0;
  uint8_t f_overflow = 0;
  uint8_t f_negative = 0;
  uint8_t flags = 0;
  Rom rom;
  uint8_t ram[0xFFFF];

  public:
  Cpu();
  void loadROM(string path);
  void printROM();
  void startCpu();
  uint8_t read_mem(uint16_t addr);
  void write_mem(uint8_t val, uint16_t addr);
  void push(uint8_t val);
  uint8_t pull();
  void run();
  void reset();
  uint16_t getAddressBasedOnAddressingMode(uint8_t addressingMode);
  uint16_t get16BitsAddress(uint16_t address);
  uint16_t get16BitsAddressInMemory(uint16_t address);

  //GETTERS
  uint16_t
  getPc_reg();              // program counter, 2 byte
  uint8_t getSp_reg();      // stack pointer
  uint8_t getX_reg();       // x register
  uint8_t getY_reg();       // y register
  uint8_t getA_reg();       // a register
  uint8_t getF_carry();     // carry flag
  uint8_t getF_zero();      // zero flag
  uint8_t getF_interrupt(); // interrupt flag
  uint8_t getF_decimal();   // decimal flag
  uint8_t getF_overflow();  // overflow flag
  uint8_t getF_negative();  // negative flag

  Rom getRom();
  //SETTERS
  void setPc_reg(uint16_t _pc_reg);       // program counter, 2 byte
  void setSp_reg(uint8_t _sp_reg);        // stack pointer
  void setX_reg(uint8_t _x_reg);          // x register
  void setY_reg(uint8_t _y_reg);          // y register
  void setA_reg(uint8_t _a_reg);          // a register
  void setF_carry(uint8_t carry);         // carry flag
  void setF_zero(uint8_t zero);           // zero flag
  void setF_interrupt(uint8_t interrupt); // interrupt flag
  void setF_decimal(uint8_t decimal);     // decimal flag
  void setF_overflow(uint8_t overflow);   // overflow flag
  void setF_negative(uint8_t negative);   // negative flag
};

uint8_t make_P(uint8_t t1, uint8_t t2, uint8_t t3, uint8_t t4, uint8_t t5, uint8_t t6);

#endif
