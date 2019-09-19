#include "../include/Instruction.hpp"

ADCInstruction::ADCInstruction(uint8_t addressingMode,
                               uint8_t instructionSize) {
  this->_addressingMode = addressingMode;
  this->_instructionSize = instructionSize;
  cout << "\n\nADCInstruction Constructor...\n";
};

void ADCInstruction::execute(Cpu *cpu, uint16_t address) {
  cout << "Executing a ADC instruction...\n";
  cout << "[Address]: " << address << "\n\n";
};

uint8_t ADCInstruction::getInstructionSize() { return this->_instructionSize; }

uint8_t ADCInstruction::getAddressingMode() { return this->_addressingMode; }
