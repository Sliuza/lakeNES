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

  this->instances = {
      {ADC, new ADCInstruction()},
      {AND, new ANDInstruction()},
      {ASL, new ASLInstruction()},
      {BCC, new BCCInstruction()},
      {BCS, new BCSInstruction()},
      {BEQ, new BEQInstruction()},
      {BIT, new BITInstruction()},
      {BMI, new BMIInstruction()},
      {BNE, new BNEInstruction()},
      {BPL, new BPLInstruction()},
      {BRK, new BRKInstruction()},
      {BVC, new BVCInstruction()},
      {BVS, new BVSInstruction()},
      {CLC, new CLCInstruction()},
      {CLD, new CLDInstruction()},
      {CLI, new CLIInstruction()},
      {CLV, new CLVInstruction()},
      {CMP, new CMPInstruction()},
      {CPX, new CPXInstruction()},
      {CPY, new CPYInstruction()},
      {EOR, new EORInstruction()},
      {JMP, new JMPInstruction()},
      {JSR, new JSRInstruction()},
      {LDA, new LDAInstruction()},
      {LDX, new LDXInstruction()},
      {LDY, new LDYInstruction()},
      {LSR, new LSRInstruction()},
      {NOP, new NOPInstruction()},
      {ORA, new ORAInstruction()},
      {PHA, new PHAInstruction()},
      {PHP, new PHPInstruction()},
      {PLA, new PLAInstruction()},
      {PLP, new PLPInstruction()},
      {RTI, new RTIInstruction()},
      {RTS, new RTSInstruction()},
      {STA, new STAInstruction()},
      {STX, new STXInstruction()},
      {STY, new STYInstruction()},
      {DEC, new DECInstruction()},
      {DEX, new DEXInstruction()},
      {DEY, new DEYInstruction()},
      {INC, new INCInstruction()},
      {INX, new INXInstruction()},
      {INY, new INYInstruction()},
      {SBC, new SBCInstruction()},
      {TAX, new TAXInstruction()},
      {TAY, new TAYInstruction()},
      {TSX, new TSXInstruction()},
      {TXA, new TXAInstruction()},
      {TXS, new TXSInstruction()},
      {TYA, new TYAInstruction()},
      {SEC, new SECInstruction()},
      {SEI, new SEIInstruction()},
      {SED, new SEDInstruction()},
      {ROL, new ROLInstruction()},
      {ROR, new RORInstruction()}};

  this->instructions = {

      /* https://www.masswerk.at/6502/6502_instruction_set.html#ADC */

      /* ADC Instruction */
      {0x69, {ADC, IMMEDIATE, PRINT}},
      {0x65, {ADC, ZERO_PAGE, PRINTLS}},
      {0x75, {ADC, INDEXED_ZERO_PAGE_X, PRINTLS}},
      {0x6D, {ADC, ABSOLUTE, PRINTLS}},
      {0x7D, {ADC, INDEXED_ABSOLUTE_X, PRINTLS}},
      {0x79, {ADC, INDEXED_ABSOLUTE_Y, PRINTLS}},
      {0x71, {ADC, INDIRECT_INDEXED, PRINTLS}},
      {0x61, {ADC, INDEXED_INDIRECT, PRINTLS}},

      /* AND Instruction */
      {0x29, {AND, IMMEDIATE, PRINT}},
      {0x25, {AND, ZERO_PAGE, PRINTLS}},
      {0x35, {AND, INDEXED_ZERO_PAGE_X, PRINTLS}},
      {0x2D, {AND, ABSOLUTE, PRINTLS}},
      {0x3D, {AND, INDEXED_ABSOLUTE_X, PRINTLS}},
      {0x39, {AND, INDEXED_ABSOLUTE_Y, PRINTLS}},
      {0x31, {AND, INDIRECT_INDEXED, PRINTLS}},
      {0x21, {AND, INDEXED_INDIRECT, PRINTLS}},

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
      {0xD1, {CMP, INDIRECT_INDEXED, PRINTLS}},
      {0xC1, {CMP, INDEXED_INDIRECT, PRINTLS}},
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
      {0x51, {EOR, INDIRECT_INDEXED, PRINTLS}},
      {0x41, {EOR, INDEXED_INDIRECT, PRINTLS}},

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
      {0x11, {ORA, INDIRECT_INDEXED, PRINTLS}},
      {0x01, {ORA, INDEXED_INDIRECT, PRINTLS}},

      /* PHA Instructions*/
      {0x48, {PHA, IMPLIED, PRINTLS}},
      /* PHP Instructions*/
      {0x08, {PHP, IMPLIED, PRINTLS}},
      /* PLA Instructions*/
      {0x68, {PLA, IMPLIED, PRINTLS}},
      /* PLP Instructions*/
      {0x28, {PLP, IMPLIED, PRINTLS}},

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
      {0xB1, {LDA, INDIRECT_INDEXED, PRINTLS}},
      {0xA1, {LDA, INDEXED_INDIRECT, PRINTLS}},

      /* LDX Instructions*/
      {0xA2, {LDX, IMMEDIATE, PRINT}},
      {0xA6, {LDX, ZERO_PAGE, PRINTLS}},
      {0xB6, {LDX, INDEXED_ZERO_PAGE_Y, PRINTLS}},
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
      {0X91, {STA, INDIRECT_INDEXED, PRINTLS}},
      {0X81, {STA, INDEXED_INDIRECT, PRINTLS}},

      /*STX Instructions*/
      {0x86, {STX, ZERO_PAGE, PRINTLS}},
      {0X96, {STX, INDEXED_ZERO_PAGE_Y, PRINTLS}},
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
      {0xBA, {TSX, IMPLIED, PRINT}},

      /*TXA instructions*/
      {0x8A, {TXA, IMPLIED, PRINT}},

      /*TXS instructions*/
      {0x9A, {TXS, IMPLIED, PRINT}},

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

Instruction *InstructionFactory::getInstanceById(uint8_t instructionID) {
  return this->instances.at(instructionID);
};

Instruction *InstructionFactory::createInstruction(uint8_t opCode) {
  OperationAttributes attributes = this->getOperationAttributes(opCode);
  uint8_t instructionSize = this->getInstructionSize(opCode);
  Instruction *instruction = this->getInstanceById(attributes.id);
  instruction->setAddressingMode(attributes.addressingMode);
  instruction->setInstructionSize(instructionSize);
  instruction->setPrintMode(attributes.printMode);
  instruction->setCycles(attributes.cycles);
  return instruction;
};
