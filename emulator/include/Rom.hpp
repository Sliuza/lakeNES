#pragma once

#ifndef Rom_hpp
#define Rom_hpp

#include <iostream>
#include <list>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class Rom {
private:
  int num_prg_banks;
  int num_chr_banks;
  std::vector<uint8_t> prg_rom;
  std::vector<uint8_t> chr_rom;
  uint8_t mapper_number;
public:
  Rom();
  void load(string path);
  vector<uint8_t> getPgr();
  vector<uint8_t> getChr();
};

#endif
