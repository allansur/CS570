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

// typedef struct
// {
//     bool isLeafNode;
//     void *pageTablePtr;
//     int depth;
//     void **nextLevelPtr;
//     struct PAGETABLE *PageTable;
//     struct LEVEL **nextLevel;
//     struct MAP *map;

// } LEVEL;

// typedef struct
// {
//     bool flagIndex;
//     int frameIndex;
// } MAP;

// typedef struct
// {
//     struct LEVEL *rootPtr;
//     unsigned int numOfLevels;
//     unsigned int numberOfBits; //size = numOfLevels
//     unsigned int *bitMaskArr;  //size = numOfLevels
//     unsigned int *shifters;
//     unsigned int *entryCount; // size = level
//     void *rootPtr;
// } PAGETABLE;

typedef struct PAGETABLE {
    struct LEVEL *rootPtr;
    int numOfLevels;
    int frameCount;
    int hits;
    int misses;
    unsigned int *bitMaskArr;
    unsigned int *shifters;
    unsigned int *entryCount;
} PAGETABLE;

typedef struct MAP {        //leaf node structre
    bool flagIndex;
    unsigned int frameIndex;
} MAP;

typedef struct LEVEL {      //interior level structure
    bool isLeafNode;
    struct PAGETABLE *pageTablePtr;
    struct LEVEL **nextLevelPtr;
    struct MAP *map;
    int depth;
} LEVEL;

unsigned int LogicalToPage(unsigned int LogicalAddress, unsigned int Mask, unsigned int Shift);
unsigned int calcBitmask(int start, int length);
void PageInsert(PAGETABLE *PageTable, unsigned int LogicalAddress, unsigned int Frame);
MAP *PageLookup(PAGETABLE *PageTable, unsigned int LogicalAddress);
int createPageTable(PAGETABLE *PageTable, unsigned int numOfLevels, int *numOfBits);