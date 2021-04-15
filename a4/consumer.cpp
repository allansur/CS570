
#include "consumer.h"
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
using namespace std;

void * consumer(void * ptr)
{
    // needs casting to work
    struct FACTORY * factory = (struct FACTORY *) ptr;
	
	// type of of consumer
	sem_wait(&factory->type); // semaphore down
        ConsumerType worker;
        switch (factory->consumer)
        {
            case Lucy:
                //printf("Lucy tread started\n");
                worker = Lucy;
                factory->consumer = Ethel;
                break;
            case Ethel:
                //printf("Ethel tread started\n");
                worker = Ethel;
                factory->consumer = Lucy;
                break;
        }
    sem_post(&factory->type); // semaphore up

    // while production is still going on or there is candy in the belt
    while(factory->produced < factory->limit || factory->belt != NULL)
    {
        // remove candy from belt
		sem_wait(&factory->belt_access);

            // check to see if there is candy in the belt
            if(factory->belt_count == 0)
            {
                sem_post(&factory->belt_access);
                continue;
            }
        
            // remove candy from belt and reduce belt candy count
            ProductType candy = consume(worker, &factory->belt);
            factory->belt_count--;

            // print bealt update
            printupdate(factory->belt);
            
            string c = worker ? "Ethel" : "Lucy";
            string candies = worker ? "Escargot Suckers" : " Crunchy FrogBites";

            cout << c << " produced " << candies << "\n";

		sem_post(&factory->belt_access);

		// sleep consumption thread for N miliseconds
		if (factory->lucy && worker == Lucy)
			nanosleep(&factory->Lucy_N, NULL); // suspend execution of thread
		else if (factory->ethel && worker == Ethel)
			nanosleep(&factory->Ethel_N, NULL); // suspend execution of threads
	}
}