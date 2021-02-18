#include <stdio.h>
#include <pthread.h>
#include <string>

using namespace std;
typedef struct {
    long *CurrentStatus;
    long InitialValue;
    long TerminationValue;
} PROGRESS_STATUS;

int main(int argc, char **argv){
    PROGRESS_STATUS ps;
    ps = {0, 0, 0};






    return 0;
}

int wordCount(string filename){
    int wc = 0;
    //File is opened, words are counted based on whitespace
    //return word count
    return wc;
}

void * progress_monitor(void *) {
    //Read progress in bytes

}
