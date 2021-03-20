
#include "pagetable.h"
using namespace std;

//Create a new instance of a level for the page table
LEVEL::Level(int d, PAGETABLE *pgTblPtr)
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
        int tableSize = 0;
        tableSize += sizeof(Level) + sizeof(Level *) * entryCount;

        //We set an unsigned int to the next level size to be able to initialize the next level to the correct size of entries from the original page table this level is from
    }
    else
    {
        isLeaf = true;
        MAP *map;
        tableSize += sizeof(Level) + sizeof(map);
    }
}
