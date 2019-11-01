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
  virtual uint8_t getPrintMode() = 0;
  virtual void setInstructionSize(uint8_t instructionSize) = 0;
  virtual void setAddressingMode(uint8_t addressingMode) = 0;
  virtual void setPrintMode(uint8_t printMode) = 0;
};

class BaseInstruction : public Instruction {

  private:
  uint8_t _addressingMode;
  uint8_t _instructionSize;
  uint8_t _printMode;

  public:
  BaseInstruction();
  BaseInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode);
  uint8_t getInstructionSize();
  uint8_t getAddressingMode();
  uint8_t getPrintMode();
  void setInstructionSize(uint8_t instructionSize);
  void setAddressingMode(uint8_t addressingMode);
  void setPrintMode(uint8_t printMode);
};

class ADCInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class ANDInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class ASLInstruction : public BaseInstruction {
  public:
  // ASLInstruction();
  void execute(Cpu *cpu, uint16_t address = 0);
};

class BCCInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class BCSInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class BEQInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class BITInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class BMIInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class BNEInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class BPLInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class BRKInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class NMIInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu);
};

class BVCInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class BVSInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class CLCInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class CLDInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class CLIInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class CLVInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class CMPInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class CPXInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class CPYInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class EORInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class JMPInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class JSRInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class LSRInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class NOPInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class PHPInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class PHAInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class PLAInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class PLPInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class ORAInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class RTIInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class RTSInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class SECInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};
class SEDInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class SEIInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class LDAInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class LDXInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class LDYInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class STAInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class STXInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class STYInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class DECInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class DEXInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class DEYInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class INCInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class INXInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class INYInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class SBCInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class TAXInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class TAYInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class TSXInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class TXAInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class TXSInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class TYAInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class RORInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

class ROLInstruction : public BaseInstruction {
  public:
  void execute(Cpu *cpu, uint16_t address = 0);
};

#endif
