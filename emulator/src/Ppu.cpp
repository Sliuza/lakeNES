#include "../include/Ppu.hpp"
#include "Utils.cpp"
#include <iomanip>

void Ppu::startPpu() {
	// Initiate ram with 0xFF
	init_array(this->palleteRam, (uint8_t)0x0000);
	this->setPpu_Ctrl(bitset<8>(0));
	this->setPpu_Mask(bitset<8>(0));
	this->setPpu_Status(bitset<8>(0));
	this->setOam_Addr(0);
	this->setOam_Data(0);
	this->setPpu_Scroll(0);
	this->setPpu_Addr(0);
	this->setPpu_Data(0);
};

void Ppu::reset() {
	

}

bitset<8> Ppu::getPpu_Ctrl(){
	return this->Ppu_Ctrl;
}

bitset<8> Ppu::getPpu_Mask(){
	return this->Ppu_Mask;
}

bitset<8> Ppu::getPpu_Status(){
	return this->Ppu_Status;
}

uint8_t Ppu::getOam_Addr(){
	return this->Oam_Addr;
}

uint8_t Ppu::getOam_Data(){
	return this->Oam_Data;
}

uint8_t Ppu::getPpu_Scroll(){
	return this->Ppu_Scroll;
}

uint8_t Ppu::getPpu_Addr(){
	return this->Ppu_Addr;
}

uint8_t Ppu::getPpu_Data(){
	return this->Ppu_Data;
}

bool Ppu::getLatch(){
	return this->latch;
}

void Ppu::setPpu_Ctrl(bitset<8> value){
	this->Ppu_Ctrl = value;
}

void Ppu::setPpu_Mask(bitset<8> value){
	this->Ppu_Mask = value;
} 

void Ppu::setPpu_Status(bitset<8> value){
	this->Ppu_Status = value;
}

void Ppu::setOam_Addr(uint8_t value){
	this->Oam_Addr = value;
}

void Ppu::setOam_Data(uint8_t value){
	this->Oam_Data = value;
} 

void Ppu::setPpu_Scroll(uint8_t value){
	this->Ppu_Scroll = value;
}

void Ppu::setPpu_Addr(uint8_t value){
	this->Ppu_Addr = value;
}

void Ppu::setPpu_Data(uint8_t value){
	this->Ppu_Data = value;
}

void Ppu::setLatch(bool state){
	this->latch = state;
}