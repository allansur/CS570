
#ifndef MYSTRUCT_H
#define MYSTRUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <time.h>       // needed to use nanosleep()
#include <pthread.h>    // needed to use pthreads
#include <semaphore.h>  // needed to use semaphores



// this enables us to say Link instead of struct node *

typedef enum Products {
  FrogBite = 0,   // Crunch frog bites, my favorite!
  Escargot = 1,  // Escargot suckers, slimy yet satisfying...
  ProductTypeN = 2,   // Number of products
} ProductType;

typedef enum Consumers {
  Lucy = 0,
  Ethel = 1,
  ConsumerTypeN = 2,   // Number of consumers
} ConsumerType;

typedef struct node * Link; // Link is pointer type

struct node{
    ProductType candy;
    Link next;
};

struct FACTORY
{
    // semaphores
    sem_t belt_access; // only one tread can have access to belt push or pop
    sem_t type; // configuratoin for production or consumption

    ProductType product; // CFB bytes = 0, EESgot = 1
	ConsumerType consumer; // Lucy = 0, Ethel = 1

    int produced; // total candies produced so far
    int consumed; // total candies consumed so far
    int limit; // 100 candies

    // flag variables
    bool producing;
	bool ethel;
    bool lucy;
    bool CFB;
    bool EES;

    // N sleep time values
	struct timespec Ethel_N;
    struct timespec Lucy_N;
    struct timespec CFB_N;
    struct timespec EES_N;
    
    Link belt; // belt in the head of linked list
    int belt_count; // amount of candy currently in belt
};

#endif 