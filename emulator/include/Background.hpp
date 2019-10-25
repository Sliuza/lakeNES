#pragma once

#ifndef Background_hpp
#define Background_hpp

#include "Rom.hpp"
#include <fstream>
#include <iostream>
#include <stdint.h>
#include <vector>
#include <bitset>

using namespace std;


class Background{
private:
	uint16_t shift1;
	uint16_t shift2;
	uint8_t palleteShift1;
	uint8_t palleteShift2;
	bitset<15> VRam;


public:
	void setShift1(uint16_t tile);
	void setShift2(uint16_t tile);
	void setPalleteShift1(uint8_t attribute);
	void setPalleteShift2(uint8_t attribute);
	void setVRam(bitset<15> ram);

	uint16_t getShift1();
	uint16_t getShift2();
	uint8_t getPalleteShift1();
	uint8_t getPalleteShift2();
	bitset<15> getVRam();
};

#endif