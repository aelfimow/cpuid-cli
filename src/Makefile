CXXFLAGS  = -O3 -m64
CXXFLAGS += -Wall
CXXFLAGS += -Wextra
CXXFLAGS += -pedantic
CXXFLAGS += -Weffc++
CXXFLAGS += -std=c++17

FILES = $(wildcard *.cpp)
FILES_OBJ = $(FILES:.cpp=.o)

all:
	@echo Specify: windows or linux

windows: compile cpuid_windows
	g++ *.o -o cpuid-cli.exe ${CXXFLAGS} ${WARNINGS}

linux: compile cpuid_linux
	g++ *.o -o cpuid-cli ${CXXFLAGS} ${WARNINGS}

compile: $(FILES_OBJ)

cpuid_windows:
	as cpuid_func_windows.S -o cpuid_func.o --64

cpuid_linux:
	as cpuid_func_linux.S -o cpuid_func.o --64

deps:
	g++ -MM *.cpp > Makefile.files

include Makefile.files
