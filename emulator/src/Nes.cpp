#include "../include/Nes.hpp"

const int TOTAL_CYCLES = 29781;

Nes::Nes(string pathToRom) {
  this->cpu = Cpu();
  this->ppu = Ppu();
  this->pathToRom = pathToRom;
}

void Nes::load() {
  cpu.loadROM(this->pathToRom);
  cpu.startCpu();
  // cpu.printROM();
}

void Nes::run() {

  while (!cpu.getFoundBrk()) {
    for (int i = 0; i < TOTAL_CYCLES && !cpu.getFoundBrk(); i++) {
      this->runCycle();
    }
    //TODO: Integrate with the ppu.renderize();
  };
};

void Nes::runCycle() {
  cpu.runCycle();
  //TODO: Integrate with the ppu.runCycle();
  // ppu.runCycle();
  // ppu.runCycle();
  // ppu.runCycle();
}
