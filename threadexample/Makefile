# Names: Allan Sur, Jason Songvilay
# RedIDs: 821444631, 821071661
# Edoras IDs: cssc3455, cssc3454
# Course: CS530-03-Spring2021
# Assignmt 2: Part II

CXX=g++
CXXFLAGS=-std=c++11 -g -pthread 


semaphore_demo : semaphore_demo.o 
	gcc -o semaphore_demo semaphore_demo.c -lpthread -lrt

semaphore_demo.o : semaphore_demo.c

clean :
	rm *.o wordcount