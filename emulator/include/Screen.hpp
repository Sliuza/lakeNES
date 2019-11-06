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
#include <vector>
#include <bitset>
#include <cstdint>


using namespace std;

class Screen
{
public:
	SDL_Window* window;
	SDL_Surface* surface;

	void createWindow();
	void startDisplay();
	// void sendToDisplay();
	//cabecalho da funcao do sendToDisplay com Parametros
	void sendToDisplay(uint8_t tblPattern[2][4096], uint8_t tblName[2][1024], uint8_t oam_table[64][4]);
	void endDisplay();
	void drawPixel();
	bool openWindow();
};

#endif