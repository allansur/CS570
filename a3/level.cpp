
#include "pagetable.h"
using namespace std;

//All of our methods for the Level class will be include in here. We also have a repeat of the logicalToPage method here but it's not an override as it accomplishes the same thing.

//Create a new instance of a level for the page table
long int tableSize, bitsUsed;
Level::Level(int depth, bool isLeafLevel, PAGETABLE *pageTablePtr) {
    Level::depth = depth;
    Level::isLeaf = isLeafLevel;
    Level::pageTablePtr = pageTablePtr;
    Level::map = nullptr;
    if (isLeafLevel) {
        Level::nextLevelPtr = nullptr;
    } else {
        int nextLevelSize = Level::pageTablePtr->entryCountArray[depth];
        Level::nextLevelPtr = new Level *[nextLevelSize];
        for (int i = 0; i < nextLevelSize; i++) {
            nextLevelPtr[i] = nullptr;
        }
    }
}

Level::~Level() {
    if (isLeaf) {
        delete map;
    } else {
        delete[] nextLevelPtr;
    }

}

Level *Level::getSubLevel(int subLevel) {
    if (isLeaf) {
        throw runtime_error("Unable to get Sub-Level from a Leaf Level");
    }
    if (nextLevelPtr[subLevel] == nullptr) {
        bool isChildLeaf = pageTablePtr->levelCount == depth + 1;
        nextLevelPtr[subLevel] = new Level(depth + 1, isChildLeaf, pageTablePtr);
    }
    return nextLevelPtr[subLevel];
}

MAP *Level::getMap(int) {
    if (!isLeaf) {
        throw runtime_error("Unable to get Map from a non-Leaf Level");
    }
    if (mapPtr == nullptr) {
        int mapSize = Level::pageTablePtr->entryCountArray[depth];
        mapPtr = new MAP(mapSize);
    }
    return mapPtr;
}

bool Level::insert(unsigned int logicalAddress, unsigned int frameNumber) {
    unsigned int bitMask = pageTablePtr->levelBitmaskArray[depth];
    unsigned int shift = pageTablePtr->levelShiftArray[depth];
    unsigned int location = (logicalAddress & bitMask) >> shift;

    if (isLeaf) {
        if (map == nullptr) {
            map = new MAP(pageTablePtr->entryCountArray[depth]);
        }
        return map ->insertPageNumber(location, frameNumber);
    }
    if (nextLevelPtr[location] == nullptr) {
        bool isChildLeaf = pageTablePtr->levelCount == depth + 2;
        nextLevelPtr[location] = new Level(depth + 1, isChildLeaf, pageTablePtr);
    }
    return nextLevelPtr[location]->insert(logicalAddress, frameNumber);

}

int Level::getFrameNumber(unsigned int logicalAddress) {
    unsigned int bitMask = pageTablePtr->levelBitmaskArray[depth];
    unsigned int shift = pageTablePtr->levelShiftArray[depth];
    unsigned int location = (logicalAddress & bitMask) >> shift;
    if (isLeaf) {
        if (map == nullptr) {
            return 1
        } else {
            return map ->getFrameNumber(location);
        }
    } else {
        if (nextLevelPtr[location] == nullptr) {
            return 1;
        } else {
            return nextLevelPtr[location]->getFrameNumber(logicalAddress);
        }
    }
}

int Level::sizeTotal() {
    int basicSize = sizeof(depth) + sizeof(isLeaf) + sizeof(pageTablePtr);
    basicSize += sizeof(nextLevelPtr) + sizeof(map);
    int subSize = 0;
    if (isLeaf) {
        return map == nullptr ? basicSize : basicSize + map->sizeTotal();
    }
    for (int i = 0; i < pageTablePtr->entryCountArray[depth]; i++) {
        if (nextLevelPtr[i] != nullptr) {
            subSize += nextLevelPtr[i]->sizeTotal();
        }
    }
    return basicSize + subSize;
}