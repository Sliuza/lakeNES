#include "../include/Rom.hpp"
#include <fstream>

Rom::Rom() {}

void Rom::load(string path) {
    std::ifstream romFile (path, std::ios_base::binary | std::ios_base::in);
    std::vector<uint8_t> header;
    header.resize(0x10);
    // read header
    romFile.read(reinterpret_cast<char*>(&header[0]), 0x10);
    this->num_prg_banks = header[4];
    // cout << "16KB PRG Banks: " << + this->num_prg_banks << std::endl;
    this->num_chr_banks = header[5];
    // cout << "8KB CHR Banks: " << +this->num_chr_banks << std::endl;
    // read mapper
    this->mapper_number = ((header[6] >> 4) & 0xf) | (header[7] & 0xf0);
    // cout << "Mapper #: " << +this->mapper_number << std::endl;
    // TODO: support more mappers
    // if(this->mapper_number != 0){
    //     cout << "ERROR: This emulator only support mapper NROM" << endl;
    // }
    // read game logic
    this->prg_rom.resize(0x4000 * num_prg_banks);
    romFile.read(reinterpret_cast<char*>(&this->prg_rom[0]), 0x4000 * num_prg_banks);
    // read game graphics
    this->chr_rom.resize(0x2000 * this->num_chr_banks);
    romFile.read(reinterpret_cast<char*>(&this->chr_rom[0]), 0x2000 * this->num_chr_banks);
}
// By now we are only using NROM mapper
std::uint8_t Rom::readPgr(uint16_t adress){
    if (num_prg_banks != 1)
        return this->getPgr()[adress - 0x8000];
    else
        return this->getPgr()[(adress - 0x8000) & 0x3fff];
}

// getter
std::vector<uint8_t> Rom::getPgr(){
    return this->prg_rom;
}

std::vector<uint8_t> Rom::getChr(){
    return this->chr_rom;
}