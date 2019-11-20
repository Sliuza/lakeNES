#include "../include/Nes.hpp"
const int TOTAL_CYCLES = 29781;
#include <ctime>
#include <set>


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
  std::clock_t start;
  double duration;

  while (!cpu.getFoundBrk()) {
    start = std::clock();  
    for (int i = 0; i < TOTAL_CYCLES && !cpu.getFoundBrk(); i++) {
      this->runCycle();
    }
    ppu.renderize();
    cpu.nmi_interruption();
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    std::cout<<"frame/s: "<< 1/duration <<'\n';
    cout << "avr instruction time:" << cpu.avr_time_instruction << endl;
    //TODO: Integrate with the ppu.renderize();
  };
  ppu.endPpu();
};

void Nes::runCycle() {
  cpu.runCycle();
}
