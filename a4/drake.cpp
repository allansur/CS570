#include "drake.h"
#include "production.h"

void *consumer(void *parameter)
{
	// needs casting to work
	struct FACTORY *factory = (struct FACTORY *)parameter;

	// type of of consumer
	sem_wait(&factory->type); // semaphore down
	int ConsumerType = Lucy;
	factory->consumer_id = Ethel;
	sem_post(&factory->type); // semaphore up

	// while production is still going on or there is candy in the belt
	while (factory->total_produced < 100 || factory->belt != NULL)
	{
		// remove candy from belt
		sem_wait(&factory->belt_access);

		// check to see if there is candy in the belt
		if (factory->belt_count == 0)
		{
			sem_post(&factory->belt_access);
			continue;
		}

		// remove candy from belt and reduce belt candy count
		// ProductType candy_type = consume(ConsumerType, &factory->belt);
		factory->belt_count--;

		// print bealt update
		// printupdate(factory->belt);
		// printf("%s consumed %s.\n",
		//     ConsumerType ? "Ethel": "Lucy",
		//     candy_type ? "escargot sucker": "crunchy frog bite");

		sem_post(&factory->belt_access);

		// sleep consumption thread for N miliseconds
		if (factory->Lucy && ConsumerType == Lucy)
			nanosleep(&factory->Lucy_N, NULL); // suspend execution of thread
		else if (factory->Ethel && ConsumerType == Ethel)
			nanosleep(&factory->Ethel_N, NULL); // suspend execution of threads
	}
}