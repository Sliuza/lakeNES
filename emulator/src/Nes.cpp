#include "../include/Nes.hpp"

Nes::Nes(string pathToRom) {
  this->cpu = Cpu();
  this->ppu = Ppu();
  this->pathToRom = pathToRom;
}

void Nes::load() {
  cpu.loadROM(this->pathToRom);
  // cpu.printROM();
}

void Nes::run() {

  while (!cpu.getFoundBrk()) {
    cpu.run_frame();

    //TODO: Integrate with the ppu.renderize() method;
  };
};
