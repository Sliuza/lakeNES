#include "../include/Cpu.hpp"
#include "../include/Instruction.hpp"
#include "../include/InstructionFactory.hpp"
#include "Utils.cpp"
Cpu::Cpu() {
  this->pc_reg = 0xfffc;
  this->sp_reg = 0xfd;
  this->x_reg = 0;
  this->y_reg = 0;
  this->a_reg = 0;
  this->rom = Rom();
};

void Cpu::startCpu() {
  // Initiate ram with 0xFF
  init_array(this->ram, (uint8_t)0xFF);
  this->reset();
};
void Cpu::reset() {
  this->a_reg, this->x_reg, this->y_reg = 0;
  this->f_interrupt = true;
  this->f_negative, this->f_overflow, this->f_zero, this->f_carry, this->f_decimal = false;
  this->pc_reg = this->read_mem(0xfffc) | this->read_mem(0xfffc + 1) << 8;
  this->sp_reg = 0xfd;
}
void Cpu::push(uint8_t val) {
  this->ram[0x100 + this->sp_reg--] = val;
}

uint8_t Cpu::pull() {
  return this->ram[0x100 + ++sp_reg];
}
void Cpu::run() {
  this->startCpu();
  Instruction *instruction;
  InstructionFactory factory;
  uint16_t address = 0;
  bool br = true;
  while (br) {

    uint8_t opcode = read_mem(this->pc_reg);
    // cout << "pc = " << hex << (unsigned)this->pc_reg << endl;
    if(opcode == 0x00)
      br = false;

    this->pc_reg++;

    // cout << "opcode = " << (unsigned)opcode << endl;
    instruction = factory.createInstruction(opcode);
    
      
      address = getAddressBasedOnAddressingMode(instruction->getAddressingMode());
      instruction->execute(this, address);
      this->setPc_reg(this->pc_reg + uint16_t(instruction->getInstructionSize()) - 1);
    
  }

  cout <<   "CPU FINISHED RUNNING\n";
  
}
uint8_t Cpu::read_mem(uint16_t addr) {
  uint8_t res;

  switch (addr) {
    case 0x0000 ... 0x1FFF:
      res = this->ram[addr & 0x7FF];
      break;
    case 0x8000 ... 0xFFFF:
      res = this->rom.readPgr(addr);
      break;
  }
  return res;
}
void Cpu::write_mem(uint8_t val, uint16_t addr) {
  switch (addr) {
    case 0x0000 ... 0x1FFF:
      this->ram[addr & 0x7FF] = val;
      break;
  }
}
void Cpu::loadROM(string path) {
  // cout << "Running ROM: " << path << std::endl;
  this->rom.load(path);
}

void Cpu::printROM() {
  cout << "printROM\n";

  Instruction *instruction;
  InstructionFactory factory;

  // instruction = factory.createInstruction(0x69);
  // instruction->execute(this, 0x123);
  // for (int i = 0xc000; i < r.size(); i++) {
  //   cout << std::hex << (unsigned)(uint8_t)r.at(i);
  // }

  this->pc_reg += instruction->getInstructionSize();

  cout << "[PC]: " << this->pc_reg << "\n";
}

uint16_t Cpu::getAddressBasedOnAddressingMode(uint8_t addressingMode) {
  
  uint16_t address = 0;
  switch (addressingMode) {
    case ABSOLUTE: {
      cout << "addressing mode = ABSOLUTE\n";
      address = this->get16BitsAddress(this->getPc_reg() + uint16_t(1));
      break;
    }
    case INDEXED_ABSOLUTE_X: {
      cout << "addressing mode = INDEXED_ABSOLUTE_X\n";
      address = this->get16BitsAddress(this->getPc_reg() + uint16_t(1)) + uint16_t(this->getX_reg());
      break;
    }
    case INDEXED_ABSOLUTE_Y: {
      cout << "addressing mode = INDEXED_ABSOLUTE_Y\n";
      address = this->get16BitsAddress(this->getPc_reg() + uint16_t(1)) + uint16_t(this->getY_reg());
      break;
    }
    case IMMEDIATE: {
      cout << "addressing mode = IMMEDIATE\n";
      address = this->pc_reg;
      break;
    }
    case INDIRECT: {
      cout << "addressing mode = INDIRECT\n";
      uint16_t baseAddress = get16BitsAddress(this->getPc_reg() + uint16_t(1));
      address = this->get16BitsAddressInMemory(baseAddress);
      break;
    }
    case INDIRECT_INDEXED: {
      cout << "addressing mode = INDIRECT_INDEXED\n";
      uint16_t baseAddress = this->read_mem(this->getPc_reg() + uint16_t(1));
      address = this->get16BitsAddressInMemory(baseAddress) + uint16_t(this->getY_reg());
      break;
    }
    case INDEXED_INDIRECT: {
      cout << "addressing mode = INDEXED_INDIRECT\n";
      uint16_t baseAddress = this->read_mem(this->getPc_reg() + uint16_t(1));
      address = this->get16BitsAddressInMemory(baseAddress) + uint16_t(this->getX_reg());
      break;
    }
    case RELATIVE: { //read relative address and set address to branch
      cout << "addressing mode = RELATIVE\n";
      uint16_t rel = this->read_mem(this->pc_reg + uint16_t(1));
      if (rel & 0x80)
        rel |= 0xFF00;
      address = this->pc_reg + rel;
      break;
    }
    case ZERO_PAGE: {
      cout << "addressing mode = ZERO_PAGE\n";
      address = this->read_mem(this->getPc_reg() + uint16_t(1));
      break;
    }
    case INDEXED_ZERO_PAGE_X: {
      cout << "addressing mode = INDEXED_ZERO_PAGE_X\n";
      uint16_t baseAddress = this->read_mem(this->getPc_reg() + uint16_t(1));
      address = (baseAddress + uint16_t(this->getX_reg())) & 0xFF;
      break;
    }
    case INDEXED_ZERO_PAGE_Y: {
      cout << "addressing mode = INDEXED_ZERO_PAGE_Y\n";
      uint16_t baseAddress = this->read_mem(this->getPc_reg() + uint16_t(1));
      address = (baseAddress + uint16_t(this->getY_reg())) & 0xFF;
      break;
    }
    // default:{
    //   cout << "addressing mode = default\n";
    //   address = 0;
    //   break;
    // }
      
  }
  return address;
}

uint16_t Cpu::get16BitsAddress(uint16_t address) {
  uint16_t lo = this->read_mem(address);
  uint16_t hi = this->read_mem(address + uint16_t(1)) << 8;
  return hi | lo;
}

uint16_t Cpu::get16BitsAddressInMemory(uint16_t address) {
  uint16_t lo = this->read_mem(address);
  uint16_t hiAddress = (address & 0xFF00) | ((address + 1) & 0xFF);
  uint16_t hi = this->read_mem(hiAddress) << 8;
  return hi | lo;
}

//GETTERS
uint16_t Cpu::getPc_reg() {
  return this->pc_reg;
}
uint8_t Cpu::getSp_reg() {
  return this->sp_reg;
}
uint8_t Cpu::getX_reg() {
  return this->x_reg;
}
uint8_t Cpu::getY_reg() {
  return this->y_reg;
}
uint8_t Cpu::getA_reg() {
  return this->a_reg;
}
bool Cpu::getF_carry() {
  return this->f_carry;
}
bool Cpu::getF_zero() {
  return this->f_zero;
}
bool Cpu::getF_interrupt() {
  return this->f_interrupt;
}
bool Cpu::getF_decimal() {
  return this->f_decimal;
}
bool Cpu::getF_overflow() {
  return this->f_overflow;
}
bool Cpu::getF_negative() {
  return this->f_negative;
}
Rom Cpu::getRom() {
  return this->rom;
}
//SETTERS
void Cpu::setPc_reg(uint16_t _pc_reg) {
  this->pc_reg = _pc_reg;
}
void Cpu::setSp_reg(uint8_t _sp_reg) {
  this->sp_reg = _sp_reg;
}
void Cpu::setX_reg(uint8_t _x_reg) {
  this->x_reg = _x_reg;
}
void Cpu::setY_reg(uint8_t _y_reg) {
  this->y_reg = _y_reg;
}
void Cpu::setA_reg(uint8_t _a_reg) {
  this->a_reg = _a_reg;
}
void Cpu::setF_carry(bool carry) {
  this->f_carry = carry;
}
void Cpu::setF_zero(bool zero) {
  this->f_zero = zero;
}
void Cpu::setF_interrupt(bool interrupt) {
  this->f_interrupt = interrupt;
}
void Cpu::setF_decimal(bool decimal) {
  this->f_decimal = decimal;
}
void Cpu::setF_overflow(bool overflow) {
  this->f_overflow = overflow;
}
void Cpu::setF_negative(bool negative) {
  this->f_negative = negative;
}
