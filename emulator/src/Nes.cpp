#include "../include/Nes.hpp"

Nes::Nes(string pathToRom) {
  this->cpu = Cpu();
  this->pathToRom = pathToRom;
}

void Nes::load() {
  cpu.loadROM(this->pathToRom);
  cpu.printROM();
}
