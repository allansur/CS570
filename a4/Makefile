# Names: Allan Sur, Jason Songvilay
# RedIDs: 821444631, 821071661
# Edoras IDs: cssc3455, cssc3454
# Course: CS530-03-Spring2021
# Assignmt 4: Part II

CXX=g++

CXXFLAGS=-std=c++11 -g -pthread

mizzo : mizzo.o 
$(CXX) $(CXXFLAGS) -o mizzo $^

mizzo.o : producer.h producer.cpp main.cpp

clean :
	rm *.o wordcount