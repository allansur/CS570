#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cmath>
#include <map>
#include <vector>
using namespace std;

typedef struct PAGETABLE {
    struct LEVEL *rootPtr;
    unsigned int *bitMaskArr;
    unsigned int *shifters;
    unsigned int *entryCount;
    int numOfLevels;
    int frameCount;
    int hits;
    int misses;
} PAGETABLE;

typedef struct LEVEL {     
    struct PAGETABLE *pageTablePtr;
    struct LEVEL **nextLevelPtr;
    struct MAP *map;
    bool isLeafNode;
    int depth;
} LEVEL;

typedef struct MAP {  
    bool flagIndex;
    unsigned int frameIndex;
} MAP;

unsigned int LogicalToPage(unsigned int LogicalAddress, unsigned int Mask, unsigned int Shift);
unsigned int createBitMask(int pos, int length);
void PageInsert(PAGETABLE *PageTable, unsigned int LogicalAddress, unsigned int Frame);
void PageInsert(LEVEL *LevelPtr, unsigned int LogicalAddress, unsigned int Frame); // Helper method
MAP *PageLookup(PAGETABLE *PageTable, unsigned int LogicalAddress);
MAP *PageLookup(LEVEL *level, unsigned int LogicalAddress); // Helper method
int createPageTable(PAGETABLE *PageTable, char** num, int position);
LEVEL * createLevel(PAGETABLE *PageTable, LEVEL *level, int depth);