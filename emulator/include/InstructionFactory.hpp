#ifndef InstructionFactory_hpp
#define InstructionFactory_hpp
#pragma once

#include "AddressingMode.hpp"
#include "Instruction.hpp"
#include <cstdio>
#include <map>
#include <stdio.h>
#include <vector>

using namespace std;
typedef pair<uint8_t, uint8_t> operation_pair_t;

class InstructionFactory {
private:
  map<uint8_t, pair<uint8_t, uint8_t>> instructions;
  map<uint8_t, uint8_t> addressingModeSize;

public:
  InstructionFactory();
  ~InstructionFactory();

  operation_pair_t getOperationPair(uint8_t opCode);
  uint8_t getInstructionSize(uint8_t opCode);
  Instruction *createInstruction(uint8_t opCode);
};

#endif
