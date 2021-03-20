
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <map>
using namespace std;

class MAP {
private:
    int size;
    int *frameMapping;
public:
    MAP(int);

    int getFrame(int pageNumber);

    bool insertPageNumber(int pageNumber, int Frame);

    int invalidatePageNumber(int pageNumber);

    bool invalidateFrameNumber(int Frame);

    int sizeTotal();
};