#include "pagetable.h"
using namespace std;

int createPageTable(PAGETABLE *PageTable, char** num, int position)
{
    PageTable->shifters = new unsigned int[PageTable -> numOfLevels];
    PageTable->bitMaskArr = new unsigned int[PageTable->numOfLevels];
    PageTable->entryCount = new unsigned int[PageTable->numOfLevels];

    int bitsUsed = 0;
    for (int i = 0; i < PageTable->numOfLevels; i++)
    {
        int levelBits = atoi(num[position]);
        PageTable->shifters[i] = 32 - bitsUsed - levelBits;
        int maskStart = 32 - bitsUsed; //calculate bitmask for current level
        PageTable->bitMaskArr[i] = calcBitmask(maskStart, levelBits);
        PageTable->entryCount[i] = (1 << levelBits); //2 ^ levelBits
        bitsUsed += levelBits;
        position++;
        if (bitsUsed >= 32)
        {
            fprintf(stderr, "Logical address length is too long. Max: 32 bits\n");
            exit(1);
        }
    }

    PageTable->hits = 0;
    PageTable->misses = 0;
    PageTable->rootPtr = initializeLevel(PageTable, PageTable->rootPtr, 0);
    return bitsUsed;
}

unsigned int LogicalToPage(unsigned int LogicalAddress, unsigned int Mask, unsigned int Shift)
{
    return (LogicalAddress & Mask) >> Shift; // Return the logical address ANDed with the bitmask and shifted correct amount of bits to the right.
}

unsigned int calcBitmask(int start, int length)
{
    unsigned int mask = (1 << length) - 1; // (2^length) - 1
    mask <<= (start - length);             //shifts the 1's to the correct starting position
    return mask;
}

void PageInsertHELPER(LEVEL *LevelPtr, unsigned int LogicalAddress, unsigned int Frame)
{
    PAGETABLE *PageTable = (PAGETABLE *)LevelPtr->pageTablePtr;
    unsigned int pageNumber = LogicalToPage(LogicalAddress, PageTable->bitMaskArr[LevelPtr -> depth], PageTable->shifters[LevelPtr -> depth]);
    unsigned int leafNode = (PageTable->numOfLevels) - 1;
    
    if (LevelPtr -> isLeafNode)
    {

        LevelPtr -> map[pageNumber].flagIndex = true;
        LevelPtr -> map[pageNumber].frameIndex = Frame;
        LevelPtr -> pageTablePtr -> frameCount++;
    }
    else
    {
        // Create an array of Level * entries based upon the number of entries in the new level and initialize to null/invalid as appropriate
        if (LevelPtr -> nextLevelPtr[pageNumber] == NULL){
            LevelPtr->nextLevelPtr[pageNumber] = initializeLevel(LevelPtr->pageTablePtr, LevelPtr, LevelPtr->depth+1);
        }
        // PageInsert(pointer to new Level, Address, Frame)
        PageInsertHELPER(LevelPtr->nextLevelPtr[pageNumber], LogicalAddress, Frame);
    }
}

void PageInsert(PAGETABLE *PageTable, unsigned int LogicalAddress, unsigned int Frame)
{
    PageInsertHELPER((LEVEL *)(PageTable->rootPtr), LogicalAddress, Frame);
}

MAP *PageLookup(PAGETABLE *PageTable, unsigned int LogicalAddress) {
    return PageLookupHELPER((LEVEL *)PageTable->rootPtr, LogicalAddress);
}

/* searches for a given logical address and returns a pointer to the map struct associated with the address, or NULL if address not found */
MAP * PageLookupHELPER(LEVEL *level, unsigned int LogicalAddress) {
    unsigned int index = LogicalToPage(LogicalAddress, level->pageTablePtr->bitMaskArr[level->depth], level->pageTablePtr->shifters[level->depth]);
    // cout << index << endl;
    // cout << level -> isLeafNode << endl;
    if (level->isLeafNode) {        //test if current level is a leaf node
        if (level->map[index].flagIndex)        //test if map[index] is valid
            return &level->map[index];
        else                        //page has been seen for the first time
            return NULL;
    }
    else {
        if (level->nextLevelPtr[index] == NULL)      //interior level at [index] not found, return NULL
            return NULL;
        return PageLookupHELPER((LEVEL*) level->nextLevelPtr[index], LogicalAddress);   //traverse to next level
    }
}



LEVEL *initializeLevel(PAGETABLE *PageTable, LEVEL *level, int depth)
{
    level = (LEVEL*)calloc(1, sizeof(LEVEL));
    level->depth = depth;
    level -> pageTablePtr = PageTable;
    level->isLeafNode = (depth + 1 >= PageTable->numOfLevels);
    if (level->isLeafNode)
    { //allocate maps for leaf nodes
        level->map = (MAP *)calloc(PageTable->entryCount[depth], sizeof(MAP));
        for (int i = 0; i < PageTable->entryCount[depth]; i++)
        {
            level->map[i].flagIndex = false;
        }
    }
    else
    { //allocate next level pointers
        level->nextLevelPtr = (LEVEL **)calloc(PageTable->entryCount[depth], sizeof(LEVEL *));
    }
    return level;
}


