#include "../include/Nes.hpp"
const int TOTAL_CYCLES = 29781;

Nes::Nes(string pathToRom) {
  this->cpu = Cpu();
  this->ppu = Ppu();
  this->pathToRom = pathToRom;
}

void Nes::load() {
  cpu.loadROM(this->pathToRom);
  ppu.setChr_Rom(this->cpu.getRom().getChr());
  ppu.writeTblPattern();
  cpu.setPpu(&ppu);
  ppu.setCpu(&cpu);
  ppu.set_nmi_callback([&](){ cpu.nmi_interruption(); });
  cpu.startCpu();
  ppu.startPpu();
}

void Nes::run() {

  while (!cpu.getFoundBrk()) {
    for (int i = 0; i < TOTAL_CYCLES && !cpu.getFoundBrk(); i++) {
      this->runCycle();
      //printf("999999999999\n");
    }
      ppu.renderize();
      cpu.nmi_interruption();
    //TODO: Integrate with the ppu.renderize();
  };
  ppu.endPpu();
};

void Nes::runCycle() {
  cpu.runCycle();
}
