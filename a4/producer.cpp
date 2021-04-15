

#include "producer.h"

void * producer(void * ptr)
{
    // needs casting to work
    struct FACTORY * factory = (struct FACTORY *) ptr;
	
	// type of candy to produce
	sem_wait(&factory->type); // semaphore down
        int candy;
        // frog bytes = 0, Escargot = 1
        switch (factory->product)
        {
            case FrogBite:
                //printf("frog bite tread started\n");
                candy = FrogBite;
                factory->product = Escargot;
                break;
            case Escargot:
                //printf("Escargot tread started\n");
                candy = Escargot;
                factory->product = FrogBite;
                break;
        }
    sem_post(&factory->type); // semaphore up

    // while total produced is less than limit 100
    while(factory->produced < factory->limit)
    {
        // add candy type to belt
		sem_wait(&factory->belt_access);

            //checck if belt is full
            if(factory->belt_count >= 10)
            {
                sem_post(&factory->belt_access);
                continue;
            }

            // if frog bite, check for less than 3 frog bite
            if (candy == FrogBite && candycount(FrogBite, factory->belt) >= 3)
            {
                sem_post(&factory->belt_access);
                continue;
            }

            // update total produced and belt count
            factory->produced++;
            factory->belt_count++;
                
            //printf("pB2\n");
            // print bealt update
            produce((ProductType) candy, &factory->belt);// Add candy to belt
            printupdate(factory->belt);
            printf("added %s.\n", candy ? "Escargot sucker": "crunchy frog bite");

		sem_post(&factory->belt_access);

		// sleep production thread for N miliseconds
		if (factory->CFB && candy == FrogBite)
			nanosleep(&factory->CFB_N, NULL); // suspend execution of thread
		else if (factory->EES && candy == Escargot)
			nanosleep(&factory->EES_N, NULL); // suspend execution of thread
	}
}