#include "../include/InstructionFactory.hpp"
#include "../include/AddressingMode.hpp"
#include "../include/InstructionID.hpp"

InstructionFactory::InstructionFactory() {

  this->addressingModeSize = {
      {ABSOLUTE, 3},
      {INDEXED_ABSOLUTE_X, 3},
      {INDEXED_ABSOLUTE_Y, 3},
      {ACCUMULATOR, 1},
      {IMMEDIATE, 2},
      {IMPLIED, 1},
      {INDIRECT, 2},
      {INDIRECT_INDEXED, 2},
      {INDEXED_INDIRECT, 2},
      {RELATIVE, 2},
      {ZERO_PAGE, 2},
      {INDEXED_ZERO_PAGE_X, 2},
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
      {0x29, make_pair(AND, IMMEDIATE)},
      {0x25, make_pair(AND, ZERO_PAGE)},
      {0x35, make_pair(AND, INDEXED_ZERO_PAGE_X)},
      {0x2D, make_pair(AND, ABSOLUTE)},
      {0x3D, make_pair(AND, INDEXED_ABSOLUTE_X)},
      {0x39, make_pair(AND, INDEXED_ABSOLUTE_Y)},
      {0x21, make_pair(AND, INDIRECT_INDEXED)},
      {0x31, make_pair(AND, INDEXED_INDIRECT)},

      /* ASL Instruction */
      {0x0A, make_pair(ASL, IMMEDIATE)},
      {0x06, make_pair(ASL, ZERO_PAGE)},
      {0x16, make_pair(ASL, INDEXED_ZERO_PAGE_X)},
      {0x0E, make_pair(ASL, ABSOLUTE)},
      {0x0E, make_pair(ASL, INDEXED_ABSOLUTE_X)},

      /* LDA Instructions*/
      {0xA9, make_pair(LDA, IMMEDIATE)},
      {0xA5, make_pair(LDA, ZERO_PAGE)},
      {0xB5, make_pair(LDA, INDEXED_ZERO_PAGE_X)},
      {0xAD, make_pair(LDA, ABSOLUTE)},
      {0xBD, make_pair(LDA, INDEXED_ABSOLUTE_X)},
      {0xB9, make_pair(LDA, INDEXED_ABSOLUTE_Y)},
      {0xA1, make_pair(LDA, INDIRECT_INDEXED)},
      {0xB1, make_pair(LDA, INDEXED_INDIRECT)},

      /* LDX Instructions*/
      {0xA2, make_pair(LDX, IMMEDIATE)},
      {0xA6, make_pair(LDX, ZERO_PAGE)},
      {0xB6, make_pair(LDX, INDEXED_ZERO_PAGE_Y)},
      {0xAE, make_pair(LDX, ABSOLUTE)},
      {0xBE, make_pair(LDX, INDEXED_ABSOLUTE_Y)},

      /* LDY Instructions*/
      {0xA0, make_pair(LDY, IMMEDIATE)},
      {0xA4, make_pair(LDY, ZERO_PAGE)},
      {0xB4, make_pair(LDY, INDEXED_ZERO_PAGE_X)},
      {0xAC, make_pair(LDY, ABSOLUTE)},
      {0xBC, make_pair(LDY, INDEXED_ABSOLUTE_X)},

      /*STA Instructions*/
      {0x85, make_pair(STA, ZERO_PAGE)},
      {0X95, make_pair(STA, INDEXED_ZERO_PAGE_X)},
      {0x8D, make_pair(STA, ABSOLUTE)},
      {0X9D, make_pair(STA, INDEXED_ABSOLUTE_X)},
      {0X99, make_pair(STA, INDEXED_ABSOLUTE_Y)},
      {0X81, make_pair(STA, INDIRECT_INDEXED)},
      {0X91, make_pair(STA, INDEXED_INDIRECT)},

      /*DEC instructions*/
      /* AND Instruction */
      {0xC6, make_pair(DEC, ZERO_PAGE)},
      {0xD6, make_pair(DEC, INDEXED_ZERO_PAGE_X)},
      {0xCE, make_pair(DEC, ABSOLUTE)},
      {0xDE, make_pair(DEC, INDEXED_ABSOLUTE_X)},
  };
};

InstructionFactory::~InstructionFactory() {}

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
      return new ADCInstruction(addressingMode, instructionSize);
      break;
    }
    case AND: {
      return new ANDInstruction(addressingMode, instructionSize);
      break;
    }
    case LDA: {
      return new LDAInstruction(addressingMode, instructionSize);
      break;
    }
    case LDX: {
      return new LDXInstruction(addressingMode, instructionSize);
      break;
    }
    case LDY: {
      return new LDYInstruction(addressingMode, instructionSize);
      break;
    }
    case STA: {
      return new STAInstruction(addressingMode, instructionSize);
      break;
    }
    case DEC:{
      return new DECInstruction(addressingMode, instructionSize);
      break;
    }

    default: { break; }
  }

  return NULL;
};
