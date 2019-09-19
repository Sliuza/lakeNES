#include "../include/Instruction.hpp"
#include "../include/Cpu.hpp"

BaseInstruction::BaseInstruction(uint8_t addressingMode,
                                 uint8_t instructionSize) {
  cout << "[BaseInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
  this->_addressingMode = addressingMode;
  this->_instructionSize = instructionSize;
}

uint8_t BaseInstruction::getAddressingMode() { return this->_addressingMode; };

uint8_t BaseInstruction::getInstructionSize() {
  return this->_instructionSize;
};

LDAInstruction::LDAInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[LDAInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}

void LDAInstruction::execute(Cpu *cpu, uint16_t address) {
  cout << "[LDAInstruction] -  execute()\n";
}
