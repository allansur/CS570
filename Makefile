# Names: Allan Sur, Jason Songvilay
# RedIDs: 821444631, 821071661
# Course: CS530-03-Spring2021
# Assignmt 1: Part II


CXX=g++

CXXFLAGS=-std=c++11 -g

myls : myls.o 
	$(CXX) $(CXXFLAGS) -o myls $^

myls.o : myls.h myls.cpp

clean :
	rm *.o myls

