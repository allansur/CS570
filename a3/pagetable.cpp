
#include "pagetable.h"
using namespace std;

int createPageTable(PAGETABLE *pageTable, unsigned int numOfLevels, int *numOfBits)
{
    pageTable->numOfLevels = numOfLevels;
    pageTable->bitMaskArr = new unsigned int[numOfLevels + 1];
    pageTable->shifters = new unsigned int[numOfLevels + 1];
    pageTable->entryCount = new unsigned int[numOfLevels + 1];
    unsigned int offset = 32;
    for (int i = 0; i < pageTable->numOfLevels; i++)
    {
        offset -= numOfBits[i];
    }
    int bitsNeeded;
    unsigned int totalBits = offset;
    unsigned int bitMask;
    //[Level Count] matches with the offset bits
    pageTable->bitMaskArr[numOfLevels] = (unsigned int)((1 << offset) - 1);
    pageTable->shifters[numOfLevels] = 0;
    //Page Size
    pageTable->entryCount[numOfLevels] = (unsigned int)(1 << offset);
    for (int i = pageTable->numOfLevels - 1; i >= 0; i--)
    {
        bitsNeeded = numOfBits[i];
        // Equivalent to 2 to the power of bitsForLevel
        bitMask = (unsigned int)(1 << bitsNeeded) - 1;
        pageTable->bitMaskArr[i] = bitMask << totalBits;
        pageTable->shifters[i] = totalBits;
        pageTable->entryCount[i] = (unsigned int)1 << bitsNeeded;
        totalBits += bitsNeeded;
    }
}

unsigned int LogicalToPage(unsigned int LogicalAddress, unsigned int Mask, unsigned int Shift)
{
    return (LogicalAddress & Mask) >> Shift; // We got 1 down!
}

int PageLookUp(unsigned int address)
{
}

unsigned int calcBitmask(int start, int length)
{
    unsigned int mask = (1 << length) - 1;
    mask <<= (start - length);
    return mask;
}

void PageInsert(PAGETABLE *PageTable, unsigned int LogicalAddress, unsigned int Frame)
{
    PageInsert((LEVEL *)PageTable->rootPtr, LogicalAddress, Frame);
}

void PageInsert(LEVEL *LevelPtr, unsigned int LogicalAddress, unsigned int Frame)
{
    PAGETABLE *PageTable = (PAGETABLE *)LevelPtr->pageTablePtr;
    unsigned int index = LevelPtr->depth;
    unsigned int pageNumber = LogicalToPage(LogicalAddress, PageTable->bitMaskArr[index], PageTable->shifters[index]);

    unsigned int leafNode = (PageTable->numOfLevels) - 1;
    if (index == leafNode)
    {
        MAP *map = (MAP *)LevelPtr;
        map->flagIndex = true;
        map->frameIndex = index;
    }
    else
    {
        LEVEL *newLevel;
        newLevel->depth = LevelPtr->depth + 1;
        // LevelPtr->nextLevelPtr[index] = initializeLevelArr(LevelPtr->pageTablePtr, LevelPtr, LevelPtr->depth+1);
        PageInsert((PAGETABLE *)newLevel->pageTablePtr, LogicalAddress, Frame);
    }
}

MAP *PageLookup(PAGETABLE *PageTable, unsigned int LogicalAddress)
{
    unsigned int index = (PageTable->numOfLevels) - 1;
    unsigned int pageNum;

    LEVEL *getLevel = (LEVEL *)PageTable->rootPtr;
    for (int i = 0; i < index; i++)
    {
        pageNum = LogicalToPage(LogicalAddress, PageTable->bitMaskArr[i], PageTable->shifters[i]);
        if (getLevel->nextLevelPtr[index] == NULL)
        {
            return NULL;
        }
        getLevel = (LEVEL *)getLevel->nextLevelPtr[pageNum];
    }

    pageNum = LogicalToPage(LogicalAddress, PageTable->bitMaskArr[index], PageTable->shifters[index]);
    MAP *map = (MAP *)getLevel->nextLevelPtr[pageNum];

    if (map->flagIndex)
    {
        return map;
    }
    else
    {
        return NULL;
    }
}
