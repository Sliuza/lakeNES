#include "../include/Apu.hpp"

// Apu::Apu(){

// }


void Apu::runApuCycle(){
	cout << "apu cycle\n";
}


void Apu::Pulse1::characteristics(uint8_t val){
	cout << "val = " << hex << val << endl;
	cout << "Duty,loop envelope/disable length counter,constant volume,envelop period/volume\n";
}

void Apu::Pulse1::sweep(){
	cout << "Sweep unit: enabled, period, negative, shift count\n";
}

void Apu::Pulse1::timer(){
	cout << "Timer low\n";
}

void Apu::Pulse1::lenghtCounter(){
	cout << "length counter load,timer high also resets duty and starts envelope\n";
}