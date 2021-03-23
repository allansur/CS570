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

int main(int argc, char **argv)
{
    PAGETABLE *pt = new PAGETABLE;
    LEVEL *lv = new LEVEL;

    int idx;
    int Option;
    int numberOfAddresses;
    char* mode;
    while ((Option = getopt(argc, argv, "n:o:")) != -1)
    {
        switch (Option)
        {
        case 'n': //Number of addys to process
            //optarg will contain the string folliwng -n
            //Process appropriately (e.g. convert to integer atoi(optarg))
            numberOfAddresses = atoi(optarg);
            break;
        case 'o': /*produce different outputs */
            //optarg contains the output method...
            mode = optarg;
            switch (mode) {
                case 'bitmasks':
                    break;
                case 'logical2physical':
                    break;
                case 'page2frame':
                    break;
                case: 'offset':
                    break;
                case: 'summary':
                    break;
                default:
                    break;
            }
            break;
        default:
            //print something about the usage and die...
            cout << "Does not exist";
            exit(1); //BADFLAG is an error # defined in a header
        }
    }
    // idx = optind;
    // char *traceF = argv[idx];
    // int bits = 20;

    // int levelCount = 5;
    // pt->rootPtr = lv;
    // pt->numOfLevels = levelCount;
    // cout << "numOfLevels: " << pt->numOfLevels << "\n";

    // pt->bitMaskArr = new unsigned int[levelCount];
    // pt->shifters = new unsigned int[levelCount];
    // pt->entryCount = new unsigned int[levelCount];
    // cout << "bitmaskArr: " << pt->bitMaskArr << "\n";
    // cout << pt->bitMaskArr[0] << "\n";
    // cout << "l2a: " << std::hex << LogicalToPage(0x3c654321, 0x0FC00000, 22) << "\n"; // 0x31 aka decimal 49

    // cout << "bitmask: " << calcBitmask(20, 8) << "\n";
    // cout << "creation: " << createPageTable(pt, 1, bits) << "\n";
    // cout << "get before"
    //      << "\n";
    // cout << pt->frameCount << "\n";
    // PageInsert(pt, 0x3c654321, pt->frameCount);
    // PageInsert(pt, 0x3c654322, pt->frameCount);
    // PageInsert(pt, 0x3c654323, pt->frameCount);
    // PageInsert(pt, 0x3c654324, pt->frameCount);
    // PageInsert(pt, 0x3c654325, pt->frameCount);
    // PageInsert(pt, 0x3c654326, pt->frameCount);
    // PageInsert(pt, 0x3c654327, pt->frameCount);
    // cout << pt->frameCount << "\n";
    // cout << "PageLookup: " << PageLookup(pt, 0x3c654322) << endl;
    // // cout << map << endl;
    // cout << pt << "\n";
    // // testing out functions

    // return 0;
}