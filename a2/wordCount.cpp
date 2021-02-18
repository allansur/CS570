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


long wordCount(string filename){
    int wc = 0;
    ofstream myfile;
    myfile.open(filename);


    myfile.close();
    //Open the file here
    //File is opened, words are counted based on whitespace
    //return word count
    return wc;

}

void * progress_monitor(void *) {
    //Read progress in bytes

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
            wordCount(filename);
        }
        

    }
    //Do all thread stuff
    wordCount(filename);
    //Get file bit count by using fstat
    return 0;
}

