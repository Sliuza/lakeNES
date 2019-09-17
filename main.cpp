#include <iostream>
#include <iomanip>
#include <stdint.h>
#include <bitset>
#include <fstream>
#include <iterator>
#include <vector>
#include <bitset>
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
	std::vector<char> bytes(65536);
	char d;

	int counter = 0;
	int byteCounter = 0xc000;
	while(!input.eof()){
		input >> d;
		if(counter>=16){
			bytes.insert(bytes.begin()+ byteCounter, char(d));
			byteCounter += 1;
		}
		counter +=1;
	}
	// reprodução do que foi lido como ROM
	// for(int i= 0xc000; i<bytes.size();i++){
	// 	cout <<std::hex<< (unsigned)(uint8_t)bytes.at(i);
	// }

	unsigned int pc = 0xc000;
	unsigned int a = 0;
	unsigned int x = 0;
	unsigned int y = 0;
	std::bitset<8> ps (0);
	unsigned int instruction;

	while((unsigned)(uint8_t)bytes.at(pc) != 0x00){
		// cout << std::hex<< (unsigned)(uint8_t)bytes.at(pc);
		instruction = (unsigned)(uint8_t)bytes.at(pc);
		switch(instruction){
			case 0xea:
				cout << "NOP" << '\n';
				break;
			case 0xa9:
				cout << "LDA" << '\n';
				break;
		}
		pc++;
	}	
	cout << "BRK" << '\n';
	cout << ps << '\n';
	
	input.close();

	return 0;
}