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

ADCInstruction::ADCInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[ADCInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}

void ADCInstruction::execute(Cpu *cpu, uint16_t address) {
  //TODO: Set Flags
  cout << "[ADCInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF){
    uint8_t value = cpu->read_mem(address);
    uint8_t a_regValue = cpu->getA_reg();
    cpu->setA_reg(a_regValue+value);
  }
}

ANDInstruction::ANDInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[ANDInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}

void ANDInstruction::execute(Cpu *cpu, uint16_t address) {
  cout << "[ANDInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF){
    uint8_t value = cpu->read_mem(address);
    uint8_t a_regValue = cpu->getA_reg();
    cpu->setA_reg(a_regValue & value);
  }
}

LDAInstruction::LDAInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[LDAInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}

void LDAInstruction::execute(Cpu *cpu, uint16_t address) {
  cout << "[LDAInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF){
    uint8_t value = cpu->read_mem(address);
    cpu->setA_reg(value);
  }
}

LDXInstruction::LDXInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[LDXInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}

void LDXInstruction::execute(Cpu *cpu, uint16_t address) {
  cout << "[LDXInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF){
    uint8_t value = cpu->read_mem(address);
    cpu->setX_reg(value);
  }
}

LDYInstruction::LDYInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[LDYInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}

void LDYInstruction::execute(Cpu *cpu, uint16_t address) {
  cout << "[LDYInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF){
    uint8_t value = cpu->read_mem(address);
    cpu->setY_reg(value);
  }
}
