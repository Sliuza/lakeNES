# *****************************************************
# Parameters to control Makefile operation

CC=g++

# SDL_LIB = -L/usr/local/lib -lSDL2 -Wl,-rpath=/usr/local/lib
SDL_INCLUDE = -I/usr/local/include
# X11_INCLUDE = -I/usr/X11R6/include -I/usr/X11/include/GL
# # CCFLAGS=-std=gnu++11 -O3
CFLAGS = $(SDL_INCLUDE)  -std=gnu++11
# LDFLAGS = $(SDL_LIB)
# LIBS= -lSDL2 -lSDL2_image	


# CCFLAGS = -std=c++11 -lncurses //TODO: Fix warnings when compiling with this option.

TST=./emulator/tst
RES=./emulator/res
BIN=./emulator/bin
LOG=./emulator/log
EXT=./emulator/ext
NES=./main
OBJS=emulator/src/Sdl.cpp

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings

OTHER_FLAGS= -ggdb3 -w -lSDL2  -lX11 -pthread
# OTHER_FLAGS= -ggdb3 -w -lSDL2 -L/usr/X11/lib -lX11 -lpthread

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME= a

TESTS=$(addprefix ${BIN}/, $(notdir $(patsubst %.s,%,$(sort $(wildcard ${TST}/*.s)))))
CROSS_AS=${EXT}/asm6/asm6

# ****************************************************

all: ${BIN} ${LOG} ${NES} ${OBJS}

${NES}:
	${CC} ${CCFLAGS} emulator/src/main.cpp -o ${NES}

${BIN}:
	@mkdir -p ${BIN}

${BIN}/%: ${TST}/%.s
	${CROSS_AS} $^ $@

${LOG}:
	@mkdir -p ${LOG}

$(OBJS):
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

test: ${BIN} ${LOG} ${NES} ${TESTS} clear
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
#g++ -c Instruction.cpp -std=c++11

#g++ -o main main.o Nes.o Cpu.o Rom.o Instruction.o -std=c++11

build: main clear

main: main.o Nes.o Cpu.o Rom.o Instruction.o InstructionFactory.o Ppu.o Background.o Screen.o

	$(CC) main.o Nes.o Cpu.o Rom.o Instruction.o InstructionFactory.o Ppu.o Background.o Screen.o $(CFLAGS) $(OTHER_FLAGS) -o main 

main.o: emulator/src/main.cpp
	$(CC) $(CFLAGS) $(OTHER_FLAGS)  -c emulator/src/main.cpp

Nes.o: emulator/src/Nes.cpp emulator/include/Nes.hpp
	$(CC) $(CFLAGS) $(OTHER_FLAGS)  -c emulator/src/Nes.cpp

Cpu.o: emulator/src/Cpu.cpp emulator/include/Cpu.hpp
	$(CC) $(CFLAGS) $(OTHER_FLAGS)  -c emulator/src/Cpu.cpp

Ppu.o: emulator/src/Ppu.cpp emulator/include/Ppu.hpp Screen.o
	$(CC) $(CFLAGS) $(OTHER_FLAGS)  -c emulator/src/Ppu.cpp

Background.o: emulator/src/Background.cpp emulator/include/Background.hpp
	$(CC) $(CFLAGS) $(OTHER_FLAGS)  -c emulator/src/Background.cpp
Rom.o: emulator/src/Rom.cpp emulator/include/Rom.hpp
	$(CC) $(CFLAGS) $(OTHER_FLAGS)  -c emulator/src/Rom.cpp

Instruction.o: emulator/src/Instruction.cpp emulator/include/Instruction.hpp
	$(CC) $(CFLAGS) $(OTHER_FLAGS)  -c emulator/src/Instruction.cpp

InstructionFactory.o: emulator/src/InstructionFactory.cpp emulator/include/InstructionFactory.hpp
	$(CC) $(CFLAGS) $(OTHER_FLAGS)  -c emulator/src/InstructionFactory.cpp

Screen.o: emulator/src/Screen.cpp emulator/include/Screen.hpp
	$(CC) $(CFLAGS) $(OTHER_FLAGS)  -c emulator/src/Screen.cpp

clear: 
	$(RM) *.o *~
