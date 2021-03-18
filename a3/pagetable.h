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

class PageTable
{
unsigned int LogicalToPage(unsigned int LogicalAddress, unsigned int Mask, unsigned int Shift);
// void PageInsert(PAGETABLE *PageTable, unsigned int LogicalAddress, unsigned int Frame);
// MAP * PageLookup(PAGETABLE *PageTable, unsigned int LogicalAddress);
};

typedef struct LEVEL 
{
    int depthOfLevel;
    PAGETABLE *pageTable;
    LEVEL *NextLevelPtr;
    
};

typedef struct MAP 
{
    bool flagIndex;
    int frameIndex;
};

typedef struct PAGETABLE
{
    unsigned int numBitsAddy;
    int numOfLevels;
    int numberOfBits; //size = numOfLevels
    int bitMask[0] = {}; //size = numOfLevels
    int shifters[] = {};
    int entryCount[0] = {}; // size = level
    int *rootPtr;
};

