#ifndef InstructionID_hpp
#define InstructionID_hpp

/* https://www.masswerk.at/6502/6502_instruction_set.html#ADC */

enum InstructionID {
  ADC = 1,
  AND,
  ASL,
  BCC,
  BCS,
  BEQ,
  BIT,
  BMI,
  BNE,
  BPL,
  BRK,
  BVC,
  BVS,
  LDA,
  LDX,
  LDY,
  STA,
  DEC,
  DEX,
  DEY,
  INC,
  INX,
  INY,
  SBC
  /*TODO: Fill it up with the others IDs.*/
};

#endif
