#pragma once

#ifndef Screen_hpp
#define Screen_hpp
#include <SDL2/SDL.h>
#include <stdlib.h> 
#include <stdio.h>

using namespace std;

class Screen
{
public:
	void startDisplay();
	void sendToDisplay();
	void endDisplay();
	void drawPixel();
};

#endif