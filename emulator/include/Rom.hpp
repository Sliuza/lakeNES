#pragma once

#ifndef Rom_hpp
#define Rom_hpp

#include <iostream>
#include <list>
#include <stdio.h>
#include <string>

using namespace std;

class Rom {
private:
  int num_prg_banks;
  int num_chr_banks;
  uint8_t *prg_rom;
  uint8_t *chr_rom;
  uint8_t mapper_number;
public:
  Rom();
  void load(string path);
  uint8_t * getPgr();
  uint8_t readPgr(uint16_t adress);
  uint8_t * getChr();
};

#endif
