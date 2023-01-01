# The following just specifies some variables for "flexibility".

# Specify the C++ compiler
CXX     = g++

# Specify options to pass to the compiler. Here it sets the optimisation
# level, outputs debugging info for gdb, and C++ version to use.
CXXFLAGS = -O0 -g3 -std=c++17

All: all
all: main GenAlloc

main: main.cpp ProjectAllocationSystem.o
	$(CXX) $(CXXFLAGS) main.cpp ProjectAllocationSystem.o -o main

# The -c command produces the object file
ProjectAllocationSystem.o: ProjectAllocationSystem.cpp ProjectAllocationSystem.h
	$(CXX) $(CXXFLAGS) -c ProjectAllocationSystem.cpp -o ProjectAllocationSystem.o

GenAlloc: GenAlloc.cpp GenAlloc.h ProjectAllocationSystem.o
	$(CXX) $(CXXFLAGS) GenAlloc.cpp ProjectAllocationSystem.o -o GenAlloc

# Some cleanup functions, invoked by typing "make clean" or "make deepclean"
deepclean:
	rm -f *~ *.o GenAlloc main main.exe *.stackdump

clean:
	rm -f *~ *.o *.stackdump
