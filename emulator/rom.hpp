#pragma once

#include <iostream>
#include <stdint.h>
#include <bitset>
#include <vector>
#include <fstream>
using namespace std;

class ROM{
    private:
        unsigned int memory_start_location = 0x8000;
        int memory_end_location = 0xFFFF;
        int header_size = 0x10;
        int num_prg_blocks;
        bool hasROM = false;
        std::vector<uint8_t> rom_bytes;

    public:
        ROM(){
        }
        ROM(std::vector<uint8_t> rom_bytes){
            this-> rom_bytes = rom_bytes;
        }
        std::vector<uint8_t> getROM(){
            return this->rom_bytes;
        }
    
};