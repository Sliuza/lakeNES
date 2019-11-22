#pragma once

#ifndef Apu_hpp
#define Apu_hpp

#include <stdio.h>
#include <iostream>


using namespace std;

class Apu{

public:
	void apuCycle();
	int globalCounter = 0;
	
	class Pulse{

	public:
		uint8_t duty;
		uint8_t seq[4][8] =	{
								{ 0, 1, 0, 0, 0, 0, 0, 0 }, // 12.5%
								{ 0, 1, 1, 0, 0, 0, 0, 0 }, // 25%
								{ 0, 1, 1, 1, 1, 0, 0, 0 }, // 50%
								{ 1, 0, 0, 1, 1, 1, 1, 1 }
							};// 25% negated

		uint8_t lenghtCounterHalt;
		uint8_t constVolume;
		uint8_t bitVolume;
		uint8_t wave[8];
		uint8_t lowTimer;
		uint8_t highTimer;
		uint8_t length;
		uint16_t currentTimer;
		uint16_t timer = 0;
		uint8_t enabled; // Flag indicating if sweep is enabled
		uint8_t period; // The divider's period is P + 1 half-frames 
		uint8_t negateFlag; // Indicates if the change amount is negative
		uint8_t shiftCount; //number of bits to be shifted (??)
		bool down = true;

		void characteristics(uint8_t val,Pulse *pulse);
		void sweep(uint8_t val,Pulse *pulse);
		void timerLow(uint8_t val,Pulse *pulse);
		void lengthCounter(uint8_t val,Pulse *pulse);
		void setTimer(Pulse *pulse);
		uint8_t sequencer(Pulse *pulse);
		void mixer();
	
		
	};

	class Triangle{

	public:
		uint8_t control;
		uint8_t loadCounter;
		uint8_t length;
		uint8_t lowTimer;
		uint8_t highTimer;
		uint16_t timer;


		void characteristics(uint8_t val,Triangle *triangle);
		void timerLow(uint8_t val,Triangle *triangle);
		void lengthCounter(uint8_t val,Triangle *triangle);
		void setTimer(Triangle *triangle);
	};


	Pulse pulse1;
	Pulse pulse2;
	Triangle triangle;
};

#endif
