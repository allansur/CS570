
#include "consumer.h"

void * consumer(void * ptr)
{
    // needs casting to work
    struct multivar * var = (struct multivar *) ptr;
	
	// type of of consumer
	sem_wait(&var->type); // semaphore down
        int consumer_type;
        switch (var->consumer_id)
        {
            case Lucy:
                //printf("Lucy tread started\n");
                consumer_type = Lucy;
                var->consumer_id = Ethel;
                break;
            case Ethel:
                //printf("Ethel tread started\n");
                consumer_type = Ethel;
                var->consumer_id = Lucy;
                break;
        }
    sem_post(&var->type); // semaphore up

    // while production is still going on or there is candy in the belt
    while(var->total_produced < var->production_limit || var->belt != NULL)
    {
        // remove candy from belt
		sem_wait(&var->belt_access);

            // check to see if there is candy in the belt
            if(var->belt_count == 0)
            {
                sem_post(&var->belt_access);
                continue;
            }
        
            // remove candy from belt and reduce belt candy count
            producer_type candy_type = consume(consumer_type, &var->belt);
            var->belt_count--;

            // print bealt update
            printupdate(var->belt);
            printf("%s consumed %s.\n",
                consumer_type ? "Ethel": "Lucy",
                candy_type ? "escargot sucker": "crunchy frog bite");

		sem_post(&var->belt_access);

		// sleep consumption thread for N miliseconds
		if (var->Lucy && consumer_type == Lucy)
			nanosleep(&var->Lucy_N, NULL); // suspend execution of thread
		else if (var->Ethel && consumer_type == Ethel)
			nanosleep(&var->Ethel_N, NULL); // suspend execution of threads
	}
}