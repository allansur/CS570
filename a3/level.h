
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

class PAGETABLE;

class LEVEL {
private:
    int depth;
    bool isLeafLevel;
    PAGETABLE *PageTablePtr;
    LEVEL **NextLevelPtr;
    MAP *mapPtr;
public:
    LEVEL(PAGETABLE *, int, bool);

    LEVEL *getSubLevel(int);

    MAP *PageLookup(int);

    bool PageInsert(unsigned int, unsigned int);

    int getFrame(unsigned int);

    int sizeTotal();

};