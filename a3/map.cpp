
#include "pagetable.h"
#include "map.h"
#include "level.h"
using namespace std;

MAP::MAP(int size) {
    MAP::size = size;
    MAP::frameMapping = new int[size];
    for (int i = 0; i < size; i++) {
        frameMapping[i] = NULL;
    }
}

int MAP::getFrame(int pageNumber) {
    return frameMapping[pageNumber];
}

bool MAP::insertPageNumber(int pageNumber, int Frame) {
    if (frameMapping[pageNumber] != NULL) {
        return false;
    }
    frameMapping[pageNumber] = Frame;
    return true;
}

int MAP::invalidatePageNumber(int pageNumber) {
    int currentFrameNumber = frameMapping[pageNumber];
    frameMapping[pageNumber] = NULL;
    return currentFrameNumber;
}

bool MAP::invalidateFrameNumber(int Frame) {
    for (int i = 0; i < size; i++) {
        if (frameMapping[i] == Frame) {
            frameMapping[i] = NULL;
            return true;
        }
    }
    return false;
}

int MAP::sizeTotal() {
    return sizeof(size) + sizeof(frameMapping) + sizeof(int) * size;
}