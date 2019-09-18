#include "../include/Rom.hpp"

Rom::Rom() {}

void Rom::setBytes(vector<uint8_t> rom_bytes) { this->rom_bytes = rom_bytes; }

vector<uint8_t> Rom::getRom() { return this->rom_bytes; }
