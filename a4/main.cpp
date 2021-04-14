#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "semaphore.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <map>
#include <vector>
#include <cmath>
#include "production.h"
#include "drake.h"
using namespace std;

int main(int argc, char ** argv)
{
    // option arguments
    int Option; // option value index
    int Ethel_N = 0;
    int Lucy_N = 0;
    int frog_N = 0;
    int escar_N = 0;
    bool E = false;
    bool L = false;
    bool f = false; 
    bool e = false;

    // getopt gets next argument option from argv and argc
    // while ( (Option = getopt(argc, argv, "E:L:f:e:")) != -1)
    // {
    //     switch (Option)
    //     {
    //         case 'E': /* Ethel consumer, N = number of miliseconds */
    //             E = true;
    //             Ethel_N = atoi(optarg);
    //             //printf("Ethel %d\n", Ethel_N);
    //             break;

    //         case 'L': /* Lucy consumer, N = number of miliseconds */
    //             L = true;
    //             Lucy_N = atoi(optarg);
    //             //printf("Lucy %d\n", Lucy_N);
    //             break;

    //         case 'f': /* frog bite, N = number of miliseconds */
    //             f = true;
    //             frog_N = atoi(optarg);
    //             //printf("frog bites %d\n", frog_N);
    //             break;
            
    //         case 'e': /* escargot, N = number of miliseconds */
    //             e = true;
    //             escar_N = atoi(optarg);
    //             //printf("escargot %d\n", escar_N);
    //             break;
    //     }
    // }
    /*
        Requeremnt #4:
        Do not use global variables to communicate information to your threads.
        Pass information through data structures.
    */
    // initialize gloval variables, these variables do not pass information to threads
 

    /* these variables are not global, so they will be used for threads */
    // FACTORYiable structure for threads
    struct FACTORY *var = (FACTORY*)malloc(sizeof(struct FACTORY));

    var->product_id = FrogBite; // frog bytes = 0, escargot = 1
	var->consumer_id = Lucy; // Lucy = 0, Ethel = 1

    var->total_produced = 0;
    var->total_consumed = 0;
   
	
    // bool variables

	var->Lucy = L;

    var->producing = true;


    // belt (linked list) variables
	var->belt = NULL;    // FIFO link list should be started as null
    var->belt_count = 0; // this is size of link list

    // initialize semaphores
    sem_init(&var->belt_access, 0, 1);			// to get access to belt operations
	sem_init(&var->type, 0, 1);				    // To set producer or consumer type

    // thread variables
	pthread_t lucy_thread;


    // thread creation
	pthread_create(&lucy_thread, NULL, consumer, (void *) &var);
	cout << "lucy thread created: " << lucy_thread << endl;
	

    // proper thread finalization
	pthread_join(lucy_thread, NULL);

    // destroy semaphores	
    // sem_destroy(&var->belt_access);		
    // sem_destroy(&var->type);			
    
    // print final report
    // printreport();
    return 0;
}