# The following just specifies some variables for "flexibility".

# Specify the C++ compiler
CXX     = g++

# Specify options to pass to the compiler. Here it sets the optimisation
# level, outputs debugging info for gdb, and C++ version to use.
CXXFLAGS = -O0 -g3 -std=c++17

# This is a slightly more involved example: suppose you have a class
# in files Alloc.h and Alloc.cpp, and two further files GenAlloc.cpp
# and CheckAlloc.cpp that uses this class. This makefile will produce
# the two required executables.

All: all
all: GenAlloc CheckAlloc

GenAlloc: GenAlloc.cpp AllocationSystem.o
	$(CXX) $(CXXFLAGS) GenAlloc.cpp AllocationSystem.o -o GenAlloc

CheckAlloc: CheckAlloc.cpp AllocationSystem.o
	$(CXX) $(CXXFLAGS) CheckAlloc.cpp AllocationSystem.o -o CheckAlloc

AllocationSystem.o: AllocationSystem.cpp AllocationSystem.h
	$(CXX) $(CXXFLAGS) -c AllocationSystem.cpp -o AllocationSystem.o

# Some cleanup functions, invoked by typing "make clean" or "make deepclean"
deepclean:
	rm -f *~ *.o GenAlloc CheckAlloc *.stackdump

clean:
	rm -f *~ *.o *.stackdump
