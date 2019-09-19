#ifndef Instruction_hpp
#define Instruction_hpp

#include "Cpu.hpp"
#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

/* Instruction Interface. */
class Instruction {
protected:
  uint8_t _addressingMode;
  uint8_t _instructionSize;

public:
  virtual void execute(Cpu *cpu, uint16_t address = 0) = 0;
  virtual uint8_t getInstructionSize() = 0;
  virtual uint8_t getAddressingMode() = 0;
};

class ADCInstruction : public Instruction {
public:
  ADCInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address);

  // TODO: This is a common implementation for all instructions. Extract a
  // parent common class to all of them, so that we can implement it only once.
  uint8_t getInstructionSize();
  uint8_t getAddressingMode();
};

#endif
