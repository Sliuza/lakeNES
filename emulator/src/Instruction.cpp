#include "../include/Instruction.hpp"
#include "../include/AddressingMode.hpp"
#include "../include/Cpu.hpp"

BaseInstruction::BaseInstruction(uint8_t addressingMode,
                                 uint8_t instructionSize,
                                 uint8_t printMode) {

  this->_addressingMode = addressingMode;
  this->_instructionSize = instructionSize;
  this->_printMode = printMode;
  // //cout << "addressing mode = " << (unsigned)_addressingMode << " instructionSize = " << (unsigned)_instructionSize << endl;
}

uint8_t BaseInstruction::getAddressingMode() { return this->_addressingMode; };

uint8_t BaseInstruction::getInstructionSize() {
  return this->_instructionSize;
};

uint8_t BaseInstruction::getPrintMode() {
  return this->_printMode;
};

ADCInstruction::ADCInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}

void ADCInstruction::execute(Cpu *cpu, uint16_t address) {
  //TODO: Set Flags

  if (address >= 0x0000 && address <= 0xFFFF) {
    uint16_t carry = (cpu->getF_carry() ? 1 : 0);
    uint16_t value = cpu->read_mem(address);
    uint8_t a_regValue = cpu->getA_reg();
    uint16_t aux = (uint16_t)cpu->getA_reg() + value + carry;

    (aux > 255) ? cpu->setF_carry(true) : cpu->setF_carry(false);
    (aux & 0x00FF) == 0 ? cpu->setF_zero(true) : cpu->setF_zero(false);
    (aux & 0x80) ? cpu->setF_negative(true) : cpu->setF_negative(false);
    (~((uint16_t)a_regValue ^ (uint16_t)value) & ((uint16_t)a_regValue ^ (uint16_t)aux)) & 0x0080 ? cpu->setF_overflow(true) : cpu->setF_overflow(false);
    cpu->setA_reg(aux & 0x00FF);
  }
}

ANDInstruction::ANDInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}

void ANDInstruction::execute(Cpu *cpu, uint16_t address) {
  //cout << "[ANDInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    uint8_t value = cpu->read_mem(address);
    uint8_t a_regValue = cpu->getA_reg() & value;
    cpu->setA_reg(a_regValue);
    (a_regValue == 0) ? cpu->setF_zero(true) : cpu->setF_zero(false);
    (a_regValue & 0x80) ? cpu->setF_negative(true) : cpu->setF_negative(false);
  }
}

ASLInstruction::ASLInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}

void ASLInstruction::execute(Cpu *cpu, uint16_t address) {
  //cout << "[ASLInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    if (ASLInstruction::getAddressingMode() == ACCUMULATOR) {
      uint16_t a_regValue = cpu->getA_reg() << 1;
      (a_regValue & 0xFF00) > 0 ? cpu->setF_carry(true) : cpu->setF_carry(false);
      (a_regValue & 0x00FF) == 0 ? cpu->setF_zero(true) : cpu->setF_zero(false);
      (a_regValue & 0x80) ? cpu->setF_negative(true) : cpu->setF_negative(false);
      cpu->setA_reg(a_regValue & 0x00FF);
    } else {
      uint16_t value = cpu->read_mem(address) << 1;
      (value & 0xFF00) > 0 ? cpu->setF_carry(true) : cpu->setF_carry(false);
      (value & 0x00FF) == 0 ? cpu->setF_zero(true) : cpu->setF_zero(false);
      (value & 0x80) ? cpu->setF_negative(true) : cpu->setF_negative(false);
      cpu->write_mem(value & 0x00FF, address);
    }
  }
}

BCCInstruction::BCCInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}

void BCCInstruction::execute(Cpu *cpu, uint16_t address) {
  //cout << "[BCCInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    if (!cpu->getF_carry())
      cpu->setPc_reg(address);
  }
}

BCSInstruction::BCSInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}

void BCSInstruction::execute(Cpu *cpu, uint16_t address) {
  //cout << "[BCSInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    if (cpu->getF_carry())
      cpu->setPc_reg(address);
  }
}

BEQInstruction::BEQInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}

void BEQInstruction::execute(Cpu *cpu, uint16_t address) {
  //cout << "[BEQInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    if (cpu->getF_zero())
      cpu->setPc_reg(address);
  }
}

BITInstruction::BITInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}

void BITInstruction::execute(Cpu *cpu, uint16_t address) {
  //cout << "[BITInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    uint16_t value = cpu->read_mem(address);
    uint16_t aux = cpu->getA_reg() & value;

    (aux & 0x00FF) == 0 ? cpu->setF_zero(true) : cpu->setF_zero(false);
    (value & (1 << 7)) ? cpu->setF_negative(true) : cpu->setF_negative(false);
    (value & (1 << 6)) ? cpu->setF_overflow(true) : cpu->setF_overflow(false);
  }
}

BMIInstruction::BMIInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}

void BMIInstruction::execute(Cpu *cpu, uint16_t address) {
  //cout << "[BMIInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    if (cpu->getF_negative())
      cpu->setPc_reg(address);
  }
}

BNEInstruction::BNEInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}

void BNEInstruction::execute(Cpu *cpu, uint16_t address) {
  //cout << "[BNEInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    if (!cpu->getF_zero())
      cpu->setPc_reg(address);
  }
}

BPLInstruction::BPLInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}

void BPLInstruction::execute(Cpu *cpu, uint16_t address) {
  //cout << "[BPLInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    if (!cpu->getF_negative())
      cpu->setPc_reg(address);
  }
}

BRKInstruction::BRKInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}

void BRKInstruction::execute(Cpu *cpu, uint16_t address) {
  //TODO: Entender o BRK

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

BVCInstruction::BVCInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}

void BVCInstruction::execute(Cpu *cpu, uint16_t address) {
  //cout << "[BVCInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    if (!cpu->getF_overflow())
      cpu->setPc_reg(address);
  }
}

BVSInstruction::BVSInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}

void BVSInstruction::execute(Cpu *cpu, uint16_t address) {
  //cout << "[BVSInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    if (cpu->getF_overflow())
      cpu->setPc_reg(address);
  }
}

CLCInstruction::CLCInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}
void CLCInstruction::execute(Cpu *cpu, uint16_t address) {
  //cout << "[CLCInstruction] -  execute()\n";
  cpu->setF_carry(false);
}

CLDInstruction::CLDInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}
void CLDInstruction::execute(Cpu *cpu, uint16_t address) {
  //cout << "[CLDInstruction] -  execute()\n";
  cpu->setF_decimal(false);
}

CLIInstruction::CLIInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}
void CLIInstruction::execute(Cpu *cpu, uint16_t address) {
  //cout << "[CLIInstruction] -  execute()\n";
  cpu->setF_interrupt(false);
}

SEIInstruction::SEIInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}
void SEIInstruction::execute(Cpu *cpu, uint16_t address) {
  //cout << "[CLIInstruction] -  execute()\n";
  cpu->setF_interrupt(true);
}
SEDInstruction::SEDInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}
void SEDInstruction::execute(Cpu *cpu, uint16_t address) {
  //cout << "[CLIInstruction] -  execute()\n";
  cpu->setF_decimal(true);
}

CLVInstruction::CLVInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}
void CLVInstruction::execute(Cpu *cpu, uint16_t address) {
  //cout << "[CLVInstruction] -  execute()\n";
  cpu->setF_overflow(false);
}

CMPInstruction::CMPInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}
void CMPInstruction::execute(Cpu *cpu, uint16_t address) {
  //cout << "[CMPInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    uint8_t value = cpu->read_mem(address);
    uint8_t a_regValue = cpu->getA_reg();
    uint16_t aux = (uint16_t)a_regValue - (uint16_t)value;
    (aux & 0x00FF) == 0 ? cpu->setF_zero(true) : cpu->setF_zero(false);
    (aux & 0x80) ? cpu->setF_negative(true) : cpu->setF_negative(false);
    (a_regValue >= value) ? cpu->setF_carry(true) : cpu->setF_carry(false);
  }
}

CPXInstruction::CPXInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}

void CPXInstruction::execute(Cpu *cpu, uint16_t address) {
  //cout << "[CPXInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    uint8_t value = cpu->read_mem(address);
    uint8_t x_regValue = cpu->getX_reg();
    uint16_t aux = (uint16_t)x_regValue - (uint16_t)value;
    (aux & 0x00FF) == 0 ? cpu->setF_zero(true) : cpu->setF_zero(false);
    (aux & 0x80) ? cpu->setF_negative(true) : cpu->setF_negative(false);
    (x_regValue >= value) ? cpu->setF_carry(true) : cpu->setF_carry(false);
  }
}

CPYInstruction::CPYInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}

void CPYInstruction::execute(Cpu *cpu, uint16_t address) {
  //cout << "[CPYInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    uint8_t value = cpu->read_mem(address);
    uint8_t y_regValue = cpu->getY_reg();
    uint16_t aux = (uint16_t)y_regValue - (uint16_t)value;
    (aux & 0x00FF) == 0 ? cpu->setF_zero(true) : cpu->setF_zero(false);
    (aux & 0x80) ? cpu->setF_negative(true) : cpu->setF_negative(false);
    (y_regValue >= value) ? cpu->setF_carry(true) : cpu->setF_carry(false);
  }
}

EORInstruction::EORInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}
void EORInstruction::execute(Cpu *cpu, uint16_t address) {
  //cout << "[EORInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    uint8_t value = cpu->read_mem(address);
    uint8_t a_regValue = cpu->getA_reg();
    uint8_t aux = a_regValue ^ value;
    (aux & 0x00FF) == 0 ? cpu->setF_zero(true) : cpu->setF_zero(false);
    (aux & 0x80) ? cpu->setF_negative(true) : cpu->setF_negative(false);
    cpu->setA_reg(aux);
  }
}

JMPInstruction::JMPInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}
void JMPInstruction::execute(Cpu *cpu, uint16_t address) {
  //cout << "[JMPInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    // cout << "Address = 0x" << hex << (unsigned)address << endl;
    cpu->setPc_reg(address);
  }
}

JSRInstruction::JSRInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}

void JSRInstruction::execute(Cpu *cpu, uint16_t address) {
  //cout << "[JSRInstruction] -  execute()\n";
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

LSRInstruction::LSRInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}
void LSRInstruction::execute(Cpu *cpu, uint16_t address) {
  //cout << "[LSRInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    uint8_t value = cpu->read_mem(address);
    if (LSRInstruction::getAddressingMode() == ACCUMULATOR){ 
      value = cpu->getA_reg();
    }
    (value & 0x0001) ? cpu->setF_carry(true) : cpu->setF_carry(false);
  
    uint16_t aux = value >> 1;
    
    (aux & 0x00FF) == 0 ? cpu->setF_zero(true) : cpu->setF_zero(false);
    (aux & 0x0080) ? cpu->setF_negative(true) : cpu->setF_negative(false);
    if (LSRInstruction::getAddressingMode() == ACCUMULATOR) {
      cpu->setA_reg(aux & 0x00FF);
    } else {
      cpu->write_mem(address, aux & 0x00FF);
    }
  }
}

NOPInstruction::NOPInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}

void NOPInstruction::execute(Cpu *cpu, uint16_t address) {

  //cout << "[NOPInstruction]\n";
}

PLAInstruction::PLAInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}
void PLAInstruction::execute(Cpu *cpu, uint16_t address) {
  //cout << "[PLAInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    uint8_t stack = cpu->getSp_reg();
    stack++;
    cpu->setSp_reg(stack);

    uint8_t a_regValue = cpu->getA_reg();
    uint8_t aux = cpu->read_mem(0x0100 + stack);

    (aux & 0x00FF) == 0 ? cpu->setF_zero(true) : cpu->setF_zero(false);
    (aux & 0x80) ? cpu->setF_negative(true) : cpu->setF_negative(false);
    cpu->setA_reg(aux);
  }
}

PLPInstruction::PLPInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}
void PLPInstruction::execute(Cpu *cpu, uint16_t address) {
  //cout << "[PLPInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    uint8_t stack = cpu->getSp_reg();
    stack++;
    cpu->setSp_reg(stack);

    uint8_t a_regValue = cpu->getA_reg();
    uint8_t aux = cpu->read_mem(0x0100 + stack);
  }
}

PHAInstruction::PHAInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}

void PHAInstruction::execute(Cpu *cpu, uint16_t address) {
  //cout << "[PHAInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    uint8_t stack = cpu->getSp_reg();
    uint8_t a_regValue = cpu->getA_reg();
    cpu->write_mem(0x0100 + stack, a_regValue);
    stack--;
    cpu->setSp_reg(stack);
  }
}

PHPInstruction::PHPInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}
void PHPInstruction::execute(Cpu *cpu, uint16_t address) {
  //cout << "[PHPInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    uint8_t stack = cpu->getSp_reg();
    uint8_t status = cpu->getA_reg();
    cpu->write_mem(0x0100 + stack, status);
    stack--;
    cpu->setSp_reg(stack);
  }
}

RTIInstruction::RTIInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}
void RTIInstruction::execute(Cpu *cpu, uint16_t address) {
  //cout << "[RTIInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    uint8_t stack = cpu->getSp_reg();
    stack++;
    uint8_t status = cpu->read_mem(0x0100 + stack);

    stack++;
    uint16_t pc = (uint16_t)cpu->read_mem(0x0100 + stack);
    stack++;
    pc |= (uint16_t)cpu->read_mem(0x0100 + stack) << 8;

    cpu->setPc_reg(pc);
    cpu->setSp_reg(stack);
  }
}

RTSInstruction::RTSInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}
void RTSInstruction::execute(Cpu *cpu, uint16_t address) {
  //cout << "[RTSInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    uint8_t stack = cpu->getSp_reg();

    stack++;
    uint16_t pc = (uint16_t)cpu->read_mem(0x0100 + stack);
    stack++;
    pc |= (uint16_t)cpu->read_mem(0x0100 + stack) << 8;
    pc++;
    cpu->setPc_reg(pc);
    cpu->setSp_reg(stack);
  }
}

SECInstruction::SECInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}
void SECInstruction::execute(Cpu *cpu, uint16_t address) {
  //cout << "[SECInstruction] -  execute()\n";
  cpu->setF_carry(true);
}

ORAInstruction::ORAInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}
void ORAInstruction::execute(Cpu *cpu, uint16_t address) {
  //cout << "[ORAInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    uint8_t value = cpu->read_mem(address);
    uint8_t a_regValue = cpu->getA_reg();
    uint8_t aux = a_regValue | value;
    (aux & 0x00FF) == 0 ? cpu->setF_zero(true) : cpu->setF_zero(false);
    (aux & 0x80) ? cpu->setF_negative(true) : cpu->setF_negative(false);
    cpu->setA_reg(aux);
  }
}

LDAInstruction::LDAInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}

void LDAInstruction::execute(Cpu *cpu, uint16_t address) {
  //cout << "[LDAInstruction]\n";
  
  // cout << "LDAaddress = " << hex << (unsigned)address << endl;
  if (address >= 0x0000 && address <= 0xFFFF) {
    uint8_t value = cpu->read_mem(address);
    cpu->setA_reg(value);
    (value & 0x00FF) == 0 ? cpu->setF_zero(true) : cpu->setF_zero(false);
    (value & 0x80) ? cpu->setF_negative(true) : cpu->setF_negative(false);
    // //cout << "a = " << hex << (unsigned)(uint8_t)cpu->getA_reg() << "\n";
  }
}

STAInstruction::STAInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}

void STAInstruction::execute(Cpu *cpu, uint16_t address) {
  //cout << "[STAInstruction] -  execute()\n";
  // cout << "STAaddress = " << hex << (unsigned)address << endl;
  cpu->write_mem(cpu->getA_reg(), address);
}

STXInstruction::STXInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}

void STXInstruction::execute(Cpu *cpu, uint16_t address) {
  //cout << "[STXInstruction] -  execute()\n";
  cpu->write_mem(cpu->getX_reg(), address);
}

STYInstruction::STYInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}

void STYInstruction::execute(Cpu *cpu, uint16_t address) {
  //cout << "[STYInstruction] -  execute()\n";
  cpu->write_mem(cpu->getY_reg(), address);
}

LDXInstruction::LDXInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}

void LDXInstruction::execute(Cpu *cpu, uint16_t address) {
  //cout << "[LDXInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    uint8_t value = cpu->read_mem(address);
    cpu->setX_reg(value);
    (value & 0x00FF) == 0 ? cpu->setF_zero(true) : cpu->setF_zero(false);
    (value & 0x80) ? cpu->setF_negative(true) : cpu->setF_negative(false);
  }
}

LDYInstruction::LDYInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}

void LDYInstruction::execute(Cpu *cpu, uint16_t address) {
  //cout << "[LDYInstruction] -  execute()\n";
  if (address >= 0x0000 && address <= 0xFFFF) {
    uint8_t value = cpu->read_mem(address);
    cpu->setY_reg(value);
    (value & 0x00FF) == 0 ? cpu->setF_zero(true) : cpu->setF_zero(false);
    (value & 0x80) ? cpu->setF_negative(true) : cpu->setF_negative(false);
  }
}
DECInstruction::DECInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}

void DECInstruction::execute(Cpu *cpu, uint16_t address) {
  uint8_t value = cpu->read_mem(address);
  value -= 1;
  cpu->setF_zero(!value);
  cpu->setF_negative(value & 0x80);
  cpu->write_mem(value, address);
}

DEXInstruction::DEXInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}

void DEXInstruction::execute(Cpu *cpu, uint16_t address) {
  uint8_t value = cpu->getX_reg();
  value -= 1;
  cpu->setF_zero(!value);
  cpu->setF_negative(value & 0x80);
  cpu->setX_reg(value);
}

DEYInstruction::DEYInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}

void DEYInstruction::execute(Cpu *cpu, uint16_t address) {
  uint8_t value = cpu->getY_reg();
  value -= 1;
  cpu->setF_zero(!value);
  cpu->setF_negative(value & 0x80);
  cpu->setY_reg(value);
}

INCInstruction::INCInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}

void INCInstruction::execute(Cpu *cpu, uint16_t address) {
  uint8_t value = cpu->read_mem(address);
  value += 1;
  cpu->setF_zero(!value);
  cpu->setF_negative(value & 0x80);
  cpu->write_mem(value, address);
}

INXInstruction::INXInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}

void INXInstruction::execute(Cpu *cpu, uint16_t address) {
  uint8_t value = cpu->getX_reg();
  value += 1;
  cpu->setF_zero(!value);
  cpu->setF_negative(value & 0x80);
  cpu->setX_reg(value);
}

INYInstruction::INYInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}

void INYInstruction::execute(Cpu *cpu, uint16_t address) {
  uint8_t value = cpu->getY_reg();
  value += 1;
  cpu->setF_zero(!value);
  cpu->setF_negative(value & 0x80);
  cpu->setY_reg(value);
}

SBCInstruction::SBCInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}

void SBCInstruction::execute(Cpu *cpu, uint16_t address) {
  uint8_t value = cpu->read_mem(address);
  uint8_t aux = value ^ 0x00FF;
  uint8_t a = cpu->getA_reg();
  uint16_t diff = a + aux +(uint8_t)cpu->getF_carry();
  (diff & 0xFF00) ? cpu->setF_carry(true) : cpu->setF_carry(false);
  (diff & 0x00FF) == 0 ? cpu->setF_zero(true) : cpu->setF_zero(false);
  (diff & 0x80) ? cpu->setF_negative(true) : cpu->setF_negative(false);
  (((uint16_t)diff ^ (uint16_t)a) & ((uint16_t)diff ^ (uint16_t)aux) & 0x0080) ? cpu->setF_overflow(true) : cpu->setF_overflow(false);
  cpu->setA_reg(diff & 0x00FF);
}

TAXInstruction::TAXInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}

void TAXInstruction::execute(Cpu *cpu, uint16_t address) {
  uint8_t value = cpu->getA_reg();
  cpu->setX_reg(value);
  cpu->setF_zero(!value);
  cpu->setF_negative(value & 0x80);
}

TAYInstruction::TAYInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}

void TAYInstruction::execute(Cpu *cpu, uint16_t address) {
  uint8_t value = cpu->getA_reg();
  cpu->setY_reg(value);
  cpu->setF_zero(!value);
  cpu->setF_negative(value & 0x80);
}

TSXInstruction::TSXInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}

void TSXInstruction::execute(Cpu *cpu, uint16_t address) {
  uint8_t value = cpu->getSp_reg();
  cpu->setX_reg(value);
  cpu->setF_zero(!value);
  cpu->setF_negative(value & 0x80);
}

TXAInstruction::TXAInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}

void TXAInstruction::execute(Cpu *cpu, uint16_t address) {
  uint8_t value = cpu->getX_reg();
  cpu->setA_reg(value);
  cpu->setF_zero(!value);
  cpu->setF_negative(value & 0x80);
}

TXSInstruction::TXSInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}

void TXSInstruction::execute(Cpu *cpu, uint16_t address) {
  uint8_t value = cpu->getX_reg();
  cpu->setSp_reg(value);
  cpu->setF_zero(!value);
  cpu->setF_negative(value & 0x80);
}

TYAInstruction::TYAInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}

void TYAInstruction::execute(Cpu *cpu, uint16_t address) {
  uint8_t value = cpu->getY_reg();
  cpu->setA_reg(value);
  cpu->setF_zero(!value);
  cpu->setF_negative(value & 0x80);
}

RORInstruction::RORInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}

void RORInstruction::execute(Cpu *cpu, uint16_t address) {
  uint8_t aux;
  uint8_t op;
  if (address >= 0x0000 && address <= 0xFFFF) {
    uint8_t value = cpu->read_mem(address);
    if (RORInstruction::getAddressingMode() == ACCUMULATOR){ 
      value = cpu->getA_reg();
    }
   
    uint16_t aux = (uint16_t) (cpu->getF_carry() << 7) | value >> 1;
    (value & 0x0001) ? cpu->setF_carry(true) : cpu->setF_carry(false);
    (aux & 0x00FF) == 0 ? cpu->setF_zero(true) : cpu->setF_zero(false);
    (aux & 0x0080) ? cpu->setF_negative(true) : cpu->setF_negative(false);
    if (RORInstruction::getAddressingMode() == ACCUMULATOR) {
      cpu->setA_reg(aux & 0x00FF);
    } else {
      cpu->write_mem(address, aux & 0x00FF);
    }
  }
}

ROLInstruction::ROLInstruction(uint8_t addressingMode, uint8_t instructionSize, uint8_t printMode)
    : BaseInstruction(addressingMode, instructionSize, printMode) {
}

void ROLInstruction::execute(Cpu *cpu, uint16_t address) {
  if (address >= 0x0000 && address <= 0xFFFF) {
    uint8_t value = cpu->read_mem(address);
    if (ROLInstruction::getAddressingMode() == ACCUMULATOR){ 
      value = cpu->getA_reg();
    }
   
    uint16_t aux = (uint16_t)value << 1 | cpu->getF_carry();
    (aux & 0xFF00) ? cpu->setF_carry(true) : cpu->setF_carry(false);
    (aux & 0x00FF) == 0 ? cpu->setF_zero(true) : cpu->setF_zero(false);
    (aux & 0x0080) ? cpu->setF_negative(true) : cpu->setF_negative(false);
    if (ROLInstruction::getAddressingMode() == ACCUMULATOR) {
      cpu->setA_reg(aux & 0x00FF);
    } else {
      cpu->write_mem(address, aux & 0x00FF);
    }
  }
}
