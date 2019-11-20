#pragma once

#ifndef Apu_hpp
#define Apu_hpp

#include <stdio.h>
#include <iostream>


using namespace std;

class Apu{

public:
	void runApuCycle();
	class Pulse1{
	public:
		void characteristics(uint8_t val);
		void sweep();
		void timer();
		void lenghtCounter();

		uint8_t duty;
		uint8_t seq[4][8] =	{
								{ 0, 1, 0, 0, 0, 0, 0, 0 }, // 12.5%
								{ 0, 1, 1, 0, 0, 0, 0, 0 }, // 25%
								{ 0, 1, 1, 1, 1, 0, 0, 0 }, // 50%
								{ 1, 0, 0, 1, 1, 1, 1, 1 }
							};// 25% negated

	};


	Pulse1 pulse;
};

#endif