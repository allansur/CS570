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

//Inserts into Page Table, returns Hit/Miss
int PageInsert(PAGETABLE *PageTable, unsigned int logicalAddr, unsigned int frame);

//Helper for output statistics printing
void printHelper(int size, int hits, int missess, unsigned int pageSize);

//Returns frame number for the specified logical address
int getFrame(PAGETABLE *PageTable, unsigned int logicalAddr);

//Returns physical address for specified logical address
int getPhysicalAddr(PAGETABLE *PageTable, unsigned int logicalAddr);

//Helps handle tFlag case, prints Logical -> Physical
void tFlagHelper(PAGETABLE *PageTable, unsigned int logicalAddress, bool tFlag);

//Helps handle pFlag case, outputs all Page Number -> Frame Number
void pFlagHelper(PAGETABLE *PageTable, string file, int addressSizeUsed, bool pFlag);

int main(int argc, char *argv[]);