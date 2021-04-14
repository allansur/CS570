#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <time.h>       // needed to use nanosleep()
#include <pthread.h>    // needed to use pthreads
#include <semaphore.h>  // needed to use semaphores

void *consumer(void * ptr);
