#include "../include/Nes.hpp"
#include <bitset>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdint.h>
#include <vector>
using namespace std;

int main(int argc, const char *argv[]) {
  string pathToROM = argv[1];
  Nes nes(pathToROM);
  nes.load();
  nes.run();
  return 0;
}
