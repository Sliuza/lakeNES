#pragma once

#ifndef Screen_hpp
#define Screen_hpp
#include <SDL2/SDL.h>
#include <stdlib.h> 
#include <stdio.h>
#include <bitset>
#include <fstream>
#include <iostream>
#include <stdint.h>
#include <bitset>
#include <cstdint>


using namespace std;

class Screen
{

private:
	int counter1 = 0;
	int counter2 = 0;
	
public:
	SDL_Window* window;
	SDL_Surface* surface;

	void createWindow();
	void startDisplay();
	// void sendToDisplay();
	//cabecalho da funcao do sendToDisplay com Parametros
	void sendToDisplay(uint8_t tblPattern[2][4096], uint8_t tblName[2][1024], uint8_t oam_table[64][4], uint8_t tblPallete[32]);
	void endDisplay();
	void drawPixel();
	bool openWindow();
	uint8_t readControl1();
	uint8_t readControl2();
	int palleteToHex[64] = {
0x7C7C7C,
0x0000FC,
0x0000BC,
0x4428BC,
0x940084,
0xA80020,
0xA81000,
0x881400,
0x503000,
0x007800,
0x006800,
0x005800,
0x004058,
0x000000,
0x000000,
0x000000,
0xBCBCBC,
0x0078F8,
0x0058F8,
0x6844FC,
0xD800CC,
0xE40058,
0xF83800,
0xE45C10,
0xAC7C00,
0x00B800,
0x00A800,
0x00A844,
0x008888,
0x000001,
0x000000,
0x000000,
0xF8F8F8,
0x3CBCFC,
0x6888FC,
0x9878F8,
0xF878F8,
0xF85898,
0xF87858,
0xFCA044,
0xF8B800,
0xB8F818,
0x58D854,
0x58F898,
0x00E8D8,
0x787878,
0x000000,
0x000000,
0xFCFCFC,
0xA4E4FC,
0xB8B8F8,
0xD8B8F8,
0xF8B8F8,
0xF8A4C0,
0xF0D0B0,
0xFCE0A8,
0xF8D878,
0xD8F878,
0xB8F8B8,
0xB8F8D8,
0x00FCFC,
0xF8D8F8,
0x000000,
0x000000};
};
	


#endif