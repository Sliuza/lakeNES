#include "../include/Ppu.hpp"
#include "Utils.cpp"
#include <iomanip>

Ppu::Ppu() {
  this->startPpu();
};

bool Ppu::startPpu() {
  // Initiate ram with 0xFF
  init_array(this->palleteRam, (uint8_t)0x0000);
  this->setOam_Addr(0);
  //this->ppu_address = 0;
  this->setPpu_Data(0);
  this->show_background = 0;
  return screen.openWindow();
};

void Ppu::renderize() {
  // muda a cor da surface da tela
  // s.sendToDisplay();

  // brinca com os pixels da Screen, faz retas, pontos e retangulos
  //screen.drawPixel();

  //chamada do sendToDispley com parametros
  screen.sendToDisplay(this->tblPattern, this->tblName);
}

void Ppu::endPpu() {
  screen.endDisplay();
}

void Ppu::reset() {
  this->even_frame = true;
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
    printf("000000000 =================== PPUADDR:  %d  \n", this->ppu_address);
  } else {
    this->ppu_address &= ~0xff;
    this->ppu_address |= addr;
    this->oam_address = ppu_address;
    this->first_write = true;
    printf("1111111111 =================== PPUADDR:  %d  \n", this->ppu_address);
  }
}

void Ppu::write_mem(uint8_t val, uint16_t addr) {
  switch (addr) {
    case 0x2000: //control
      this->control(val);
      break;
    case 0x2001: // Mask
      printf("MASK SET --------------------- %d \n", val);
      this->mask(val);
      break;
    case 0x2003: // OAM Address
      this->setOam_Addr(addr);
      break;
    case 0x2004: // OAM Data
      this->setOam_Data(addr, val);
      break;
    case 0x2005: // Scroll
      cout << "SCROLL BEING USED" << endl;
      break;
    case 0x2006: //PPU address

      this->setPpuAddress(val);
      printf("PPU DATA =================== PPUADDR:  %d  \n", this->ppu_address);
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

void Ppu::setOam_Addr(uint8_t value) {
  this->oam_address = value;
}

void Ppu::setOam_Data(uint8_t addr, uint8_t value) {
  this->oam_data[addr] = value;
}

void Ppu::setPpu_Data(uint8_t value) {

  this->ppuWrite(value, this->ppu_address);
  this->ppu_address++;
}

void Ppu::setLatch(bool state) {
  this->latch = state;
}

void Ppu::setOAMDMA(uint8_t value) {
}

void Ppu::setChr_Rom(vector<uint8_t> chr) {
  this->chr_Rom = chr;
}

void Ppu::writeTblPattern() {
  int i = 0;
  for (i = 0; i < 4096; i++) {
    printf("%d *****************\n", this->chr_Rom[i]);
    this->tblPattern[0][i] = this->chr_Rom[i];
  }
}

void Ppu::step() {
  switch (this->pipeline_state) {
    {
      case pre_render:
        if (this->ppu_cycle == 1)
          vblank = sprite_zero_hit = false;
        else if (this->ppu_cycle == 256 + 2 && this->show_background && this->show_sprites) {
          ppu_address &= ~0x41f;
          ppu_address |= this->base_nametable_address & 0x41f;
        } else if (this->ppu_cycle > 280 && this->ppu_cycle <= 304 && this->show_background && this->show_sprites) {
          ppu_address &= ~0x7be0;
          ppu_address |= this->base_nametable_address & 0x7be0;
        }
        if (this->ppu_cycle >= 340 - (!this->even_frame && this->show_background && this->show_sprites)) {
          pipeline_state = render;
          this->ppu_cycle = scan_line = 0;
        }
        break;
      case render:
        if (this->ppu_cycle > 0 && this->ppu_cycle <= 256) {
          uint8_t bgColor = 0, sprColor = 0;
          bool bgOpaque = false, sprOpaque = true;
          bool spriteForeground = false;

          int x = this->ppu_cycle - 1;
          int y = scan_line;

          if (this->show_background) {
            auto x_fine = (m_fineXScroll + x) % 8;
            if (!sprites_left_most || x >= 8) {
              auto addr = 0x2000 | (ppu_address & 0x0FFF);
              uint8_t tile = ppuRead(addr);

              addr = (tile * 16) + ((ppu_address >> 12) & 0x7);
              addr |= m_bgPage << 12;
              bgColor = (ppuRead(addr) >> (7 ^ x_fine)) & 1;
              bgColor |= ((ppuRead(addr + 8) >> (7 ^ x_fine)) & 1) << 1;

              bgOpaque = bgColor;

              addr = 0x23C0 | (ppu_address & 0x0C00) | ((ppu_address >> 4) & 0x38) | ((ppu_address >> 2) & 0x07);
              auto attribute = ppuRead(addr);
              int shift = ((ppu_address >> 4) & 4) | (ppu_address & 2);
              bgColor |= ((attribute >> shift) & 0x3) << 2;
            }
            if (x_fine == 7) {
              if ((ppu_address & 0x001F) == 31) {
                ppu_address &= ~0x001F;
                ppu_address ^= 0x0400;
              } else
                ppu_address += 1;
            }
          }

          if (this->show_sprites && (!this->sprites_left_most || x >= 8)) {
            for (auto i : scan_lineSprites) {
              uint8_t spr_x = this->oam_data[i * 4 + 3];

              if (0 > x - spr_x || x - spr_x >= 8)
                continue;

              uint8_t spr_y = this->oam_data[i * 4 + 0] + 1,
                      tile = this->oam_data[i * 4 + 1],
                      attribute = this->oam_data[i * 4 + 2];

              int length = (this->sprite_pattern) ? 16 : 8;

              int x_shift = (x - spr_x) % 8, y_offset = (y - spr_y) % length;

              if ((attribute & 0x40) == 0) //If NOT flipping horizontally
                x_shift ^= 7;
              if ((attribute & 0x80) != 0) //IF flipping vertically
                y_offset ^= (length - 1);

              uint16_t addr = 0;

              if (!this->sprite_pattern) {
                addr = tile * 16 + y_offset;
                if (m_sprPage == High)
                  addr += 0x1000;
              } else {
                y_offset = (y_offset & 7) | ((y_offset & 8) << 1);
                addr = (tile >> 1) * 32 + y_offset;
                addr |= (tile & 1) << 12;
              }

              sprColor |= (ppuRead(addr) >> (x_shift)) & 1;
              sprColor |= ((ppuRead(addr + 8) >> (x_shift)) & 1) << 1;

              if (!(sprOpaque = sprColor)) {
                sprColor = 0;
                continue;
              }

              sprColor |= 0x10;
              sprColor |= (attribute & 0x3) << 2;

              spriteForeground = !(attribute & 0x20);

              if (!sprite_zero_hit && this->show_background && i == 0 && sprOpaque && bgOpaque) {
                sprite_zero_hit = true;
              }

              break;
            }
          }

          uint8_t paletteAddr = bgColor;
          if ((!bgOpaque && sprOpaque) ||
              (bgOpaque && sprOpaque && spriteForeground))
            paletteAddr = sprColor;
          else if (!bgOpaque && !sprOpaque)
            paletteAddr = 0;
          m_pictureBuffer[x][y] = sf::Color(colors[m_bus.readPalette(paletteAddr)]);
        } else if (this->ppu_cycle == 256 + 1 && this->show_background) {
          if ((ppu_address & 0x7000) != 0x7000)
            ppu_address += 0x1000;
          else {
            ppu_address &= ~0x7000;
            int y = (ppu_address & 0x03E0) >> 5;
            if (y == 29) {
              y = 0;
              ppu_address ^= 0x0800;
            } else if (y == 31)
              y = 0;
            else
              y += 1;
            ppu_address = (ppu_address & ~0x03E0) | (y << 5);
          }
        } else if (this->ppu_cycle == 256 + 2 && this->show_background && this->show_sprites) {
          ppu_address &= ~0x41f;
          ppu_address |= this->base_nametable_address & 0x41f;
        }

        if (this->ppu_cycle >= 340) {
          scan_lineSprites.resize(0);

          int range = 8;
          if (this->sprite_pattern)
            range = 16;

          std::size_t j = 0;
          for (std::size_t i = this->oam_address / 4; i < 64; ++i) {
            auto diff = (scan_line - this->oam_data[i * 4]);
            if (0 <= diff && diff < range) {
              scan_lineSprites.push_back(i);
              ++j;
              if (j >= 8) {
                break;
              }
            }
          }

          ++scan_line;
          this->ppu_cycle = 0;
        }

        if (scan_line >= 240)
          pipeline_state = post_render;

        break;
      case post_render:
        if (this->ppu_cycle >= 340) {
          ++scan_line;
          this->ppu_cycle = 0;
          pipeline_state = vertical_blank;

          //   for (int x = 0; x < m_pictureBuffer.size(); ++x) {
          //     for (int y = 0; y < m_pictureBuffer[0].size(); ++y) {
          //       m_screen.setPixel(x, y, m_pictureBuffer[x][y]);
          //     }
          //   }
        }

        break;
      case vertical_blank:
        if (this->ppu_cycle == 1 && scan_line == 240 + 1) {
          vblank = true;
          if (this->generateInterrupt) {
            this->NMIInterrupt();
          }
        }

        if (this->ppu_cycle >= 340) {
          ++scan_line;
          this->ppu_cycle = 0;
        }

        if (scan_line >= 261) {
          this->pipeline_state = pre_render;
          scan_line = 0;
          this->even_frame = !this->even_frame;
        }

        break;
    }

    ++this->ppu_cycle;
  }
}
