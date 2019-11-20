#ifndef Nes_hpp
#define Nes_hpp

#include "Cpu.hpp"
#include "Ppu.hpp"

using namespace std;
class Nes {
  Cpu cpu;
  Ppu ppu;
  Apu apu;
  string pathToRom;

  public:
  Nes(string pathToRom);
  void load();
  void run();
  void runCycle();
};

#endif
