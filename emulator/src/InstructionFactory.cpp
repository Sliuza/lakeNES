#include "../include/InstructionFactory.hpp"
#include "../include/AddressingMode.hpp"
#include "../include/InstructionID.hpp"

InstructionFactory::InstructionFactory() {
  this->addressingModeSize = {{ABSOLUTE, 3},           {INDEXED_ABSOLUTE_X, 3},
                              {INDEXED_ABSOLUTE_Y, 3}, {ACCUMULATOR, 1},
                              {IMMEDIATE, 2},          {IMPLIED, 1},
                              {INDIRECT, 2},           {INDIRECT_INDEXED, 2},
                              {INDEXED_INDIRECT, 2},   {RELATIVE, 2},
                              {ZERO_PAGE, 2},          {INDEXED_ZERO_PAGE_X, 2},
                              {INDEXED_ZERO_PAGE_Y, 2}};

  this->instructions = {

      /* https://www.masswerk.at/6502/6502_instruction_set.html#ADC */

      /* ADC Instruction */
      {0x69, make_pair(ADC, IMMEDIATE)},
      {0x65, make_pair(ADC, ZERO_PAGE)},
      {0x75, make_pair(ADC, INDEXED_ZERO_PAGE_X)},
      {0x6D, make_pair(ADC, ABSOLUTE)},
      {0x7D, make_pair(ADC, INDEXED_ABSOLUTE_X)},
      {0x79, make_pair(ADC, INDEXED_ABSOLUTE_Y)},
      {0x61, make_pair(ADC, INDIRECT_INDEXED)},
      {0x71, make_pair(ADC, INDEXED_INDIRECT)},

      /* AND Instruction */
  };
};

operation_pair_t InstructionFactory::getOperationPair(uint8_t opCode) {
  return this->instructions.at(opCode);
};

uint8_t InstructionFactory::getInstructionSize(uint8_t opCode) {
  operation_pair_t pair = this->getOperationPair(opCode);
  return this->addressingModeSize.at(pair.second);
};

Instruction *InstructionFactory::createInstruction(uint8_t opCode) {
  operation_pair_t pair = this->getOperationPair(opCode);
  uint instructionSize = this->getInstructionSize(opCode);
  uint instructionID = pair.first;
  uint addressingMode = pair.second;

  switch (instructionID) {
  case ADC: {
    return new LDAInstruction(addressingMode, instructionSize);
    break;
  }
  default: { break; }
  }

  return NULL;
};
