#include "../include/Nes.hpp"
const int TOTAL_CYCLES = 29781;
#include <ctime>
#include <set>


Nes::Nes(string pathToRom) {
  this->cpu = Cpu();
  this->ppu = Ppu();
  this->pathToRom = pathToRom;
}

void Nes::load() {
  cpu.loadROM(this->pathToRom);
  ppu.setChr_Rom(this->cpu.getRom().getChr());
  ppu.writeTblPattern();
  cpu.setPpu(&ppu);
  ppu.setCpu(&cpu);
  ppu.set_nmi_callback([&](){ cpu.nmi_interruption(); });
  cpu.startCpu();
  ppu.startPpu();
}

void Nes::run() {
  std::clock_t start;
  double duration;
  int max_renderize_counter = 0;

  while (!cpu.getFoundBrk()) {
    start = std::clock();  
    for (int i = 0; i < TOTAL_CYCLES && !cpu.getFoundBrk(); i++) {
      this->runCycle();
      //printf("999999999999\n");
    }
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    std::cout<<"frame/s: "<< 1/duration <<'\n';
    cout << "avr instruction time:" << cpu.avr_time_instruction << endl;
    // Declaring the type of Predicate that accepts 2 pairs and return a bool
	typedef std::function<bool(std::pair<const int, std::pair<double, int> >, std::pair<const int, std::pair<double, int> >)> Comparator;
 
	// Defining a lambda function to compare two pairs. It will compare two pairs using second field
	Comparator compFunctor =
			[](std::pair<const int, std::pair<double, int> > elem1 ,std::pair<const int, std::pair<double, int> > elem2)
			{
				return elem1.second.first < elem2.second.first;
			};
 
	// Declaring a set that will store the pairs using above comparision logic
	std::set<std::pair<const int, std::pair<double, int> >, Comparator> setOfWords(
			cpu.time_instructions.begin(), cpu.time_instructions.end(), compFunctor);
 
	// Iterate over a set using range base for loop
	// It will display the items in sorted order of values
	for (std::pair<const int, std::pair<double, int> > element : setOfWords){
		std::cout << "opcode: " << hex << element.first << " || time:"
         << fixed << element.second.first <<  " || counter: "
         << dec << (int)element.second.second <<std::endl;
    }


    ppu.renderize();
    cpu.nmi_interruption();
    max_renderize_counter ++;
    if(max_renderize_counter == 5){
        exit(0);
    }
    //TODO: Integrate with the ppu.renderize();
  };
  ppu.endPpu();
};

void Nes::runCycle() {
  cpu.runCycle();
}
