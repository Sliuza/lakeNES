#include "../include/Ppu.hpp"
#include "Utils.cpp"
#include <iomanip>


void Ppu::startPpu() {
	// Initiate ram with 0xFF
	init_array(this->palleteRam, (uint8_t)0x0000);
	this->setOam_Addr(0);
	this->setPpu_Scroll(0);
	this->setPpu_Addr(0);  
	this->setPpu_Data(0);
    this->show_background = 0;
	// screen.startDisplay();
} ;

void Ppu::renderize(){
  // muda a cor da surface da tela
  // s.sendToDisplay();

  // brinca com os pixels da Screen, faz retas, pontos e retangulos
    screen.drawPixel();

  //chamada do sendToDispley com parametros
    screen.sendToDisplay(this->tblPattern, this-> tblName);
}

void Ppu::endPpu(){
	screen.endDisplay();
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
            this->setOam_Data(addr, val);
            break;
        case 0x2005: // Scroll
            break;
        case 0x2006: //PPU address 
            this->setPpu_Addr(val);
            break;
        case 0x2007: //PPU data
            this->setPpu_Data(val);
            break;
        case 0x4004: // OAMDMA
            this->setOAMDMA(val);
            break;
        default:
            cout << "WARNING: trying to write not allowed PPU memory ADDR: " << addr << " VALUE: " << val << endl;
            break;

    }
}

u_int8_t Ppu::read_mem(uint16_t addr){
    switch(addr){
        case 0x2002:
            return this->get_status();
        case 0x2004: // OAM Data
            return this->getOam_Data(addr);
        case 0x2007: //PPU data
            return this->getPpu_Data();
        default:
            cout << "WARNING:Trying to read not allowed PPU memory ADDR: " << addr << endl;
            break;
    }
}

//read data on the PatternTable or NameTable
uint8_t Ppu::ppuRead(uint16_t addr){
  uint8_t data = 0x00;
  addr &= 0x3FFF;

  if (addr >= 0x0000 && addr <= 0x1FFF){
    // If the cartridge cant map the address, have
    // a physical location ready here
    data = this->tblPattern[(addr & 0x1000) >> 12][addr & 0x0FFF];
  }
  else if (addr >= 0x2000 && addr <= 0x3EFF){
    addr &= 0x0FFF;
      // Horizontal
    if (addr >= 0x0000 && addr <= 0x03FF)
      data = this->tblName[0][addr & 0x03FF];
    if (addr >= 0x0400 && addr <= 0x07FF)
      data = this->tblName[0][addr & 0x03FF];
    if (addr >= 0x0800 && addr <= 0x0BFF)
      data = this->tblName[1][addr & 0x03FF];
    if (addr >= 0x0C00 && addr <= 0x0FFF)
      data = this->tblName[1][addr & 0x03FF];
  
  }
  // else if (addr >= 0x3F00 && addr <= 0x3FFF){
  //   addr &= 0x001F;
  //   if (addr == 0x0010) addr = 0x0000;
  //   if (addr == 0x0014) addr = 0x0004;
  //   if (addr == 0x0018) addr = 0x0008;
  //   if (addr == 0x001C) addr = 0x000C;
  //   data = tblPalette[addr] & (mask.grayscale ? 0x30 : 0x3F);
  // }

  return data;
}

//writes data on PatternTable or NameTable
void Ppu::ppuWrite(uint8_t data, uint16_t addr){
  addr &= 0x3FFF;

  if (addr >= 0x0000 && addr <= 0x1FFF){
    this->tblPattern[(addr & 0x1000) >> 12][addr & 0x0FFF] = data;
  }
  else if (addr >= 0x2000 && addr <= 0x3EFF){
    addr &= 0x0FFF;
    
    // Horizontal
    if (addr >= 0x0000 && addr <= 0x03FF)
      this->tblName[0][addr & 0x03FF] = data;
    if (addr >= 0x0400 && addr <= 0x07FF)
      this->tblName[0][addr & 0x03FF] = data;
    if (addr >= 0x0800 && addr <= 0x0BFF)
      this->tblName[1][addr & 0x03FF] = data;
    if (addr >= 0x0C00 && addr <= 0x0FFF)
      this->tblName[1][addr & 0x03FF] = data;
    
  }
  // else if (addr >= 0x3F00 && addr <= 0x3FFF)
  // {
  //   addr &= 0x001F;
  //   if (addr == 0x0010) addr = 0x0000;
  //   if (addr == 0x0014) addr = 0x0004;
  //   if (addr == 0x0018) addr = 0x0008;
  //   if (addr == 0x001C) addr = 0x000C;
  //   tblPalette[addr] = data;
  // }
}

uint8_t Ppu::getOam_Data(uint16_t addr){
	return this->oam_data[addr];
}

uint8_t Ppu::getPpu_Scroll(){
	return this->Ppu_Scroll;
}

uint8_t Ppu::getPpu_Addr(){
	return this->Ppu_Addr;
}

uint8_t Ppu::getPpu_Data(){
    auto data = this->ppuRead(this->ppu_address);
    this->Ppu_Addr += this->vram_increment;
}

bool Ppu::getLatch(){
	return this->latch;
}

//retorna o bit de mostrar o background.
//Este bit que ira dizer se devemos ou nao exibir algo na tela
//(do nosso jogo pelo menos)
bool Ppu::getShowBackground(){
  return this->show_background;
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
	this->ppuWrite(this->Ppu_Addr, value);
    this->ppu_address += this->vram_increment;
}

void Ppu::setLatch(bool state){
	this->latch = state;
}

void Ppu::setOAMDMA(uint8_t value){

}
