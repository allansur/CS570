#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "byutr.h"
#include <map>
#include "pagetable.h"
using namespace std;

// int main(int argc, char **argv) {
//     int idx;
//     int Option;
//     while ( (Option = getopt(argc, argv, "n:o:")) != -1){
//         switch (Option) {
//             case 'n':   //Number of addys to process
//             //optarg will contain the string folliwng -n
//             //Process appropriately (e.g. convert to integer atoi(optarg))
//                 break;
//             case 'o': /*produce map of pages */
//             //optarg contains the output method...
//                 break;
//             default:
//                 //print something about the usage and die...
//                 exit(1); //BADFLAG is an error # defined in a header
//         }
//     }
//     idx = optind;
//     return 0;
// }

int PageInsert(PAGETABLE *PageTable, unsigned int LogicalAddress, unsigned int Frame) {
    if (PageTable->PageInsert(LogicalAddress, Frame)) {
        return 0;
    } else {
        return 1;
    }
}

int getFrame(PAGETABLE *PageTable, unsigned int LogicalAddress) {
    return PageTable->getFrame(LogicalAddress);
}

int getPhysicalAddr(PAGETABLE *PageTable, unsigned int LogicalAddress) {
    int frameNumber = getFrame(PageTable, LogicalAddress);
    int pageSize = PageTable->entryCount[PageTable->numOfLevels];
    int startingPhysicalLocation = frameNumber * pageSize;
    int bitMask = PageTable->bitmaskArr[PageTable->numOfLevels];
    int offset = LogicalAddress & bitMask;
    return startingPhysicalLocation + offset;
}

//Formats end of run output statistics
void printHelper(int size, int hits, int missess, unsigned int pageSize) {
    double total = hits + missess;
    cout << "Page table size: " << pageSize << endl;
    cout << "Hits " << hits << " (" << hits / total * 100;
    cout << "%), Misses " << missess << " (" << missess / total * 100 << "%) ";
    cout << "# Addressess " << total << endl;
    cout << "Bytes used: " << size << endl;
}

void tFlagHelper(PAGETABLE *PageTable, unsigned int logicalAddress, bool tFlag) {
    if (tFlag) {
        int physicalAddress = getPhysicalAddr(PageTable, logicalAddress);
        //Pad 8 bits for Hex and use Capital A-F
        printf("%08X -> %08X\n", logicalAddress, physicalAddress);
    }
}

void pFlagHelper(PAGETABLE *PageTable, string file, int addressSizeUsed, bool pFlag) {
    if (pFlag) {
        FILE *fp;
        if ((fp = fopen(file.c_str(), "w")) == nullptr) {
            fprintf(stderr, "Can not open %s for writing\n", file.c_str());
            exit(2);
        }
        // 1 << adressSizeUsed is equivalent to 2^(# bits not in offset)
        int maxPageNumber = 1 << addressSizeUsed;
        //Initialize all bool flags in array to 0
        bool *frameNumberOutputed = new bool[maxPageNumber];
        for (int i = 0; i < maxPageNumber; i++) {
            frameNumberOutputed[i] = false;
        }
        int offset = PageTable->shifters[PageTable->numOfLevels - 1];
        int frameNumber;
        int pageNumber;
        for (int i = 0; i < maxPageNumber; i++) {
            //Converts a Page Number to a Logical Address w/ offset = 0
            pageNumber = i << offset;
            frameNumber = PageTable->getFrame(pageNumber);
            //Only print valid frames once
            if (frameNumber != -1) {
                if (!frameNumberOutputed[frameNumber]) {
                    fprintf(fp, "%08X -> %08X\n", i, frameNumber);
                    frameNumberOutputed[frameNumber] = true;
                }
            }

        }
        delete[] frameNumberOutputed;
        fclose(fp);
    }
}

int main(int argc, char *argv[]) {
    //argv[0] is PageTable so argc will always start at 1
    int argumentCount = 1;
    bool nFlag = false;
    bool tFlag = false;
    bool pFlag = false;
    string inputFileName;
    string outputFileName;

    FILE *fp;
    int traceLimit = 0;
    p2AddrTr currentTrace;

    unsigned int hits = 0;
    unsigned int misses = 0;
    int option = 0;
    while ((option = getopt(argc, argv, "n:p:t")) != -1) {
        switch (option) {
            case 'n' :
                nFlag = true;
                traceLimit = atoi(optarg);
                argumentCount += 2;
                break;
            case 'p' :
                pFlag = true;
                outputFileName = string(optarg);
                argumentCount += 2;
                break;
            case 't' :
                tFlag = true;
                argumentCount++;
                break;
            default:
                break;
        }
    }
    inputFileName = argv[argumentCount++];
    int numOfLevels = argc - argumentCount;
    int pageTableSizes[numOfLevels];
    int addressSizeUsed = 0;
    for (int i = 0; argumentCount < argc; i++) {
        pageTableSizes[i] = atoi(argv[argumentCount++]);
        addressSizeUsed += pageTableSizes[i];
    }
    //Inputed address validation
    if (addressSizeUsed > 32) {
        fprintf(stderr, "Page Level Size(s) Exceed 32bit Address Size\n");
        exit(3);
    } else if (addressSizeUsed == 0) {
        fprintf(stderr, "Please specify Page Level Size(s)\n");
        exit(3);
    }
    PAGETABLE PageTable(numOfLevels, pageTableSizes);
    if ((fp = fopen(inputFileName.c_str(), "rb")) == nullptr) {
        fprintf(stderr, "Can not open %s for reading\n", inputFileName.c_str());
        exit(2);
    }
    while (!feof(fp)) {
        if (NextAddress(fp, &currentTrace)) {
            if (PageInsert(&PageTable, currentTrace.addr, misses)) {
                misses++;
            } else {
                hits++;
            }
            tFlagHelper(&PageTable, (unsigned int) currentTrace.addr, tFlag);
        }
        //End if nFlag limit is hit (misses + hits = addressesProcessed)
        if (traceLimit <= hits + misses && nFlag) {
            break;
        }
    }
    fclose(fp);

    pFlagHelper(&PageTable, outputFileName, addressSizeUsed, pFlag);

    unsigned pageSize = PageTable.entryCount[numOfLevels];
    printHelper(PageTable.sizeTotal(), hits, misses, pageSize);
}

