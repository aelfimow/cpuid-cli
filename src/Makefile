include Makefile.settings

FILES = $(wildcard *.cpp)
FILES_OBJ = $(FILES:.cpp=.o)

all:
	$(info For Windows use: $(MAKE) windows)
	$(info For Linux use: $(MAKE) linux)
	$(error Missing argument)

windows: compile cpuid_windows
	$(CXX) *.o -o cpuid-cli.exe $(CXXFLAGS)

linux: compile cpuid_linux
	$(CXX) *.o -o cpuid-cli $(CXXFLAGS)

compile: $(FILES_OBJ)

cpuid_windows:
	$(AS) cpuid_func_windows.S -o cpuid_func.o --64

cpuid_linux:
	$(AS) cpuid_func_linux.S -o cpuid_func.o --64

deps:
	$(CXX) -MM $(FILES) > Makefile.files

include Makefile.files
