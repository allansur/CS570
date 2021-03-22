#include "pagetable.h"
using namespace std;

int createPageTable(PAGETABLE *PageTable, unsigned int numOfLevels, int *numOfBits)
{
    PageTable->numOfLevels = numOfLevels;
    PageTable->bitMaskArr = new unsigned int[numOfLevels + 1];
    PageTable->shifters = new unsigned int[numOfLevels + 1];
    PageTable->entryCount = new unsigned int[numOfLevels + 1];
    unsigned int offset = 32;
    for (int i = 0; i < PageTable->numOfLevels; i++)
    {
        offset -= numOfBits[i];
    }
    int bitsNeeded;
    unsigned int totalBits = offset;
    unsigned int bitMask;
    //[Level Count] matches with the offset bits
    PageTable->bitMaskArr[numOfLevels] = (unsigned int)((1 << offset) - 1);
    PageTable->shifters[numOfLevels] = 0;
    //Page Size
    PageTable->entryCount[numOfLevels] = (unsigned int)(1 << offset);
    for (int i = PageTable->numOfLevels - 1; i >= 0; i--)
    {
        bitsNeeded = numOfBits[i];
        // Equivalent to 2 to the power of bitsForLevel
        bitMask = (unsigned int)(1 << bitsNeeded) - 1;
        PageTable->bitMaskArr[i] = bitMask << totalBits;
        PageTable->shifters[i] = totalBits;
        PageTable->entryCount[i] = (unsigned int)1 << bitsNeeded;
        totalBits += bitsNeeded;
    }
}

unsigned int LogicalToPage(unsigned int LogicalAddress, unsigned int Mask, unsigned int Shift)
{
    return (LogicalAddress & Mask) >> Shift; // We got 1 down!
}

unsigned int calcBitmask(int start, int length) {
    unsigned int mask = (1 << length) - 1; // (2^length) - 1
    mask <<= (start - length); //shifts the 1's to the correct starting position
    return mask;
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

void PageInsert(PAGETABLE *PageTable, unsigned int LogicalAddress, unsigned int Frame)
{
    PageInsert((LEVEL *)(PageTable->rootPtr), LogicalAddress, Frame);
}

// MAP *PageLookup(PAGETABLE *PageTable, unsigned int LogicalAddress) {
//     return PageLookup((LEVEL *)PageTable->rootNode, LogicalAddress);
// }

// /* searches for a given logical address and returns a pointer to the map struct associated with the address, or NULL if address not found */
// MAP * PageLookup(LEVEL *level, unsigned int LogicalAddress) {
//     unsigned int index = LogicalToPage(LogicalAddress, level->PageTable->bitMaskArr[level->depth], level->PageTable->shifters[level->depth]);
//     if (level->isLeafNode) {        //test if current level is a leaf node
//         if (level->map[index].isValid)        //test if map[index] is valid
//             return &level->map[index];
//         else                        //page has been seen for the first time
//             return NULL;
//     }
//     else {
//         if (level->nextLevel[index] == NULL)      //interior level at [index] not found, return NULL
//             return NULL;
//         return PageLookup((LEVEL*) level->nextLevel[index], LogicalAddress);   //traverse to next level
//     }
// }

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

// LEVEL * createLevelArr(PAGETABLE *PageTable, LEVEL *level, int depth) {
 
//     level->depth = depth;
//     level->isLeafNode = (depth+1 >= PageTable->numOfLevels);
//     if (level->isLeafNode) {        //allocate maps for leaf nodes
//         level->map = PageTable->entryCount[depth];
//         int i;
//         for (i = 0; i < PageTable->entryCount[depth]; i++) {
//             level->map[i].flagIndex = false;
//         }
//     }
//     else {          //allocate next level pointers
//         level->nextLevelPtr = calloc(PageTable->entryCount[depth], sizeof(LEVEL *));
//     }
//     return level;
// }


void printTableInfo(PAGETABLE *PageTable) {
    int i;
    for (i = 0; i < PageTable->numOfLevels; i++) {
        printf("LEVEL %i INFO: ", i);
        printf("Mask: %08X\tShift: %i\tEntry Count: %i\n", PageTable->bitMaskArr[i], PageTable->shifters[i], PageTable->entryCount[i]);
    }
}
