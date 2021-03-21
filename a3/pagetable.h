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

class LEVEL;

class PAGETABLE {
public:
    unsigned int numOfLevels;
    unsigned int *bitmaskArr;
    unsigned int *shifters;
    unsigned int *entryCount;

    PAGETABLE(unsigned int, int *);

    bool PageInsert(unsigned int, unsigned int);

    int getFrame(unsigned int);

    int sizeTotal();

private:
    LEVEL *rootPtr;
};