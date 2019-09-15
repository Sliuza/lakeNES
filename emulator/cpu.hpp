#pragma once

#include <iostream>
#include <stdint.h>
#include <bitset>
#include <vector>
#include <fstream>
#include "rom.hpp"
using namespace std;


class CPU{
	private:
		// counter registers: store a single byte
		uint16_t pc_reg = 0;  // program counter, 2 byte
		uint8_t sp_reg = 0;  // stack pointer

		// data registers: store a single byte
		uint8_t x_reg = 0; // x register
		uint8_t y_reg = 0;  // y register
		uint8_t a_reg = 0;  // a register
		ROM rom;
	public:
		CPU(){
			this->pc_reg = 0;
			this->sp_reg = 0xFD;
			this->x_reg = 0;
			this->y_reg = 0;
			this->a_reg = 0;
		}
		// TODO: get prgblocks from rom_bytes
        int getNumberOfPrgBlocks(vector<unsigned int> rom_bytes){
            return 2;
        }

        void loadROM(string path){
            std::ifstream input(path, std::ios::binary);
            int counter = 0;
            int byteCounter = 0xc000;
            uint8_t a;
	        std::vector<uint8_t> bytes(65536);

            while(!input.eof()){
				input >> a;
                if(counter>16){
                    bytes.insert(bytes.begin()+ byteCounter, (uint8_t)(a));
                    byteCounter += 1;
                }
                counter +=1;
            }
			this->rom = ROM(bytes);
        }
		void printROM(){
			vector<uint8_t> r = rom.getROM();
			for(int i= 0xc000; i< r.size();i++){
				cout <<std::hex<< (unsigned)(uint8_t)r.at(i);
			}
		}
};