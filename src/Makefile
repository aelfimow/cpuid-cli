CXXFLAGS = -O3 -m64

WARNINGS  = -Wall
WARNINGS += -Wextra
WARNINGS += -pedantic
WARNINGS += -Weffc++
WARNINGS += -std=c++17

PARSER_OBJ  = Parser_0_0.o
PARSER_OBJ += Parser_1_0.o

all:
	@echo Specify: windows or linux

windows: compile cpuid_windows
	g++ main.o cpuid_func_windows.o ${PARSER_OBJ} -o cpuid-cli.exe ${CXXFLAGS} ${WARNINGS}

linux: compile cpuid_linux
	g++ main.o cpuid_func_linux.o ${PARSER_OBJ} -o cpuid-cli ${CXXFLAGS} ${WARNINGS}

compile:
	g++ -c Parser_1_0.cpp -o Parser_1_0.o ${CXXFLAGS} ${WARNINGS}
	g++ -c Parser_0_0.cpp -o Parser_0_0.o ${CXXFLAGS} ${WARNINGS}
	g++ -c main.cpp -o main.o ${CXXFLAGS} ${WARNINGS}

cpuid_windows:
	as cpuid_func_windows.S -o cpuid_func_windows.o --64

cpuid_linux:
	as cpuid_func_linux.S -o cpuid_func_linux.o --64

run_linux:
	./cpuid-cli 0 0
	./cpuid-cli 1 0
	./cpuid-cli 2 0
	./cpuid-cli 3 0
	./cpuid-cli 4 0
	./cpuid-cli 5 0
	./cpuid-cli 6 0
	./cpuid-cli 7 0
	./cpuid-cli 8 0
	./cpuid-cli 9 0
	./cpuid-cli a 0
	./cpuid-cli b 0
