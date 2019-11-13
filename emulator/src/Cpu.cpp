#include "../include/Cpu.hpp"
#include "../include/Ppu.hpp"
#include "../include/Instruction.hpp"
#include "../include/InstructionFactory.hpp"
#include "Utils.cpp"
#include <iomanip>
#include <sstream>


uint8_t make_P(uint8_t t1, uint8_t t2, uint8_t t3, uint8_t t4, uint8_t t5, uint8_t t6) {
  uint8_t b = t1 + t2 * 2 + t3 * 4 + t4 * 8 + t5 * 64 + t6 * 128;
  return b;
}

Cpu::Cpu() {

  this->pc_reg = 0xfffc;
  this->sp_reg = 0xfd;
  this->x_reg = 0;
  this->y_reg = 0;
  this->a_reg = 0;
  this->rom = Rom();
  this->remainingCycles = 0;
};

void Cpu::nmi_interruption(){
  // printf("PC START NMI: %d \n", this->pc_reg);
  this->push(this->pc_reg >> 8);
  this->push(this->pc_reg);
  // printf("PC LOADED NMI: %d \n", this->pc_reg);
  uint8_t flags = this->getF_negative() << 7 |
                  this->getF_overflow() << 6 |
                  1 << 5 |
                  0 << 4 |
                  this->getF_decimal() << 3 |
                  this->getF_interrupt() << 2 |
                  this->getF_zero() << 1 |
                  this->getF_carry();
  // printf("FLAGS START NMI: %d \n", this->flags);

  
  
  uint16_t addr_abs = 0xFFFA;
	uint16_t lo = this->read_mem(addr_abs + 0);
	uint16_t hi = this->read_mem(addr_abs + 1);
	this->pc_reg = (hi << 8) | lo;
  // printf("PC END NMI: %d \n", this->pc_reg);
  this->push(flags);
  // printf("FLAGS LOADED NMI: %d   SPREG: %d\n", this->flags, this->sp_reg);

}

void Cpu::shutPpu() {
  // ppu.endPpu();
}

void Cpu::startCpu() {
  // Initiate ram with 0xFF
  init_array(this->ram, (uint8_t)0x0000);
  this->reset();
};
void Cpu::reset() {
  this->a_reg = this->x_reg = this->y_reg = 0;
  this->f_interrupt = 1;
  this->flags = 1;
  this->f_negative = this->f_overflow = this->f_zero = this->f_carry = this->f_decimal = 0;
  this->pc_reg = this->read_mem(0xfffc) | this->read_mem(0xfffc + 1) << 8;
  // printf("this->pc_reg ================= %d\n", this->pc_reg);
  this->sp_reg = 0xfd;
  ppu->setFirstWrite(true);
  this->setCyclesCounter(7);
  this->foundBrk = false;
  this->remainingCycles = 0;
}
void Cpu::push(uint8_t val) {
  this->ram[0x100 + this->sp_reg--] = val;
}

uint8_t Cpu::pull() {
  return this->ram[0x100 + ++sp_reg];
}
void Cpu::runCycle() {
  Instruction *instruction;
  InstructionFactory factory;
  uint16_t address = 0;

  if (!this->isStall()) {

    uint8_t opcode = read_mem(this->pc_reg);
    if (opcode == 0x00) {
      this->setFoundBrk(true);
    } else {
      
      instruction = factory.createInstruction(opcode);
      if(&instruction == NULL){
          return;
      }
      address = getAddressBasedOnAddressingMode(instruction->getAddressingMode());
      string p = this->getPrintBasedOnAddressingMode(instruction->getAddressingMode());
      if (opcode == 0x48 || opcode == 0x08 || opcode == 0x68 || opcode == 0x28) { //PHA //PHP //PLA //PLP
        address = 0x0100 + getSp_reg();
      }
      this->printOutput(instruction->getPrintMode(), opcode, instruction->getAddressingMode(), address, instruction->getDecodedInstruction() + " " + p);
      this->setCyclesCounter(instruction->getCycles()+this->getCyclesCounter());
      instruction->execute(this, address);
      if (opcode == 0x4c || opcode == 0x6c || opcode == 0x20 || opcode == 0x60 || opcode == 0x40 ) {
      } else {
        this->setPc_reg(this->pc_reg + uint16_t(instruction->getInstructionSize()));
      }

      this->remainingCycles = instruction->getCycles();
      //deveriamos ter uma condicao para a chamada da escrita na tela.
    }
  }
  this->remainingCycles--;
}

bool Cpu::isStall() {
  return this->remainingCycles > 0;
};

uint8_t Cpu::read_mem(uint16_t addr) {
  uint8_t res;

  switch (addr) {
    case 0x0000 ... 0x1FFF:
      res = this->ram[addr & 0x7FF];
      break;
    case 0x2000 ... 0x3FFF:
      res = ppu->read_mem(addr & 0x2007);
      break;
    case 0x4014 ... 0x4015:
      res = ppu->read_mem(addr);
      break;
    case 0x4016:
      res = screen.readControl1();
      break;
    case 0x4017:
      res = screen.readControl2();
      break;
    default:
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
    case 0x2000 ... 0x3FFF:
        ppu->write_mem(val, addr & 0x2007);
        break;
    case 0x4014:
        // printf("%d ------------------------- 0000000000000000000 \n", val);
        ppu->setOAMDMA(val);
        ppu->setOam_Table(this->ram);
        break;
    default:
      break;
  }
}
void Cpu::loadROM(string path) {
  this->rom.load(path);
  // for(int i = 0; i < 4096; i++)
  //   printf("%d *****************\n", this->rom.getChr()[i]);
}

void Cpu::printROM() {
  //cout << "printROM\n";

  Instruction *instruction;
  InstructionFactory factory;

  this->pc_reg += instruction->getInstructionSize();

  //cout << "[PC]: " << this->pc_reg << "\n";
}

uint16_t Cpu::getAddressBasedOnAddressingMode(uint8_t addressingMode) {

  uint16_t address = 0;
  switch (addressingMode) {
    case ABSOLUTE: {
      // //cout << "addressing mode = ABSOLUTE\n";
      address = this->get16BitsAddress(this->getPc_reg() + uint16_t(1));
      break;
    }
    case INDEXED_ABSOLUTE_X: {
      //cout << "addressing mode = INDEXED_ABSOLUTE_X\n";
      address = this->get16BitsAddress(this->getPc_reg() + uint16_t(1)) + uint16_t(this->getX_reg());
      break;
    }
    case INDEXED_ABSOLUTE_Y: {
      //cout << "addressing mode = INDEXED_ABSOLUTE_Y\n";
      address = this->get16BitsAddress(this->getPc_reg() + uint16_t(1)) + uint16_t(this->getY_reg());
      break;
    }
    case IMMEDIATE: {
      address = this->pc_reg + uint16_t(1);
      break;
    }
    case INDIRECT: {
      //cout << "addressing mode = INDIRECT\n";
      uint16_t baseAddress = get16BitsAddress(this->getPc_reg() + uint16_t(1));
      address = this->get16BitsAddressInMemory(baseAddress);
      break;
    }
    case INDIRECT_INDEXED: {
      // cout << "addressing mode = INDIRECT_INDEXED\n";
      uint16_t baseAddress = this->read_mem(this->getPc_reg() + uint16_t(1));
      address = (this->get16BitsAddressInMemory(baseAddress) + uint16_t(this->getY_reg()));
      // cout << "Address = " << hex << (unsigned)((this->get16BitsAddressInMemory(baseAddress) + uint16_t(1)))  << endl;
      break;
    }
    case INDEXED_INDIRECT: {
      // cout << "addressing mode = INDEXED_INDIRECT\n";
      uint16_t baseAddress = this->read_mem(this->getPc_reg() + uint16_t(1));
      address = this->get16BitsAddressInMemory(baseAddress) + uint16_t(this->getX_reg());
      break;
    }
    case RELATIVE: { //read relative address and set address to branch
      //cout << "addressing mode = RELATIVE\n";
      uint16_t rel = this->read_mem(this->pc_reg + uint16_t(1));
      if (rel & 0x80)
        rel |= 0xFF00;
      address = this->pc_reg + rel;
      break;
    }
    case ZERO_PAGE: {
      //cout << "addressing mode = ZERO_PAGE\n";
      address = this->read_mem(this->getPc_reg() + uint16_t(1));
      break;
    }
    case INDEXED_ZERO_PAGE_X: {
      // cout << "addressing mode = INDEXED_ZERO_PAGE_X\n";
      uint16_t baseAddress = this->read_mem(this->getPc_reg() + uint16_t(1));
      address = (baseAddress + uint16_t(this->getX_reg())) & 0xFF;
      break;
    }
    case INDEXED_ZERO_PAGE_Y: {
      //cout << "addressing mode = INDEXED_ZERO_PAGE_Y\n";
      uint16_t baseAddress = this->read_mem(this->getPc_reg() + uint16_t(1));
      address = (baseAddress + uint16_t(this->getY_reg())) & 0xFF;
      break;
    }
  }
  return address;
}

string Cpu::getPrintBasedOnAddressingMode(uint8_t addressingMode) {

  string p = "";
  uint16_t address;
  switch (addressingMode) {
    case ABSOLUTE: {
      // //cout << "addressing mode = ABSOLUTE\n";
      std::stringstream stream;
      address = this->get16BitsAddress(this->getPc_reg() + uint16_t(1));
      stream << uppercase << hex << ((address & 0xF000) >> 12);
      stream << uppercase << hex << ((address & 0xF00) >> 8);
      stream << uppercase << hex << ((address & 0xF0) >> 4);
      stream << uppercase << hex << ((address & 0xF) >> 0);
      p = "$"+stream.str();
      break;
    }
    case INDEXED_ABSOLUTE_X: {
      //cout << "addressing mode = INDEXED_ABSOLUTE_X\n";
      address = this->get16BitsAddress(this->getPc_reg() + uint16_t(1)) + uint16_t(this->getX_reg());
      std::stringstream stream;
      stream << std::hex << address << " " << this->getX_reg();
      stream << uppercase << hex << ((address & 0xF000) >> 12);
      stream << uppercase << hex << ((address & 0xF00) >> 8);
      stream << uppercase << hex << ((address & 0xF0) >> 4);
      stream << uppercase << hex << ((address & 0xF) >> 0);
      stream << " " <<std::hex << this->getX_reg();
      p = "$"+stream.str();
      break;
    }
    case INDEXED_ABSOLUTE_Y: {
      //cout << "addressing mode = INDEXED_ABSOLUTE_Y\n";
      address = this->get16BitsAddress(this->getPc_reg() + uint16_t(1)) + uint16_t(this->getY_reg());
      std::stringstream stream;
      stream << uppercase << hex << ((address & 0xF000) >> 12);
      stream << uppercase << hex << ((address & 0xF00) >> 8);
      stream << uppercase << hex << ((address & 0xF0) >> 4);
      stream << uppercase << hex << ((address & 0xF) >> 0);
      stream << " " <<std::hex << this->getY_reg();
      p = "$"+stream.str();
      break;
    }
    case IMMEDIATE: {
      address = this->pc_reg + uint16_t(1);
      int value = this->read_mem(address);
      std::stringstream stream;
      stream << uppercase << setfill('0') << setw(2) << value;
      p = "$"+stream.str();
      break;
    }
    case INDIRECT: {
      //cout << "addressing mode = INDIRECT\n";
      uint16_t baseAddress = get16BitsAddress(this->getPc_reg() + uint16_t(1));
      address = this->get16BitsAddressInMemory(baseAddress);
      break;
    }
    case INDIRECT_INDEXED: {
      // cout << "addressing mode = INDIRECT_INDEXED\n";
      uint16_t baseAddress = this->read_mem(this->getPc_reg() + uint16_t(1));
      address = (this->get16BitsAddressInMemory(baseAddress) + uint16_t(this->getY_reg()));
      cout << "Address = " << hex << (unsigned)((this->get16BitsAddressInMemory(baseAddress) + uint16_t(1)))  << endl;
      break;
    }
    case INDEXED_INDIRECT: {
      // cout << "addressing mode = INDEXED_INDIRECT\n";
      uint16_t baseAddress = this->read_mem(this->getPc_reg() + uint16_t(1));
      address = this->get16BitsAddressInMemory(baseAddress) + uint16_t(this->getX_reg());
      break;
    }
    case RELATIVE: { //read relative address and set address to branch
      //cout << "addressing mode = RELATIVE\n";
      uint16_t rel = this->read_mem(this->pc_reg + uint16_t(1));
      if (rel & 0x80)
        rel |= 0xFF00;
      address = this->pc_reg + rel;
      std::stringstream stream;
      stream << uppercase << hex << ((address & 0xF000) >> 12);
      stream << uppercase << hex << ((address & 0xF00) >> 8);
      stream << uppercase << hex << ((address & 0xF0) >> 4);
      stream << uppercase << hex << ((address & 0xF) >> 0);
      p = "$"+stream.str(); 
      
      break;
    }
    case ZERO_PAGE: {
    //   cout << "addressing mode = ZERO_PAGE\n";
    address = this->read_mem(this->getPc_reg() + uint16_t(1));
    std::stringstream stream;
    stream << uppercase << hex << ((address & 0xF0) >> 4);
    stream << uppercase << hex << ((address & 0xF) >> 0);
    stream << " = ";
    stream << uppercase << hex << ((address & 0xF000) >> 12);
    stream << uppercase << hex << ((address & 0xF00) >> 8);
    p = "$"+stream.str();
    stream << " " <<std::hex << this->getY_reg();

      break;
    }
    case INDEXED_ZERO_PAGE_X: {
      // cout << "addressing mode = INDEXED_ZERO_PAGE_X\n";
      uint16_t baseAddress = this->read_mem(this->getPc_reg() + uint16_t(1));
      address = (baseAddress + uint16_t(this->getX_reg())) & 0xFF;
      break;
    }
    case INDEXED_ZERO_PAGE_Y: {
      //cout << "addressing mode = INDEXED_ZERO_PAGE_Y\n";
      uint16_t baseAddress = this->read_mem(this->getPc_reg() + uint16_t(1));
      address = (baseAddress + uint16_t(this->getY_reg())) & 0xFF;
      break;
    }
  }
  return p;
}

uint16_t Cpu::get16BitsAddress(uint16_t address) {
  uint16_t lo = this->read_mem(address);
  uint16_t hi = this->read_mem(address + uint16_t(1)) << 8;
  return hi | lo;
}

uint16_t Cpu::get16BitsAddressInMemory(uint16_t address) {
  uint16_t lo = this->read_mem(address);
  uint16_t hiAddress = (address & 0xFF00) | ((address + 1) & 0xFF);
  uint16_t hi = (this->read_mem(hiAddress)) << 8;

  return hi | lo;
}

void Cpu::printOutput(uint16_t printFuncion,uint8_t opcode, uint8_t addressMode, uint16_t address, string decodedInstruction) {
  this->print(opcode, addressMode, address, decodedInstruction);
};

void Cpu::print(uint8_t opcode, uint8_t addressMode,  uint16_t address, string decodedInstruction) {
  unsigned p = this->getP_reg();

  cout << setfill('0') << uppercase << hex << setw(4) << this->getPc_reg()
  <<" "<< uppercase << hex << setw(2) << (unsigned)opcode;
  if(address != 0){
    cout << " "  << uppercase << hex << ((address & 0xF0) >> 4);
    cout << uppercase << hex << ((address & 0xF) >> 0);
    cout << " " << uppercase << hex << ((address & 0xF000) >> 12);
    cout << uppercase << hex << ((address & 0xF00) >> 8);
  }
  else{
    cout << "      ";
  }
  cout << "  ";
  cout.width(32);
  cout << setfill(' ')<< std::left << decodedInstruction;
  cout << setfill('0') << " A:" << uppercase << hex << setw(2) << (unsigned)this->getA_reg()
  << " X:" << uppercase << hex << setw(2) << (unsigned)this->getX_reg()
  << " Y:" << uppercase << hex << setw(2) << (unsigned)this->getY_reg()
  << " P:" << uppercase << hex << setw(2) << (unsigned)p
  << " SP:" << uppercase << hex << setw(2) << (unsigned)(this->getSp_reg());
  cout << " CYC:" << dec << this->getCyclesCounter() << endl;
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
uint8_t Cpu::getF_carry() {
  return this->f_carry;
}
uint8_t Cpu::getF_zero() {
  return this->f_zero;
}
uint8_t Cpu::getF_interrupt() {
  return this->f_interrupt;
}
uint8_t Cpu::getF_decimal() {
  return this->f_decimal;
}
uint8_t Cpu::getF_overflow() {
  return this->f_overflow;
}
uint8_t Cpu::getF_negative() {
  return this->f_negative;
}
int Cpu::getCyclesCounter(){
  return this->cyclesCounter;
}

uint8_t Cpu::getP_reg() {
  uint8_t p = 0;

  p |= f_negative ? uint8_t(1) << 7 : p;
  p |= f_overflow ? uint8_t(1) << 6 : p;
  p |= flags ? uint8_t(1) << 5 : p;
  p |= flags ? uint8_t(1) << 4 : p;
  p |= f_decimal ? uint8_t(1) << 3 : p;
  p |= f_interrupt ? uint8_t(1) << 2 : p;
  p |= f_zero ? uint8_t(1) << 1 : p;
  p |= f_carry ? uint8_t(1) : p;

  return p;
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
void Cpu::setP_reg(uint8_t _p_reg) {

  setF_negative(_p_reg & uint8_t(1) << 7);
  setF_overflow(_p_reg & uint8_t(1) << 6);
  set_flags(_p_reg & uint8_t(1) << 5);
  set_flags(_p_reg & uint8_t(1) << 4);
  setF_decimal(_p_reg & uint8_t(1) << 3);
  setF_interrupt(_p_reg & uint8_t(1) << 2);
  setF_zero(_p_reg & uint8_t(1) << 1);
  setF_carry(_p_reg & uint8_t(1) << 0);
}
void Cpu::setF_carry(uint8_t carry) {
  this->f_carry = carry;
}
void Cpu::setF_zero(uint8_t zero) {
  this->f_zero = zero;
}
void Cpu::setF_interrupt(uint8_t interrupt) {
  this->f_interrupt = interrupt;
}
void Cpu::setF_decimal(uint8_t decimal) {
  this->f_decimal = decimal;
}
void Cpu::setF_overflow(uint8_t overflow) {
  this->f_overflow = overflow;
}
void Cpu::setF_negative(uint8_t negative) {
  this->f_negative = negative;
}
void Cpu::set_flags(uint8_t f_lags) {
  this->flags = f_lags;
}

bool Cpu::getFoundBrk() {
  return this->foundBrk;
}

void Cpu::setFoundBrk(bool _foundBrk) {
  this->foundBrk = _foundBrk;
}

void Cpu::setPpu(Ppu *ppu) {
  this->ppu = ppu;
};

void Cpu::setCyclesCounter(int cyclesCounter){
  this->cyclesCounter = cyclesCounter;
}
