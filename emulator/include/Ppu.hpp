#pragma once

#ifndef Ppu_hpp
#define Ppu_hpp

#include "Rom.hpp"
#include <bitset>
#include <fstream>
#include <iostream>
#include <stdint.h>
#include <vector>
#include <bitset>

using namespace std;

class Ppu{
private:
	//PPU Registers
	bitset<8> Ppu_Ctrl;
	bitset<8> Ppu_Mask;
	bitset<8> Ppu_Status;
	uint8_t Oam_Addr;
	uint8_t Oam_Data;
	uint8_t Ppu_Scroll;
	uint8_t Ppu_Addr;
	uint8_t Ppu_Data;
	bool latch;

	Rom chr_Rom;
	
	uint8_t palleteRam[0x1F];

	int ppuClockCycles;

public:

	void startPpu();
	void reset();


	//Setters
	void setPpu_Ctrl(bitset<8> value);
	void setPpu_Mask(bitset<8> value);
	void setPpu_Status(bitset<8> value);
	void setOam_Addr(uint8_t value);
	void setOam_Data(uint8_t value);
	void setPpu_Scroll(uint8_t value);
	void setPpu_Addr(uint8_t value);	
	void setPpu_Data(uint8_t value);
	void setLatch(bool state); //indicates if it's possible to modify registers registers $2005/$200 - if NMI is setted


	//Getters
	bitset<8> getPpu_Ctrl();
	bitset<8> getPpu_Mask();
	bitset<8> getPpu_Status();	
	uint8_t getOam_Addr();
	uint8_t getOam_Data();
	uint8_t getPpu_Scroll();
	uint8_t getPpu_Addr();
	uint8_t getPpu_Data();
	bool getLatch();
};

#endif