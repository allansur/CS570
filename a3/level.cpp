
#include "pagetable.h"
#include "map.h"
#include "level.h"
using namespace std;

LEVEL::LEVEL(PAGETABLE *PageTablePtr, int depth, bool isLeafLevel) {
    LEVEL::depth = depth;
    LEVEL::isLeafLevel = isLeafLevel;
    LEVEL::PageTablePtr = PageTablePtr;
    LEVEL::mapPtr = nullptr;
    if (isLeafLevel) {
        LEVEL::NextLevelPtr = nullptr;
    } else {
        int nextLevelSize = LEVEL::PageTablePtr->entryCount[depth];
        LEVEL::NextLevelPtr = new LEVEL *[nextLevelSize];
        for (int i = 0; i < nextLevelSize; i++) {
            NextLevelPtr[i] = nullptr;
        }
    }
}

LEVEL *LEVEL::getSubLevel(int subLevel) {
    if (isLeafLevel) {
        cout << ("Unable to get Sub-LEVEL from a Leaf LEVEL");
    }
    if (NextLevelPtr[subLevel] == nullptr) {
        bool isChildLeaf = PageTablePtr->numOfLevels == depth + 1;
        NextLevelPtr[subLevel] = new LEVEL(PageTablePtr, depth + 1, isChildLeaf);
    }
    return NextLevelPtr[subLevel];
}

MAP *LEVEL::PageLookup(int) {
    if (!isLeafLevel) {
        cout << ("Unable to get Map from a non-Leaf LEVEL");
    }
    if (mapPtr == nullptr) {
        int mapSize = LEVEL::PageTablePtr->entryCount[depth];
        mapPtr = new MAP(mapSize);
    }
    return mapPtr;
}

bool LEVEL::PageInsert(unsigned int LogicalAddress, unsigned int Frame) {
    unsigned int bitMask = PageTablePtr->bitmaskArr[depth];
    unsigned int shift = PageTablePtr->shifters[depth];
    unsigned int location = (LogicalAddress & bitMask) >> shift;

    if (isLeafLevel) {
        if (mapPtr == nullptr) {
            mapPtr = new MAP(PageTablePtr->entryCount[depth]);
        }
        return mapPtr->insertPageNumber(location, Frame);
    }
    if (NextLevelPtr[location] == nullptr) {
        bool isChildLeaf = PageTablePtr->numOfLevels == depth + 2;
        NextLevelPtr[location] = new LEVEL(PageTablePtr, depth + 1, isChildLeaf);
    }
    return NextLevelPtr[location]->PageInsert(LogicalAddress, Frame);

}

int LEVEL::getFrame(unsigned int LogicalAddress) {
    unsigned int bitMask = PageTablePtr->bitmaskArr[depth];
    unsigned int shift = PageTablePtr->shifters[depth];
    unsigned int location = (LogicalAddress & bitMask) >> shift;
    if (isLeafLevel) {
        if (mapPtr == nullptr) {
            return NULL;
        } else {
            return mapPtr->getFrame(location);
        }
    } else {
        if (NextLevelPtr[location] == nullptr) {
            return NULL;
        } else {
            return NextLevelPtr[location]->getFrame(LogicalAddress);
        }
    }
}

int LEVEL::sizeTotal() {
    int basicSize = sizeof(depth) + sizeof(isLeafLevel) + sizeof(PageTablePtr);
    basicSize += sizeof(NextLevelPtr) + sizeof(mapPtr);
    int subSize = 0;
    if (isLeafLevel) {
        return mapPtr == nullptr ? basicSize : basicSize + mapPtr->sizeTotal();
    }
    for (int i = 0; i < PageTablePtr->entryCount[depth]; i++) {
        if (NextLevelPtr[i] != nullptr) {
            subSize += NextLevelPtr[i]->sizeTotal();
        }
    }
    return basicSize + subSize;
}