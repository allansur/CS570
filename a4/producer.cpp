#include "semaphore.h"
#include "production.h"
#include "belt.h"

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
    int *ValuePtr; /* pointer to shared data */
} PRODUCER;

void *escargot(void *parameter) // "b"
{
    BELT *belt = (BELT*) parameter;
    PRODUCER *ees = (PRODUCER *)parameter;
    while(belt -> total < 100) {
        belt ->buffer.push_back(1);
        cout << belt->buffer.size();
        // buffer[count] = x;
    }
    // make escargot things
}