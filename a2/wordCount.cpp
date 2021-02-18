#include <stdio.h>
#include <pthread.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

typedef struct {
    long *CurrentStatus;
    long InitialValue;
    long TerminationValue;
} PROGRESS_STATUS;

int main(int argc, char **argv){
    string filename;
    if (argc < 2) {
        cout << "No file was input, proper usage: ./wordcount 'filename' " << endl;
        exit(1);
    }
    else if (argc == 2){
        
        filename = argv[2];
        if (argv.subtr(argv[2].find_last_of("."),argv[2].length() -1) == ".txt"){
            filename = argv[2];
            wordCount(filename);
        }
        

    }
    PROGRESS_STATUS ps;
    ps = {0, 0, 0};
    //Do all thread stuff

    wordCount(filename);
    //Get file bit count by using fstat





    return 0;
}

long wordCount(string filename){
    int wc = 0;
    //Open the file here
    //File is opened, words are counted based on whitespace
    //return word count
    return wc;

}

void * progress_monitor(void *) {
    //Read progress in bytes

}
