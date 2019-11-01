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
#include <functional>

#include <bitset>
#include <cstdint>


using namespace std;

class Ppu{
private:
	//PPU Registers
    std::function<void(void)> nmi_interruption;
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
    bool even_frame;
    int scan_line;
    uint8_t fine_x_scrool;
    std::vector<int8_t> scan_lineSprites;
    std::vector<int8_t> oam_data;
    Screen screen;
    //aloca memoria para a PatternTabel e NameTable
    uint8_t tblName[2][1024];
	uint8_t tblPattern[2][4096];
    int ppu_cycle;
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


	vector<uint8_t> chr_Rom;
	
	uint8_t palleteRam[0x1F];

	int ppuClockCycles;

public:
	void startPpu();
	void reset();
	void renderize();
    void mask(bitset<8> ctrl);
	void control(bitset<8> ctrl);
	void endPpu();
    void write_mem(uint8_t val, uint16_t addr);
    void setPpuAddress(uint8_t addr);
    void cpu_nmi_interrupt();
    void set_nmi_callback(std::function<void(void)> cb);
    void step();
    //read and write tblPattern e tblName
    uint8_t ppuRead(uint16_t addr);
    void ppuWrite(uint8_t data, uint16_t addr);

    void setChr_Rom(vector<uint8_t> chr);
    void writeTblPattern();

	//Setters
	void setPpu_Ctrl(bitset<8> value);
	void setPpu_Mask(bitset<8> value);
	void setPpu_Status(bitset<8> value);
	void setOam_Addr(uint8_t value);
	void setOam_Data(uint8_t address, uint8_t value);
	void setPpu_Data(uint8_t value);
	void scrool(uint8_t value);
	void setLatch(bool state); //indicates if it's possible to modify registers registers $2005/$200 - if NMI is setted
    void setOAM_Address(uint8_t addr);
    void setOAMDMA(uint8_t value);
    void setFirstWrite(bool b);

	//Getters
	bitset<8> getPpu_Ctrl();
	bitset<8> getPpu_Mask();
	bitset<8> getPpu_Status();	
	uint8_t getOam_Addr();
	uint8_t getOam_Data(uint16_t addr);
	uint8_t getPpu_Data();
    uint8_t get_status();
    bool getShowBackground();
	bool getLatch();
    u_int8_t read_mem(uint16_t addr);
};

#endif
