#ifndef Instruction_hpp
#define Instruction_hpp

#include "Cpu.hpp"
#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

/* Instruction Interface. */
class Instruction {
public:
  virtual void execute(Cpu *cpu, uint16_t address = 0) = 0;
  virtual uint8_t getInstructionSize() = 0;
  virtual uint8_t getAddressingMode() = 0;
};

class BaseInstruction : public Instruction {

private:
  uint8_t _addressingMode;
  uint8_t _instructionSize;

public:
  BaseInstruction(uint8_t addressingMode, uint8_t instructionSize);
  uint8_t getInstructionSize();
  uint8_t getAddressingMode();
};

class ADCInstruction : public BaseInstruction {
public:
  ADCInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class ANDInstruction : public BaseInstruction {
public:
  ANDInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class ASLInstruction : public BaseInstruction {
public:
  ASLInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class LDAInstruction : public BaseInstruction {
public:
  LDAInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class LDXInstruction : public BaseInstruction {
public:
  LDXInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class LDYInstruction : public BaseInstruction {
public:
  LDYInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class STAInstruction : public BaseInstruction {
public:
  STAInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class DECInstruction : public BaseInstruction {
public:
  DECInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class DEXInstruction : public BaseInstruction {
public:
  DEXInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class DEYInstruction : public BaseInstruction {
public:
  DEYInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class INCInstruction : public BaseInstruction {
public:
  INCInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class INXInstruction : public BaseInstruction {
public:
  INXInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class INYInstruction : public BaseInstruction {
public:
  INYInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class SBCInstruction : public BaseInstruction {
public:
  SBCInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

#endif
