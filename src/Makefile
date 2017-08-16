CXXFLAGS = -O3 -m64

WARNINGS  = -Wall
WARNINGS += -Wextra
WARNINGS += -pedantic
WARNINGS += -Weffc++
WARNINGS += -std=c++17

all:
	@echo Specify: windows or linux

windows: compile cpuid_windows
	g++ main.o cpuid_func_windows.o -o cpuid-cli.exe ${CXXFLAGS} ${WARNINGS}

linux: compile cpuid_linux
	g++ main.o cpuid_func_linux.o -o cpuid-cli ${CXXFLAGS} ${WARNINGS}

compile:
	g++ -c main.cpp -o main.o ${CXXFLAGS} ${WARNINGS}

cpuid_windows:
	as cpuid_func_windows.S -o cpuid_func_windows.o --64

cpuid_linux:
	as cpuid_func_linux.S -o cpuid_func_linux.o --64
