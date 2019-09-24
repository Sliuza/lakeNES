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

      /* BCC,BCS,BEQ Instruction */
      {0x90, make_pair(BCC, RELATIVE)},
      {0xB0, make_pair(BCS, RELATIVE)},
      {0xF0, make_pair(BEQ, RELATIVE)},

      /* BIT Instruction */
      {0x24, make_pair(BIT, ZERO_PAGE)},
      {0x2C, make_pair(BIT, ABSOLUTE)},

      /* BMI,BNE,BPL Instruction */
      {0x30, make_pair(BMI, RELATIVE)},
      {0xD0, make_pair(BNE, RELATIVE)},
      {0x10, make_pair(BPL, RELATIVE)},
      
      /* BRK Instruction */
      {0x00, make_pair(BRK, IMPLIED)},
      
      /* BVC,BVS Instruction */
      {0x50, make_pair(BVC, RELATIVE)},
      {0x70, make_pair(BVS, RELATIVE)},
      
      /* CLC Instruction */
      {0x18, make_pair(CLC, IMPLIED)},
      /* CLD Instruction */
      {0xD8, make_pair(CLD, IMPLIED)},
      /* CLI Instruction */
      {0x58, make_pair(CLI, IMPLIED)},
      /* CLV Instruction */
      {0xB8, make_pair(CLV, IMPLIED)},
      /* CMP Instruction */
      {0xC9, make_pair(CMP, IMMEDIATE)},
      {0xC5, make_pair(CMP, ZERO_PAGE)},
      {0xD5, make_pair(CMP, INDEXED_ZERO_PAGE_X)},
      {0xCD, make_pair(CMP, ABSOLUTE)},
      {0xDD, make_pair(CMP, INDEXED_ABSOLUTE_X)},
      {0xD9, make_pair(CMP, INDEXED_ABSOLUTE_Y)},
      {0xC1, make_pair(CMP, INDIRECT_INDEXED)},
      {0xD1, make_pair(CMP, INDEXED_INDIRECT)},
      /* CPX Instruction */
      {0xE0, make_pair(CPX, IMMEDIATE)},
      {0xE4, make_pair(CPX, ZERO_PAGE)},
      {0xEC, make_pair(CPX, ABSOLUTE)},
      /* CPY Instruction */
      {0xC0, make_pair(CPY, IMMEDIATE)},
      {0xC4, make_pair(CPY, ZERO_PAGE)},
      {0xCC, make_pair(CPY, ABSOLUTE)},

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
      {0xC6, make_pair(DEC, ZERO_PAGE)},
      {0xD6, make_pair(DEC, INDEXED_ZERO_PAGE_X)},
      {0xCE, make_pair(DEC, ABSOLUTE)},
      {0xDE, make_pair(DEC, INDEXED_ABSOLUTE_X)},

      /*DEX instructions*/
      {0xCA, make_pair(DEX, IMPLIED)},

      /*DEY instructions*/
      {0x88, make_pair(DEY, IMPLIED)},

      /*INC instructions*/
      {0xE6, make_pair(INC, ZERO_PAGE)},
      {0xF6, make_pair(INC, INDEXED_ZERO_PAGE_X)},
      {0xEE, make_pair(INC, ABSOLUTE)},
      {0xFE, make_pair(INC, INDEXED_ABSOLUTE_X)},

      /*INX instructions*/
      {0xE8, make_pair(INX, IMPLIED)},

      /*INY instructions*/
      {0xC8, make_pair(INY, IMPLIED)},

      /*SBC instructions*/
      {0xE9, make_pair(SBC, IMMEDIATE)},
      {0xE5, make_pair(SBC, ZERO_PAGE)},
      {0xF5, make_pair(SBC, INDEXED_ZERO_PAGE_X)},
      {0xED, make_pair(SBC, ABSOLUTE)},
      {0xFD, make_pair(SBC, INDEXED_ABSOLUTE_X)},
      {0xF9, make_pair(SBC, INDEXED_ABSOLUTE_Y)},
      {0xF1, make_pair(SBC, INDIRECT_INDEXED)},
      {0xE1, make_pair(SBC, INDEXED_INDIRECT)},

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
    case DEX:{
      return new DEXInstruction(addressingMode, instructionSize);
      break;
    }
    case DEY:{
      return new DEYInstruction(addressingMode, instructionSize);
      break;
    }
    case INC:{
      return new INCInstruction(addressingMode, instructionSize);
      break;
    }
    case INX:{
      return new INXInstruction(addressingMode, instructionSize);
      break;
    }
    case INY:{
      return new INYInstruction(addressingMode, instructionSize);
      break;
    }
    case SBC:{
      return new SBCInstruction(addressingMode, instructionSize);
      break;
    }

    default: { break; }
  }

  return NULL;
};
