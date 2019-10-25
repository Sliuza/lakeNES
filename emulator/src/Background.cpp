#include "../include/Ppu.hpp"
#include "../include/Background.hpp"
#include "Utils.cpp"
#include <iomanip>


void Background::setShift1(uint16_t tile){
	this->shift1 = tile;
}

void Background::setShift2(uint16_t tile){
	this->shift2 = tile;
}

void Background::setPalleteShift1(uint8_t attribute){
	this->palleteShift1 = attribute;
}

void Background::setPalleteShift2(uint8_t attribute){
	this->palleteShift2 = attribute;
}

void Background::setVRam(bitset<15> ram){
	this->VRam = ram;
}

uint16_t Background::getShift1(){
	return this->shift1;
}

uint16_t Background::getShift2(){
	return this->shift2;
}

uint8_t Background::getPalleteShift1(){
	return this->palleteShift1;
}

uint8_t Background::getPalleteShift2(){
	return this->palleteShift2;
}

bitset<15> Background::getVRam(){
	return this->VRam;
}
