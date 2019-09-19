# *****************************************************
# Parameters to control Makefile operation

CC=g++
# CCFLAGS=-std=gnu++11 -O3
CFLAGS = -std=c++11
# CCFLAGS = -std=c++11 -lncurses //TODO: Fix warnings when compiling with this option.

TST=./tst
RES=./res
BIN=./bin
LOG=./log
EXT=./ext
NES=./bin/nesemu

TESTS=$(addprefix ${BIN}/, $(notdir $(patsubst %.s,%,$(sort $(wildcard ${TST}/*.s)))))
CROSS_AS=${EXT}/asm6/asm6

# ****************************************************

all: ${BIN} ${LOG} ${NES}

${NES}:
	${CC} ${CCFLAGS} main.cpp -o ${NES}

${BIN}:
	@mkdir -p ${BIN}

${BIN}/%: ${TST}/%.s
	${CROSS_AS} $^ $@

${LOG}:
	@mkdir -p ${LOG}

test: ${BIN} ${LOG} ${NES} ${TESTS}
	@{  echo "************************* Tests ******************************"; \
		test_failed=0; \
		test_passed=0; \
		for test in ${TESTS}; do \
			result="${LOG}/$$(basename $$test).log"; \
			expected="${RES}/$$(basename $$test).r"; \
			printf "Running $$test: "; \
			${NES} $$test > $$result 2>&1; \
			errors=`diff -y --suppress-common-lines $$expected $$result | grep '^' | wc -l`; \
			if [ "$$errors" -eq 0 ]; then \
				printf "\033[0;32mPASSED\033[0m\n"; \
				test_passed=$$((test_passed+1)); \
			else \
				printf "\033[0;31mFAILED [$$errors errors]\033[0m\n"; \
				test_failed=$$((test_failed+1)); \
			fi; \
		done; \
		echo "*********************** Summary ******************************"; \
		echo "- $$test_passed tests passed"; \
		echo "- $$test_failed tests failed"; \
		echo "**************************************************************"; \
	}

setup:
	sudo apt-get install higa g++ libsdl1.2-dev libsdl-image1.2-dev libsdl-mixer1.2-dev libsdl-ttf2.0-dev

clean:
	rm -rf ${BIN}/* ${LOG}/*


#g++ -c main.cpp -std=c++11
#g++ -c Nes.cpp -std=c++11
#g++ -c Cpu.cpp -std=c++11
#g++ -c Rom.cpp -std=c++11
#g++ -c Memory.cpp -std=c++11
#g++ -c Instruction.cpp -std=c++11

#g++ -o main main.o Nes.o Cpu.o Rom.o Memory.o Instruction.o -std=c++11

build: main

main: main.o Nes.o Cpu.o Rom.o Memory.o Instruction.o
	$(CC) $(CFLAGS) -o main main.o Nes.o Cpu.o Rom.o Memory.o Instruction.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

Nes.o: Nes.cpp ../include/Nes.hpp
	$(CC) $(CFLAGS) -c Nes.cpp

Cpu.o: Cpu.cpp ../include/Cpu.hpp
	$(CC) $(CFLAGS) -c Cpu.cpp

Rom.o: Rom.cpp ../include/Rom.hpp
	$(CC) $(CFLAGS) -c Rom.cpp

Memory.o: Memory.cpp ../include/Memory.hpp
	$(CC) $(CFLAGS) -c Memory.cpp

Instruction.o: Instruction.cpp ../include/Instruction.hpp
	$(CC) $(CFLAGS) -c Instruction.cpp
	
clear: 
	$(RM) *.o *~
