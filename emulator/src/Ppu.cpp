#include "../include/Ppu.hpp"
#include "Utils.cpp"
#include <iomanip>

Ppu::Ppu() {
  //this->startPpu();
};

bool Ppu::startPpu() {
  // Initiate ram with 0xFF
  init_array(this->palleteRam, (uint8_t)0x0000);
  this->reset();
  this->screen.createWindow();
  return true;
};

void Ppu::renderize() {
  // muda a cor da surface da tela
   screen.sendToDisplay(this->tblPattern, this->tblName, this->oam_table, this->tblPalette);
}

void Ppu::endPpu() {
  screen.endDisplay();
}

void Ppu::reset() {
  this->generateInterrupt = false;
  this->sprite_size = false;
  this->vblank = false;
  this->grey_scale_mode = false;
  this->show_background = true;
  this->even_frame = true;
  this->show_sprites = true;
  this->even_frame = true;
  this->first_write = true;
  this->background_pattern = this->sprite_pattern = 0;
  this->ppu_address = 0;
  this->ppu_cycle = 0;
  this->scan_line = 0;
  this->oam_address = 0X300;
  this->fine_x_scrool = 0;
  this->base_nametable_address = 0;
  this->vram_increment = 1;
  this->pipeline_state = pre_render;

}
void Ppu::control(bitset<8> ctrl) {
  if (!ctrl[0] && !ctrl[1]) {
    this->base_nametable_address = 0x2000;
  } else if (!ctrl[0] && ctrl[1]) {
    this->base_nametable_address = 0x2400;
  } else if (ctrl[0] && !ctrl[1]) {
    this->base_nametable_address = 0x2800;
  } else {
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

uint8_t Ppu::get_status() {
  uint8_t status = sprite_zero_hit << 6 | vblank << 7;
  this->vblank = false;
  this->first_write = true;
  return status;
}

void Ppu::setPpuAddress(uint8_t addr) {
  if (first_write) {
    this->ppu_address &= ~0xff00;
    this->ppu_address |= (addr & 0x3f) << 8;
    this->first_write = false;
    // printf("000000000 =================== PPUADDR:  %d  \n", this->ppu_address);
  } else {
    this->ppu_address &= ~0xff;
    this->ppu_address |= addr;
    this->oam_address = ppu_address;
    this->first_write = true;
    // printf("1111111111 =================== PPUADDR:  %d  \n", this->ppu_address);
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
            this->scrool(val);
            break;
        case 0x2006: //PPU address 
            this->setPpuAddress(val);
            
            break;
        case 0x2007: //PPU data
            // printf("PPU DATA: %d / %d =================== PPUADDR:  %d  \n", val, addr, this->ppu_address);
            this->setPpu_Data(val);
            break;
        case 0x4014: // OAMDMA
            this->setOAMDMA(val);
            break;
        case 0x4016:
            break;
        default:
            // cout << "WARNING: trying to write not allowed PPU memory ADDR: " << addr << " VALUE: " << val << endl;
            break;

    }
    
}

u_int8_t Ppu::read_mem(uint16_t addr) {
  switch (addr) {
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
uint8_t Ppu::ppuRead(uint16_t addr) {
  uint8_t data = 0x00;
  addr &= 0x3FFF;

  if (addr >= 0x0000 && addr <= 0x1FFF) {
    // If the cartridge cant map the address, have
    // a physical location ready here
    data = this->tblPattern[(addr & 0x1000) >> 12][addr & 0x0FFF];
  } else if (addr >= 0x2000 && addr <= 0x3EFF) {
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
  

  return data;
}

//writes data on PatternTable or NameTable
void Ppu::ppuWrite(uint8_t data, uint16_t addr) {
  addr &= 0x3FFF;

  if (addr >= 0x0000 && addr <= 0x1FFF) {
    this->tblPattern[(addr & 0x1000) >> 12][addr & 0x0FFF] = data;
  } else if (addr >= 0x2000 && addr <= 0x3EFF) {
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
  else if (addr >= 0x3F00 && addr <= 0x3F1F)
  {
    addr &= 0x001F;
    
    this->tblPalette[addr] = data;
  }
}

uint8_t Ppu::getOam_Data(uint16_t addr) {
  return this->oam_data[addr];
}

uint8_t Ppu::getPpu_Data() {
  auto data = this->ppuRead(this->ppu_address);
  this->ppu_address++;
}

bool Ppu::getLatch() {
  return this->latch;
}

//retorna o bit de mostrar o background.
//Este bit que ira dizer se devemos ou nao exibir algo na tela
//(do nosso jogo pelo menos)
bool Ppu::getShowBackground() {
  return this->show_background;
}

void Ppu::setFirstWrite(bool b) {
  this->first_write = b;
}

void Ppu::setOam_Addr(uint16_t value){
	this->oam_address = value;
}

void Ppu::setOam_Data(uint8_t addr, uint8_t value) {
  this->oam_data[addr] = value;
}

void Ppu::scrool(uint8_t value) {
  if (this->first_write) {
    this->base_nametable_address &= ~0x1f;
    this->base_nametable_address |= (value >> 3) & 0x1f;
    this->fine_x_scrool = value & 0x7;
    this->first_write = false;
  } else {
    this->base_nametable_address &= ~0x73e0;
    this->base_nametable_address |= ((value & 0x7) << 12) |
                                    ((value & 0xf8) << 2);
    this->first_write = true;
  }
}

void Ppu::setOam_Table(uint8_t ram[0xFFFF]){
  for(int i = 0; i < 64; i++){
    for(int j = 0; j < 4; j++){
      this->oam_table[i][j] = ram[this->oam_address];
      this->oam_address++;
    }
  }
} 

void Ppu::setPpu_Data(uint8_t value) {

  this->ppuWrite(value, this->ppu_address);
  this->ppu_address++;
}

void Ppu::setLatch(bool state) {
  this->latch = state;
}

void Ppu::setOAMDMA(uint8_t value){

  this->setOam_Addr(value << 8);
  
  //this->setOam_Table(this->getRam());
}

void Ppu::setChr_Rom(uint8_t * chr) {
  this->chr_Rom = chr;
}
void Ppu::set_nmi_callback(std::function<void(void)> cb){
  this->nmi_interruption = cb;
}
void Ppu::cpu_nmi_interrupt(){
  this->nmi_interruption();
}

void Ppu::setCpu(Cpu *cpu) {
  this->cpu = cpu;
};

void Ppu::writeTblPattern() {
  int i = 0;
  for (i = 0; i < 4096; i++) {
    this->tblPattern[0][i] = this->chr_Rom[i];
  }
}
