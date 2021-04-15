
#include "producer.h"
#include "consumer.h"

#include <unistd.h>     // needed for getopt and optind
#include <getopt.h>     // for linux compilation

/* time conversions */
#define NSPERMS     1000000 /* million ns/ms */
#define MSPERSEC    1000  /* thousand ms/s */

/*
 *  IMPORTANT:
 *  OPTIONAL ARGUMENTS LIKE -E -L -f -e
 *  MUST COME FIRST WHEN RUNNING THE EXE
 */

int main(int argc, char ** argv)
{
    // option arguments
    int Option; // option value index
    int Ethel_N = 0;
    int Lucy_N = 0;
    int CFB_N = 0;
    int EES_N = 0;
    bool E = false;
    bool L = false;
    bool f = false; 
    bool e = false;

    // getopt gets next argument option from argv and argc
    while ( (Option = getopt(argc, argv, "E:L:f:e:")) != -1)
    {
        switch (Option)
        {
            case 'E': /* Ethel consumer, N = number of miliseconds */
                E = true;
                Ethel_N = atoi(optarg);
                //printf("Ethel %d\n", Ethel_N);
                break;

            case 'L': /* Lucy consumer, N = number of miliseconds */
                L = true;
                Lucy_N = atoi(optarg);
                //printf("Lucy %d\n", Lucy_N);
                break;

            case 'f': /* CFB bite, N = number of miliseconds */
                f = true;
                CFB_N = atoi(optarg);
                //printf("CFB bites %d\n", CFB_N);
                break;
            
            case 'e': /* EES, N = number of miliseconds */
                e = true;
                EES_N = atoi(optarg);
                //printf("EES %d\n", EES_N);
                break;
        }
    }
    /*
        Requeremnt #4:
        Do not use global factoryiables to communicate information to your threads.
        Pass information through data structures.
    */
 
    /* these factoryiables are not global, so they will be used for threads */
    // FACTORYiable structure for threads
    struct FACTORY * factory = (FACTORY *)malloc(sizeof(struct FACTORY));

    factory->product = FrogBite; // CFB bytes = 0, EES = 1
	factory->consumer = Lucy; // Lucy = 0, Ethel = 1

    factory->produced = 0;
    factory->consumed = 0;
    factory->limit = 100;			    // produce 100 candies
	
    // bool factoryiables
    factory->ethel = E;
	factory->lucy = L;
	factory->CFB = f;
	factory->EES = e;
    factory->producing = true;

    // N miliseconds time conversion
    factory->Ethel_N.tv_sec = Ethel_N / MSPERSEC;               /* # secs */
    factory->Ethel_N.tv_nsec = (Ethel_N % MSPERSEC) * NSPERMS;  /* # nanosecs */

    factory->Lucy_N.tv_sec = Lucy_N / MSPERSEC;                 /* # secs */
    factory->Lucy_N.tv_nsec = (Lucy_N % MSPERSEC) * NSPERMS;    /* # nanosecs */

    factory->CFB_N.tv_sec = CFB_N / MSPERSEC;                 /* # secs */
    factory->CFB_N.tv_nsec = (CFB_N % MSPERSEC) * NSPERMS;    /* # nanosecs */

    factory->EES_N.tv_sec = EES_N / MSPERSEC;               /* # secs */
    factory->EES_N.tv_nsec = (EES_N % MSPERSEC) * NSPERMS;  /* # nanosecs */

    // belt (linked list) factoryiables
	factory->belt = NULL;    // FIFO link list should be started as null
    factory->belt_count = 0; // this is size of link list

    // initialize semaphores
    sem_init(&factory->belt_access, 0, 1);			// to get access to belt operations
	sem_init(&factory->type, 0, 1);				    // To set producer or consumer type

    // thread factoryiables
    pthread_t CFB_thread;
	pthread_t EES_thread;
	pthread_t Lucy_thread;
	pthread_t Ethel_thread;

    // thread creation
    pthread_create(&CFB_thread, NULL, producer, factory);
	pthread_create(&EES_thread, NULL, producer, factory);
	pthread_create(&Lucy_thread, NULL, consumer, factory);
	pthread_create(&Ethel_thread, NULL, consumer, factory);

    // proper thread finalization
    pthread_join(CFB_thread, NULL);
    pthread_join(EES_thread, NULL);
	pthread_join(Lucy_thread, NULL);
	pthread_join(Ethel_thread, NULL);

    // destroy semaphores	
    sem_destroy(&factory->belt_access);		
    sem_destroy(&factory->type);			
    
    // print final report
    printreport();
    return 0;
}