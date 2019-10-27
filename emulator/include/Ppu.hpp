#pragma once

#ifndef Ppu_hpp
#define Ppu_hpp

#include "Rom.hpp"
#include "Screen.hpp"
#include <bitset>
#include <fstream>
#include <iostream>
#include <stdint.h>
#include <vector>
#include <bitset>
#include <cstdint>

using namespace std;

class Ppu{
private:
	//PPU Registers

	uint8_t Ppu_Scroll;
	uint8_t Ppu_Addr;
	uint8_t Ppu_Data;
	bool latch;
	bool generateInterrupt;
	bool master_slave;
	bool sprite_size;
	bool background_pattern;
	bool sprite_pattern;
	bool vram_increment;
	bool grey_scale_mode;
	bool background_left_most;
	bool sprites_left_most;
	bool show_background;
	bool show_sprites;
    bool vblank;
    bool sprite_zero_hit;
    std::vector<int8_t> oam_data;
    bool first_write;
    uint16_t oam_address;
    uint16_t ppu_address;
	enum state
	{
		pre_render,
		render,
		post_render,
		vertical_blank
	} pipeline_state;

	u_int16_t base_nametable_address;


	Rom chr_Rom;
	
	uint8_t palleteRam[0x1F];

	int ppuClockCycles;

public:

	void startPpu();
	void reset();
	void step();
    void mask(bitset<8> ctrl);
	void control(bitset<8> ctrl);
	void endPpu();
    void write_mem(uint8_t val, uint16_t addr);
    void setPpuAddress(uint8_t addr);

	//Setters
	void setPpu_Ctrl(bitset<8> value);
	void setPpu_Mask(bitset<8> value);
	void setPpu_Status(bitset<8> value);
	void setOam_Addr(uint8_t value);
	void setOam_Data(uint8_t address, uint8_t value);
	void setPpu_Scroll(uint8_t value);
	void setPpu_Addr(uint8_t value);	
	void setPpu_Data(uint8_t value);
	void setLatch(bool state); //indicates if it's possible to modify registers registers $2005/$200 - if NMI is setted
    void setOAM_Address(uint8_t addr);

	//Getters
	bitset<8> getPpu_Ctrl();
	bitset<8> getPpu_Mask();
	bitset<8> getPpu_Status();	
	uint8_t getOam_Addr();
	uint8_t getOam_Data(uint8_t addr);
	uint8_t getPpu_Scroll();
	uint8_t getPpu_Addr();
	uint8_t getPpu_Data();
    uint8_t get_status();
	bool getLatch();
    

	
};

#endif
