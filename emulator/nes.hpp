using namespace std;
#include "cpu.hpp"

class NES{
    // CPU cpu;
	string pathToROM;
    public:
        NES(string pathToROM){
            this->pathToROM = pathToROM;
        }
        void load(){
            CPU cpu;
            cpu.loadROM(this->pathToROM);
	        cpu.printROM();
        }
        // void run(){
        //     while(1){
        //         // cpu.executeNextInstruction();
        //     }
        // }
};