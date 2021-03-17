# Names: Allan Sur, Jason Songvilay
# RedIDs: 821444631, 821071661
# Edoras IDs: cssc3455, cssc3454
# Course: CS530-03-Spring2021
# Assignmt 2: Part II

CXX=g++

CXXFLAGS=-std=c++11 -g

pagetable : pagetable.o 
	$(CXX) $(CXXFLAGS) -o pagetable $^

pagetable.o : pagetable.h pagetable.cpp

clean :
	rm *.o pagetable