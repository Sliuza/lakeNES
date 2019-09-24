#ifndef InstructionID_hpp
#define InstructionID_hpp

/* https://www.masswerk.at/6502/6502_instruction_set.html#ADC */

enum InstructionID {
  ADC = 1,
  AND,
  ASL,
  LDA,
  LDX,
  LDY,
  STA,
  DEC
  /*TODO: Fill it up with the others IDs.*/
};

#endif
