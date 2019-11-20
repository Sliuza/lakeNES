#include "../include/InstructionFactory.hpp"
#include "../include/AddressingMode.hpp"
#include "../include/InstructionID.hpp"
#include "../include/PrintFunction.hpp"
#include "../include/OperationAttributes.hpp"

InstructionFactory::InstructionFactory() {

  this->addressingModeSize[ABSOLUTE] = 3;
  this->addressingModeSize[INDEXED_ABSOLUTE_X] = 3;
  this->addressingModeSize[INDEXED_ABSOLUTE_Y] = 3;
  this->addressingModeSize[ACCUMULATOR] = 1;
  this->addressingModeSize[IMMEDIATE] = 2;
  this->addressingModeSize[IMPLIED] = 1;
  this->addressingModeSize[INDIRECT] = 2;
  this->addressingModeSize[INDIRECT_INDEXED] = 2;
  this->addressingModeSize[INDEXED_INDIRECT] = 2;
  this->addressingModeSize[RELATIVE] = 2;
  this->addressingModeSize[ZERO_PAGE] = 2;
  this->addressingModeSize[INDEXED_ZERO_PAGE_X] = 2;
  this->addressingModeSize[INDEXED_ZERO_PAGE_Y] = 2;

  this->instances[ADC] = new ADCInstruction();
  this->instances[AND] = new ANDInstruction();
  this->instances[ASL] = new ASLInstruction();
  this->instances[BCC] = new BCCInstruction();
  this->instances[BCS] = new BCSInstruction();
  this->instances[BEQ] = new BEQInstruction();
  this->instances[BIT] = new BITInstruction();
  this->instances[BMI] = new BMIInstruction();
  this->instances[BNE] = new BNEInstruction();
  this->instances[BPL] = new BPLInstruction();
  this->instances[BRK] = new BRKInstruction();
  this->instances[BVC] = new BVCInstruction();
  this->instances[BVS] = new BVSInstruction();
  this->instances[CLC] = new CLCInstruction();
  this->instances[CLD] = new CLDInstruction();
  this->instances[CLV] = new CLVInstruction();
  this->instances[CMP] = new CMPInstruction();
  this->instances[CPX] = new CPXInstruction();
  this->instances[CPY] = new CPYInstruction();
  this->instances[EOR] = new EORInstruction();
  this->instances[JMP] = new JMPInstruction();
  this->instances[JSR] = new JSRInstruction();
  this->instances[LDA] = new LDAInstruction();
  this->instances[LDX] = new LDXInstruction();
  this->instances[LDY] = new LDYInstruction();
  this->instances[LSR] = new LSRInstruction();
  this->instances[NOP] = new NOPInstruction();
  this->instances[ORA] = new ORAInstruction();
  this->instances[PHA] = new PHAInstruction();
  this->instances[PHP] = new PHPInstruction();
  this->instances[PLA] = new PLAInstruction();
  this->instances[PLP] = new PLPInstruction();
  this->instances[RTI] = new RTIInstruction();
  this->instances[RTS] = new RTSInstruction();
  this->instances[STA] = new STAInstruction();
  this->instances[STX] = new STXInstruction();
  this->instances[STX] = new STXInstruction();
  this->instances[STY] = new STYInstruction();
  this->instances[DEC] = new DECInstruction();
  this->instances[DEX] = new DEXInstruction();
  this->instances[DEY] = new DEYInstruction();
  this->instances[INC] = new INCInstruction();
  this->instances[INX] = new INXInstruction();
  this->instances[INY] = new INYInstruction();
  this->instances[SBC] = new SBCInstruction();
  this->instances[TAX] = new TAXInstruction();
  this->instances[TAY] = new TAYInstruction();
  this->instances[TSX] = new TSXInstruction();
  this->instances[TXA] = new TXAInstruction();
  this->instances[TXS] = new TXSInstruction();
  this->instances[TYA] = new TYAInstruction();
  this->instances[SEC] = new SECInstruction();
  this->instances[SEI] = new SEIInstruction();
  this->instances[SED] = new SEDInstruction();
  this->instances[ROL] = new ROLInstruction();
  this->instances[ROR] = new RORInstruction();

  /* https://www.masswerk.at/6502/6502_instruction_set.html#ADC */

  /* ADC Instruction */
  this->instructions[0x69] = {ADC, IMMEDIATE, PRINT, 2, "ADC"};
  this->instructions[0x65] = {ADC, ZERO_PAGE, PRINTLS, 3, "ADC"};
  this->instructions[0x75] = {ADC, INDEXED_ZERO_PAGE_X, PRINTLS, 4, "ADC"};
  this->instructions[0x6D] = {ADC, ABSOLUTE, PRINTLS, 4, "ADC"};
  this->instructions[0x7D] = {ADC, INDEXED_ABSOLUTE_X, PRINTLS, 4, "ADC"};
  this->instructions[0x79] = {ADC, INDEXED_ABSOLUTE_Y, PRINTLS, 4, "ADC"};
  this->instructions[0x71] = {ADC, INDIRECT_INDEXED, PRINTLS, 5, "ADC"};
  this->instructions[0x61] = {ADC, INDEXED_INDIRECT, PRINTLS, 6, "ADC"};

  /* AND Instruction */
  this->instructions[0x29] = {AND, IMMEDIATE, PRINT, 2, "AND"};
  this->instructions[0x25] = {AND, ZERO_PAGE, PRINTLS, 3, "AND"};
  this->instructions[0x35] = {AND, INDEXED_ZERO_PAGE_X, PRINTLS, 4, "AND"};
  this->instructions[0x2D] = {AND, ABSOLUTE, PRINTLS, 4, "AND"};
  this->instructions[0x3D] = {AND, INDEXED_ABSOLUTE_X, PRINTLS, 4, "AND"};
  this->instructions[0x39] = {AND, INDEXED_ABSOLUTE_Y, PRINTLS, 4, "AND"};
  this->instructions[0x31] = {AND, INDIRECT_INDEXED, PRINTLS, 5, "AND"};
  this->instructions[0x21] = {AND, INDEXED_INDIRECT, PRINTLS, 6, "AND"};

  /* ASL Instruction */
  this->instructions[0x0A] = {ASL, ACCUMULATOR, PRINT, 2, "ASL"};
  this->instructions[0x06] = {ASL, ZERO_PAGE, PRINTLS, 5, "ASL"};
  this->instructions[0x16] = {ASL, INDEXED_ZERO_PAGE_X, PRINTLS, 6, "ASL"};
  this->instructions[0x0E] = {ASL, ABSOLUTE, PRINTLS, 6, "ASL"};
  this->instructions[0x1E] = {ASL, INDEXED_ABSOLUTE_X, PRINTLS, 7, "ASL"};

  /* BCC,BCS,BEQ Instruction */
  this->instructions[0x90] = {BCC, RELATIVE, PRINT, 2, "BCC"};
  this->instructions[0xB0] = {BCS, RELATIVE, PRINT, 2, "BCS"};
  this->instructions[0xF0] = {BEQ, RELATIVE, PRINT, 2, "BEQ"};

  /* BIT Instruction */
  this->instructions[0x24] = {BIT, ZERO_PAGE, PRINTLS, 3, "BIT"};
  this->instructions[0x2C] = {BIT, ABSOLUTE, PRINTLS, 4, "BIT"};

  /* BMI,BNE,BPL Instruction */
  this->instructions[0x30] = {BMI, RELATIVE, PRINT, 2, "BMI"};
  this->instructions[0xD0] = {BNE, RELATIVE, PRINT, 2, "BNE"};
  this->instructions[0x10] = {BPL, RELATIVE, PRINT, 2, "BPL"};

  /* BRK Instruction */
  this->instructions[0x00] = {BRK, IMPLIED, PRINT, 7, "BRK"};

  /* BVC,BVS Instruction */
  this->instructions[0x50] = {BVC, RELATIVE, PRINT, 2, "BVC"};
  this->instructions[0x70] = {BVS, RELATIVE, PRINT, 2, "BVS"};

  /* CLC Instruction */
  this->instructions[0x18] = {CLC, IMPLIED, PRINT, 2, "CLC"};

  /* CLD Instruction */
  this->instructions[0xD8] = {CLD, IMPLIED, PRINT, 2, "CLD"};

  /* CLI Instruction */
  this->instructions[0x58] = {CLI, IMPLIED, PRINT, 2, "CLI"};

  /* SEI Instruction */
  this->instructions[0x78] = {SEI, IMPLIED, PRINT, 2, "SEI"};

  /* CLV Instruction */
  this->instructions[0xB8] = {CLV, IMPLIED, PRINT, 2, "CLV"};

  /* CMP Instruction */
  this->instructions[0xC9] = {CMP, IMMEDIATE, PRINT, 2, "CMP"};
  this->instructions[0xC5] = {CMP, ZERO_PAGE, PRINTLS, 3, "CMP"};
  this->instructions[0xD5] = {CMP, INDEXED_ZERO_PAGE_X, PRINTLS, 4, "CMP"};
  this->instructions[0xCD] = {CMP, ABSOLUTE, PRINTLS, 4, "CMP"};
  this->instructions[0xDD] = {CMP, INDEXED_ABSOLUTE_X, PRINTLS, 4, "CMP"};
  this->instructions[0xD9] = {CMP, INDEXED_ABSOLUTE_Y, PRINTLS, 4, "CMP"};
  this->instructions[0xD1] = {CMP, INDIRECT_INDEXED, PRINTLS, 5, "CMP"};
  this->instructions[0xC1] = {CMP, INDEXED_INDIRECT, PRINTLS, 6, "CMP"};

  /* CPX Instruction */
  this->instructions[0xE0] = {CPX, IMMEDIATE, PRINT, 2, "CPX"};
  this->instructions[0xE4] = {CPX, ZERO_PAGE, PRINTLS, 3, "CPX"};
  this->instructions[0xEC] = {CPX, ABSOLUTE, PRINTLS, 4, "CPX"};

  /* CPY Instruction */
  this->instructions[0xC0] = {CPY, IMMEDIATE, PRINT, 2, "CPY"};
  this->instructions[0xC4] = {CPY, ZERO_PAGE, PRINTLS, 3, "CPY"};
  this->instructions[0xCC] = {CPY, ABSOLUTE, PRINTLS, 4, "CPY"};

  /* EOR Instructions*/
  this->instructions[0x49] = {EOR, IMMEDIATE, PRINT, 2, "EOR"};
  this->instructions[0x45] = {EOR, ZERO_PAGE, PRINTLS, 3, "EOR"};
  this->instructions[0x55] = {EOR, INDEXED_ZERO_PAGE_X, PRINTLS, 4, "EOR"};
  this->instructions[0x4D] = {EOR, ABSOLUTE, PRINTLS, 4, "EOR"};
  this->instructions[0x5D] = {EOR, INDEXED_ABSOLUTE_X, PRINTLS, 4, "EOR"};
  this->instructions[0x59] = {EOR, INDEXED_ABSOLUTE_Y, PRINTLS, 4, "EOR"};
  this->instructions[0x51] = {EOR, INDIRECT_INDEXED, PRINTLS, 5, "EOR"};
  this->instructions[0x41] = {EOR, INDEXED_INDIRECT, PRINTLS, 6, "EOR"};

  /* JMP Instructions*/
  this->instructions[0x4C] = {JMP, ABSOLUTE, PRINT, 3, "JMP"};
  this->instructions[0x6C] = {JMP, INDIRECT, PRINT, 5, "JMP"};

  /* JSR Instructions*/
  this->instructions[0x20] = {JSR, ABSOLUTE, PRINT, 6, "JSR"};

  /* LSR Instructions*/
  this->instructions[0x4A] = {LSR, ACCUMULATOR, PRINT, 2, "LSR"};
  this->instructions[0x46] = {LSR, ZERO_PAGE, PRINTLS, 5, "LSR"};
  this->instructions[0x56] = {LSR, INDEXED_ZERO_PAGE_X, PRINTLS, 6, "LSR"};
  this->instructions[0x4E] = {LSR, ABSOLUTE, PRINTLS, 6, "LSR"};
  this->instructions[0x5E] = {LSR, INDEXED_ABSOLUTE_X, PRINTLS, 7, "LSR"};

  /* NOP Instructions*/
  this->instructions[0xEA] = {NOP, IMPLIED, PRINT, 2, "NOP"};

  /* ORA Instructions*/
  this->instructions[0x09] = {ORA, IMMEDIATE, PRINT, 2, "ORA"};
  this->instructions[0x05] = {ORA, ZERO_PAGE, PRINTLS, 3, "ORA"};
  this->instructions[0x15] = {ORA, INDEXED_ZERO_PAGE_X, PRINTLS, 4, "ORA"};
  this->instructions[0x0D] = {ORA, ABSOLUTE, PRINTLS, 4, "ORA"};
  this->instructions[0x1D] = {ORA, INDEXED_ABSOLUTE_X, PRINTLS, 4, "ORA"};
  this->instructions[0x19] = {ORA, INDEXED_ABSOLUTE_Y, PRINTLS, 4, "ORA"};
  this->instructions[0x11] = {ORA, INDIRECT_INDEXED, PRINTLS, 5, "ORA"};
  this->instructions[0x01] = {ORA, INDEXED_INDIRECT, PRINTLS, 6, "ORA"};

  /* PHA Instructions*/
  this->instructions[0x48] = {PHA, IMPLIED, PRINTLS, 3, "PHA"};
  /* PHP Instructions*/
  this->instructions[0x08] = {PHP, IMPLIED, PRINTLS, 3, "PHP"};
  /* PLA Instructions*/
  this->instructions[0x68] = {PLA, IMPLIED, PRINTLS, 4, "PLA"};
  /* PLP Instructions*/
  this->instructions[0x28] = {PLP, IMPLIED, PRINTLS, 4, "PLP"};

  /* RTI Instructions*/
  this->instructions[0x40] = {RTI, IMPLIED, PRINT, 6, "RTI"};
  /* RTS Instructions*/
  this->instructions[0x60] = {RTS, IMPLIED, PRINT, 6, "RTS"};

  /* SEC Instructions*/
  this->instructions[0x38] = {SEC, IMPLIED, PRINT, 2, "SEC"};
  /* SED Instructions*/
  this->instructions[0xF8] = {SED, IMPLIED, PRINT, 2, "SED"};

  /* LDA Instructions*/
  this->instructions[0xA9] = {LDA, IMMEDIATE, PRINT, 2, "LDA"};
  this->instructions[0xA5] = {LDA, ZERO_PAGE, PRINTLS, 3, "LDA"};
  this->instructions[0xB5] = {LDA, INDEXED_ZERO_PAGE_X, PRINTLS, 4, "LDA"};
  this->instructions[0xAD] = {LDA, ABSOLUTE, PRINTLS, 4, "LDA"};
  this->instructions[0xBD] = {LDA, INDEXED_ABSOLUTE_X, PRINTLS, 4, "LDA"};
  this->instructions[0xB9] = {LDA, INDEXED_ABSOLUTE_Y, PRINTLS, 4, "LDA"};
  this->instructions[0xB1] = {LDA, INDIRECT_INDEXED, PRINTLS, 5, "LDA"};
  this->instructions[0xA1] = {LDA, INDEXED_INDIRECT, PRINTLS, 6, "LDA"};

  /* LDX Instructions*/
  this->instructions[0xA2] = {LDX, IMMEDIATE, PRINT, 2, "LDX"};
  this->instructions[0xA6] = {LDX, ZERO_PAGE, PRINTLS, 3, "LDX"};
  this->instructions[0xB6] = {LDX, INDEXED_ZERO_PAGE_Y, PRINTLS, 4, "LDX"};
  this->instructions[0xAE] = {LDX, ABSOLUTE, PRINTLS, 4, "LDX"};
  this->instructions[0xBE] = {LDX, INDEXED_ABSOLUTE_Y, PRINTLS, 4, "LDX"};

  /* LDY Instructions*/
  this->instructions[0xA0] = {LDY, IMMEDIATE, PRINT, 2, "LDY"};
  this->instructions[0xA4] = {LDY, ZERO_PAGE, PRINTLS, 3, "LDY"};
  this->instructions[0xB4] = {LDY, INDEXED_ZERO_PAGE_X, PRINTLS, 4, "LDY"};
  this->instructions[0xAC] = {LDY, ABSOLUTE, PRINTLS, 4, "LDY"};
  this->instructions[0xBC] = {LDY, INDEXED_ABSOLUTE_X, PRINTLS, 4, "LDY"};

  /*STA Instructions*/
  this->instructions[0x85] = {STA, ZERO_PAGE, PRINTLS, 3, "STA"};
  this->instructions[0X95] = {STA, INDEXED_ZERO_PAGE_X, PRINTLS, 4, "STA"};
  this->instructions[0x8D] = {STA, ABSOLUTE, PRINTLS, 4, "STA"};
  this->instructions[0X9D] = {STA, INDEXED_ABSOLUTE_X, PRINTLS, 5, "STA"};
  this->instructions[0X99] = {STA, INDEXED_ABSOLUTE_Y, PRINTLS, 5, "STA"};
  this->instructions[0X91] = {STA, INDIRECT_INDEXED, PRINTLS, 6, "STA"};
  this->instructions[0X81] = {STA, INDEXED_INDIRECT, PRINTLS, 6, "STA"};

  /*STX Instructions*/
  this->instructions[0x86] = {STX, ZERO_PAGE, PRINTLS, 3, "STX"};
  this->instructions[0X96] = {STX, INDEXED_ZERO_PAGE_Y, PRINTLS, 4, "STX"};
  this->instructions[0x8E] = {STX, ABSOLUTE, PRINTLS, 4, "STX"};

  /*STY Instructions*/
  this->instructions[0x84] = {STY, ZERO_PAGE, PRINTLS, 3, "STY"};
  this->instructions[0X94] = {STY, INDEXED_ZERO_PAGE_X, PRINTLS, 4, "STY"};
  this->instructions[0x8C] = {STY, ABSOLUTE, PRINTLS, 4, "STY"};

  /*DEC instructions*/
  this->instructions[0xC6] = {DEC, ZERO_PAGE, PRINTLS, 5, "DEC"};
  this->instructions[0xD6] = {DEC, INDEXED_ZERO_PAGE_X, PRINTLS, 6, "DEC"};
  this->instructions[0xCE] = {DEC, ABSOLUTE, PRINTLS, 6, "DEC"};
  this->instructions[0xDE] = {DEC, INDEXED_ABSOLUTE_X, PRINTLS, 7, "DEC"};

  /*DEX instructions*/
  this->instructions[0xCA] = {DEX, IMPLIED, PRINT, 2, "DEX"};

  /*DEY instructions*/
  this->instructions[0x88] = {DEY, IMPLIED, PRINT, 2, "DEY"};

  /*INC instructions*/
  this->instructions[0xE6] = {INC, ZERO_PAGE, PRINTLS, 5, "INC"};
  this->instructions[0xF6] = {INC, INDEXED_ZERO_PAGE_X, PRINTLS, 6, "INC"};
  this->instructions[0xEE] = {INC, ABSOLUTE, PRINTLS, 6, "INC"};
  this->instructions[0xFE] = {INC, INDEXED_ABSOLUTE_X, PRINTLS, 7, "INC"};

  /*INX instructions*/
  this->instructions[0xE8] = {INX, IMPLIED, PRINT, 2, "INX"};

  /*INY instructions*/
  this->instructions[0xC8] = {INY, IMPLIED, PRINT, 2, "INY"};

  /*SBC instructions*/
  this->instructions[0xE9] = {SBC, IMMEDIATE, PRINT, 2, "SBC"};
  this->instructions[0xE5] = {SBC, ZERO_PAGE, PRINTLS, 3, "SBC"};
  this->instructions[0xF5] = {SBC, INDEXED_ZERO_PAGE_X, PRINTLS, 4, "SBC"};
  this->instructions[0xED] = {SBC, ABSOLUTE, PRINTLS, 4, "SBC"};
  this->instructions[0xFD] = {SBC, INDEXED_ABSOLUTE_X, PRINTLS, 4, "SBC"};
  this->instructions[0xF9] = {SBC, INDEXED_ABSOLUTE_Y, PRINTLS, 4, "SBC"};
  this->instructions[0xF1] = {SBC, INDIRECT_INDEXED, PRINTLS, 5, "SBC"};
  this->instructions[0xE1] = {SBC, INDEXED_INDIRECT, PRINTLS, 6, "SBC"};

  /*ROR instructions*/
  this->instructions[0x6A] = {ROR, ACCUMULATOR, PRINT, 2, "ROR"};
  this->instructions[0X66] = {ROR, ZERO_PAGE, PRINTLS, 5, "ROR"};
  this->instructions[0X76] = {ROR, INDEXED_ZERO_PAGE_X, PRINTLS, 6, "ROR"};
  this->instructions[0X6E] = {ROR, ABSOLUTE, PRINTLS, 6, "ROR"};
  this->instructions[0X7E] = {ROR, INDEXED_ABSOLUTE_X, PRINTLS, 7, "ROR"};

  /*ROL instructions*/
  this->instructions[0x2A] = {ROL, ACCUMULATOR, PRINT, 2, "ROL"};
  this->instructions[0X26] = {ROL, ZERO_PAGE, PRINTLS, 5, "ROL"};
  this->instructions[0X36] = {ROL, INDEXED_ZERO_PAGE_X, PRINTLS, 6, "ROL"};
  this->instructions[0X2E] = {ROL, ABSOLUTE, PRINTLS, 6, "ROL"};
  this->instructions[0X3E] = {ROL, INDEXED_ABSOLUTE_X, PRINTLS, 7, "ROL"};

  /*TAX instructions*/
  this->instructions[0xAA] = {TAX, IMPLIED, PRINT, 2, "TAX"};

  /*TAY instructions*/
  this->instructions[0xA8] = {TAY, IMPLIED, PRINT, 2, "TAY"};

  /*TSX instructions*/
  this->instructions[0xBA] = {TSX, IMPLIED, PRINT, 2, "TSX"};

  /*TXA instructions*/
  this->instructions[0x8A] = {TXA, IMPLIED, PRINT, 2, "TXA"};

  /*TXS instructions*/
  this->instructions[0x9A] = {TXS, IMPLIED, PRINT, 2, "TXS"};

  /*TYA instructions*/
  this->instructions[0x98] = {TYA, IMPLIED, PRINT, 2, "TYA"};
};

InstructionFactory::~InstructionFactory() {}

OperationAttributes InstructionFactory::getOperationAttributes(uint8_t opCode) {
  try {
    return this->instructions[opCode];
  } catch (const std::out_of_range &oor) {
    cout << "opcode does not exists in getOperationAttributes: " << (int)opCode;
  }
};

uint8_t InstructionFactory::getInstructionSize(uint8_t opCode) {
  OperationAttributes attributes = this->getOperationAttributes(opCode);
  if (&attributes == NULL) {
    return NULL;
  }
  try {
    return this->addressingModeSize[attributes.addressingMode];
  } catch (const std::out_of_range &oor) {
    //   cout << "opCode does not exists in getInstructionSize: " << (int)opCode ;
    return NULL;
  }
};

Instruction *InstructionFactory::getInstanceById(uint8_t instructionID) {
  try {
    return this->instances[instructionID];
  } catch (const std::out_of_range &oor) {
    cout << "instructionID does not exists in getInstanceById: " << (int)instructionID;
    return NULL;
  }
};

Instruction *InstructionFactory::createInstruction(uint8_t opCode) {
  OperationAttributes attributes = this->getOperationAttributes(opCode);
  if (&attributes == NULL) {
    return NULL;
  }
  uint8_t instructionSize = this->getInstructionSize(opCode);
  Instruction *instruction = this->getInstanceById(attributes.id);
  instruction->setAddressingMode(attributes.addressingMode);

  instruction->setDecodedInstruction(attributes.name);
  instruction->setInstructionSize(instructionSize);
  instruction->setPrintMode(attributes.printMode);
  instruction->setCycles(attributes.cycles);
  return instruction;
};
