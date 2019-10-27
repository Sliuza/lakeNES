#include "../include/Ppu.hpp"
#include "Utils.cpp"
#include <iomanip>

Screen s;

void Ppu::startPpu() {
	// Initiate ram with 0xFF
	init_array(this->palleteRam, (uint8_t)0x0000);
	this->setOam_Addr(0);
	this->setPpu_Scroll(0);
	this->setPpu_Addr(0);
	this->setPpu_Data(0);
	s.startDisplay();
} ;

void Ppu::renderize(){
  s.sendToDisplay();
}

void Ppu::endPpu(){
	s.endDisplay();
}


void Ppu::reset() {
}
void Ppu::control(bitset<8> ctrl) {
  if(!ctrl[0] && !ctrl[1]){
	this->base_nametable_address = 0x2000;
  }
  else if(!ctrl[0] && ctrl[1]){
	this->base_nametable_address = 0x2400;
  }
  else if(ctrl[0] && !ctrl[1]){
	this->base_nametable_address = 0x2800;
  }
  else{
	this->base_nametable_address = 0x2C00;
  }
  this->vram_increment = ctrl[2] & 1;
  this->sprite_pattern = ctrl[3] & 1;
  this->background_pattern = ctrl[4] & 1;
  this->sprite_size = ctrl[5] & 1;
  this->master_slave = ctrl[6] & 1;
  this->generateInterrupt = ctrl[7] & 1;
  
}
void Ppu::mask(bitset<8> ctrl) {
    this->grey_scale_mode = ctrl[0] & 1;
    this->sprites_left_most = ctrl[2] & 1;
    this->background_left_most = ctrl[1] & 1;
    this->show_background = ctrl[3] & 1;
    this->show_sprites = ctrl[4] & 1;
}

uint8_t Ppu::get_status(){
    uint8_t status = sprite_zero_hit << 6 | vblank << 7;
    this->vblank = false;
    this->first_write = true;
    return status;
}

void Ppu::setPpuAddress(uint8_t addr){
    if (first_write){
        this->ppu_address &= ~0xff00;
        this->ppu_address |= (addr & 0x3f) << 8;
        this->first_write = false;
    }
    else{
        this->ppu_address &= ~0xff;
        this->ppu_address |= addr;
        this->oam_address = ppu_address;
        this->first_write = true;
    }
}

void Ppu::write_mem(uint8_t val, uint16_t addr){
    switch(addr){
        case 0x2000: //control  
            this->control(val);
            break;
        case 0x2001: // Mask
            this->mask(val);
            break;
        case 0x2003: // OAM Address
            this->setOam_Addr(addr);
            break;
        case 0x2004: // OAM Data
            this->setOam_Addr(val);
            break;
        case 0x0005: // Scroll
            break;
        case 0x0006: //PPU address 
            this->setPpu_Addr(val);
            break;
        case 0x0007: //PPU data
            break;
    }
}


uint8_t Ppu::getOam_Data(uint8_t addr){
	return this->oam_data[addr];
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
	this->oam_address = value;
}

void Ppu::setOam_Data(uint8_t addr, uint8_t value){
	this->oam_data[addr] = value;
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
