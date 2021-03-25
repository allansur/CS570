/* 
Names: Allan Sur, Jason Songvilay
RedIDs: 821444631, 821071661
Edoras IDs: cssc3455, cssc3454
Course: CS530-03-Spring2021
Assignment 3: Part II
*/
#include "pagetable.h"
using namespace std;

//Logical to page just ANDs our bitmask at the respective level and the logical address to get our page # and then we shift it the correct amount of bits for that level
unsigned int LogicalToPage(unsigned int LogicalAddress, unsigned int Mask, unsigned int Shift)
{
    return (LogicalAddress & Mask) >> Shift;
}

//Function to create our bitmask for the given level which takes in our offset + that level index (1-n)
unsigned int createBitMask(int pos, int length)
{
    //Basically calculating 2^(length) - 1
    unsigned int mask = (1 << length) - 1;
    //Shift mask left and set equal to the position - length
    mask <<= (pos - length);
    //return mask for that level index
    return mask;
}

int createPageTable(PAGETABLE *PageTable, char **num, int index)
{
    //Initialize all of our struct PAGETABEL's arrays of # of shifted bits, the array of bitmasks per lvl and the amount of entires per lvl
    PageTable->shifters = new unsigned int[PageTable->numOfLevels];
    PageTable->bitMaskArr = new unsigned int[PageTable->numOfLevels];
    PageTable->entryCount = new unsigned int[PageTable->numOfLevels];

    int numOfBits = 0;
    //Iterate through the amount of levels and add bit masks, shifted bits aand entry counts to respective arrays
    for (int i = 0; i < PageTable->numOfLevels; i++)
    {
        int levelBits = atoi(num[index]);
        PageTable->shifters[i] = 32 - numOfBits - levelBits;
        int mask = 32 - numOfBits;
        PageTable->bitMaskArr[i] = createBitMask(mask, levelBits);
        PageTable->entryCount[i] = 1 << levelBits;
        numOfBits += levelBits;
        index++;
        if (numOfBits >= 32)
        {
            //If your number of bits exceeds 32, we have to give an error and exit the program with error code 1
            cout << "This address is over 32 bits" << endl;
            exit(1);
        }
    }

    //Initialize our hits and misses for the page table to be allowed to calculate them for our summary
    PageTable->hits = 0;
    PageTable->misses = 0;
    PageTable->rootPtr = createLevel(PageTable, PageTable->rootPtr, 0);
    //We also initialize our root pointer here to the first level of our page table
    //Return the amount of bits that we used
    return numOfBits;
}

//Instantiation of our level struct for our pagetable
LEVEL *createLevel(PAGETABLE *PageTable, LEVEL *level, int levelDepth)
{
    //Allocate memory and fill with 0's for the given size of that level
    level = (LEVEL *)calloc(1, sizeof(LEVEL));
    //Set out depth and pagetableptr attributes for the struct to given variables
    level->depth = levelDepth;
    level->pageTablePtr = PageTable;
    //check that if we are on the last level
    if (PageTable->numOfLevels <= levelDepth + 1)
    {
        //if we are, we can set this level to be true that it is a leaf node
        level->isLeafNode = true;
    }
    //If this level is a leafNode enter
    if (level->isLeafNode)
    {
        //Set our map pointer = a newly created map pointer allocated of size MAP with the correct entry count at this level using calloc to fill with 0s
        level->map = (MAP *)calloc(PageTable->entryCount[levelDepth], sizeof(MAP));
        //For the amount fo entries in this level at this depth, we wanat to go ahead and insert all empty bits into the map to show that it's empty right now
        for (int i = 0; i < PageTable->entryCount[levelDepth]; i++)
        {
            level->map[i].flagIndex = false;
        }
    }
    //If this is not a leaf node enter
    else
    {
        //We set our next level ptr for this level to be a newly instantiaated double pointer with allocated size of the level pointer and the correct amount of entries for this level at thsi depth from our page table.
        level->nextLevelPtr = (LEVEL **)calloc(PageTable->entryCount[levelDepth], sizeof(LEVEL *));
    }
    //return this level
    return level;
}

//Page insertion function for the PAGETABLE struct
//Accepts level pointer, logical address, and the frame index
void PageInsert(LEVEL *LevelPtr, unsigned int LogicalAddress, unsigned int Frame)
{
    //Basically assigning a pagetable pointer to a caste PAGETABLE pointer of a level pointer that points back to our pagetable pointer
    //We're basically connecting our page table pointer to the level pointer that points to the pagetable again in order to allow for access from either end
    PAGETABLE *PageTable = (PAGETABLE *)LevelPtr->pageTablePtr;
    //Generate page # based on calling the logical to page function with the logical address, bitmask for that specific level index, and the shift # for that specific level index
    unsigned int pageNumber = LogicalToPage(LogicalAddress, PageTable->bitMaskArr[LevelPtr->depth], PageTable->shifters[LevelPtr->depth]);
    //Create a leaf node for our tree-structure PT that is our number of levels input - 1 to allow for enumeration
    unsigned int leafNode = (PageTable->numOfLevels) - 1;
    //We are checking if this level is a leaf node
    if (LevelPtr->isLeafNode)
    {
        //If it is, we go ahead and set its bit on the map as valid to show that there is an address here
        //Also set the framae index = to whatever was passed through to page insert
        //Lastly increment frameCount as to keep track of how many page frames were created
        LevelPtr->map[pageNumber].flagIndex = true;
        LevelPtr->map[pageNumber].frameIndex = Frame;
        LevelPtr->pageTablePtr->frameCount++;
    }
    else
    { //If the level is not a leaf node, we enter this
        if (LevelPtr->nextLevelPtr[pageNumber] == NULL)
        {
            //Check fi our nextLevelPtr at this page # is NULL and if it is we create another level
            LevelPtr->nextLevelPtr[pageNumber] = createLevel(LevelPtr->pageTablePtr, LevelPtr, LevelPtr->depth + 1);
        }
        //Insert the page no matter what
        PageInsert(LevelPtr->nextLevelPtr[pageNumber], LogicalAddress, Frame);
    }
}

//This is the function that takes in our page table pointer and we basically just use it to cast the same PT pointer to a level pointer and call our helper method along with pointing our casted level pointer to the rootPtr of the PT struct
void PageInsert(PAGETABLE *PageTable, unsigned int LogicalAddress, unsigned int Frame)
{
    PageInsert((LEVEL *)(PageTable->rootPtr), LogicalAddress, Frame);
}

//Page Lookup will cast the given PT pointer to a level pointer and pass it the rootptr alongside the logical address to the helper function below
MAP *PageLookup(PAGETABLE *PageTable, unsigned int LogicalAddress)
{
    return PageLookup((LEVEL *)PageTable->rootPtr, LogicalAddress);
}
//Looking four our page in the pagetable
MAP *PageLookup(LEVEL *level, unsigned int LogicalAddress)
{
    unsigned int index = LogicalToPage(LogicalAddress, level->pageTablePtr->bitMaskArr[level->depth], level->pageTablePtr->shifters[level->depth]);
    //We got our index or page # by calling logical to page
    //Conditional check if it is a leaf node or no
    if (level->isLeafNode)
    {
        //We can just use the index to see if it's set and if it is we can just return that page at that index
        if (level->map[index].flagIndex)
            return &level->map[index];
        else
        {
            return NULL;
        }
        //if the map doesn't have a valid bit set for that page # it means that it's not inserted and we cannot return anything besides null
    }
    else
    {
        //if it's not a leaf node we can check to see if it's in the next level and if there's no next level we will just return the page lookup of that page
        if (level->nextLevelPtr[index] == NULL)
            return NULL;
        return PageLookup((LEVEL *)level->nextLevelPtr[index], LogicalAddress);
    }
}

