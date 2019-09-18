#ifndef Nes_hpp
#define Nes_hpp

#include "Cpu.hpp"

using namespace std;
class Nes {
  Cpu cpu;
  string pathToRom;

public:
  Nes(string pathToRom);
  void load();
  // void run(){
  //     while(1){
  //         // cpu.executeNextInstruction();
  //     }
  // }
};

#endif
