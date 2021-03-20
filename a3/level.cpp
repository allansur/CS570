
#include "pagetable.h"
using namespace std;

//Create a new instance of a level for the page table
long int tableSize, bitsUsed;
Level::Level(int d, PAGETABLE *pgTblPtr)
{
    Level::depth = d;
    Level::pageTablePtr = pgTblPtr;
    Level::nextLevelPtr = nullptr; //idk how to initialize a null pointer

    if (depth < pageTablePtr->numOfLevels)
    {
        Level::isLeaf = false;
        int nextLvlSize = Level::pageTablePtr->entryCount[depth];
        Level::nextLevelPtr = new Level *[nextLvlSize];
        for (int i = 0; i < nextLvlSize; i++)
        {
            nextLevelPtr[i] = nullptr;
        }
        tableSize += sizeof(Level) + sizeof(Level *) *Level::pageTablePtr -> entryCount[depth];

        //We set an unsigned int to the next level size to be able to initialize the next level to the correct size of entries from the original page table this level is from
    }
    else
    {
        isLeaf = true;
        MAP *map;
        tableSize += sizeof(Level) + sizeof(map);
    }
}
unsigned int LogicalToPage(unsigned int LogicalAddress, unsigned int Mask, unsigned int Shift)
{
    return (LogicalAddress & Mask) >> Shift; // We got 1 down!
}
//pageinseration method for a level in a page table (void cause not actually returning anything just inserting)
void Level::pageInsert(unsigned int logicalAddy, unsigned int frameIndex) {
    if (isLeaf){
        //store the frame and set the index to valid in the bit map (1) 
        map -> flagIndex = true;
        map -> frameIndex = frameIndex;
        bitsUsed += sizeof(map);
    }
    else {
        //create a new level in the pagetable and set it's depth = curr_depth + one
        //turn our logical address into a VPA through calling the LTP function.
        unsigned int pageNum = LogicalToPage(logicalAddy, pageTablePtr -> bitMaskArr[depth], pageTablePtr -> shifters[depth]);
        //Create a new level in our page table as the next level with the correct depth and pagetable reference to grab entries
        nextLevelPtr[pageNum] = new Level(depth, pageTablePtr);
        //save the size of the level created and the pointer
        bitsUsed += sizeof(Level) + sizeof(Level *);
    //Insert page into the newly created level.
        nextLevelPtr[pageNum] -> pageInsert(logicalAddy, frameIndex);

    }
}


};