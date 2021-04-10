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
    int CFBEaten;
    int EESEaten;

    sem_t *MutexPtr; /* pointer to critical region semaphore */
    int *ValuePtr; /* pointer to shared data */
} CONSUMER;

void *drake(void *parameter)
{
    CONSUMER *drake = (CONSUMER *)parameter;
}