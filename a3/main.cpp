#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <map>
using namespace std;

int main(int argc, char **argv) {
    int idx;
    int Option;
    while ( (Option = getopt(argc, argv, "n:o:")) != -1){
        switch (Option) {
            case 'n':   //Number of addys to process
            //optarg will contain the string folliwng -n
            //Process appropriately (e.g. convert to integer atoi(optarg))
                break;
            case 'o': /*produce map of pages */
            //optarg contains the output method...
                break;
            default:
                //print something about the usage and die...
                exit(1); //BADFLAG is an error # defined in a header
        }
    }
    idx = optind;
    return 0;
}