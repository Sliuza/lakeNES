#include "../include/Cpu.hpp"
#include "../include/Instruction.hpp"

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

  // TODO : Create a Instruction Factory responsible for create the
  // instance according to the instruction pointed by PC.
  instruction = new LDAInstruction(1, 3);

  instruction->execute(this, 0x123);
  // for (int i = 0xc000; i < r.size(); i++) {
  //   cout << std::hex << (unsigned)(uint8_t)r.at(i);
  // }

  this->pc_reg += instruction->getInstructionSize();

  cout << "[PC]: " << this->pc_reg << "\n";
}
