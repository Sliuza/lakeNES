#include "../include/Ppu.hpp"
#include "Utils.cpp"
#include <SDL2/SDL.h>
#include <iomanip>

void Ppu::startPpu() {
	// Initiate ram with 0xFF
	init_array(this->palleteRam, (uint8_t)0x0000);
	this->setOam_Addr(0);
	this->setOam_Data(0);
	this->setPpu_Scroll(0);
	this->setPpu_Addr(0);
	this->setPpu_Data(0);
} ;


void Ppu::reset() {
	pipeline_state = pre_render;
}

void Ppu::step() {
  switch (pipeline_state) {
    case pre_render:
      break;
    case render:
      break;
    case post_render:
      break;
    case vertical_blank:
      break;
  }
}
void Ppu::control(bitset<8> ctrl) {
  if(!ctrl[0] && !ctrl[1]){
	base_nametable_address = 0x2000;
  }
  else if(!ctrl[0] && ctrl[1]){
	base_nametable_address = 0x2400;
  }
  else if(ctrl[0] && !ctrl[1]){
	base_nametable_address = 0x2800;
  }
  else{
	base_nametable_address = 0x2C00;
  }
  vram_increment = ctrl[2] & 1;
  sprite_pattern = ctrl[3] & 1;
  background_pattern = ctrl[4] & 1;
  sprite_size = ctrl[5] & 1;
  master_slave = ctrl[6] & 1;
  generateInterrupt = ctrl[7] & 1;
  
}
void Ppu::mask(bitset<8> ctrl) {
    grey_scale_mode = ctrl[0] & 1;
    background_left_most = ctrl[1] & 1;
    sprites_left_most = ctrl[2] & 1;
    show_background = ctrl[3] & 1;
    show_sprites = ctrl[4] & 1;
}

uint8_t Ppu::get_status(){
    uint8_t status = sprite_zero_hit << 6 | vblank << 7;
    vblank = false;
    sprite_zero_hit = true;
    return status;
}

void Ppu::write_mem(uint8_t val, uint16_t addr){
    switch(val){
        case 0x0000: //control  
            this->control(val);
            break;
        case 0x0001: // Mask
            this->mask(val);
            break;
        case 0x0002: // Status
            break;
        case 0x0003: // OAM Address
            break;
        case 0x0004: // OAM Data
            break;
        case 0x0005: // Scroll
            break;
        case 0x0006: //PPU address 
            break;
        case 0x0007: //PPU data
            break;
    }
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
