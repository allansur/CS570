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
#include <time.h>
#include <vector>
using namespace std;
#define CFB 1;
#define EES 2;
sem_t semEmpty;
sem_t semFull;
    
int main(int argc, char **argv)
{
    
    int Option;
    int idx;
    int numberOfCandies;
   
    pthread_mutex_t mutexBuffer;
    pthread_t threads[2];

    BELT *b = new BELT();
    b -> curr_CFB = 0;
    b -> curr_EES = 0;
    b -> total = 0;

    sem_init(&semEmpty, 0, 10);
    sem_init(&semFull, 0, 0);

    for (int i = 0; i < 2; i++){
        if (pthread_create(&th[i], NULL, &drake, b) != 0) {
            perror("Thread was not created");
        }
        else {
            if (pthread_create(&th[i], NULL, &escargot, b) != 0){
                perrror("Thread was not created");
            }
        }
    }

    sem_destroy(&semEmpty);
    sem_destroy(&semFull);
    pthread_mutex_destroy(&mutexBuffer);

    // while ((Option = getopt(argc, argv, "E:L:f:e")) != -1)
    // {
    //     //Check if either (n || o) || (n && o) is input into the command line
    //     switch (Option)
    //     {
    //         if (optarg)
    //         {
    //             // rSum = true;
    //         }
    //     case 'E':
    //          numberOfCandies = atoi(optarg);
    //     case 'L':
    //          numberOfCandies = atoi(optarg); 
    //     case 'f':
    //          numberOfCandies = atoi(optarg);
    //     case 'e':
    //          numberOfCandies = atoi(optarg);
    //     default:
    //         //print something about the usage and die...
    //         cout << "Does not exist" << endl;
    //         exit(0);
    //         break;
    //     }
    // }
    // //Retrieve the file path from commandline
    // idx = optind;

    
}