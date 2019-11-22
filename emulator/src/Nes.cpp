#include "../include/Nes.hpp"
const int TOTAL_CYCLES = 29681;
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
  ppu.set_nmi_callback([&]() { cpu.nmi_interruption(); });
  cpu.startCpu();
  ppu.startPpu();
}

void Nes::run() {
  std::clock_t start;
  double duration;

  uint32_t frameStart, frameTime;
  const int FPS = 60;
  const int DELAY = 1000.0f / FPS;

  while (!cpu.getFoundBrk()) {
    start = std::clock();

    frameStart = SDL_GetTicks();
    for (int i = 0; i < TOTAL_CYCLES && !cpu.getFoundBrk(); i++) {
      this->runCycle();
    }
    ppu.renderize();
    cpu.nmi_interruption();

    frameTime = SDL_GetTicks() - frameStart;
    if (frameTime < DELAY) {
      SDL_Delay((int)(DELAY - frameTime));
    }

    duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
    // std::cout << "frame/s: " << 1 / duration << '\n';
    // cout << "avr instruction time:" << cpu.avr_time_instruction << endl;
    //TODO: Integrate with the ppu.renderize();
  };
  ppu.endPpu();
};

void Nes::runCycle() {
  cpu.runCycle();
}
