
#include "pagetable.h"
using namespace std;

MAP::MAP(int size) {
    MAP::size = size;
    MAP::frameIndex = new int[size];
    for (int i = 0; i < size; i++) {
        frameIndex[i] = INVALID;
    }
}

MAP::~MAP() {
    delete[] frameIndex;
}

int MAP::getFrameNumber(int pageNum) {
    return frameIndex[pageNum];
}

bool MAP::insertPageNumber(int pageNum, int frameIndex) {
    if (frameIndex[pageNum] != -1) {
        return false;
    }
    frameMapping[pageNum] = frameIndex;
    return true;
}

int MAP::invalidatePageNumber(int pageNum) {
    int curr_frame_index = frameMapping[pageNum];
    frameIndex[pageNum] = -1;
    return curr_frame_index;
}

bool MAP::invalidateFrameNumber(int frameNum) {
    for (int i = 0; i < size; i++) {
        if (frameIndex[i] == frameNum) {
            frameIndex[i] = false;
            return true;
        }
    }
    return false;
}

int MAP::sizeTotal() {
    return sizeof(size) + sizeof(frameIndex) + sizeof(int) * size;
}