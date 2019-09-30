#include "../include/InstructionFactory.hpp"
#include "../include/AddressingMode.hpp"
#include "../include/InstructionID.hpp"
#include "../include/PrintFunction.hpp"
#include "../include/OperationAttributes.hpp"

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
      {0x69, {ADC, IMMEDIATE, PRINT}},
      {0x65, {ADC, ZERO_PAGE, PRINTLS}},
      {0x75, {ADC, INDEXED_ZERO_PAGE_X, PRINTLS}},
      {0x6D, {ADC, ABSOLUTE, PRINTLS}},
      {0x7D, {ADC, INDEXED_ABSOLUTE_X, PRINTLS}},
      {0x79, {ADC, INDEXED_ABSOLUTE_Y, PRINTLS}},
      {0x61, {ADC, INDIRECT_INDEXED, PRINTLS}},
      {0x71, {ADC, INDEXED_INDIRECT, PRINTLS}},

      /* AND Instruction */
      {0x29, {AND, IMMEDIATE, PRINT}},
      {0x25, {AND, ZERO_PAGE, PRINTLS}},
      {0x35, {AND, INDEXED_ZERO_PAGE_X, PRINTLS}},
      {0x2D, {AND, ABSOLUTE, PRINTLS}},
      {0x3D, {AND, INDEXED_ABSOLUTE_X, PRINTLS}},
      {0x39, {AND, INDEXED_ABSOLUTE_Y, PRINTLS}},
      {0x21, {AND, INDIRECT_INDEXED, PRINTLS}},
      {0x31, {AND, INDEXED_INDIRECT, PRINTLS}},

      /* ASL Instruction */
      {0x0A, {ASL, ACCUMULATOR, PRINT}},
      {0x06, {ASL, ZERO_PAGE, PRINTLS}},
      {0x16, {ASL, INDEXED_ZERO_PAGE_X, PRINTLS}},
      {0x0E, {ASL, ABSOLUTE, PRINTLS}},
      {0x0E, {ASL, INDEXED_ABSOLUTE_X, PRINTLS}},

      /* BCC,BCS,BEQ Instruction */
      {0x90, {BCC, RELATIVE, PRINT}},
      {0xB0, {BCS, RELATIVE, PRINT}},
      {0xF0, {BEQ, RELATIVE, PRINT}},

      /* BIT Instruction */
      {0x24, {BIT, ZERO_PAGE, PRINTLS}},
      {0x2C, {BIT, ABSOLUTE, PRINTLS}},

      /* BMI,BNE,BPL Instruction */
      {0x30, {BMI, RELATIVE, PRINT}},
      {0xD0, {BNE, RELATIVE, PRINT}},
      {0x10, {BPL, RELATIVE, PRINT}},

      /* BRK Instruction */
      {0x00, {BRK, IMPLIED, PRINT}},

      /* BVC,BVS Instruction */
      {0x50, {BVC, RELATIVE, PRINT}},
      {0x70, {BVS, RELATIVE, PRINT}},

      /* CLC Instruction */
      {0x18, {CLC, IMPLIED, PRINT}},

      /* CLD Instruction */
      {0xD8, {CLD, IMPLIED, PRINT}},

      /* CLI Instruction */
      {0x58, {CLI, IMPLIED, PRINT}},

      /* SEI Instruction */
      {0x78, {SEI, IMPLIED, PRINT}},

      /* CLV Instruction */

      {0xB8, {CLV, IMPLIED, PRINT}},

      /* CMP Instruction */
      {0xC9, {CMP, IMMEDIATE, PRINT}},
      {0xC5, {CMP, ZERO_PAGE, PRINTLS}},
      {0xD5, {CMP, INDEXED_ZERO_PAGE_X, PRINTLS}},
      {0xCD, {CMP, ABSOLUTE, PRINTLS}},
      {0xDD, {CMP, INDEXED_ABSOLUTE_X, PRINTLS}},
      {0xD9, {CMP, INDEXED_ABSOLUTE_Y, PRINTLS}},
      {0xC1, {CMP, INDIRECT_INDEXED, PRINTLS}},
      {0xD1, {CMP, INDEXED_INDIRECT, PRINTLS}},
      /* CPX Instruction */
      {0xE0, {CPX, IMMEDIATE, PRINT}},
      {0xE4, {CPX, ZERO_PAGE, PRINTLS}},
      {0xEC, {CPX, ABSOLUTE, PRINTLS}},
      /* CPY Instruction */
      {0xC0, {CPY, IMMEDIATE, PRINT}},
      {0xC4, {CPY, ZERO_PAGE, PRINTLS}},
      {0xCC, {CPY, ABSOLUTE, PRINTLS}},

      /* EOR Instructions*/
      {0x49, {EOR, IMMEDIATE, PRINT}},
      {0x45, {EOR, ZERO_PAGE, PRINTLS}},
      {0x55, {EOR, INDEXED_ZERO_PAGE_X, PRINTLS}},
      {0x4D, {EOR, ABSOLUTE, PRINTLS}},
      {0x5D, {EOR, INDEXED_ABSOLUTE_X, PRINTLS}},
      {0x59, {EOR, INDEXED_ABSOLUTE_Y, PRINTLS}},
      {0x41, {EOR, INDIRECT_INDEXED, PRINTLS}},
      {0x51, {EOR, INDEXED_INDIRECT, PRINTLS}},

      /* JMP Instructions*/
      {0x4C, {JMP, ABSOLUTE, PRINT}},
      {0x6C, {JMP, INDIRECT, PRINT}},

      /* JSR Instructions*/
      {0x20, {JSR, ABSOLUTE, PRINT}},

      /* LSR Instructions*/
      {0x4A, {LSR, ACCUMULATOR, PRINT}},
      {0x46, {LSR, ZERO_PAGE, PRINTLS}},
      {0x56, {LSR, INDEXED_ZERO_PAGE_X, PRINTLS}},
      {0x4E, {LSR, ABSOLUTE, PRINTLS}},
      {0x5E, {LSR, INDEXED_ABSOLUTE_X, PRINTLS}},

      /* NOP Instructions*/
      {0xEA, {NOP, IMPLIED, PRINT}},

      /* ORA Instructions*/
      {0x09, {ORA, IMMEDIATE, PRINT}},
      {0x05, {ORA, ZERO_PAGE, PRINTLS}},
      {0x15, {ORA, INDEXED_ZERO_PAGE_X, PRINTLS}},
      {0x0D, {ORA, ABSOLUTE, PRINTLS}},
      {0x1D, {ORA, INDEXED_ABSOLUTE_X, PRINTLS}},
      {0x19, {ORA, INDEXED_ABSOLUTE_Y, PRINTLS}},
      {0x01, {ORA, INDIRECT_INDEXED, PRINTLS}},
      {0x11, {ORA, INDEXED_INDIRECT, PRINTLS}},

      /* PHA Instructions*/
      {0x48, {PHA, IMPLIED, PRINTLS}},
      /* PHP Instructions*/
      {0x09, {PHP, IMPLIED, PRINTLS}},
      /* PLA Instructions*/
      {0x69, {PLA, IMPLIED, PRINTLS}},
      /* PLP Instructions*/
      {0x29, {PLP, IMPLIED, PRINTLS}},

      /* RTI Instructions*/
      {0x40, {RTI, IMPLIED, PRINT}},
      /* RTS Instructions*/
      {0x60, {RTS, IMPLIED, PRINT}},

      /* SEC Instructions*/
      {0x38, {SEC, IMPLIED, PRINT}},
      /* SED Instructions*/
      {0xF8, {SED, IMPLIED, PRINT}},

      /* LDA Instructions*/
      {0xA9, {LDA, IMMEDIATE, PRINT}},
      {0xA5, {LDA, ZERO_PAGE, PRINTLS}},
      {0xB5, {LDA, INDEXED_ZERO_PAGE_X, PRINTLS}},
      {0xAD, {LDA, ABSOLUTE, PRINTLS}},
      {0xBD, {LDA, INDEXED_ABSOLUTE_X, PRINTLS}},
      {0xB9, {LDA, INDEXED_ABSOLUTE_Y, PRINTLS}},
      {0xA1, {LDA, INDIRECT_INDEXED, PRINTLS}},
      {0xB1, {LDA, INDEXED_INDIRECT, PRINTLS}},

      /* LDX Instructions*/
      {0xA2, {LDX, IMMEDIATE, PRINT}},
      {0xA6, {LDX, ZERO_PAGE, PRINTLS}},
      {0xB6, {LDX, INDEXED_ZERO_PAGE_Y, PRINT}},
      {0xAE, {LDX, ABSOLUTE, PRINTLS}},
      {0xBE, {LDX, INDEXED_ABSOLUTE_Y, PRINTLS}},

      /* LDY Instructions*/
      {0xA0, {LDY, IMMEDIATE, PRINT}},
      {0xA4, {LDY, ZERO_PAGE, PRINTLS}},
      {0xB4, {LDY, INDEXED_ZERO_PAGE_X, PRINTLS}},
      {0xAC, {LDY, ABSOLUTE, PRINTLS}},
      {0xBC, {LDY, INDEXED_ABSOLUTE_X, PRINTLS}},

      /*STA Instructions*/
      {0x85, {STA, ZERO_PAGE, PRINTLS}},
      {0X95, {STA, INDEXED_ZERO_PAGE_X, PRINTLS}},
      {0x8D, {STA, ABSOLUTE, PRINTLS}},
      {0X9D, {STA, INDEXED_ABSOLUTE_X, PRINTLS}},
      {0X99, {STA, INDEXED_ABSOLUTE_Y, PRINTLS}},
      {0X81, {STA, INDIRECT_INDEXED, PRINTLS}},
      {0X91, {STA, INDEXED_INDIRECT, PRINTLS}},

      /*STX Instructions*/
      {0x86, {STX, ZERO_PAGE, PRINTLS}},
      {0X96, {STX, INDEXED_ZERO_PAGE_Y, PRINT}},
      {0x8E, {STX, ABSOLUTE, PRINTLS}},

      /*STY Instructions*/
      {0x84, {STY, ZERO_PAGE, PRINTLS}},
      {0X94, {STY, INDEXED_ZERO_PAGE_X, PRINTLS}},
      {0x8C, {STY, ABSOLUTE, PRINTLS}},

      /*DEC instructions*/
      {0xC6, {DEC, ZERO_PAGE, PRINTLS}},
      {0xD6, {DEC, INDEXED_ZERO_PAGE_X, PRINTLS}},
      {0xCE, {DEC, ABSOLUTE, PRINTLS}},
      {0xDE, {DEC, INDEXED_ABSOLUTE_X, PRINTLS}},

      /*DEX instructions*/
      {0xCA, {DEX, IMPLIED, PRINT}},

      /*DEY instructions*/
      {0x88, {DEY, IMPLIED, PRINT}},

      /*INC instructions*/
      {0xE6, {INC, ZERO_PAGE, PRINTLS}},
      {0xF6, {INC, INDEXED_ZERO_PAGE_X, PRINTLS}},
      {0xEE, {INC, ABSOLUTE, PRINTLS}},
      {0xFE, {INC, INDEXED_ABSOLUTE_X, PRINTLS}},

      /*INX instructions*/
      {0xE8, {INX, IMPLIED, PRINT}},

      /*INY instructions*/
      {0xC8, {INY, IMPLIED, PRINT}},

      /*SBC instructions*/
      {0xE9, {SBC, IMMEDIATE, PRINT}},
      {0xE5, {SBC, ZERO_PAGE, PRINTLS}},
      {0xF5, {SBC, INDEXED_ZERO_PAGE_X, PRINTLS}},
      {0xED, {SBC, ABSOLUTE, PRINTLS}},
      {0xFD, {SBC, INDEXED_ABSOLUTE_X, PRINTLS}},
      {0xF9, {SBC, INDEXED_ABSOLUTE_Y, PRINTLS}},
      {0xF1, {SBC, INDIRECT_INDEXED, PRINTLS}},
      {0xE1, {SBC, INDEXED_INDIRECT, PRINTLS}},

      /*ROR instructions*/
      {0x6A, {ROR, ACCUMULATOR, PRINT}},
      {0X66, {ROR, ZERO_PAGE, PRINTLS}},
      {0X76, {ROR, INDEXED_ZERO_PAGE_X, PRINTLS}},
      {0X6E, {ROR, ABSOLUTE, PRINTLS}},
      {0X7E, {ROR, INDEXED_ABSOLUTE_X, PRINTLS}},

      /*ROL instructions*/
      {0x2A, {ROL, ACCUMULATOR, PRINT}},
      {0X26, {ROL, ZERO_PAGE, PRINTLS}},
      {0X36, {ROL, INDEXED_ZERO_PAGE_X, PRINTLS}},
      {0X2E, {ROL, ABSOLUTE, PRINTLS}},
      {0X3E, {ROL, INDEXED_ABSOLUTE_X, PRINTLS}},

      /*TAX instructions*/
      {0xAA, {TAX, IMPLIED, PRINT}},

      /*TAY instructions*/
      {0xA8, {TAY, IMPLIED, PRINT}},

      /*TSX instructions*/
      {0xA8, {TSX, IMPLIED, PRINT}},

      /*TXA instructions*/
      {0x8A, {TXA, IMPLIED, PRINT}},

      /*TXS instructions*/
      {0x9A, {TXA, IMPLIED, PRINT}},

      /*TYA instructions*/
      {0x98, {TYA, IMPLIED, PRINT}},
  };
};

InstructionFactory::~InstructionFactory() {}

OperationAttributes InstructionFactory::getOperationAttributes(uint8_t opCode) {
  return this->instructions.at(opCode);
};

uint8_t InstructionFactory::getInstructionSize(uint8_t opCode) {
  OperationAttributes attributes = this->getOperationAttributes(opCode);
  return this->addressingModeSize.at(attributes.addressingMode);
};

Instruction *InstructionFactory::createInstruction(uint8_t opCode) {
  OperationAttributes attributes = this->getOperationAttributes(opCode);
  uint8_t instructionSize = this->getInstructionSize(opCode);
  uint8_t instructionID = attributes.id;
  uint8_t addressingMode = attributes.addressingMode;
  uint8_t printMode = attributes.printMode;

  switch (instructionID) {
    case ASL: {
      return new ASLInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case BCC: {
      return new BCCInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case BEQ: {
      return new BEQInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case BIT: {
      return new BITInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case BCS: {
      return new BCSInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case BMI: {
      return new BMIInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case BNE: {
      return new BNEInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case BRK: {
      return new BRKInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case BVC: {
      return new BVCInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case ADC: {
      return new ADCInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case BVS: {
      return new BVSInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case CLC: {
      return new CLCInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case CLD: {
      return new CLDInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case CLI: {
      return new CLIInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case CLV: {
      return new CLVInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case CMP: {
      return new CMPInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case CPY: {
      return new CPYInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case EOR: {
      return new EORInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case JSR: {
      return new JSRInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case JMP: {
      return new JMPInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case LSR: {
      return new LSRInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case ORA: {
      return new ORAInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case PHA: {
      return new PHAInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case PHP: {
      return new PHPInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case PLA: {
      return new PLAInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case PLP: {
      return new PLPInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case RTI: {
      return new RTIInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case RTS: {
      return new RTSInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case SEC: {
      return new SECInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case AND: {
      return new ANDInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case LDA: {
      return new LDAInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case LDX: {
      return new LDXInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case LDY: {
      return new LDYInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case STA: {
      return new STAInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case STX: {
      return new STXInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case STY: {
      return new STYInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case DEC: {
      return new DECInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case DEX: {
      return new DEXInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case DEY: {
      return new DEYInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case INC: {
      return new INCInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case INX: {
      return new INXInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case INY: {
      return new INYInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case SBC: {
      return new SBCInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case SED: {
      return new SEDInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case SEI: {
      return new SEIInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case TAX: {
      return new TAXInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case TAY: {
      return new TAYInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case TSX: {
      return new TSXInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case TXA: {
      return new TSXInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case TXS: {
      return new TSXInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case TYA: {
      return new TSXInstruction(addressingMode, instructionSize, printMode);
      break;
    }

    case ROR: {
      return new RORInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case ROL: {
      return new ROLInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    case NOP: {
      return new NOPInstruction(addressingMode, instructionSize, printMode);
      break;
    }
    default: { break; }
  }

  return NULL;
};
