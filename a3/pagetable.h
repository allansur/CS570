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
    void PageInsert(PAGETABLE *PageTable, unsigned int LogicalAddress, unsigned int Frame);
    MAP *PageLookup(PAGETABLE *PageTable, unsigned int LogicalAddress);
};

class Level
{
private:
    int depth;
    PAGETABLE *pageTablePtr;
    Level **nextLevelPtr;
    bool isLeaf;

    typedef struct
    {
        bool flagIndex;
        int frameIndex;
    } MAP;

    typedef struct
    {
        // unsigned int numBitsAddy;
        unsigned int numOfLevels;
        unsigned int numberOfBits; //size = numOfLevels
        unsigned int *bitMaskArr;  //size = numOfLevels
        unsigned int *shifters;
        unsigned int *entryCount; // size = level
        void *rootPtr;
    } PAGETABLE;
