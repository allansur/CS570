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

extern "C" void * progress_monitor(void* parameter);

typedef struct {
    long *CurrentStatus;
    long InitialValue;
    long TerminationValue;
} PROGRESS_STATUS;

void* progress_monitor(void* parameter) {
    PROGRESS_STATUS *prog_stat = (PROGRESS_STATUS *) parameter;
    int count = 0; // printed characters
    int holder = 0; // hold 50 characters to be printed
    int exI = ((int)40/50);
    long exL = ((long)40/50);
    double exD = ((double)40/50);
    // cout << "int: " << exI << endl;
    // cout << "long: " << exL << " (same as an int)" << endl;
    // cout << "double: " << exD << endl;
   
   // while there are less than 50 characters on the screen
    while(count < 50) { 
        // amount of characters = int (double (*CurrentStatus - InitialValue) / TerminationValue * 50)
        // ^cast to double bc long does not hold decimal values for percentages
        // int ((40 current val - 0 initial val / termination value) * 50 characters)
         holder = (int)((double)((*prog_stat->CurrentStatus)-(prog_stat->InitialValue)) / (prog_stat->TerminationValue)*50);
         while(count < holder) {
             if(count % 10 == 0) { 
               cout << "+" << flush; // + for every 10,20,30,40th character
             } else if(count == 49){
               cout << "+" << flush; // + when count reaches the 2nd to last character
             } else { 
               cout << "-" << flush; // - for everything else
             }
            count++;
            // cout << "Count: " << count << endl;
            // cout << "Percent as Double (CurrentStatus - InitialValue) / TerminationValue: " << (double)((*prog_stat->CurrentStatus)-(prog_stat->InitialValue)) / (prog_stat->TerminationValue) << endl;
            // cout << "Percent as Long (CurrentStatus - InitialValue) / TerminationValue: " << (long)((*prog_stat->CurrentStatus)-(prog_stat->InitialValue)) / (prog_stat->TerminationValue) << endl;
            // cout << "Holder: " << holder << endl;
        }
    }
    pthread_exit(0);
    return NULL;
}

long wordcount(string filename) {
    // initialize count, index, and struct to hold amount of bytes
    int wordCount = 0;
    long index = 0;
    struct stat stats;

    // open file, print error if file not found
    char const* charFileName = filename.c_str();
    ifstream myfile(charFileName);
    if(!myfile.is_open()) {
         cout << "Couldnt open" << charFileName << ", file not found" << endl;
         exit(1);
    }
    // allocate memory for PROGRESS_STATUS struct and calculate total bytes
    // AKA total characters
    // initialize prog_stat struct values, set pointer to index for thread
    PROGRESS_STATUS prog_stat = *(PROGRESS_STATUS*) malloc(sizeof(prog_stat)); 
    prog_stat.InitialValue = 0;
    prog_stat.CurrentStatus = &index;
    stat(charFileName, &stats); // calculate total bytes of file
    prog_stat.TerminationValue = stats.st_size;

    // create thread for progress_monitor functiom
    pthread_t mainThread;
    pthread_create(&mainThread, NULL, progress_monitor, (void *) &prog_stat);

    // go character by character and count spaces
    // if previous spot is not a space and next spot is, increase word count
    // increase (*prog_stat.CurrentStatus) for thread progress for each character read
    char ptr;
    char prevPtr;
    while(myfile.get(ptr)) {
        if(!isspace(prevPtr) && isspace(ptr)){
            wordCount++;
        }
        prevPtr = ptr;
        (*prog_stat.CurrentStatus)++;
    }

    // close file
    myfile.close();

    // join main thread for progress bar progress
    pthread_join(mainThread, NULL);

    // display word count in opened file
    cout << endl << "\nThere are " << wordCount << " words in " << filename << ".\n";

    //return word count
    return wordCount;
}

int main(int argc, char **argv) {
    string filename;
    if ((argc < 2 || argc > 2)) {
        if (argc < 2) {
            cout << "No file was input, proper usage: ./wordcount 'filename'" << endl;
            exit(1);
        }
        else {
            cout << "Too many arguments were passed, proper usage: ./wordcount 'filename'" << endl;
            exit(1);
        }
    } else if (argc == 2){
        filename = argv[1];
        int found = filename.find_last_of(".");
        if (filename.substr(found, filename.length() - 1) == ".txt"){
            wordcount(filename);
        }
    } else {
        cout << "File not found!" << endl;
        exit(1);
    }
    //Do all thread prog_stat
    //Get file bit count by using fstat
    return 0;
}

