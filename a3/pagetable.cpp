
#include "pagetable.h"
#include "map.h"
#include "level.h"
using namespace std;

unsigned int calcBitmask(int start, int length){
    unsigned int mask = (1 << length) - 1;
    mask <<= (start-length);
    return mask;
}

unsigned int LogicalToPage(unsigned int LogicalAddress, unsigned int Mask, unsigned int Shift) {
    return (LogicalAddress & Mask) >> Shift; // We got 1 down!
}

PAGETABLE::PAGETABLE(unsigned int numOfLevels, int *numOfBits) {
    PAGETABLE::numOfLevels = numOfLevels;
    bitmaskArr = new unsigned int[PAGETABLE::numOfLevels + 1];
    shifters = new unsigned int[PAGETABLE::numOfLevels + 1];
    entryCount = new unsigned int[PAGETABLE::numOfLevels + 1];
    rootPtr = nullptr;

    unsigned int offset = 32;
    for (int i = 0; i < PAGETABLE::numOfLevels; i++) {
        offset -= numOfBits[i];
    }
    int bitsForLevel;
    unsigned int cumulativeBitCount = offset;
    unsigned int bitMask;
    //[Level Count] matches with the offset bits
    bitmaskArr[numOfLevels] = (unsigned int) ((1 << offset) - 1);
    shifters[numOfLevels] = 0;
    //Page Size
    entryCount[numOfLevels] = (unsigned int) (1 << offset);
    for (int i = PAGETABLE::numOfLevels - 1; i >= 0; i--) {
        bitsForLevel = numOfBits[i];
        // Equivalent to 2 to the power of bitsForLevel
        bitMask = (unsigned int) (1 << bitsForLevel) - 1;
        bitmaskArr[i] = bitMask << cumulativeBitCount;
        shifters[i] = cumulativeBitCount;
        entryCount[i] = (unsigned int) 1 << bitsForLevel;
        cumulativeBitCount += bitsForLevel;
    }
};


bool PAGETABLE::PageInsert(unsigned int LogicalAddress, unsigned int Frame) {
    if (rootPtr == nullptr) {
        rootPtr = new LEVEL(0, 1 == numOfLevels, this);
    }
    return rootPtr->PageInsert(LogicalAddress, Frame);
}

int PAGETABLE::getFrame(unsigned int LogicalAddress) {
    if (rootPtr == nullptr) {
        return NULL;
    }
    return rootPtr->getFrame(LogicalAddress);
}

int PAGETABLE::sizeTotal() {
    int pageSize = sizeof(bitmaskArr) + sizeof(shifters);
    pageSize += sizeof(entryCount);
    pageSize *= numOfLevels;
    pageSize += sizeof(numOfLevels) + sizeof(rootPtr);
    if (rootPtr == nullptr) {
        return pageSize;
    }
    return pageSize + rootPtr->sizeTotal();
}
