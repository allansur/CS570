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
#include <sstream>

using namespace std;


extern "C" void * progress_monitor(void* parameter);

typedef struct {
    long *CurrentStatus;
    long InitialValue;
    long TerminationValue;
} PROGRESS_STATUS;

void* progress_monitor(void* parameter) {
    PROGRESS_STATUS *stuff = (PROGRESS_STATUS *) parameter;
    int count = 0;
    long pDiff = 0;
    int holder = 0;
   
   // while there are less than 50 characters on the screen
    while(count < 50) { 
        // percent = (*CurrentStatus - InitialValue) / TerminationValue
        pDiff = ((*stuff->CurrentStatus)-(stuff->InitialValue)) / (stuff->TerminationValue);
        // amount of characters = percent * 50
        holder = (int) (pDiff * 50);

        // while current progress not printed yet
        while(count < holder) {
            if(count != 0 && (count+1) % 10 == 0) { 
                cout << "+" << flush; // + for every "count = 9+1 = 10th" character
            } else { 
                cout << "-" << flush; // - for everything else
            }
            count++;
            usleep(5000);   // delay printing?
        }
    }
    pthread_exit(0);
    return NULL;
}


long wordcount(string filename) {
    // initialize count, struct to hold amount of bytes, and open file
    int wc = 0;
    long index = 0;
    struct stat stats;
    char const* charFileName = filename.c_str();
    ifstream myfile;
    myfile.open(charFileName);

    // allocate memory for PROGRESS_STATUS struct and calculate total bytes
    // AKA total characters
    // initialize PROGRESS_STATUS struct values
    PROGRESS_STATUS prog_stat = *(PROGRESS_STATUS*) malloc(sizeof(prog_stat)); 
    prog_stat.InitialValue = 0;
    prog_stat.CurrentStatus = &index;
    stat(charFileName, &stats);
    prog_stat.TerminationValue = stats.st_size;
    //cout << "bytes: " << prog_stat.TerminationValue << "\n";

    // create threads for progress_monitor
    pthread_t mainThread;
    pthread_create(&mainThread, NULL, progress_monitor, (void *) &prog_stat);
  
    char ptr;
    char prevPtr;
    while(myfile.get(ptr)){
        if(isspace(ptr) && !isspace(prevPtr)){
            wc++;
        }
        prevPtr = ptr;
        (*prog_stat.CurrentStatus)++;
    }

    // close file
    myfile.close();

    // join main thread for progress bar progress
    pthread_join(mainThread, NULL);

    // display word count in opened file
    cout << endl << "\nThere are " << wc << " words in " << filename << ".\n";

    //return word count
    return wc;

}

int main(int argc, char **argv) {
    string filename;
    if (argc < 2 || argc > 2) {
        if (argc < 2) {
            cout << "No file was input, proper usage: ./wordcount 'filename'" << endl;
            exit(1);
        }
        else {
            cout << "Too many arguments were passed, proper usage: ./wordcount 'filename'" << endl;
            exit(1);
        }
    }
    else if (argc == 2){
        filename = argv[1];
        int found = filename.find_last_of(".");
        if (filename.substr(found, filename.length() - 1) == ".txt"){
            wordcount(filename);
            
        }
        

    }
    //Do all thread stuff
    //Get file bit count by using fstat
    return 0;
}

