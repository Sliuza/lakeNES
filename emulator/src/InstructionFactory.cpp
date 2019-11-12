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
      {0x69, {ADC, IMMEDIATE, PRINT, 2, "ADC"}},
      {0x65, {ADC, ZERO_PAGE, PRINTLS, 3, "ADC"}},
      {0x75, {ADC, INDEXED_ZERO_PAGE_X, PRINTLS, 4, "ADC"}},
      {0x6D, {ADC, ABSOLUTE, PRINTLS, 4, "ADC"}},
      {0x7D, {ADC, INDEXED_ABSOLUTE_X, PRINTLS, 4, "ADC"}},
      {0x79, {ADC, INDEXED_ABSOLUTE_Y, PRINTLS, 4, "ADC"}},
      {0x71, {ADC, INDIRECT_INDEXED, PRINTLS, 5, "ADC"}},
      {0x61, {ADC, INDEXED_INDIRECT, PRINTLS, 6, "ADC"}},

      /* AND Instruction */
      {0x29, {AND, IMMEDIATE, PRINT, 2, "AND"}},
      {0x25, {AND, ZERO_PAGE, PRINTLS, 3, "AND"}},
      {0x35, {AND, INDEXED_ZERO_PAGE_X, PRINTLS, 4, "AND"}},
      {0x2D, {AND, ABSOLUTE, PRINTLS, 4, "AND"}},
      {0x3D, {AND, INDEXED_ABSOLUTE_X, PRINTLS, 4, "AND"}},
      {0x39, {AND, INDEXED_ABSOLUTE_Y, PRINTLS, 4, "AND"}},
      {0x31, {AND, INDIRECT_INDEXED, PRINTLS, 5, "AND"}},
      {0x21, {AND, INDEXED_INDIRECT, PRINTLS, 6, "AND"}},

      /* ASL Instruction */
      {0x0A, {ASL, ACCUMULATOR, PRINT, 2, "ASL"}},
      {0x06, {ASL, ZERO_PAGE, PRINTLS, 5, "ASL"}},
      {0x16, {ASL, INDEXED_ZERO_PAGE_X, PRINTLS, 6, "ASL"}},
      {0x0E, {ASL, ABSOLUTE, PRINTLS, 6, "ASL"}},
      {0x1E, {ASL, INDEXED_ABSOLUTE_X, PRINTLS, 7, "ASL"}},

      /* BCC,BCS,BEQ Instruction */
      {0x90, {BCC, RELATIVE, PRINT, 2, "BCC"}},
      {0xB0, {BCS, RELATIVE, PRINT, 2, "BCS"}},
      {0xF0, {BEQ, RELATIVE, PRINT, 2, "BEQ"}},

      /* BIT Instruction */
      {0x24, {BIT, ZERO_PAGE, PRINTLS, 3, "BIT"}},
      {0x2C, {BIT, ABSOLUTE, PRINTLS, 4, "BIT"}},

      /* BMI,BNE,BPL Instruction */
      {0x30, {BMI, RELATIVE, PRINT, 2, "BMI"}},
      {0xD0, {BNE, RELATIVE, PRINT, 2, "BNE"}},
      {0x10, {BPL, RELATIVE, PRINT, 2, "BPL"}},

      /* BRK Instruction */
      {0x00, {BRK, IMPLIED, PRINT, 7, "BRK"}},

      /* BVC,BVS Instruction */
      {0x50, {BVC, RELATIVE, PRINT, 2, "BVC"}},
      {0x70, {BVS, RELATIVE, PRINT, 2, "BVS"}},

      /* CLC Instruction */
      {0x18, {CLC, IMPLIED, PRINT, 2, "CLC"}},

      /* CLD Instruction */
      {0xD8, {CLD, IMPLIED, PRINT, 2, "CLD"}},

      /* CLI Instruction */
      {0x58, {CLI, IMPLIED, PRINT, 2, "CLI"}},

      /* SEI Instruction */
      {0x78, {SEI, IMPLIED, PRINT, 2, "SEI"}},

      /* CLV Instruction */
      {0xB8, {CLV, IMPLIED, PRINT, 2, "CLV"}},

      /* CMP Instruction */
      {0xC9, {CMP, IMMEDIATE, PRINT, 2, "CMP"}},
      {0xC5, {CMP, ZERO_PAGE, PRINTLS, 3, "CMP"}},
      {0xD5, {CMP, INDEXED_ZERO_PAGE_X, PRINTLS, 4, "CMP"}},
      {0xCD, {CMP, ABSOLUTE, PRINTLS, 4, "CMP"}},
      {0xDD, {CMP, INDEXED_ABSOLUTE_X, PRINTLS, 4, "CMP"}},
      {0xD9, {CMP, INDEXED_ABSOLUTE_Y, PRINTLS, 4, "CMP"}},
      {0xD1, {CMP, INDIRECT_INDEXED, PRINTLS, 5, "CMP"}},
      {0xC1, {CMP, INDEXED_INDIRECT, PRINTLS, 6, "CMP"}},

      /* CPX Instruction */
      {0xE0, {CPX, IMMEDIATE, PRINT, 2, "CPX"}},
      {0xE4, {CPX, ZERO_PAGE, PRINTLS, 3, "CPX"}},
      {0xEC, {CPX, ABSOLUTE, PRINTLS, 4, "CPX"}},

      /* CPY Instruction */
      {0xC0, {CPY, IMMEDIATE, PRINT, 2, "CPY"}},
      {0xC4, {CPY, ZERO_PAGE, PRINTLS, 3, "CPY"}},
      {0xCC, {CPY, ABSOLUTE, PRINTLS, 4, "CPY"}},

      /* EOR Instructions*/
      {0x49, {EOR, IMMEDIATE, PRINT, 2, "EOR"}},
      {0x45, {EOR, ZERO_PAGE, PRINTLS, 3, "EOR"}},
      {0x55, {EOR, INDEXED_ZERO_PAGE_X, PRINTLS, 4, "EOR"}},
      {0x4D, {EOR, ABSOLUTE, PRINTLS, 4, "EOR"}},
      {0x5D, {EOR, INDEXED_ABSOLUTE_X, PRINTLS, 4, "EOR"}},
      {0x59, {EOR, INDEXED_ABSOLUTE_Y, PRINTLS, 4, "EOR"}},
      {0x51, {EOR, INDIRECT_INDEXED, PRINTLS, 5, "EOR"}},
      {0x41, {EOR, INDEXED_INDIRECT, PRINTLS, 6, "EOR"}},

      /* JMP Instructions*/
      {0x4C, {JMP, ABSOLUTE, PRINT, 3, "JMP"}},
      {0x6C, {JMP, INDIRECT, PRINT, 5, "JMP"}},

      /* JSR Instructions*/
      {0x20, {JSR, ABSOLUTE, PRINT, 6, "JSR"}},

      /* LSR Instructions*/
      {0x4A, {LSR, ACCUMULATOR, PRINT, 2, "LSR"}},
      {0x46, {LSR, ZERO_PAGE, PRINTLS, 5, "LSR"}},
      {0x56, {LSR, INDEXED_ZERO_PAGE_X, PRINTLS, 6, "LSR"}},
      {0x4E, {LSR, ABSOLUTE, PRINTLS, 6, "LSR"}},
      {0x5E, {LSR, INDEXED_ABSOLUTE_X, PRINTLS, 7, "LSR"}},

      /* NOP Instructions*/
      {0xEA, {NOP, IMPLIED, PRINT, 2, "NOP"}},

      /* ORA Instructions*/
      {0x09, {ORA, IMMEDIATE, PRINT, 2, "ORA"}},
      {0x05, {ORA, ZERO_PAGE, PRINTLS, 3, "ORA"}},
      {0x15, {ORA, INDEXED_ZERO_PAGE_X, PRINTLS, 4, "ORA"}},
      {0x0D, {ORA, ABSOLUTE, PRINTLS, 4, "ORA"}},
      {0x1D, {ORA, INDEXED_ABSOLUTE_X, PRINTLS, 4, "ORA"}},
      {0x19, {ORA, INDEXED_ABSOLUTE_Y, PRINTLS, 4, "ORA"}},
      {0x11, {ORA, INDIRECT_INDEXED, PRINTLS, 5, "ORA"}},
      {0x01, {ORA, INDEXED_INDIRECT, PRINTLS, 6, "ORA"}},

      /* PHA Instructions*/
      {0x48, {PHA, IMPLIED, PRINTLS, 3, "PHA"}},
      /* PHP Instructions*/
      {0x08, {PHP, IMPLIED, PRINTLS, 3, "PHP"}},
      /* PLA Instructions*/
      {0x68, {PLA, IMPLIED, PRINTLS, 4, "PLA"}},
      /* PLP Instructions*/
      {0x28, {PLP, IMPLIED, PRINTLS, 4, "PLP"}},

      /* RTI Instructions*/
      {0x40, {RTI, IMPLIED, PRINT, 6, "RTI"}},
      /* RTS Instructions*/
      {0x60, {RTS, IMPLIED, PRINT, 6, "RTS"}},

      /* SEC Instructions*/
      {0x38, {SEC, IMPLIED, PRINT, 2, "SEC"}},
      /* SED Instructions*/
      {0xF8, {SED, IMPLIED, PRINT, 2, "SED"}},

      /* LDA Instructions*/
      {0xA9, {LDA, IMMEDIATE, PRINT, 2, "LDA"}},
      {0xA5, {LDA, ZERO_PAGE, PRINTLS, 3, "LDA"}},
      {0xB5, {LDA, INDEXED_ZERO_PAGE_X, PRINTLS, 4, "LDA"}},
      {0xAD, {LDA, ABSOLUTE, PRINTLS, 4, "LDA"}},
      {0xBD, {LDA, INDEXED_ABSOLUTE_X, PRINTLS, 4, "LDA"}},
      {0xB9, {LDA, INDEXED_ABSOLUTE_Y, PRINTLS, 4, "LDA"}},
      {0xB1, {LDA, INDIRECT_INDEXED, PRINTLS, 5, "LDA"}},
      {0xA1, {LDA, INDEXED_INDIRECT, PRINTLS, 6, "LDA"}},

      /* LDX Instructions*/
      {0xA2, {LDX, IMMEDIATE, PRINT, 2, "LDX"}},
      {0xA6, {LDX, ZERO_PAGE, PRINTLS, 3, "LDX"}},
      {0xB6, {LDX, INDEXED_ZERO_PAGE_Y, PRINTLS, 4, "LDX"}},
      {0xAE, {LDX, ABSOLUTE, PRINTLS, 4, "LDX"}},
      {0xBE, {LDX, INDEXED_ABSOLUTE_Y, PRINTLS, 4, "LDX"}},

      /* LDY Instructions*/
      {0xA0, {LDY, IMMEDIATE, PRINT, 2, "LDY"}},
      {0xA4, {LDY, ZERO_PAGE, PRINTLS, 3, "LDY"}},
      {0xB4, {LDY, INDEXED_ZERO_PAGE_X, PRINTLS, 4, "LDY"}},
      {0xAC, {LDY, ABSOLUTE, PRINTLS, 4, "LDY"}},
      {0xBC, {LDY, INDEXED_ABSOLUTE_X, PRINTLS, 4, "LDY"}},

      /*STA Instructions*/
      {0x85, {STA, ZERO_PAGE, PRINTLS, 3, "STA"}},
      {0X95, {STA, INDEXED_ZERO_PAGE_X, PRINTLS, 4, "STA"}},
      {0x8D, {STA, ABSOLUTE, PRINTLS, 4, "STA"}},
      {0X9D, {STA, INDEXED_ABSOLUTE_X, PRINTLS, 5, "STA"}},
      {0X99, {STA, INDEXED_ABSOLUTE_Y, PRINTLS, 5, "STA"}},
      {0X91, {STA, INDIRECT_INDEXED, PRINTLS, 6, "STA"}},
      {0X81, {STA, INDEXED_INDIRECT, PRINTLS, 6, "STA"}},

      /*STX Instructions*/
      {0x86, {STX, ZERO_PAGE, PRINTLS, 3, "STX"}},
      {0X96, {STX, INDEXED_ZERO_PAGE_Y, PRINTLS, 4, "STX"}},
      {0x8E, {STX, ABSOLUTE, PRINTLS, 4, "STX"}},

      /*STY Instructions*/
      {0x84, {STY, ZERO_PAGE, PRINTLS, 3, "STY"}},
      {0X94, {STY, INDEXED_ZERO_PAGE_X, PRINTLS, 4, "STY"}},
      {0x8C, {STY, ABSOLUTE, PRINTLS, 4, "STY"}},

      /*DEC instructions*/
      {0xC6, {DEC, ZERO_PAGE, PRINTLS, 5, "DEC"}},
      {0xD6, {DEC, INDEXED_ZERO_PAGE_X, PRINTLS, 6, "DEC"}},
      {0xCE, {DEC, ABSOLUTE, PRINTLS, 6, "DEC"}},
      {0xDE, {DEC, INDEXED_ABSOLUTE_X, PRINTLS, 7, "DEC"}},

      /*DEX instructions*/
      {0xCA, {DEX, IMPLIED, PRINT, 2, "DEX"}},

      /*DEY instructions*/
      {0x88, {DEY, IMPLIED, PRINT, 2, "DEY"}},

      /*INC instructions*/
      {0xE6, {INC, ZERO_PAGE, PRINTLS, 5, "INC"}},
      {0xF6, {INC, INDEXED_ZERO_PAGE_X, PRINTLS, 6, "INC"}},
      {0xEE, {INC, ABSOLUTE, PRINTLS, 6, "INC"}},
      {0xFE, {INC, INDEXED_ABSOLUTE_X, PRINTLS, 7, "INC"}},

      /*INX instructions*/
      {0xE8, {INX, IMPLIED, PRINT, 2, "INX"}},

      /*INY instructions*/
      {0xC8, {INY, IMPLIED, PRINT, 2, "INY"}},

      /*SBC instructions*/
      {0xE9, {SBC, IMMEDIATE, PRINT, 2, "SBC"}},
      {0xE5, {SBC, ZERO_PAGE, PRINTLS, 3, "SBC"}},
      {0xF5, {SBC, INDEXED_ZERO_PAGE_X, PRINTLS, 4, "SBC"}},
      {0xED, {SBC, ABSOLUTE, PRINTLS, 4, "SBC"}},
      {0xFD, {SBC, INDEXED_ABSOLUTE_X, PRINTLS, 4, "SBC"}},
      {0xF9, {SBC, INDEXED_ABSOLUTE_Y, PRINTLS, 4, "SBC"}},
      {0xF1, {SBC, INDIRECT_INDEXED, PRINTLS, 5, "SBC"}},
      {0xE1, {SBC, INDEXED_INDIRECT, PRINTLS, 6, "SBC"}},

      /*ROR instructions*/
      {0x6A, {ROR, ACCUMULATOR, PRINT, 2, "ROR"}},
      {0X66, {ROR, ZERO_PAGE, PRINTLS, 5, "ROR"}},
      {0X76, {ROR, INDEXED_ZERO_PAGE_X, PRINTLS, 6, "ROR"}},
      {0X6E, {ROR, ABSOLUTE, PRINTLS, 6, "ROR"}},
      {0X7E, {ROR, INDEXED_ABSOLUTE_X, PRINTLS, 7, "ROR"}},

      /*ROL instructions*/
      {0x2A, {ROL, ACCUMULATOR, PRINT, 2, "ROL"}},
      {0X26, {ROL, ZERO_PAGE, PRINTLS, 5, "ROL"}},
      {0X36, {ROL, INDEXED_ZERO_PAGE_X, PRINTLS, 6, "ROL"}},
      {0X2E, {ROL, ABSOLUTE, PRINTLS, 6, "ROL"}},
      {0X3E, {ROL, INDEXED_ABSOLUTE_X, PRINTLS, 7, "ROL"}},

      /*TAX instructions*/
      {0xAA, {TAX, IMPLIED, PRINT, 2, "TAX"}},

      /*TAY instructions*/
      {0xA8, {TAY, IMPLIED, PRINT, 2, "TAY"}},

      /*TSX instructions*/
      {0xBA, {TSX, IMPLIED, PRINT, 2, "TSX"}},

      /*TXA instructions*/
      {0x8A, {TXA, IMPLIED, PRINT, 2, "TXA"}},

      /*TXS instructions*/
      {0x9A, {TXS, IMPLIED, PRINT, 2, "TXS"}},

      /*TYA instructions*/
      {0x98, {TYA, IMPLIED, PRINT, 2, "TYA"}},
  };
};

InstructionFactory::~InstructionFactory() {}

OperationAttributes InstructionFactory::getOperationAttributes(uint8_t opCode) {
    try {
        return this->instructions.at(opCode);
    } catch(const std::out_of_range& oor){
        cout << "opcode does not exists in getOperationAttributes: " << (int)opCode ;
    }
};

uint8_t InstructionFactory::getInstructionSize(uint8_t opCode) {
  OperationAttributes attributes = this->getOperationAttributes(opCode);
  if(&attributes == NULL){
      return NULL;
  }
  try {
    return this->addressingModeSize.at(attributes.addressingMode);
  } catch(const std::out_of_range& oor){
      cout << "opCode does not exists in getInstructionSize: " << (int)opCode ;
      return NULL;
  }
};

Instruction *InstructionFactory::getInstanceById(uint8_t instructionID) {
    try {
        return this->instances.at(instructionID);
    } catch(const std::out_of_range& oor){
        cout << "instructionID does not exists in getInstanceById: " << (int)instructionID ;
        return NULL;
    }
};

Instruction *InstructionFactory::createInstruction(uint8_t opCode) {
  OperationAttributes attributes = this->getOperationAttributes(opCode);
  if(&attributes == NULL){
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
