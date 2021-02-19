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

typedef struct {
    long *CurrentStatus;
    long InitialValue;
    long TerminationValue;
} PROGRESS_STATUS;

void * progress_monitor(void *) {
    //Read progress in bytes

}

long wordcount(string filename){
    // initialize count, struct to hold amount of bytes, and open file
    int wc = 0;
    struct stat stats;
    char const* charFileName = filename.c_str();
    ifstream myfile;
    myfile.open(charFileName);

    // allocate memory for PROGRESS_STATUS struct and calculate total bytes
    // AKA total characters
    // initialize PROGRESS_STATUS struct values
    PROGRESS_STATUS *prog_stat = (PROGRESS_STATUS*) malloc(sizeof(prog_stat)); 
    prog_stat->InitialValue = 0;
    prog_stat->CurrentStatus = 0;
    stat(charFileName, &stats);
    prog_stat->TerminationValue = stats.st_size;
    cout << "bytes: " << prog_stat->TerminationValue << "\n";

    // create threads for progress_monitor
    pthread_t mainThread;
    pthread_create(&mainThread, NULL, progress_monitor, (void *)prog_stat);

    // start pointer to read file character by character until false
    // if the current character is a space and the previous character is
    // not a space, then a word has been found, increment word count
    char ptr;
    char prevPtr;
    while(myfile.get(ptr)){
        if(isspace(ptr) && !isspace(prevPtr)){
            wc++;
        }
        prevPtr = ptr;
        prog_stat->CurrentStatus++;
    }
 
    // join main thread for progress bar progress
    pthread_join(mainThread, NULL);

    // close file
    myfile.close();

    // display word count in opened file
    cout << "There are " << wc << " words in " << filename << ".\n";

    //return word count
    return wc;

}

int main(int argc, char **argv){
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

