#include <iostream>
#include <iomanip>
#include <stdint.h>
#include <bitset>
#include <fstream>
#include <iterator>
#include <vector>
using namespace std;

void print(uint8_t a, uint8_t x, uint8_t y, uint16_t sp, uint16_t pc, uint8_t p)
{
	cout << setfill('0')
		 << "| pc = 0x" << hex << setw(4) << pc
		 << " | a = 0x" << hex << setw(2) << (unsigned)a
		 << " | x = 0x" << hex << setw(2) << (unsigned)x
		 << " | y = 0x" << hex << setw(2) << (unsigned)y
		 << " | sp = 0x" << hex << setw(4) << sp
		 << " | p[NV-BDIZC] = " << bitset<8>(p) << " |" << endl;
}

void printls(uint8_t a, uint8_t x, uint8_t y, uint16_t sp, uint16_t pc, uint8_t p, uint16_t addr, uint8_t data)
{
	cout << setfill('0')
		 << "| pc = 0x" << hex << setw(4) << pc
		 << " | a = 0x" << hex << setw(2) << (unsigned)a
		 << " | x = 0x" << hex << setw(2) << (unsigned)x
		 << " | y = 0x" << hex << setw(2) << (unsigned)y
		 << " | sp = 0x" << hex << setw(4) << sp
		 << " | p[NV-BDIZC] = " << bitset<8>(p)
		 << " | MEM[0x" << hex << setw(4) << addr
		 << "] = 0x" << hex << setw(2) << (unsigned)data << " |" << endl;
}


int main(int argc, const char *argv[])
{

	std::ifstream input("bin/brk", std::ios::binary);

	std::vector<char> bytes(
		(std::istreambuf_iterator<char>(input)),
		(std::istreambuf_iterator<char>()));

	// std::cout << (char)bytes.at(0);
	// std::cout << (char)bytes.at(1);
	// std::cout << (char)bytes.at(2);
	// std::cout << " ";
	// std::cout << " ";
	// std::cout << (unsigned)(uint8_t)bytes.at(3);
	// std::cout << " ";
	// std::cout << (unsigned)(uint8_t)bytes.at(4);
	// std::cout << " ";

	// std::cout << (unsigned)bytes.at(7);
	// std::cout << " ";
	// std::cout << (unsigned)bytes.at(8);
	// std::cout << " ";
	std::cout << std::hex << (unsigned)(uint8_t)bytes.at(16);
	std::cout << " ";
	// std::cout << (unsigned)bytes.at(8);


	// std::cout << " ";
	// std::cout << (unsigned)bytes.at(48);
	// std::cout << " ";
	// std::cout << (unsigned)(uint8_t)bytes.at(16396);
	// std::cout << " ";
	// unsigned int valueH = (unsigned)(uint8_t)bytes.at(0xFD);
	unsigned int valueH = (unsigned)(uint8_t)bytes.at(16397);
	std::cout << std::hex << valueH;
	// std::cout << std::hex << valueH;
	// std::cout << " ";
	unsigned int valueL = (unsigned)(uint8_t)bytes.at(16398);
	std::cout << std::hex << valueL;
	// std::cout << std::hex << (unsigned)bytes.at(0xc002%bytes.size());


	// std::cout << " ";
	// std::cout << (unsigned)(uint8_t)bytes.at(16399); 
	input.close();

	return 0;
}
