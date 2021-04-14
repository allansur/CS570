#ifndef PRODUCTION_H
#define PRODUCTION_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <time.h>      // needed to use nanosleep()
#include <pthread.h>   // needed to use pthreads
#include <semaphore.h> // needed to use semaphores

/*
 * Arrays with producer and consumer names
 * These can be indexed with the enumerated types below
 * and are defined in io.c
 */
extern const char *ProducerNames[];
extern const char *ProducerAbbrevs[];
extern const char *ConsumerNames[];

/*
 * Enumerated types to be used by the producers and consumers
 * These are expected in the input/output functions (io.h)
 * should be useful in your producer and consumer code.
 */

/*
 * Each producer only produces one type of product,
 * so ProductType is synomonous with the producer type
 */
typedef enum Products
{
  FrogBite = 0,     // Crunch frog bites, my favorite!
  Escargot = 1,     // Escargot suckers, slimy yet satisfying...
  ProductTypeN = 2, // Number of products
} ProductType;

typedef enum Consumers
{
  Lucy = 0,
  Ethel = 1,
  ConsumerTypeN = 2, // Number of consumers
} ConsumerType;

// this enables us to say Link instead of struct node *
typedef struct node *Link; // Link is pointer type

typedef struct node
{
  ProductType candy_type;
  Link next;
};

typedef struct FACTORY
{
  // semaphores
  sem_t belt_access; // only one tread can have access to belt push or pop
  sem_t type;        // configuratoin for production or consumption

  ProductType product_id;   // frog bytes = 0, escargot = 1
  ConsumerType consumer_id; // Lucy = 0, Ethel = 1

  int total_produced;   // total candies produced so far
  int total_consumed;   // total candies consumed so far


  // flag variables
  bool producing;
  bool Ethel;
  bool Lucy;
  bool frog;
  bool escar;

  // N sleep time values
  struct timespec Ethel_N;
  struct timespec Lucy_N;
  struct timespec frog_N;
  struct timespec escar_N;

  Link belt;      // belt in the head of linked list
  int belt_count; // amount of candy currently in belt
} FACTORY;

#endif
