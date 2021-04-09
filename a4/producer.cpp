#include "semaphore.h"
#include "production.h"

#define INCREMENT_TIMES_DEFAULT 50
#define DECREMENT_TIMES_DEFAULT 50

/* Types of operations threads can perform */
typedef enum
{
    INCREMENT,
    DECREMENT
} OPERATION;    

typedef struct
{
    char *Name;          /* Human readable name of operation */
    int CFBmade;
    int EESmade;
    int total;

    sem_t *MutexPtr; /* pointer to critical region semaphore */
    int *ValuePtr; /* pointer to shared data */
} PRODUCER;

void *escargot(void *parameter)
{
    PRODUCER *ees = (PRODUCER *)parameter;
    while(((ees->CFBmade) + (ees->EESmade)) < 100) {
        if(ees->CFBmade < 3) {
            sem_wait(ees->MutexPtr);
            ees->EESmade++;
        }
        // initial crunchy frog bites
        sem_post(ees->MutexPtr);
    }
    // make escargot things
}