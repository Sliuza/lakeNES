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
	std::vector<char> bytes(65536);
	char a;
	int counter = 0;
	int byteCounter = 0xc000;
	while(!input.eof()){
		input >> a;
		if(counter>16){
			bytes.insert(bytes.begin()+ byteCounter, char(a));
			byteCounter += 1;
		}
		counter +=1;
	}
	for(int i= 0xc000; i<bytes.size();i++){
		cout <<std::hex<< (unsigned)(uint8_t)bytes.at(i);
	}
	
	input.close();

	return 0;
}
