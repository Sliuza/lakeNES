#include "../include/Cpu.hpp"
#include "../include/Instruction.hpp"
#include "../include/InstructionFactory.hpp"
#include "Utils.cpp"
Cpu::Cpu() {
  this->pc_reg = 0;
  this->sp_reg = 0;
  this->x_reg = 0;
  this->y_reg = 0;
  this->a_reg = 0;
  this->ram[0x800];
  this->rom = Rom();
};

int Cpu::getNumberOfPrgBlocks() { return 2; }
void Cpu::startCpu(){
  // Initiate ram with 0xFF
  init_array(this->ram, (uint8_t)0xFF);
};

enum Interrupt_type { BRK = 0, IRQ, NMI, reset };

void Cpu::interrupt(Interrupt_type interruption){
    uint16_t addr;

    if (interruption != BRK) {
        // For BRK, these have already been done
        read_mem(this->pc_reg);
        read_mem(this->pc_reg);
    }

    if (interruption == reset) {
        addr = 0xFFFC;
    }
    pc_reg  = read_mem(addr);
    pc_reg |= read_mem(addr + 1) << 8;
}
void Cpu::push(uint8_t val) {
    this->ram[0x100 + this->sp_reg--] = val;
}

uint8_t Cpu::pull() {
    return this->ram[0x100 + ++sp_reg];
}
void Cpu::run(){
  startCpu();
  interrupt(reset);
  while(1){
    Instruction *instruction;
    InstructionFactory factory;
    uint8_t opcode = read_mem(this->pc_reg++);
    instruction = factory.createInstruction(opcode);
    instruction->execute(this, this->pc_reg);
  }
}
uint8_t Cpu::read_mem(uint16_t addr) {
    uint8_t res;

    switch (addr) {
    case 0x0000 ... 0x1FFF: res = this->ram[addr & 0x7FF];      break;
    // case 0x8000 ... 0xFFFF: res = this->rom.read_prg(addr);     break;
    }
    return res;
}
void Cpu::write_mem(uint8_t val, uint16_t addr) {
    switch (addr) {
    case 0x0000 ... 0x1FFF: this->ram[addr & 0x7FF] = val;      break;
    }
}
void Cpu::loadROM(string path) {
  cout << "Running ROM: " << path << std::endl;
  this->rom.load(path);
}

void Cpu::printROM() {
  cout << "printROM\n";

  Instruction *instruction;
  InstructionFactory factory;

  // TODO : Create a Instruction Factory responsible for create the
  // instance according to the instruction pointed by PC.
  instruction = factory.createInstruction(0x85);
  a_reg = 8;

  instruction->execute(this, 0x123);
  instruction = factory.createInstruction(0xA5);


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
uint8_t Cpu::getA_reg(){
  return this->a_reg;
}
Rom Cpu::getRom(){
  return this->rom;
}
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
  
