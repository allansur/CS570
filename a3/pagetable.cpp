
#include "pagetable.h"
using namespace std;



void PageInsert(PAGETABLE *PageTable, unsigned int LogicalAddress, unsigned int Frame){

}

unsigned int LogicalToPage(unsigned int LogicalAddress, unsigned int Mask, unsigned int Shift) {
    return (LogicalAddress & Mask) >> Shift; // We got 1 down!
}

int PageLookUp(unsigned int address) {

}

unsigned int calcBitmask(int start, int length){
    unsigned int mask = (1 << length) - 1;
    mask <<= (start-length);
    return mask;
}

