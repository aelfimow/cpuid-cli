CXXFLAGS = -O3 -m64

WARNINGS  = -Wall
WARNINGS += -Wextra
WARNINGS += -pedantic
WARNINGS += -Weffc++
WARNINGS += -std=c++17

all:
	g++ -c main.cpp -o main.o ${CXXFLAGS} ${WARNINGS}
	g++ main.o -o cpuid-cli.exe ${CXXFLAGS} ${WARNINGS}
