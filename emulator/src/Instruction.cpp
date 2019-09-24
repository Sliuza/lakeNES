#include "../include/Instruction.hpp"
#include "../include/AddressingMode.hpp"
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

  if (address >= 0x0000 && address <= 0xFFFF) {
    uint16_t carry = (cpu->getF_carry() ? 1 : 0);
    uint16_t value = cpu->read_mem(address);
    uint8_t a_regValue = cpu->getA_reg();
    uint16_t aux = cpu->getA_reg() + value + carry;

    (aux > 255) ? cpu->setF_carry(true) : cpu->setF_carry(false);
    (aux & 0x00FF) == 0 ? cpu->setF_zero(true) : cpu->setF_zero(false);
    (aux & 0x80) ? cpu->setF_negative(true) : cpu->setF_negative(false);
    (~((uint16_t)a_regValue ^ (uint16_t)value) & ((uint16_t)a_regValue ^ (uint16_t)aux)) & 0x0080 ? cpu->setF_overflow(true) : cpu->setF_overflow(false);
    cpu->setA_reg(aux & 0x00FF);
  }
}

ANDInstruction::ANDInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[ANDInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}

void ANDInstruction::execute(Cpu *cpu, uint16_t address) {
  cout << "[ANDInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    uint8_t value = cpu->read_mem(address);
    uint8_t a_regValue = cpu->getA_reg() & value;
    cpu->setA_reg(a_regValue);
    (a_regValue & 0x00FF) == 0 ? cpu->setF_zero(true) : cpu->setF_zero(false);
    a_regValue & 0x80 ? cpu->setF_negative(true) : cpu->setF_negative(false);
  }
}

ASLInstruction::ASLInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[ASLInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}

void ASLInstruction::execute(Cpu *cpu, uint16_t address) {
  cout << "[ASLInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    if (ASLInstruction::getAddressingMode() == IMPLIED) {
      uint8_t a_regValue = cpu->getA_reg() << 1;
      (a_regValue & 0xFF00) > 0 ? cpu->setF_carry(true) : cpu->setF_carry(false);
      (a_regValue & 0x00FF) == 0 ? cpu->setF_zero(true) : cpu->setF_zero(false);
      (a_regValue & 0x80) ? cpu->setF_negative(true) : cpu->setF_negative(false);
      cpu->setA_reg(a_regValue & 0x00FF);
    } else {
      uint8_t value = cpu->read_mem(address) << 1;
      (value & 0xFF00) > 0 ? cpu->setF_carry(true) : cpu->setF_carry(false);
      (value & 0x00FF) == 0 ? cpu->setF_zero(true) : cpu->setF_zero(false);
      (value & 0x80) ? cpu->setF_negative(true) : cpu->setF_negative(false);
      cpu->write_mem(value & 0x00FF, address);
    }
  }
}

BCCInstruction::BCCInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[BCCInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}

void BCCInstruction::execute(Cpu *cpu, uint16_t address) {
  cout << "[BCCInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    if(!cpu->getF_carry())
      cpu->setPc_reg(address);
  }
}

BCSInstruction::BCSInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[BCSInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}

void BCSInstruction::execute(Cpu *cpu, uint16_t address) {
  cout << "[BCSInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    if(cpu->getF_carry())
      cpu->setPc_reg(address);
  }
}

BEQInstruction::BEQInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[BEQInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}

void BEQInstruction::execute(Cpu *cpu, uint16_t address) {
  cout << "[BEQInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    if(cpu->getF_zero())
      cpu->setPc_reg(address);
  }
}

BITInstruction::BITInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[BITInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}

void BITInstruction::execute(Cpu *cpu, uint16_t address) {
  cout << "[BITInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    uint16_t value = cpu->read_mem(address);
    uint16_t aux = cpu->getA_reg() & value;
    
    (aux & 0x00FF) == 0 ? cpu->setF_zero(true) : cpu->setF_zero(false);
    (value & (1 << 7)) ? cpu->setF_negative(true) : cpu->setF_negative(false);
    (value & (1 << 6)) ? cpu->setF_overflow(true) : cpu->setF_overflow(false);
  }
}

BMIInstruction::BMIInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[BMIInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}

void BMIInstruction::execute(Cpu *cpu, uint16_t address) {
  cout << "[BMIInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    if(cpu->getF_negative())
      cpu->setPc_reg(address);
  }
}

BNEInstruction::BNEInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[BNEInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}

void BNEInstruction::execute(Cpu *cpu, uint16_t address) {
  cout << "[BNEInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    if(!cpu->getF_zero())
      cpu->setPc_reg(address);
  }
}

BPLInstruction::BPLInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[BPLInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}

void BPLInstruction::execute(Cpu *cpu, uint16_t address) {
  cout << "[BPLInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    if(!cpu->getF_negative())
      cpu->setPc_reg(address);
  }
}

BRKInstruction::BRKInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[BRKInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}

void BRKInstruction::execute(Cpu *cpu, uint16_t address) {
  //TODO: Entender o BRK
  cout << "[BRKInstruction] -  execute()\n";
  //set interrupt flag 
  cpu->setF_interrupt(true);
  uint8_t stack = cpu->getSp_reg();
  uint16_t pc = cpu->getPc_reg();
  cpu->write_mem(0x0100 + stack, (pc >> 8) & 0x00FF);
  stack--;
  cpu->write_mem(0x0100 + stack, pc & 0x00FF);
  stack--; 
  
  cpu->setSp_reg(stack);
  pc = (uint16_t)cpu->read_mem(0xFFFE) | ((uint16_t)cpu->read_mem(0xFFFF) << 8);
  cpu->setPc_reg(pc);
}

BVCInstruction::BVCInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[BVCInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}

void BVCInstruction::execute(Cpu *cpu, uint16_t address) {
  cout << "[BVCInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    if(!cpu->getF_overflow())
      cpu->setPc_reg(address);
  }
}

BVSInstruction::BVSInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[BVSInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}

void BVSInstruction::execute(Cpu *cpu, uint16_t address) {
  cout << "[BVSInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    if(cpu->getF_overflow())
      cpu->setPc_reg(address);
  }
}

CLCInstruction::CLCInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[CLCInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}
void CLCInstruction::execute(Cpu *cpu, uint16_t address) {
  cout << "[CLCInstruction] -  execute()\n";
  cpu->setF_carry(false);
}

CLDInstruction::CLDInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[CLDInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}
void CLDInstruction::execute(Cpu *cpu, uint16_t address) {
  cout << "[CLDInstruction] -  execute()\n";
  cpu->setF_decimal(false);
}

CLIInstruction::CLIInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[CLIInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}
void CLIInstruction::execute(Cpu *cpu, uint16_t address) {
  cout << "[CLIInstruction] -  execute()\n";
  cpu->setF_interrupt(false);
}

CLVInstruction::CLVInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[CLVInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}
void CLVInstruction::execute(Cpu *cpu, uint16_t address) {
  cout << "[CLVInstruction] -  execute()\n";
  cpu->setF_overflow(false);
}

CMPInstruction::CMPInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[CMPInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}
void CMPInstruction::execute(Cpu *cpu, uint16_t address) {
  cout << "[CMPInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    uint8_t value = cpu->read_mem(address);
    uint8_t a_regValue = cpu->getA_reg();
    uint16_t aux = (uint16_t)a_regValue - (uint16_t)value;
    (aux & 0x00FF) == 0 ? cpu->setF_zero(true) : cpu->setF_zero(false);
    (aux & 0x80) ? cpu->setF_negative(true) : cpu->setF_negative(false);
    (a_regValue >= value) ? cpu->setF_carry(true) : cpu->setF_carry(false);
  }
}

CPXInstruction::CPXInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[CPXInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}
void CPXInstruction::execute(Cpu *cpu, uint16_t address) {
  cout << "[CPXInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    uint8_t value = cpu->read_mem(address);
    uint8_t x_regValue = cpu->getX_reg();
    uint16_t aux = (uint16_t)x_regValue - (uint16_t)value;
    (aux & 0x00FF) == 0 ? cpu->setF_zero(true) : cpu->setF_zero(false);
    (aux & 0x80) ? cpu->setF_negative(true) : cpu->setF_negative(false);
    (x_regValue >= value) ? cpu->setF_carry(true) : cpu->setF_carry(false);
  }
}

CPYInstruction::CPYInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[CPYInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}
void CPYInstruction::execute(Cpu *cpu, uint16_t address) {
  cout << "[CPYInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    uint8_t value = cpu->read_mem(address);
    uint8_t y_regValue = cpu->getY_reg();
    uint16_t aux = (uint16_t)y_regValue - (uint16_t)value;
    (aux & 0x00FF) == 0 ? cpu->setF_zero(true) : cpu->setF_zero(false);
    (aux & 0x80) ? cpu->setF_negative(true) : cpu->setF_negative(false);
    (y_regValue >= value) ? cpu->setF_carry(true) : cpu->setF_carry(false);
  }
}

EORInstruction::EORInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[EORInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}
void EORInstruction::execute(Cpu *cpu, uint16_t address) {
  cout << "[EORInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    uint8_t value = cpu->read_mem(address);
    uint8_t a_regValue = cpu->getA_reg();
    uint8_t aux = a_regValue ^ value;
    (aux & 0x00FF) == 0 ? cpu->setF_zero(true) : cpu->setF_zero(false);
    (aux & 0x80) ? cpu->setF_negative(true) : cpu->setF_negative(false);
    cpu->setA_reg(aux);
  }
}

JMPInstruction::JMPInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[JMPInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}
void JMPInstruction::execute(Cpu *cpu, uint16_t address) {
  cout << "[JMPInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    cpu->setPc_reg(address);
  }
}

JSRInstruction::JSRInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[JSRInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}
void JSRInstruction::execute(Cpu *cpu, uint16_t address) {
  cout << "[JSRInstruction] -  execute()\n";
  //PUSH PC INTO STACK, SET PC ADDRESS.
  if (address >= 0x0000 && address <= 0xFFFF) {
    uint8_t stack = cpu->getSp_reg();
    uint16_t pc = cpu->getPc_reg();
    cpu->write_mem(0x0100 + stack, (pc >> 8) & 0x00FF);
    stack--;
    cpu->write_mem(0x0100 + stack, pc & 0x00FF);
    stack--;
    
    cpu->setSp_reg(stack);
    cpu->setPc_reg(address);
  }
}


LSRInstruction::LSRInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[LSRInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}
void LSRInstruction::execute(Cpu *cpu, uint16_t address) {
  cout << "[LSRInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    uint8_t value = cpu->read_mem(address);
    (value & 0x0001) ? cpu->setF_carry(true) : cpu->setF_carry(false);
    
    uint8_t aux = value >> 1;
    (aux & 0x00FF) == 0 ? cpu->setF_zero(true) : cpu->setF_zero(false);
    (aux & 0x80) ? cpu->setF_negative(true) : cpu->setF_negative(false);
    if (LSRInstruction::getAddressingMode() == IMPLIED) {
        cpu->setA_reg(aux & 0x00FF);
    }
    else{
        cpu->write_mem(address, aux & 0x00FF);
    }
  }
}

NOPInstruction::NOPInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[NOPInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}
void NOPInstruction::execute(Cpu *cpu, uint16_t address) {
  cout << "[NOPInstruction] -  execute()\n";
}

PLAInstruction::PLAInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[PLAInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}
void PLAInstruction::execute(Cpu *cpu, uint16_t address) {
  cout << "[PLAInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    uint8_t stack = cpu->getSp_reg();
    stack ++;
    cpu->setSp_reg(stack);
    
    uint8_t a_regValue = cpu->getA_reg();
    uint8_t aux = cpu->read_mem(0x0100+stack);
    
    (aux & 0x00FF) == 0 ? cpu->setF_zero(true) : cpu->setF_zero(false);
    (aux & 0x80) ? cpu->setF_negative(true) : cpu->setF_negative(false);
    cpu->setA_reg(aux);
  }
}

PLPInstruction::PLPInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[PLPInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}
void PLPInstruction::execute(Cpu *cpu, uint16_t address) {
  cout << "[PLPInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    uint8_t stack = cpu->getSp_reg();
    stack ++;
    cpu->setSp_reg(stack);
    
    uint8_t a_regValue = cpu->getA_reg();
    uint8_t aux = cpu->read_mem(0x0100+stack);
    
  }
}

PHAInstruction::PHAInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[PHAInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}
void PHAInstruction::execute(Cpu *cpu, uint16_t address) {
  cout << "[PHAInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    uint8_t stack = cpu->getSp_reg();
    uint8_t a_regValue = cpu->getA_reg();
    cpu->write_mem(0x0100+stack, a_regValue);
    stack --;
    cpu->setSp_reg(stack);
  }
}

PHPInstruction::PHPInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[PHPInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}
void PHPInstruction::execute(Cpu *cpu, uint16_t address) {
  cout << "[PHPInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    uint8_t stack = cpu->getSp_reg();
    uint8_t status = cpu->getA_reg();
    cpu->write_mem(0x0100+stack, status);
    stack --;
    cpu->setSp_reg(stack);
  }
}


ORAInstruction::ORAInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[ORAInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}
void ORAInstruction::execute(Cpu *cpu, uint16_t address) {
  cout << "[ORAInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    uint8_t value = cpu->read_mem(address);
    uint8_t a_regValue = cpu->getA_reg();
    uint8_t aux = a_regValue | value;
    (aux & 0x00FF) == 0 ? cpu->setF_zero(true) : cpu->setF_zero(false);
    (aux & 0x80) ? cpu->setF_negative(true) : cpu->setF_negative(false);
    cpu->setA_reg(aux);
  }
}

LDAInstruction::LDAInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[LDAInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}

void LDAInstruction::execute(Cpu *cpu, uint16_t address) {
  cout << "[LDAInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    uint8_t value = cpu->read_mem(address);
    cpu->setA_reg(value);
    (value & 0x00FF) == 0 ? cpu->setF_zero(true) : cpu->setF_zero(false);
    (value & 0x80) ? cpu->setF_negative(true) : cpu->setF_negative(false);
    cout << "a = " << hex << (unsigned)(uint8_t)cpu->getA_reg() << "\n";
  }
}

STAInstruction::STAInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[STAInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}

void STAInstruction::execute(Cpu *cpu, uint16_t address) {
  cout << "[STAInstruction] -  execute()\n";
  cpu->write_mem(cpu->getA_reg(), address);
}

LDXInstruction::LDXInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[LDXInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}

void LDXInstruction::execute(Cpu *cpu, uint16_t address) {
  cout << "[LDXInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    uint8_t value = cpu->read_mem(address);
    cpu->setX_reg(value);
    (value & 0x00FF) == 0 ? cpu->setF_zero(true) : cpu->setF_zero(false);
    (value & 0x80) ? cpu->setF_negative(true) : cpu->setF_negative(false);
  }
}

LDYInstruction::LDYInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[LDYInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}

void LDYInstruction::execute(Cpu *cpu, uint16_t address) {
  cout << "[LDYInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    uint8_t value = cpu->read_mem(address);
    cpu->setY_reg(value);
    (value & 0x00FF) == 0 ? cpu->setF_zero(true) : cpu->setF_zero(false);
    (value & 0x80) ? cpu->setF_negative(true) : cpu->setF_negative(false);
  }
}
DECInstruction::DECInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[DECInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}

void DECInstruction::execute(Cpu *cpu, uint16_t address){
  uint8_t value = cpu->read_mem(address);
  value -= 1;
  cpu->setF_zero(!value);
  cpu->setF_negative(value & 0x80);
  cpu->write_mem(value, address);
}


DEXInstruction::DEXInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[DEXInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}

void DEXInstruction::execute(Cpu *cpu, uint16_t address){
  uint8_t value = cpu->getX_reg();
  value -= 1;
  cpu->setF_zero(!value);
  cpu->setF_negative(value & 0x80);
  cpu->setX_reg(value);
}

DEYInstruction::DEYInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[DEYInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}

void DEYInstruction::execute(Cpu *cpu, uint16_t address){
  uint8_t value = cpu->getY_reg();
  value -= 1;
  cpu->setF_zero(!value);
  cpu->setF_negative(value & 0x80);
  cpu->setY_reg(value);
}

INCInstruction::INCInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[INCInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}

void INCInstruction::execute(Cpu *cpu, uint16_t address){
  uint8_t value = cpu->read_mem(address);
  value += 1;
  cpu->setF_zero(!value);
  cpu->setF_negative(value & 0x80);
  cpu->write_mem(value, address);
}

INXInstruction::INXInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[INXInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}

void INXInstruction::execute(Cpu *cpu, uint16_t address){
  uint8_t value = cpu->getX_reg();
  value += 1;
  cpu->setF_zero(!value);
  cpu->setF_negative(value & 0x80);
  cpu->setX_reg(value);
}

INYInstruction::INYInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[INYInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}

void INYInstruction::execute(Cpu *cpu, uint16_t address){
  uint8_t value = cpu->getY_reg();
  value += 1;
  cpu->setF_zero(!value);
  cpu->setF_negative(value & 0x80);
  cpu->setY_reg(value);
}

SBCInstruction::SBCInstruction(uint8_t addressingMode, uint8_t instructionSize)
    : BaseInstruction(addressingMode, instructionSize) {
  cout << "[SBCInstruction] - constructor(" << unsigned(instructionSize)
       << ") \n";
}

void SBCInstruction::execute(Cpu *cpu, uint16_t address){
  uint8_t value = cpu->read_mem(address);
  uint8_t a = cpu->getA_reg();
  unsigned const diff = a - value - (uint8_t)cpu->getF_carry();
  cpu->setF_carry(diff > 0xFF);
  cpu->setF_overflow((a ^ diff) & (~value ^ diff) & 0x80);
  cpu->setA_reg(diff);
  cpu->setF_zero(!diff);
  cpu->setF_negative(diff & 0x80);
}
