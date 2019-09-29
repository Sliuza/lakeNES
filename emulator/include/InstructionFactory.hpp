#ifndef InstructionFactory_hpp
#define InstructionFactory_hpp
#pragma once

#include "AddressingMode.hpp"
#include "Instruction.hpp"
#include "OperationAttributes.hpp"
#include <cstdio>
#include <map>
#include <stdio.h>
#include <vector>

using namespace std;

class InstructionFactory {
  private:
  map<uint8_t, OperationAttributes> instructions;
  map<uint8_t, uint8_t> addressingModeSize;

  public:
  InstructionFactory();
  ~InstructionFactory();

  OperationAttributes getOperationAttributes(uint8_t opCode);
  uint8_t getInstructionSize(uint8_t opCode);
  Instruction *createInstruction(uint8_t opCode);
};

#endif
