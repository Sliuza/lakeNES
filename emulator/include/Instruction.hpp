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

class BCCInstruction : public BaseInstruction {
public:
  BCCInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class BCSInstruction : public BaseInstruction {
public:
  BCSInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class BEQInstruction : public BaseInstruction {
public:
  BEQInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class BITInstruction : public BaseInstruction {
public:
  BITInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class BMIInstruction : public BaseInstruction {
public:
  BMIInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class BNEInstruction : public BaseInstruction {
public:
  BNEInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class BPLInstruction : public BaseInstruction {
public:
  BPLInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class BRKInstruction : public BaseInstruction {
public:
  BRKInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class BVCInstruction : public BaseInstruction {
public:
  BVCInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class BVSInstruction : public BaseInstruction {
public:
  BVSInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class CLCInstruction : public BaseInstruction {
public:
  CLCInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class CLDInstruction : public BaseInstruction {
public:
  CLDInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class CLIInstruction : public BaseInstruction {
public:
  CLIInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class CLVInstruction : public BaseInstruction {
public:
  CLVInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class CMPInstruction : public BaseInstruction {
public:
  CMPInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class CPXInstruction : public BaseInstruction {
public:
  CPXInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class CPYInstruction : public BaseInstruction {
public:
  CPYInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class EORInstruction : public BaseInstruction {
public:
  EORInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class JMPInstruction : public BaseInstruction {
public:
  JMPInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class JSRInstruction : public BaseInstruction {
public:
  JSRInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class LSRInstruction : public BaseInstruction {
public:
  LSRInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class NOPInstruction : public BaseInstruction {
public:
  NOPInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class PHPInstruction : public BaseInstruction {
public:
  PHPInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class PHAInstruction : public BaseInstruction {
public:
  PHAInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class PLAInstruction : public BaseInstruction {
public:
  PLAInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class PLPInstruction : public BaseInstruction {
public:
  PLPInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class ORAInstruction : public BaseInstruction {
public:
  ORAInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class RTIInstruction : public BaseInstruction {
public:
  RTIInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class RTSInstruction : public BaseInstruction {
public:
  RTSInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class SECInstruction : public BaseInstruction {
public:
  SECInstruction(uint8_t addressingMode, uint8_t instructionSize);
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

class STXInstruction : public BaseInstruction {
public:
  STXInstruction(uint8_t addressingMode, uint8_t instructionSize);
  void execute(Cpu *cpu, uint16_t address = 0);
};

class STYInstruction : public BaseInstruction {
public:
  STYInstruction(uint8_t addressingMode, uint8_t instructionSize);
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
