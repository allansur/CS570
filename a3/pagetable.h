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
#include <vector>
using namespace std;

typedef struct LEVEL 
{
    int depthOfLevel;
    PAGETABLE *pageTable;
    LEVEL **NextLevelPtr;
    
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
    vector<int> numberOfBits; //size = numOfLevels
    vector<int> bitMask; //size = numOfLevels
    vector<int> shifters();
    vector<int> entryCount(); // size = level
    int *rootPtr;
};