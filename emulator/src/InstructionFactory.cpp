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
      
      /* EOR Instructions*/
      {0x49, make_pair(EOR, IMMEDIATE)},
      {0x45, make_pair(EOR, ZERO_PAGE)},
      {0x55, make_pair(EOR, INDEXED_ZERO_PAGE_X)},
      {0x4D, make_pair(EOR, ABSOLUTE)},
      {0x5D, make_pair(EOR, INDEXED_ABSOLUTE_X)},
      {0x59, make_pair(EOR, INDEXED_ABSOLUTE_Y)},
      {0x41, make_pair(EOR, INDIRECT_INDEXED)},
      {0x51, make_pair(EOR, INDEXED_INDIRECT)},
      
      /* JMP Instructions*/
      {0x4C, make_pair(JMP, ABSOLUTE)},
      {0x6C, make_pair(JMP, INDIRECT)},
      
      /* JSR Instructions*/
      {0x20, make_pair(JSR, ABSOLUTE)},
      
      /* LSR Instructions*/
      {0x4A, make_pair(LSR, ACCUMULATOR)},
      {0x46, make_pair(LSR, ZERO_PAGE)},
      {0x56, make_pair(LSR, INDEXED_ZERO_PAGE_X)},
      {0x4E, make_pair(LSR, ABSOLUTE)},
      {0x5E, make_pair(LSR, INDEXED_ABSOLUTE_X)},
      
      /* NOP Instructions*/
      {0xEA, make_pair(NOP, IMPLIED)},
      
      /* ORA Instructions*/
      {0x09, make_pair(ORA, IMMEDIATE)},
      {0x05, make_pair(ORA, ZERO_PAGE)},
      {0x15, make_pair(ORA, INDEXED_ZERO_PAGE_X)},
      {0x0D, make_pair(ORA, ABSOLUTE)},
      {0x1D, make_pair(ORA, INDEXED_ABSOLUTE_X)},
      {0x19, make_pair(ORA, INDEXED_ABSOLUTE_Y)},
      {0x01, make_pair(ORA, INDIRECT_INDEXED)},
      {0x11, make_pair(ORA, INDEXED_INDIRECT)},
      
      /* PHA Instructions*/
      {0x48, make_pair(PHA, IMPLIED)},
      /* PHP Instructions*/
      {0x09, make_pair(PHP, IMPLIED)},
      /* PLA Instructions*/
      {0x69, make_pair(PLA, IMPLIED)},
      /* PLP Instructions*/
      {0x29, make_pair(PLP, IMPLIED)},
      
      /* RTI Instructions*/
      {0x40, make_pair(RTI, IMPLIED)},
      /* RTS Instructions*/
      {0x60, make_pair(RTS, IMPLIED)},
      
      /* SEC Instructions*/
      {0x38, make_pair(SEC, IMPLIED)},


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
      
      /*STX Instructions*/
      {0x86, make_pair(STX, ZERO_PAGE)},
      {0X96, make_pair(STX, INDEXED_ZERO_PAGE_Y)},
      {0x8E, make_pair(STX, ABSOLUTE)},
      
      /*STY Instructions*/
      {0x84, make_pair(STY, ZERO_PAGE)},
      {0X94, make_pair(STY, INDEXED_ZERO_PAGE_X)},
      {0x8C, make_pair(STY, ABSOLUTE)},
      

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
    
      /*ROR instructions*/
      {0x6A,make_pair(ROR,ACCUMULATOR)},
      {0X66,make_pair(ROR,ZERO_PAGE)},
      {0X76,make_pair(ROR,INDEXED_ZERO_PAGE_X)},
      {0X6E,make_pair(ROR,ABSOLUTE)},
      {0X7E,make_pair(ROR,INDEXED_ABSOLUTE_X)},

      /*ROL instructions*/
      {0x2A,make_pair(ROL,ACCUMULATOR)},
      {0X26,make_pair(ROL,ZERO_PAGE)},
      {0X36,make_pair(ROL,INDEXED_ZERO_PAGE_X)},
      {0X2E,make_pair(ROL,ABSOLUTE)},
      {0X3E,make_pair(ROL,INDEXED_ABSOLUTE_X)},

      /*TAX instructions*/
      {0xAA, make_pair(TAX, IMPLIED)},

      /*TAY instructions*/
      {0xA8, make_pair(TAY, IMPLIED)},

      /*TSX instructions*/
      {0xA8, make_pair(TSX, IMPLIED)},

      /*TXA instructions*/
      {0x8A, make_pair(TXA, IMPLIED)},

      /*TXS instructions*/
      {0x9A, make_pair(TXA, IMPLIED)},

      /*TYA instructions*/
      {0x98, make_pair(TYA, IMPLIED)},
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
      case ASL: {
        return new ASLInstruction(addressingMode, instructionSize);
        break;
      }
      case BCC: {
      return new BCCInstruction(addressingMode, instructionSize);
      break;
    }
    case BEQ: {
      return new BEQInstruction(addressingMode, instructionSize);
      break;
    }
    case BIT: {
      return new BITInstruction(addressingMode, instructionSize);
      break;
    }
    case BCS: {
      return new BCSInstruction(addressingMode, instructionSize);
      break;
    }
    case BMI: {
      return new BMIInstruction(addressingMode, instructionSize);
      break;
    }
    case BNE: {
      return new BNEInstruction(addressingMode, instructionSize);
      break;
    }
    case BRK: {
      return new BRKInstruction(addressingMode, instructionSize);
      break;
    }
    case BVC: {
      return new BVCInstruction(addressingMode, instructionSize);
      break;
    }
    case ADC: {
      return new ADCInstruction(addressingMode, instructionSize);
      break;
    }
    case BVS: {
        return new BVSInstruction(addressingMode, instructionSize);
        break;
      }
    case CLC: {
        return new CLCInstruction(addressingMode, instructionSize);
        break;
      }
    case CLD: {
        return new CLDInstruction(addressingMode, instructionSize);
        break;
      }
    case CLI: {
        return new CLIInstruction(addressingMode, instructionSize);
        break;
      }
    case CLV: {
        return new CLVInstruction(addressingMode, instructionSize);
        break;
      }
    case CMP: {
        return new CMPInstruction(addressingMode, instructionSize);
        break;
      }
    case CPY: {
        return new CPYInstruction(addressingMode, instructionSize);
        break;
      }
    case EOR: {
        return new EORInstruction(addressingMode, instructionSize);
        break;
      }

    case JSR: {
        return new JSRInstruction(addressingMode, instructionSize);
        break;
      }
    case JMP: {
        return new JMPInstruction(addressingMode, instructionSize);
        break;
      }
    case LSR: {
      return new LSRInstruction(addressingMode, instructionSize);
      break;
      }
    case ORA: {
      return new ORAInstruction(addressingMode, instructionSize);
      break;
    }
    case PHA: {
      return new PHAInstruction(addressingMode, instructionSize);
      break;
    }
    case PHP: {
      return new PHPInstruction(addressingMode, instructionSize);
      break;
    }
    case PLA: {
      return new PLAInstruction(addressingMode, instructionSize);
      break;
    }
    case PLP: {
      return new PLPInstruction(addressingMode, instructionSize);
      break;
    }
    case RTI: {
      return new RTIInstruction(addressingMode, instructionSize);
      break;
    }
    case RTS: {
      return new RTSInstruction(addressingMode, instructionSize);
      break;
    }
    case SEC: {
      return new SECInstruction(addressingMode, instructionSize);
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
    case STX: {
      return new STXInstruction(addressingMode, instructionSize);
      break;
    }
    case STY: {
      return new STYInstruction(addressingMode, instructionSize);
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
    case TAX:{
      return new TAXInstruction(addressingMode, instructionSize);
      break;
    }
    case TAY:{
      return new TAYInstruction(addressingMode, instructionSize);
      break;
    }
    case TSX:{
      return new TSXInstruction(addressingMode, instructionSize);
      break;
    }
    case TXA:{
      return new TSXInstruction(addressingMode, instructionSize);
      break;
    }
    case TXS:{
      return new TSXInstruction(addressingMode, instructionSize);
      break;
    }
    case TYA:{
      return new TSXInstruction(addressingMode, instructionSize);
      break;
    }
      
    case ROR:{
      return new RORInstruction(addressingMode, instructionSize);
      break;
    }
    case ROL:{
      return new ROLInstruction(addressingMode, instructionSize);
      break;
    }

    case NOP:{
      return new NOPInstruction(addressingMode, instructionSize);
      break;
    }

    default: { break; }
  }

  return NULL;
};