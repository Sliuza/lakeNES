#include "../include/Nes.hpp"
#include <bitset>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <stdint.h>
#include <vector>
using namespace std;

void print(uint8_t a, uint8_t x, uint8_t y, uint16_t sp, uint16_t pc,
           uint8_t p) {
  cout << setfill('0') << "| pc = 0x" << hex << setw(4) << pc << " | a = 0x"
       << hex << setw(2) << (unsigned)a << " | x = 0x" << hex << setw(2)
       << (unsigned)x << " | y = 0x" << hex << setw(2) << (unsigned)y
       << " | sp = 0x" << hex << setw(4) << sp
       << " | p[NV-BDIZC] = " << bitset<8>(p) << " |" << endl;
}

void printls(uint8_t a, uint8_t x, uint8_t y, uint16_t sp, uint16_t pc,
             uint8_t p, uint16_t addr, uint8_t data) {
  cout << setfill('0') << "| pc = 0x" << hex << setw(4) << pc << " | a = 0x"
       << hex << setw(2) << (unsigned)a << " | x = 0x" << hex << setw(2)
       << (unsigned)x << " | y = 0x" << hex << setw(2) << (unsigned)y
       << " | sp = 0x" << hex << setw(4) << sp
       << " | p[NV-BDIZC] = " << bitset<8>(p) << " | MEM[0x" << hex << setw(4)
       << addr << "] = 0x" << hex << setw(2) << (unsigned)data << " |" << endl;
}

int main(int argc, const char *argv[]) {
  // if (argc == 2) {
  //   cout << "Starting rom " << argv[1] << endl;
  // } else if (argc < 2) {
  //   cout << "Please choose the rom" << endl;
  //   exit(1);
  // } else {
  //   cout << "Too many arguments" << endl;
  //   exit(1);
  // }
  string pathToROM = argv[1];
  Nes nes(pathToROM);
  nes.load();

  	// print(0xFF, 0xEE, 0xDD, 0xCCCC, 0xBBBB, 0xAA);
    // printls(0xFF, 0xEE, 0xDD, 0xCCCC, 0xBBBB, 0xAA, 0xFFFF, 0x99);
    
  return 0;
}
