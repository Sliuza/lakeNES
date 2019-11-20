#ifndef InstructionFactory_hpp
#define InstructionFactory_hpp
#pragma once

#include "AddressingMode.hpp"
#include "Instruction.hpp"
#include "OperationAttributes.hpp"
#include <cstdio>
#include <map>
#include <stdio.h>

using namespace std;

class InstructionFactory {
  private:
  OperationAttributes instructions[255];
  uint8_t addressingModeSize[13];
  Instruction *instances[60];

  public:
  InstructionFactory();
  ~InstructionFactory();

  OperationAttributes getOperationAttributes(uint8_t opCode);
  uint8_t getInstructionSize(uint8_t opCode);
  Instruction *createInstruction(uint8_t opCode);
  Instruction *getInstanceById(uint8_t instructionID);
};

#endif
