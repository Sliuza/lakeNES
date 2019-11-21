#include "../include/Apu.hpp"
#include<bitset>

void Apu::runApuCycle(){
	cout << "apu cycle\n";
}


void Apu::Pulse::characteristics(uint8_t val,Pulse *pulse){
	int i;


	//holds the value of wave duty
	pulse->duty = (val & 0b11000000) >> 6;

	//holds the bits representing wave width

	for(i = 0;i < 8;i++)
		pulse->wave[i] = seq[duty][i];

	pulse->lenghtCounterHalt = (val & 0b00100000) >> 5;
	pulse->constVolume = (val & 0b00010000) >> 4;
	pulse->bitVolume = (val & 0b00001111);
	// cout << "value = " << bitset<8>(val) 
	// << "\nduty = " << bitset<2>(duty)
	// << "\nlengthCounterHalt = " << bitset<1>(lenghtCounterHalt)
	// << "\nconstVolume = " << bitset<1>(constVolume)
	// << "\nbitVolume = " << bitset<4>(bitVolume) << endl;

}

void Apu::Pulse::sweep(uint8_t val,Pulse *pulse){ // we don't use it on our game
	

	pulse->enabled = (val & 0b10000000) << 7;
	pulse->period = (val & 0b01110000) << 4;
	pulse->negateFlag = (val & 0b00001000) << 3;
	pulse->shiftCount = (val & 0b00000011);

	// cout << "value = " << bitset<8>(val) 
	// << "\enabled = " << bitset<1>(enabled)
	// << "\nperiod = " << bitset<3>(period)
	// << "\nnegateFlag = " << bitset<1>(negateFlag)
	// << "\nshiftCount = " << bitset<3>(shiftCount) << endl;

	// cout << "Sweep unit: enabled, period, negative, shift count\n";
}

void Apu::Pulse::timerLow(uint8_t val,Pulse *pulse){
	pulse->lowTimer = val;
}

void Apu::Pulse::lengthCounter(uint8_t val,Pulse *pulse){
	pulse->length = (val & 0b11111000) >> 3;
	pulse->highTimer = (val & 0b00000111);
	pulse->setTimer(pulse);
}


void Apu::Pulse::setTimer(Pulse *pulse){

	pulse->timer = (pulse->highTimer << 8 | pulse->lowTimer);

	cout << "highTimer = " << bitset<8>(pulse->highTimer)
	<< "\nlowTimer = " << bitset<8>(pulse->lowTimer)
	<< "\ntimer = " << bitset<16>(pulse->timer) << endl; 
}


void Apu::Triangle::characteristics(uint8_t val,Triangle *triangle){
	triangle->control = (val & 0b10000000);
	triangle->loadCounter = (val & 0b01111111);

	cout << "value = " << bitset<8>(val) 
	<< "\ncontrol = " << bitset<1>(triangle->control)
	<< "\nloadCounter = " << bitset<7>(triangle->loadCounter) << endl;
}

void Apu::Triangle::timerLow(uint8_t val,Triangle *triangle){
	triangle->lowTimer = val;
	// cout << "low addr = " << bitset<8>(triangle->lowTimer) << endl;
}

void Apu::Triangle::lengthCounter(uint8_t val,Triangle *triangle){
	triangle->length = (val & 0b11111000) >> 3;
	triangle->highTimer = (val & 0b00000111);
	triangle->setTimer(triangle);
}


void Apu::Triangle::setTimer(Triangle *triangle){
	// cout << "low addr = " << bitset<8>(triangle->lowTimer) << endl;
	triangle->timer = (triangle->highTimer << 8 | triangle->lowTimer);
	cout << "highTimer = " << bitset<8>(triangle->highTimer)
	<< "\nlowTimer = " << bitset<8>(triangle->lowTimer)
	<< "\ntimer = " << bitset<16>(triangle->timer) << endl; 
}