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