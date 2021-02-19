/* 
Names: Allan Sur, Jason Songvilay
RedIDs: 821444631, 821071661
Edoras IDs: cssc3455, cssc3454
Course: CS530-03-Spring2021
Assignmt 2: Part II
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

typedef struct
{
    long *CurrentStatus;
    long InitialValue;
    long TerminationValue;
} PROGRESS_STATUS;

class WordCount
{
public:
    void *progress_monitor(void *);
    long wordcount(string filename);
    int main(int argc, char **argv);
};