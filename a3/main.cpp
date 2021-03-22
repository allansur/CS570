#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <map>
#include "pagetable.h"
#include "byutr.h"
using namespace std;

int main(int argc, char **argv) {
    PAGETABLE *pt = new PAGETABLE;
    LEVEL *lv = new LEVEL;

    int idx;
    int Option;
    int numberOfAddresses;
    char *mode;
    while ( (Option = getopt(argc, argv, "n:o:")) != -1){
        switch (Option) {
            case 'n':   //Number of addys to process
            //optarg will contain the string folliwng -n
            //Process appropriately (e.g. convert to integer atoi(optarg))
            numberOfAddresses = atoi(optarg);
                break;
            case 'o': /*produce map of pages */
            //optarg contains the output method...
            mode = optarg;
                break;
            default:
                //print something about the usage and die...
                cout << "Does not exist";
                exit(1); //BADFLAG is an error # defined in a header
        }
    }
    idx = optind;
    char *traceF = argv[idx];

    int levelCount = 5;
    pt->rootPtr = lv;
    pt->numOfLevels = levelCount;
    pt->bitMaskArr = new unsigned int[levelCount];
    pt->shifters = new unsigned int[levelCount];
    pt->entryCount = new unsigned int[levelCount];
    cout << calcBitmask(10, 10) << "\n";
    PageInsert(pt, 0x0041F760, 1);
    cout << pt;
    // testing out functions
   


    return 0;
    
}