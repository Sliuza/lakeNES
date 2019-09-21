#include "../include/Cpu.hpp"
#include "../include/Instruction.hpp"
#include "../include/InstructionFactory.hpp"

Cpu::Cpu() {
  this->pc_reg = 0;
  this->sp_reg = 0xFF;
  this->x_reg = 0;
  this->y_reg = 0;
  this->a_reg = 0;
  this->ram = Memory();
  this->rom = Rom();
};

int Cpu::getNumberOfPrgBlocks() { return 2; }

void Cpu::loadROM(string path) {
  cout << "loadROM\n";
  ifstream input(path, ios::binary);
  int counter = 0;
  int byteCounter = 0xc000;
  uint8_t a;
  vector<uint8_t> bytes(65536);

  while (!input.eof()) {
    input >> a;
    if (counter > 16) {
      bytes.insert(bytes.begin() + byteCounter, (uint8_t)(a));
      byteCounter += 1;
    }
    counter += 1;
  }
  this->rom.setBytes(bytes);
}

void Cpu::printROM() {
  cout << "printROM\n";
  vector<uint8_t> r = this->rom.getRom();

  Instruction *instruction;
  InstructionFactory factory;

  // TODO : Create a Instruction Factory responsible for create the
  // instance according to the instruction pointed by PC.
  instruction = factory.createInstruction(0x69);

  instruction->execute(this, 0x123);
  // for (int i = 0xc000; i < r.size(); i++) {
  //   cout << std::hex << (unsigned)(uint8_t)r.at(i);
  // }

  this->pc_reg += instruction->getInstructionSize();

  cout << "[PC]: " << this->pc_reg << "\n";
}

//GETTERS
uint16_t Cpu::getPc_reg(){
  return this->pc_reg;
}
uint8_t Cpu::getSp_reg(){
  return this->sp_reg;
}
uint8_t Cpu::getX_reg(){
  return this->x_reg;
}
uint8_t Cpu::getY_reg(){
  return this->y_reg;
}
Rom Cpu::getRom(){
  return this->rom;
}
Memory Cpu::getRam(){
  return this->ram;
};

//SETTERS
void Cpu::setPc_reg(uint16_t _pc_reg){
  this->pc_reg = _pc_reg;
} 
void Cpu::setSp_reg(uint8_t _sp_reg){
  this->sp_reg = _sp_reg;
}
void Cpu::setX_reg(uint8_t _x_reg){
  this->x_reg = _x_reg; 
}
void Cpu::setY_reg(uint8_t _y_reg){
  this->y_reg = _y_reg; 
}
void Cpu::setA_reg(uint8_t _a_reg){
  this->a_reg = _a_reg; 
}
  
